#ifndef OMENLINUX_FOURZONEKBLIGHT_H
#define OMENLINUX_FOURZONEKBLIGHT_H

#include <OmenModule.h>

bool DetectFourZoneKbLight();
QWidget* InitializeFourZoneKbLight();

static OmenModule FourZoneKbLightModule = {
        .name = "Four Zone Keyboard",
        .detector = DetectFourZoneKbLight,
        .initialize = InitializeFourZoneKbLight,
};

#endif //OMENLINUX_FOURZONEKBLIGHT_H
