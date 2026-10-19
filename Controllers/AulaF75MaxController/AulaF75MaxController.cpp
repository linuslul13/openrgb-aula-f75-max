/*---------------------------------------------------------*\
| AulaF75MaxController.cpp                                  |
|                                                           |
|   Transport for AULA F75 MAX 2.4 GHz RGB                  |
|   Community prototype                                     |
|   SPDX-License-Identifier: GPL-2.0-or-later               |
\*---------------------------------------------------------*/
#include "AulaF75MaxController.h"
#include "AulaF75MaxPackets.h"
#include <algorithm>
#include <chrono>
#include <thread>

AulaF75MaxController::AulaF75MaxController(hid_device* dev, const std::string& p)
    : device(dev), path(p)
{
}

AulaF75MaxController::~AulaF75MaxController()
{
    if(device != nullptr)
    {
        hid_close(device);
    }
}

std::string AulaF75MaxController::GetDeviceLocation() const
{
    return "HID: " + path;
}

bool AulaF75MaxController::SendSequence(const unsigned char* commit,
                                       unsigned int commit_size,
                                       const unsigned char* payload,
                                       unsigned int payload_size)
{
    // The dongle expects an OUTPUT commit and then an OUTPUT lighting report.
    // A HID write success only means USB accepted the report, not that the
    // receiver/keyboard applied it. There is no documented RGB ACK.
    if(hid_write(device, commit, commit_size) != (int)commit_size)
    {
        return false;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(75));
    return hid_write(device, payload, payload_size) == (int)payload_size;
}

bool AulaF75MaxController::SetLighting(uint8_t mode, RGBColor color,
                                       unsigned int brightness, unsigned int speed,
                                       bool colorful)
{
    if(device == nullptr)
    {
        return false;
    }

    std::lock_guard<std::mutex> lock(device_mutex);
    const AulaF75Max::Report commit = AulaF75Max::Commit();
    const AulaF75Max::Report payload = AulaF75Max::RGB(
        mode,
        RGBGetRValue(color), RGBGetGValue(color), RGBGetBValue(color),
        (uint8_t)std::max(1U, std::min(5U, brightness)),
        (uint8_t)std::max(1U, std::min(5U, speed)), colorful);

    // Some receivers miss the first update. Send a complete second sequence
    // after a short settling delay; retry even when the first HID write
    // returned success, since the radio side has no verified acknowledgement.
    bool sent = SendSequence(commit.data(), commit.size(),
                             payload.data(), payload.size());
    std::this_thread::sleep_for(std::chrono::milliseconds(90));
    bool repeated = SendSequence(commit.data(), commit.size(),
                                 payload.data(), payload.size());
    return sent || repeated;
}
