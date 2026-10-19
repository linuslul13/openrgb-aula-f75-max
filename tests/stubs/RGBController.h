#pragma once
#include <cstdint>
#include <string>
#include <vector>
typedef unsigned int RGBColor;
#define RGBGetRValue(rgb)   ((rgb) & 0x000000FF)
#define RGBGetGValue(rgb)   (((rgb) >> 8) & 0x000000FF)
#define RGBGetBValue(rgb)   (((rgb) >> 16) & 0x000000FF)
#define ToRGBColor(r,g,b) ((RGBColor)(((b)<<16)|((g)<<8)|(r)))
#define DEVICE_TYPE_KEYBOARD 1
#define ZONE_TYPE_SINGLE 0
#define MODE_FLAG_HAS_BRIGHTNESS 16
#define MODE_FLAG_HAS_SPEED 1
#define MODE_FLAG_HAS_MODE_SPECIFIC_COLOR 64
#define MODE_COLORS_NONE 0
#define MODE_COLORS_MODE_SPECIFIC 2
struct mode {
    std::string name;
    int value=0;
    unsigned int flags=0;
    unsigned int brightness_min=0, brightness_max=0, brightness=0;
    unsigned int speed_min=0, speed_max=0, speed=0;
    unsigned int color_mode=0, colors_min=0, colors_max=0;
    std::vector<RGBColor> colors;
};
struct led { std::string name; };
struct zone {
    std::string name;
    int type=0;
    unsigned int leds_min=0, leds_max=0, leds_count=0;
};
class RGBController {
public:
    virtual ~RGBController() = default;
    std::string name,vendor,description,location;
    int type=0, active_mode=0;
    std::vector<led> leds;
    std::vector<zone> zones;
    std::vector<RGBColor> colors;
    std::vector<mode> modes;
    void SetupColors() { colors.resize(leds.size(), ToRGBColor(255,255,255)); }
    void Shutdown() {}
};
