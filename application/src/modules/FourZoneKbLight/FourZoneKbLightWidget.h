#ifndef OMENLINUX_FOURZONEKBLIGHTWIDGET_H
#define OMENLINUX_FOURZONEKBLIGHTWIDGET_H

#include <rapidjson/document.h>
#include <QWidget>
#include <QButtonGroup>
#include <QRadioButton>
#include <QLineEdit>

#include "FourZoneKbLightDriver.h"
#include "ColorLineEditControl.h"

class FourZoneKbLightWidget: public QWidget {
Q_OBJECT

public:
    explicit FourZoneKbLightWidget(rapidjson::Value &configuration);
    ~FourZoneKbLightWidget() override = default;
    rapidjson::Value SaveConfiguration(rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator> &allocator) const;

public slots:
    void onOnOffChanged(int id, bool checked);
    void onZone1ColorChanged(unsigned int color);
    void onZone2ColorChanged(unsigned int color);
    void onZone3ColorChanged(unsigned int color);
    void onZone4ColorChanged(unsigned int color);

signals:
    void ConfigurationChanged();

private:
    FourZoneKbLightDriver mDriver;

    QButtonGroup* mOnOffGroup;
    QRadioButton* mOnButton;
    QRadioButton* mOffButton;

    ColorLineEditControl* mZone1ColorEdit;
    ColorLineEditControl* mZone2ColorEdit;
    ColorLineEditControl* mZone3ColorEdit;
    ColorLineEditControl* mZone4ColorEdit;

    bool mLightOn;
    unsigned int mZone1Color;
    unsigned int mZone2Color;
    unsigned int mZone3Color;
    unsigned int mZone4Color;

    void initializeState();
    void updateOnOffControls();
    void updateColorControls();
    void applyState(bool publishEvent);
};


#endif //OMENLINUX_FOURZONEKBLIGHTWIDGET_H
