#ifndef OMENLINUX_FOURZONEKBLIGHTDRIVER_H
#define OMENLINUX_FOURZONEKBLIGHTDRIVER_H

enum FourZoneKbLightState {
    KB_LIGHT_OFF = 0,
    KB_LIGHT_ON
};

class FourZoneKbLightDriver {
public:
    FourZoneKbLightDriver();
    ~FourZoneKbLightDriver() = default;

    bool DriverDetect();

    int DriverGetOnOff(FourZoneKbLightState *state) const;
    int DriverSetOnOff(FourZoneKbLightState state) const;

    int DriverGetColors(unsigned int *zone1, unsigned int *zone2, unsigned int *zone3, unsigned int *zone4) const;
    int DriverSetColors(unsigned int zone1, unsigned int zone2, unsigned int zone3, unsigned int zone4) const;

private:
    bool mDetected;
};

#endif //OMENLINUX_FOURZONEKBLIGHTDRIVER_H
