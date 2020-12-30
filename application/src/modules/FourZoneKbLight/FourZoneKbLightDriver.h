#ifndef OMENLINUX_FOURZONEKBLIGHTDRIVER_H
#define OMENLINUX_FOURZONEKBLIGHTDRIVER_H

enum FourZoneKbLightState {
    KB_LIGHT_OFF = 0,
    KB_LIGHT_ON
};

class FourZoneKbLightDriver {
public:
    static bool DriverDetect();

    static int DriverGetOnOff(FourZoneKbLightState *state);
    static int DriverSetOnOff(FourZoneKbLightState state);

    static int DriverGetColors(unsigned int *zone1, unsigned int *zone2, unsigned int *zone3, unsigned int *zone4);
    static int DriverSetColors(unsigned int zone1, unsigned int zone2, unsigned int zone3, unsigned int zone4);

private:
    FourZoneKbLightDriver() = default;
    ~FourZoneKbLightDriver() = default;
};

#endif //OMENLINUX_FOURZONEKBLIGHTDRIVER_H
