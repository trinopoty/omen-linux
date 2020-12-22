#ifndef OMENLINUX_FOURZONEKBLIGHTWIDGET_H
#define OMENLINUX_FOURZONEKBLIGHTWIDGET_H

#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>

#include "FourZoneKbLightDriver.h"
#include "ColorLineEditControl.h"

class FourZoneKbLightWidget: public QWidget {
Q_OBJECT

public:
    FourZoneKbLightWidget();
    ~FourZoneKbLightWidget() override = default;

public slots:
    void onOnOffChanged(int id, bool checked);
    void onZone1ColorChanged(unsigned int color);
    void onZone2ColorChanged(unsigned int color);
    void onZone3ColorChanged(unsigned int color);
    void onZone4ColorChanged(unsigned int color);

private:
    FourZoneKbLightDriver mDriver;

    QButtonGroup* mOnOffGroup;
    QRadioButton* mOnButton;
    QRadioButton* mOffButton;

    ColorLineEditControl* mZone1ColorEdit;
    ColorLineEditControl* mZone2ColorEdit;
    ColorLineEditControl* mZone3ColorEdit;
    ColorLineEditControl* mZone4ColorEdit;

    unsigned int mZone1Color;
    unsigned int mZone2Color;
    unsigned int mZone3Color;
    unsigned int mZone4Color;

    void initializeState();
    void updateColorControls();
    void applyState(FourZoneKbLightState state);
};


#endif //OMENLINUX_FOURZONEKBLIGHTWIDGET_H
