#ifndef OMENLINUX_OMENMODULES_H
#define OMENLINUX_OMENMODULES_H

#include <OmenModule.h>
#include "modules/FourZoneKbLight/FourZoneKbLight.h"

static GetModule Modules[] = {
        &GetFourZoneModule,
        nullptr
};

#endif //OMENLINUX_OMENMODULES_H
