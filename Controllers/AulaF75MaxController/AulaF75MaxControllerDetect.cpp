/*---------------------------------------------------------*\
| AulaF75MaxControllerDetect.cpp                             |
|                                                           |
|   Device detection for AULA F75 MAX wireless receiver     |
|   Community prototype                                     |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#include "DetectionManager.h"
#include "RGBController.h"
#include "hidapi.h"
#include "AulaF75MaxController.h"
#include "RGBController_AulaF75Max.h"

// Limit detection to FF60, not the receiver's generic keyboard interfaces.
DetectedControllers DetectAulaF75MaxDongle(hid_device_info* info, const std::string&)
{
    DetectedControllers detected_controllers;
    hid_device* dev = hid_open_path(info->path);
    if(dev != nullptr)
    {
        AulaF75MaxController* hw = new AulaF75MaxController(dev, info->path);
        detected_controllers.push_back(new RGBController_AulaF75Max(hw));
    }
    return detected_controllers;
}

REGISTER_HID_DETECTOR_P("AULA F75 MAX receiver RGB (experimental)", DetectAulaF75MaxDongle, 0x05AC, 0x024F, 0xFF60);
