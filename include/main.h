#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>
#include <stdlib.h>

#include "tilemap.h"

#define WIDTH 240
#define HEIGHT 160

#define CLOCK 16777216
#define CYCLES_PER_BLANK 280806

#define DISPCNT     0x4000000 // LCD Control (2 R/W)
#define BG0CNT      0x4000008 // BG0 Control (2 R/W)
#define SOUNDCNT_H  0x4000082 // DMA Sound Control/Mixing (2 R/W)
#define SOUNDCNT_X  0x4000084 // Sound on/off (4 R/W)
#define FIFO_A_L    0x40000A0 // Sound A FIFO, Data 0 and Data 1 (2 W)
#define FIFO_A_H    0x40000A2 // Sound A FIFO, Data 2 and Data 3 (2 W)
#define FIFO_B_L    0x40000A4 // Sound B FIFO, Data 0 and Data 1 (2 W)
#define FIFO_B_H    0x40000A6 // Sound B FIFO, Data 2 and Data 3 (2 W)
#define DMA1SAD     0x40000BC // DMA 1 Source Address (4 W)
#define DMA1DAD     0x40000C0 // DMA 1 Destination Address (4 W)
#define DMA1CNT_L   0x40000C4 // DMA 1 Word Count (2 W)
#define DMA1CNT_H   0x40000C6 // DMA 1 Control (2 R/W)
#define DMA2SAD     0x40000C8
#define DMA2DAD     0x40000CC
#define DMA2CNT_L   0x40000D0
#define DMA2CNT_H   0x40000D2
#define TM0CNT_L    0x4000100 // Timer 0 Counter/Reload (2 R/W)
#define TM0CNT_H    0x4000102 // Timer 0 Control (2 R/W)
#define VRAM        0x6000000

#define BG2_ENABLE 0x400
#define BGMODE_3 0x3

#define SOUND_MASTER_ENABLE 0x80
#define SOUND_A_RIGHT_CHANNEL 0x100
#define SOUND_A_LEFT_CHANNEL 0x200
#define SOUND_A_FIFO_RESET 0x800
#define SOUND_B_RIGHT_CHANNEL 0x1000
#define SOUND_B_LEFT_CHANNEL 0x2000
#define SOUND_B_FIFO_RESET 0x8000

#define DMA_ENABLE 0x80000000
#define DMA_16 0x0
#define DMA_32 0x4000000

#define DMA_DEST_FIXED 0x400000 // DMA destination stays the same; does not increment
#define DMA_REPEAT 0x2000000 // Repeat transfer automatically on some interval
#define DMA_SYNC_TO_TIMER 0x30000000 // Sync DMA with timer 0

#define TIMER_FREQ_1 0x0
#define TIMER_FREQ_64 0x2
#define TIMER_FREQ_256 0x3
#define TIMER_FREQ_1024 0x4
#define TIMER_ENABLE 0x80

#define BUTTON_A (1 << 0)
#define BUTTON_B (1 << 1)
#define BUTTON_SELECT (1 << 2)
#define BUTTON_START (1 << 3)
#define BUTTON_RIGHT (1 << 4)
#define BUTTON_LEFT (1 << 5)
#define BUTTON_UP (1 << 6)
#define BUTTON_DOWN (1 << 7)
#define BUTTON_R (1 << 8)
#define BUTTON_L (1 << 9)

u16 getColor(u8 r, u8 g, u8 b);

#endif
