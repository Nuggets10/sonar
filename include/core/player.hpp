#pragma once
#include <iostream>

#include "tui/playerWindow.hpp"

void initPlayer(PlayerWindow& playerWindowRef);
void uninitPlayer();
bool playAudio(const std::string& filePath);
bool getAudioTime(float* current, float* total);
void increaseVolume();
void decreaseVolume();
void togglePauseAudio();
int getAutoPlayMode();
void setAutoPlayMode(int mode);
bool getPauseState();
void restartAudio();
