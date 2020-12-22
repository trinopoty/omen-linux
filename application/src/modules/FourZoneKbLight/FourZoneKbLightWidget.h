#ifndef OMENLINUX_FOURZONEKBLIGHTWIDGET_H
#define OMENLINUX_FOURZONEKBLIGHTWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>

#include "FourZoneKbLightDriver.h"

class FourZoneKbLightWidget: public QWidget {
Q_OBJECT

public:
    FourZoneKbLightWidget();
    ~FourZoneKbLightWidget();

public slots:
    void onOnOffChanged(int id, bool checked);

private:
    FourZoneKbLightDriver mDriver;

    QButtonGroup* mOnOffGroup;
    QRadioButton* mOnButton;
    QRadioButton* mOffButton;

    void initializeState();
};


#endif //OMENLINUX_FOURZONEKBLIGHTWIDGET_H
