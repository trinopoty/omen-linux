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

    int DriverGetOnOff(FourZoneKbLightState *state);
    int DriverSetOnOff(FourZoneKbLightState state);

private:
    bool mDetected;
};

#endif //OMENLINUX_FOURZONEKBLIGHTDRIVER_H
