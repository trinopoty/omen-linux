#ifndef OMENLINUX_MACROSWIDGET_H
#define OMENLINUX_MACROSWIDGET_H

#include <QWidget>

class MacrosWidget: public QWidget {
Q_OBJECT

public:
    MacrosWidget();
    ~MacrosWidget() = default;

public slots:
    void handleClick(bool checked);
};


#endif //OMENLINUX_MACROSWIDGET_H
