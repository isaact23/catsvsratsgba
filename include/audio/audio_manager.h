#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "data/music_between_rounds.h"
#include "gba_dma.h"
#include "gba_sound.h"
#include "gba_timers.h"
#include "gba_types.h"

#define CLOCK_RATE 16777216
#define CYCLES_PER_BLANK 280806

#define FIFO_BUFFER_A 0x40000a0
#define FIFO_BUFFER_B 0x40000a4

#define SOUND_MASTER_ENABLE 0x80
#define TIMER_ENABLE 0x80
#define TIMER_FREQ_1 0x0

// Initialize audio manager
void audio_manager_init();

// Update audio manager once per frame
void audio_manager_update();

// Play a sound effect
void audio_manager_play_sound(const s8* sound, u32 sample_count, u32 sample_rate, char channel);

// Stop all sounds
void audio_manager_stop_sounds();

#endif
