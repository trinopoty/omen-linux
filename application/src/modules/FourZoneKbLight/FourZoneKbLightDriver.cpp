#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>

#include "FourZoneKbLightDriver.h"

FourZoneKbLightDriver::FourZoneKbLightDriver(): mDetected(false) {}

bool FourZoneKbLightDriver::DriverDetect() {
    this->mDetected = false;

    const bool driver_detected = !access("/sys/devices/platform/hp-wmi", F_OK) &&
            !access("/sys/devices/platform/hp-wmi/fourzone_detect", F_OK | R_OK);
    if (driver_detected) {
        const int fd = open("/sys/devices/platform/hp-wmi/fourzone_detect", O_RDONLY);
        if (fd > 0) {
            char buf[20] = {0};
            const int bytes_read = read(fd, buf, 20);
            if (bytes_read > 0) {
                if (strcmp("present\n", buf) == 0) {
                    this->mDetected = true;
                }
            }

            close(fd);
        }
    }

    return this->mDetected;
}

int FourZoneKbLightDriver::DriverGetOnOff(FourZoneKbLightState *state) {
    if (this->mDetected) {
        const int fd = open("/sys/devices/platform/hp-wmi/fourzone_onoff", O_RDONLY);
        if (fd > 0) {
            char buf[20] = {0};
            const int bytes_read = read(fd, buf, 20);
            if (bytes_read > 0) {
                if (strcmp("on\n", buf) == 0) {
                    *state = KB_LIGHT_ON;
                } else {
                    *state = KB_LIGHT_OFF;
                }

                close(fd);
                return 0;
            }

            close(fd);
        }
    }

    return -EINVAL;
}

int FourZoneKbLightDriver::DriverSetOnOff(FourZoneKbLightState state) {
    if (this->mDetected) {
        const int fd = open("/sys/devices/platform/hp-wmi/fourzone_onoff", O_WRONLY);
        if (fd > 0) {
            const char* value = (state == KB_LIGHT_ON)? "on" : "off";
            write(fd, value, strlen(value) + 1);
            close(fd);
            return 0;
        }
    }

    return -EINVAL;
}
