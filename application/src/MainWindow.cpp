#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

#include <QDir>
#include <QStandardPaths>

#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "MainWindow.h"
#include "OmenModules.h"

MainWindow::MainWindow(): mEnabledModules() {
    setWindowTitle(tr("Omen Linux"));
    showMaximized();

    // Determine config file path
    mConfigFileDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    if (mConfigFileDir.length() > 0) {
        // We have a config path
        mConfigFilePath = QString(mConfigFileDir);
        mConfigFilePath.append("/config.json");
    } else {
        mConfigFilePath = QString("");
    }

    // Load configuration

    auto configuration = rapidjson::Document();
    auto configFilePath = mConfigFilePath.toStdString();
    if (mConfigFilePath.length() > 0 && access(configFilePath.c_str(), R_OK) == 0) {
        struct stat st = {0};
        stat(configFilePath.c_str(), &st);
        auto buffer = std::make_unique<char[]>(st.st_size + 1);
        std::memset(buffer.get(), 0, st.st_size + 1);

        auto configStream = std::ifstream();
        configStream.open(configFilePath, std::ios::in | std::ios::binary);
        configStream.read(buffer.get(), st.st_size);

        configuration.Parse(buffer.get());
    }

    if (!configuration.IsObject()) {
        configuration = rapidjson::Document();
        configuration.SetObject();
    }

    // Initialize view

    mTabWidget = new QTabWidget(this);
    this->setCentralWidget(mTabWidget);

    for (int i = 0; Modules[i]; i++) {
        auto module = Modules[i]();
        if (module->ShouldEnable()) {
            auto moduleConfig = rapidjson::Value(rapidjson::kObjectType);
            if (configuration.HasMember(module->GetName().c_str())) {
                moduleConfig = configuration[module->GetName().c_str()].GetObject();
            }

            auto instance = module->MakeInstance(moduleConfig);
            auto tabLabel = QString(module->GetDisplayName().c_str());
            mTabWidget->addTab(instance->GetView().get(), tabLabel);
            connect(instance.get(), &OModuleInstance::ConfigurationChanged, this,
                    &MainWindow::HandleConfigurationChanged);
            mEnabledModules.push_back(std::move(instance));
        }
    }
}

MainWindow::~MainWindow() = default;

void MainWindow::HandleConfigurationChanged() {
    // Create JSON document
    auto document = rapidjson::Document();
    document.SetObject();

    for (auto &item : mEnabledModules) {
        document.AddMember(
                rapidjson::Value(item->GetModule()->GetName().c_str(), document.GetAllocator()),
                item->GetConfiguration(document.GetAllocator()),
                document.GetAllocator());
    }

    auto buffer = rapidjson::StringBuffer();
    buffer.Clear();
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    // Write out to file
    if (mConfigFilePath.length() > 0) {
        QDir dir(mConfigFileDir);
        if (dir.mkpath(mConfigFileDir)) {
            std::ofstream ofile(mConfigFilePath.toStdString());
            ofile.write(buffer.GetString(), buffer.GetSize());
            ofile.flush();
        }
    }
}
