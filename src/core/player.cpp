#include <iostream>
#include <string>

#define MINIAUDIO_IMPLEMENTATION
#include <algorithm>

#include "libs/miniaudio/miniaudio.h"
#include "tui/playerWindow.hpp"

static ma_engine maEngine;
static ma_sound maSound;
static bool engineInitialized = false;
static bool audioInitialized = false;
static bool isPaused = false;
static PlayerWindow* playerWindow = nullptr;
static int autoPlayMode = 0;  // 0: none
// 1: repeat
// 2: linear
// 3: shuffle

bool initPlayer(PlayerWindow& playerWindowRef)
{
    if (engineInitialized) return true;

    playerWindow = &playerWindowRef;

    const ma_result result = ma_engine_init(nullptr, &maEngine);
    if (result != MA_SUCCESS)
    {
        std::cerr << "Audio engine initialization failed: " << result << '\n';
        return false;
    }

    engineInitialized = true;
    return true;
}

void unloadAudio()
{
    if (!audioInitialized) return;

    ma_sound_stop(&maSound);
    ma_sound_uninit(&maSound);
    audioInitialized = false;
    isPaused = false;
}

void uninitPlayer()
{
    unloadAudio();

    if (engineInitialized)
    {
        ma_engine_uninit(&maEngine);
        engineInitialized = false;
    }
}

bool loadAudio(const std::string& filePath)
{
    if (!engineInitialized)
    {
        return false;
    }

    unloadAudio();

    const ma_uint32 flags =
        MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION;

    const ma_result result =
        ma_sound_init_from_file(&maEngine, filePath.c_str(), flags, nullptr, nullptr, &maSound);

    if (result != MA_SUCCESS)
    {
        playerWindow->updateAudioName(false, "");
        std::cerr << result << "\n";
        return false;
    }
    else
    {
        playerWindow->updateAudioName(true, filePath);
    }

    audioInitialized = true;
    isPaused = false;
    return true;
}

bool playAudio(const std::string& filePath)
{
    if (!loadAudio(filePath))
    {
        return false;
    }

    const ma_result result = ma_sound_start(&maSound);
    if (result != MA_SUCCESS)
    {
        unloadAudio();
        return false;
    }

    return true;
}

void togglePauseAudio()
{
    if (audioInitialized)
    {
        if (isPaused)
        {
            ma_sound_start(&maSound);
            isPaused = false;
        }
        else
        {
            ma_sound_stop(&maSound);
            isPaused = true;
        }
    }
}

bool getAudioTime(float* current, float* total)
{
    if (!audioInitialized)
    {
        return false;
    }
    ma_sound_get_cursor_in_seconds(&maSound, current);
    ma_sound_get_length_in_seconds(&maSound, total);
    return true;
}

void increaseVolume()
{
    float volume = ma_engine_get_volume(&maEngine);
    volume = std::min(volume + 0.1f, 2.0f);
    ma_engine_set_volume(&maEngine, volume);
}

void decreaseVolume()
{
    float volume = ma_engine_get_volume(&maEngine);
    volume = std::max(volume - 0.1f, 0.0f);
    ma_engine_set_volume(&maEngine, volume);
}

int getAutoPlayMode() {
    return autoPlayMode;
}

void setAutoPlayMode(int mode) {
    autoPlayMode = mode;
}

bool getPauseState() {
    return isPaused;
}

void restartAudio()
{
    if (audioInitialized)
    {
        ma_sound_seek_to_pcm_frame(&maSound, 0);
        ma_sound_start(&maSound);
    }
}
