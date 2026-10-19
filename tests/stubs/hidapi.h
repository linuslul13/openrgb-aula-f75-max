#pragma once
#include <cstddef>
struct hid_device_;
typedef struct hid_device_ hid_device;
int hid_write(hid_device*, const unsigned char*, size_t);
void hid_close(hid_device*);
