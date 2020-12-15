#include <QApplication>

#include "MainWindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QCoreApplication::setOrganizationName("Trinopoty Biswas");
    QCoreApplication::setOrganizationDomain("trinopoty.me");
    QCoreApplication::setApplicationName("Omen Linux");

    MainWindow mw;
    mw.show();

    return QApplication::exec();
}
