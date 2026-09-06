
#include <iostream>
#include <string>

#define MINIAUDIO_IMPLEMENTATION
#include "libs/miniaudio/miniaudio.h"

static ma_engine maEngine;
static ma_sound maSound;
static bool engineInitialized = false;
static bool audioInitialized = false;

bool initPlayer()
{
    if (engineInitialized) return true;

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
    if (!engineInitialized && !initPlayer()) return false;

    unloadAudio();

    const ma_uint32 flags =
        MA_SOUND_FLAG_STREAM | MA_SOUND_FLAG_NO_PITCH | MA_SOUND_FLAG_NO_SPATIALIZATION;

    const ma_result result =
        ma_sound_init_from_file(&maEngine, filePath.c_str(), flags, nullptr, nullptr, &maSound);

    if (result != MA_SUCCESS)
    {
        std::cerr << "Failed to load music file: " << filePath << '\n';
        std::cerr << "miniaudio.h error: " << result << '\n';
        return false;
    }

    audioInitialized = true;
    return true;
}

bool playAudio(const std::string& filePath)
{
    if (!loadAudio(filePath)) return false;

    const ma_result result = ma_sound_start(&maSound);
    if (result != MA_SUCCESS)
    {
        std::cerr << "Failed to start music: " << result << '\n';
        unloadAudio();
        return false;
    }

    return true;
}

void pauseAudio()
{
    if (audioInitialized) ma_sound_stop(&maSound);
}

void resumeAudio()
{
    if (audioInitialized) ma_sound_start(&maSound);
}

bool isAudioPlaying() { return audioInitialized && ma_sound_is_playing(&maSound) == MA_TRUE; }
