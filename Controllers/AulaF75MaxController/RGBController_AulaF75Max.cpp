/*---------------------------------------------------------*\
| RGBController_AulaF75Max.cpp                               |
|                                                           |
|   OpenRGB adapter for AULA F75 MAX receiver RGB           |
|   Community prototype                                     |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#include "RGBController_AulaF75Max.h"

/**------------------------------------------------------------------*\
    @name AULA F75 MAX (2.4 GHz)
    @category Keyboard
    @type USB
    @save :x:
    @direct :x:
    @effects :white_check_mark:
    @detectors DetectAulaF75MaxDongle
    @comment Community-prototype global RGB zone over receiver 05AC:024F FF60.
\*-------------------------------------------------------------------*/
RGBController_AulaF75Max::RGBController_AulaF75Max(AulaF75MaxController* c)
    : controller(c)
{
    name = "AULA F75 MAX (2.4G)";
    vendor = "AULA / EPOMAKER";
    description = "F75 MAX RGB via wireless receiver (one global lighting zone)";
    location = controller->GetDeviceLocation();
    type = DEVICE_TYPE_KEYBOARD;

    const struct { const char* name; int value; bool color; bool speed; } entries[] = {
        {"Off",             0,  false, false},
        {"Static",          1,  true,  false},
        {"Breathing",       7,  true,  true },
        {"Spectrum",        8,  false, true },
        {"Rolling Rainbow", 11, false, true },
        {"Ripples",         15, true,  true }
    };

    for(const auto& entry : entries)
    {
        mode m;
        m.name = entry.name;
        m.value = entry.value;
        m.flags = (entry.value == 0) ? 0 : MODE_FLAG_HAS_BRIGHTNESS;
        m.brightness_min = 1;
        m.brightness_max = 5;
        m.brightness = 5;
        if(entry.speed)
        {
            m.flags |= MODE_FLAG_HAS_SPEED;
            m.speed_min = 1;
            m.speed_max = 5;
            m.speed = 3;
        }
        if(entry.color)
        {
            m.flags |= MODE_FLAG_HAS_MODE_SPECIFIC_COLOR;
            m.color_mode = MODE_COLORS_MODE_SPECIFIC;
            m.colors_min = 1;
            m.colors_max = 1;
            m.colors.resize(1);
            m.colors[0] = ToRGBColor(255, 255, 255);
        }
        else
        {
            m.color_mode = MODE_COLORS_NONE;
        }
        modes.push_back(m);
    }

    SetupZones();
}

RGBController_AulaF75Max::~RGBController_AulaF75Max()
{
    Shutdown();
    delete controller;
}

void RGBController_AulaF75Max::SetupZones()
{
    leds.clear();
    colors.clear();
    zones.clear();
    led one_led;
    one_led.name = "Keyboard RGB";
    leds.push_back(one_led);
    zone global_zone;
    global_zone.name = "Keyboard";
    global_zone.type = ZONE_TYPE_SINGLE;
    global_zone.leds_min = 1;
    global_zone.leds_max = 1;
    global_zone.leds_count = 1;
    zones.push_back(global_zone);
    SetupColors();
}

void RGBController_AulaF75Max::DeviceUpdateLEDs()
{
    // OpenRGB's global LED color path changes the LEDs array, not the
    // mode-specific color. The previous implementation ignored this value:
    // setting all LEDs to black did NOT actually turn the lights off.
    if(colors.empty())
    {
        return;
    }

    const RGBColor rgb = colors[0];
    if(RGBGetRValue(rgb) == 0 && RGBGetGValue(rgb) == 0 && RGBGetBValue(rgb) == 0)
    {
        active_mode = 0; // Hardware mode 0: turn off the RGB backlight.
    }
    else
    {
        active_mode = 1; // Hardware mode 1: static global color.
        if(!modes[1].colors.empty())
        {
            modes[1].colors[0] = rgb;
        }
    }
    DeviceUpdateMode();
}

void RGBController_AulaF75Max::DeviceUpdateZoneLEDs(int) { DeviceUpdateLEDs(); }
void RGBController_AulaF75Max::DeviceUpdateSingleLED(int) { DeviceUpdateLEDs(); }

void RGBController_AulaF75Max::DeviceUpdateMode()
{
    if(active_mode < 0 || (size_t)active_mode >= modes.size())
    {
        return;
    }
    const mode& current = modes[active_mode];
    RGBColor color = ToRGBColor(255, 255, 255);
    if(!current.colors.empty())
    {
        color = current.colors[0];
    }
    const bool colorful = current.value == 8 || current.value == 11;
    controller->SetLighting((uint8_t)current.value, color,
                            current.brightness ? current.brightness : 5,
                            current.speed ? current.speed : 3, colorful);
}
