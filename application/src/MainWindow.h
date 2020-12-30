#ifndef OMENLINUX_MAINWINDOW_H
#define OMENLINUX_MAINWINDOW_H

#include <vector>
#include <QMainWindow>
#include <QBoxLayout>
#include <QTabWidget>

#include <OmenModule.h>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

private slots:
    void HandleConfigurationChanged();

private:
    std::vector<std::unique_ptr<OModuleInstance>> mEnabledModules;
    QString mConfigFileDir;
    QString mConfigFilePath;

    QTabWidget* mTabWidget;
};

#endif //OMENLINUX_MAINWINDOW_H
