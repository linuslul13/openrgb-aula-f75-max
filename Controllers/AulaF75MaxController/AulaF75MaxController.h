/*---------------------------------------------------------*\
| AulaF75MaxController.h                                    |
|                                                           |
|   Transport for AULA F75 MAX 2.4 GHz RGB                  |
|   Community prototype                                     |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#pragma once
#include <cstdint>
#include <mutex>
#include <string>
#include <hidapi.h>
#include "RGBController.h"

class AulaF75MaxController
{
public:
    AulaF75MaxController(hid_device* device, const std::string& path);
    ~AulaF75MaxController();
    std::string GetDeviceLocation() const;
    bool SetLighting(uint8_t mode, RGBColor color, unsigned int brightness,
                     unsigned int speed, bool colorful);
private:
    bool SendSequence(const unsigned char* commit, unsigned int commit_size,
                      const unsigned char* payload, unsigned int payload_size);
    hid_device* device;
    std::string path;
    std::mutex device_mutex;
};
