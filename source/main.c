
// Copyright 2025 David Guillen Fandos <david@davidgf.net>

// Dumb slot2 timing testing tool

#include <limits.h>
#include <stdio.h>
#include <stdint.h>
#include <nds.h>
#include <nds/memory.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
  PrintConsole tops, bots;

  videoSetMode(MODE_0_2D);
  videoSetModeSub(MODE_0_2D);
  vramSetBankA(VRAM_A_MAIN_BG);
  vramSetBankC(VRAM_C_SUB_BG);

  consoleInit(&tops, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
  consoleInit(&bots, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

  sysSetCartOwner(BUS_OWNER_ARM9);

  unsigned cfg_val = 0;
  const int nseq[4] = {10, 8, 6, 18};   // /2-1? So 4, 3, 2, 8? I think so!
  const int seq[2] = {6,4};
  while (1) {
    // Render menu
    consoleSelect(&tops);
    consoleClear();
    printf("\x1b[36;1m");
    printf("\x1b[1;5HWaitCNT test tool");
    printf("\x1b[37;1m");

    printf("\x1b[7;1H < EXMEMCNT %d,%d > ", nseq[cfg_val & 3], seq[cfg_val >> 2]);

    swiWaitForVBlank();
    scanKeys();

    if (keysDown() & KEY_LEFT)
      cfg_val = (cfg_val - 1) & 0x7;
    if (keysDown() & KEY_RIGHT)
      cfg_val = (cfg_val + 1) & 0x7;

    if (keysDown() & KEY_A) {
      // Performs one single u16 access, then a u32 access.
      REG_EXMEMCNT &= ~0x1C;             // Clear bits
      REG_EXMEMCNT |= (cfg_val << 2);    // Set the config bits

      volatile uint16_t* ptr16 = (uint16_t*)0x08000000;
      volatile uint32_t* ptr32 = (uint32_t*)0x08000000;
      (*ptr16);
      (*ptr32);
      (*ptr16) = ~0;
      (*ptr32) = ~0;
    }
  }

  return 0;
}

// Results:

// 10,6  (GBA's 4,2)
// 16 bit access (2CS, 2RD)
// CS is lo for 4 GBA cycles
// RD is lo for 2 GBA cycles
// 32 bit access (2CS, 2RD, 1gap, 2RD)
// CS is lo for 7 GBA cycles
// RD is lo for 2 GBA cycles, 1 cycle gap in between.

// 8,6   (GBA's 3,2)
// 16 bit access (2CS, 1RD)
// CS is lo for 3 GBA cycles
// RD is lo for 1 GBA cycle
// 32 bit access (2CS, 1RD, 1gap, 2RD)
// CS is lo for 6 GBA cycles
// RD is lo for 1 GBA cycle, then 2 cycles on the second access.

// 6,6   (GBA's 2,2)
// 16 bit access (1CS, 1RD)
// CS is lo for 2 GBA cycles
// RD is lo for 1 GBA cycle
// 32 bit access (1CS, 1RD, 1gap, 2RD)
// CS is lo for 5 GBA cycles
// RD is lo for 1 GBA cycle, then 2 cycles on the second access.

// 6,2 (GBA's 2,1)
// 16 bit access (1CS, 1RD)
// CS is low for a total of 2 cycles, RD for 1 cycle at the end
// 32 bit access (1CS, 1RD, 1gap, 1RD)
// CS is low for a total of 4 cycles, RD is 1x2 cycles down.



