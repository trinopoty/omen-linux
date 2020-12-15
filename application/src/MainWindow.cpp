#include <iostream>

#include <QWidget>

#include "MainWindow.h"
#include "OmenModules.h"

MainWindow::MainWindow() {
    setWindowTitle(tr("Omen Linux"));
    showMaximized();

    mTabWidget = new QTabWidget(this);
    this->setCentralWidget(mTabWidget);

    for (int i = 0; ModuleDetectors[i]; i++) {
        auto module = ModuleDetectors[i];
        if (module->detector()) {
            mTabWidget->addTab(module->initialize(), tr(module->name));
        }
    }
}

MainWindow::~MainWindow() {
}
