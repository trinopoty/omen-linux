#ifndef OMENLINUX_OMENMODULES_H
#define OMENLINUX_OMENMODULES_H

#include "../include/OmenModule.h"
#include "modules/FourZoneKbLight/FourZoneKbLight.h"

static OmenModule* ModuleDetectors[] = {
        &FourZoneKbLightModule,
        nullptr
};

#endif //OMENLINUX_OMENMODULES_H
