/*---------------------------------------------------------*\
| AulaF75MaxPackets.h                                       |
|                                                           |
|   RGB report serialization for AULA F75 MAX receiver     |
|   Based on publicly documented device protocol           |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#pragma once
#include <array>
#include <cstdint>

namespace AulaF75Max
{
    // Byte 0: HID report ID 0; bytes 1-32: USB output report body.
    using Report = std::array<uint8_t, 33>;

    inline void Checksum(Report& report)
    {
        unsigned int sum = 0;
        for(unsigned int i = 1; i <= 31; ++i)
        {
            sum += report[i];
        }
        report[32] = (uint8_t)(sum & 0xFF);
    }

    inline Report Commit()
    {
        Report report{};
        report[1] = 0x0F;
        Checksum(report);
        return report;
    }

    inline Report RGB(uint8_t mode, uint8_t r, uint8_t g, uint8_t b,
                      uint8_t brightness, uint8_t speed, bool colorful)
    {
        Report report{};
        report[1] = 0x05;
        report[2] = 0x10;
        report[4] = mode;
        if(mode != 0)
        {
            report[5] = r;
            report[6] = g;
            report[7] = b;
            report[12] = colorful ? 1 : 0;
            report[13] = brightness;
            report[14] = speed;
            report[15] = 0; // Direction: right.
        }
        report[18] = 0xAA;
        report[19] = 0x55;
        Checksum(report);
        return report;
    }
}
