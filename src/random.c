#include "global.h"
#include "main.h"
#include "random.h"

// The number 1103515245 comes from the example implementation
// of rand and srand in the ISO C standard.

u32 gRngValue;

u16 Random(void)
{
    gRngValue = 1103515245 * gRngValue + 24691;
    return gRngValue >> 16;
}

void SeedRng(u16 seed)
{
    gRngValue = seed;
}

u16 AdvanceSeed(u32 seed, u32 frames) {
    s32 i;
    u32 value = seed;

    for (i = 0; i < frames; i++) {
        value = ISO_RANDOMIZE1(value);
    }
    return value >> 16;
}

// Get the randomly generated u32 returned after the given number of frames. 
u32 AdvanceSeed32(u32 seed, u32 frames) {
    return AdvanceSeed(seed, frames * 2) << 16 |
           AdvanceSeed(seed, frames * 2 + 1);
}

void EnableTimerRNG(void) {
    StartTimer1();
    StartTimer2();
}

// Generate a random u32 using the GBA timer registers. For sufficient entropy,
// do not call consecutively without some player input in between.
u32 TimerRNG(void) {
    return (REG_TM2CNT_L << 16) | REG_TM1CNT_L;
}
