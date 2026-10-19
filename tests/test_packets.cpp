#include "../Controllers/AulaF75MaxController/AulaF75MaxPackets.h"
#include <cassert>
#include <cstdio>

int main()
{
    auto commit = AulaF75Max::Commit();
    assert(commit[0] == 0);
    assert(commit[1] == 0x0F && commit[32] == 0x0F);

    auto red = AulaF75Max::RGB(1, 255, 0, 0, 5, 3, false);
    assert(red.size() == 33);
    assert(red[0] == 0 && red[1] == 5 && red[2] == 0x10);
    assert(red[4] == 1 && red[5] == 255 && red[6] == 0 && red[7] == 0);
    assert(red[13] == 5 && red[14] == 3);
    assert(red[18] == 0xaa && red[19] == 0x55);
    unsigned sum = 0;
    for(int i=1; i<=31; ++i) sum += red[i];
    assert(red[32] == (sum & 0xff));
    auto off = AulaF75Max::RGB(0, 255, 100, 100, 5, 3, true);
    assert(off[4] == 0 && off[5] == 0 && off[12] == 0);
    std::puts("PASS: RGB packet layouts and checksums (no hardware involved)");
    return 0;
}
