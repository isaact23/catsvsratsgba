#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include "data/music_between_rounds.h"
#include "data/music_during_rounds.h"
#include "data/music_lose.h"
#include "data/music_title.h"
#include "data/music_win.h"

#include "gba_dma.h"
#include "gba_sound.h"
#include "gba_timers.h"
#include "gba_types.h"

#define CHANNEL_A 'A'
#define CHANNEL_B 'B'

#define CLOCK_RATE 16777216
#define CYCLES_PER_BLANK 280806

#define FIFO_BUFFER_A 0x40000a0
#define FIFO_BUFFER_B 0x40000a4

#define SOUND_MASTER_ENABLE 0x80
#define TIMER_ENABLE 0x80
#define TIMER_FREQ_1 0x0

// List of sounds
enum sounds {
    MUSIC_BETWEEN_ROUNDS = 0,
    MUSIC_DURING_ROUNDS,
    MUSIC_TITLE,
    MUSIC_WIN,
    MUSIC_LOSE
};

// Initialize audio manager
void audio_manager_init();

// Update audio manager once per frame
void audio_manager_update();

// Play a sound effect from enum sounds. Return true if successful.
bool audio_manager_play_sound(enum sounds sound);

// Stop all sounds
void audio_manager_stop_sounds();

#endif
