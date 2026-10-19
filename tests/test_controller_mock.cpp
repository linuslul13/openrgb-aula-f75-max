// Build with mock hidapi and a minimal stand-in for OpenRGB's RGBController.
#include <cassert>
#include <cstdio>
#include <vector>
#include <array>
#include "hidapi.h"
#include "RGBController_AulaF75Max.h"

static std::vector<std::array<unsigned char,33>> writes;
static int fail_next = 0;
int hid_write(hid_device*, const unsigned char* data, size_t n)
{
    assert(n == 33);
    std::array<unsigned char,33> item{};
    for(size_t i=0; i<n; ++i) item[i] = data[i];
    writes.push_back(item);
    if(fail_next) { --fail_next; return -1; }
    return (int)n;
}
void hid_close(hid_device*) {}

void check_sequence(unsigned char mode, int r, int g, int b)
{
    assert(writes.size() == 4);
    for(int i=0;i<4;i+=2)
    {
        assert(writes[i][1] == 0x0f);
        assert(writes[i+1][1] == 0x05);
        assert(writes[i+1][4] == mode);
        if(mode != 0)
        {
            assert(writes[i+1][5] == r);
            assert(writes[i+1][6] == g);
            assert(writes[i+1][7] == b);
        }
    }
}

int main()
{
    {
        RGBController_AulaF75Max ctl(new AulaF75MaxController((hid_device*)0x1, "test-dongle"));
        assert(ctl.modes.size() == 6);
        assert(ctl.colors.size() == 1);
        writes.clear();
        ctl.colors[0] = ToRGBColor(255,0,0);
        ctl.DeviceUpdateLEDs();
        assert(ctl.active_mode == 1);
        check_sequence(1,255,0,0);

        writes.clear();
        ctl.colors[0] = ToRGBColor(0,0,0);
        ctl.DeviceUpdateLEDs();
        assert(ctl.active_mode == 0);
        check_sequence(0,0,0,0);

        writes.clear();
        ctl.active_mode = 0;
        ctl.DeviceUpdateMode();
        check_sequence(0,0,0,0);

        writes.clear();
        ctl.colors[0] = ToRGBColor(0,0,255);
        ctl.DeviceUpdateZoneLEDs(0);
        check_sequence(1,0,0,255);

        // A failed first commit is followed by an entire second sequence.
        writes.clear();
        fail_next=1;
        ctl.active_mode=1;
        ctl.DeviceUpdateMode();
        assert(writes.size()==3);
        assert(writes.back()[4] == 1);
    }
    std::puts("PASS: mock transport, Off, black LED color, static RGB and retry");
}
