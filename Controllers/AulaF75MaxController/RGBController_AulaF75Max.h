/*---------------------------------------------------------*\
| RGBController_AulaF75Max.h                                 |
|                                                           |
|   OpenRGB adapter for AULA F75 MAX receiver RGB           |
|   Community prototype                                     |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#pragma once
#include "RGBController.h"
#include "AulaF75MaxController.h"

class RGBController_AulaF75Max : public RGBController
{
public:
    explicit RGBController_AulaF75Max(AulaF75MaxController* controller);
    ~RGBController_AulaF75Max();
    void SetupZones();
    void DeviceUpdateLEDs();
    void DeviceUpdateZoneLEDs(int zone);
    void DeviceUpdateSingleLED(int led);
    void DeviceUpdateMode();
private:
    AulaF75MaxController* controller;
};
