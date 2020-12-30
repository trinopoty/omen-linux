#ifndef OMENLINUX_OMENMODULES_H
#define OMENLINUX_OMENMODULES_H

#include <OmenModule.h>
#include "modules/FourZoneKbLight/FourZoneKbLightModule.h"
#include "modules/MacrosModule/MacrosModule.h"

static GetModule Modules[] = {
        &GetFourZoneModule,
        &GetMacrosModule,
        nullptr
};

#endif //OMENLINUX_OMENMODULES_H
