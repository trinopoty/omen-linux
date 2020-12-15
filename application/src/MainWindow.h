#ifndef OMENLINUX_MAINWINDOW_H
#define OMENLINUX_MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QTabWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow() override;

private:
    QTabWidget* mTabWidget;
};

#endif //OMENLINUX_MAINWINDOW_H
