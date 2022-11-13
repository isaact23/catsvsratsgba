// Implementations based off http://ianfinlayson.net/class/cpsc305/samples/gba/sound/sound.c

#include "audio/audio_manager.h"

// Data on current sounds
u32 channel_a_vblanks_remaining = 0;
u32 channel_a_vblanks_total = 0;
const s8* channel_a_sound;
u32 channel_b_vblanks_remaining = 0;

// Play a sound effect
static bool _audio_manager_play_sound(const s8* sound, u32 sample_count, u32 sample_rate, char channel);


// Initialize audio manager
void audio_manager_init() {

}

// Update audio manager once per frame
void audio_manager_update() {
    // Update channel A
    if (channel_a_vblanks_remaining == 0) {
        // Restart sound when vblanks run out
        channel_a_vblanks_remaining = channel_a_vblanks_total;
        REG_DMA1CNT = 0;
        REG_DMA1SAD = (u32) channel_a_sound;
        REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

    } else {
        channel_a_vblanks_remaining--;
    }

    /* update channel B */
    if (channel_b_vblanks_remaining == 0) {
        /* disable the sound and DMA transfer on channel B */
        REG_SOUNDCNT_H &= ~(SNDB_L_ENABLE | SNDB_R_ENABLE | SNDB_RESET_FIFO);
        REG_DMA2CNT = 0;
    }
    else {
        channel_b_vblanks_remaining--;
    }
}

// Play a sound effect from enum sounds. Return true if successful.
bool audio_manager_play_sound(enum sounds sound) {
    switch (sound) {
        case MUSIC_BETWEEN_ROUNDS: {
            return _audio_manager_play_sound(MUSIC_BETWEEN_ROUNDS_DATA, MUSIC_BETWEEN_ROUNDS_SAMPLES, MUSIC_BETWEEN_ROUNDS_RATE, CHANNEL_A);
        }
        case MUSIC_DURING_ROUNDS: {
            return _audio_manager_play_sound(MUSIC_DURING_ROUNDS_DATA, MUSIC_DURING_ROUNDS_SAMPLES, MUSIC_DURING_ROUNDS_RATE, CHANNEL_A);
        }
        case MUSIC_TITLE: {
            return _audio_manager_play_sound(MUSIC_TITLE_DATA, MUSIC_TITLE_SAMPLES, MUSIC_TITLE_RATE, CHANNEL_A);
        }
        case MUSIC_WIN: {
            return _audio_manager_play_sound(MUSIC_WIN_DATA, MUSIC_WIN_SAMPLES, MUSIC_WIN_RATE, CHANNEL_B);
        }
        case MUSIC_LOSE: {
            return _audio_manager_play_sound(MUSIC_LOSE_DATA, MUSIC_LOSE_SAMPLES, MUSIC_LOSE_RATE, CHANNEL_B);
        }
        default: {
            return false;
        }
    }
}

// Stop all sounds
void audio_manager_stop_sounds() {
    REG_SOUNDCNT_X &= ~SOUND_MASTER_ENABLE;
    REG_TM0CNT_H &= ~TIMER_ENABLE;
    REG_DMA1CNT = 0;
    REG_DMA2CNT = 0;
}

// Play a sound effect. Return true if successful.
static bool _audio_manager_play_sound(const s8* sound, u32 sample_count, u32 sample_rate, char channel) {

    // Disable timer and dma controller to reset previous sound
    REG_TM0CNT = 0;
    if (channel == CHANNEL_A) {
        REG_DMA1CNT = 0;
    } else if (channel == CHANNEL_B) {
        REG_DMA2CNT = 0;
    }
    // If channel is neither A nor B, function was called improperly.
    else {
        return false;
    }

    // Output to both sides and reset FIFO
    if (channel == CHANNEL_A) {
        REG_SOUNDCNT_H |= SNDA_L_ENABLE | SNDA_R_ENABLE | SNDA_RESET_FIFO;
    } else {
        REG_SOUNDCNT_H |= SNDB_L_ENABLE | SNDB_R_ENABLE | SNDB_RESET_FIFO;
    }

    // Enable all sound
    REG_SOUNDCNT_X = SOUND_MASTER_ENABLE;

    // Set DMA channel to transfer from sound array to sound buffer
    if (channel == 'A') {
        channel_a_sound = sound;
        REG_DMA1SAD = (u32) sound;
        REG_DMA1DAD = (u32) FIFO_BUFFER_A;
        // DMA_SPECIAL syncs DMA repeat interval with timer 0
        REG_DMA1CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
    } else {
        REG_DMA2SAD = (u32) sound;
        REG_DMA2DAD = (u32) FIFO_BUFFER_B;
        REG_DMA2CNT = DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;
    }

    // Set timer to overflow whenever we need a sample, triggering DMA to send sample to FIFO
    u16 ticks_per_sample = CLOCK_RATE / sample_rate;
    REG_TM0CNT = 65536 - ticks_per_sample;

    // Determine length of playback in vblanks
    if (channel == 'A') {
        channel_a_vblanks_remaining = (sample_count * ticks_per_sample) / CYCLES_PER_BLANK;
        channel_a_vblanks_total = channel_a_vblanks_remaining;
    } else if (channel == 'B') {
        channel_b_vblanks_remaining = (sample_count * ticks_per_sample) / CYCLES_PER_BLANK;
    }

    // Enable the timer
    REG_TM0CNT_H = TIMER_ENABLE | TIMER_FREQ_1;

    return true;
}
