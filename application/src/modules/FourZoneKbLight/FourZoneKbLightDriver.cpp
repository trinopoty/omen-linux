#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <unistd.h>

#include "FourZoneKbLightDriver.h"

bool FourZoneKbLightDriver::DriverDetect() {
    const bool driver_detected = !access("/sys/devices/platform/hp-wmi", F_OK) &&
            !access("/sys/devices/platform/hp-wmi/fourzone_detect", F_OK | R_OK);
    bool result = false;
    if (driver_detected) {
        const int fd = open("/sys/devices/platform/hp-wmi/fourzone_detect", O_RDONLY);
        if (fd > 0) {
            char buf[20] = {0};
            const int bytes_read = read(fd, buf, 20);
            if (bytes_read > 0) {
                if (strcmp("present\n", buf) == 0) {
                    result = true;
                }
            }

            close(fd);
        }
    }

    return result;
}

int FourZoneKbLightDriver::DriverGetOnOff(FourZoneKbLightState *state) {
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

    return -EINVAL;
}

int FourZoneKbLightDriver::DriverSetOnOff(FourZoneKbLightState state) {
    const int fd = open("/sys/devices/platform/hp-wmi/fourzone_onoff", O_WRONLY);
    if (fd > 0) {
        const char* value = (state == KB_LIGHT_ON)? "on" : "off";
        write(fd, value, strlen(value) + 1);
        close(fd);
        return 0;
    }

    return -EINVAL;
}

int FourZoneKbLightDriver::DriverGetColors(unsigned int *zone1, unsigned int *zone2, unsigned int *zone3,
                                           unsigned int *zone4) {
    const int fd = open("/sys/devices/platform/hp-wmi/fourzone_color", O_RDONLY);
    if (fd > 0) {
        char buf[50] = {0};
        const int bytes_read = read(fd, buf, 50);
        if (bytes_read > 0) {
            std::string token;
            std::istringstream reader(buf);

            unsigned int* outputs[] = {zone1, zone2,  zone3, zone4};
            for (auto & output : outputs) {
                reader >> token;
                *output = std::strtoul(token.c_str(), nullptr, 16);
            }

            close(fd);
            return 0;
        }

        close(fd);
    }

    return -EINVAL;
}

int FourZoneKbLightDriver::DriverSetColors(unsigned int zone1, unsigned int zone2, unsigned int zone3,
                                           unsigned int zone4) {
    const int fd = open("/sys/devices/platform/hp-wmi/fourzone_color", O_WRONLY);
    if (fd > 0) {
        std::ostringstream stream;
        stream << "0x"
               << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
               << std::hex << zone1;
        stream << " 0x"
               << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
               << std::hex << zone2;
        stream << " 0x"
               << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
               << std::hex << zone3;
        stream << " 0x"
               << std::setfill ('0') << std::setw(sizeof(unsigned int)*2)
               << std::hex << zone4;
        stream << "\n";
        std::string str = stream.str();

        write(fd, str.c_str(), str.length() + 1);
        close(fd);
    }

    return -EINVAL;
}
