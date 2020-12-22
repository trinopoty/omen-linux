#include <QWidget>
#include "FourZoneKbLight.h"
#include "FourZoneKbLightDriver.h"
#include "FourZoneKbLightWidget.h"

bool DetectFourZoneKbLight() {
    FourZoneKbLightDriver driver;
    return driver.DriverDetect();
}

QWidget* InitializeFourZoneKbLight() {
    return new FourZoneKbLightWidget();
}
