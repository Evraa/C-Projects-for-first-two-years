#include "SoundEffects.h"
#include <iostream>
#include <Windows.h>
using namespace std;

#pragma comment(lib, "Winmm.lib")

SoundEffects::SoundEffects()
{
}

SoundEffects::~SoundEffects()
{
}

void SoundEffects::Background()
{
	mciSendString("play Audio/BG.mp3", NULL, 0, NULL);
	mciSendString("setaudio Audio/BG.mp3 volume to 50", NULL, 0, NULL);
	mciSendString("play Audio/BG.mp3 repeat", NULL, 0, NULL);
}

void SoundEffects::Killedenemies()
{
	mciSendString("play Audio/Killed.mp3", NULL, 0, NULL);
}

void SoundEffects::FighterSound()
{
	PlaySound(TEXT("Audio/Fighter2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundEffects::ShieldedSound()
{
	PlaySound(TEXT("Audio/Shielded Fighter2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void SoundEffects::PavingSound()
{
	PlaySound(TEXT("Audio/Paver2.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void SoundEffects::TowerFallingSound()
{
	PlaySound(TEXT("Audio/Zcastle falling.wav"), NULL, SND_FILENAME | SND_ASYNC);
}
void SoundEffects::VictorySound()
{
	PlaySound(TEXT("Audio/ZVictory.wav"), NULL, SND_ALIAS);
}
void SoundEffects::DefeatSound()
{
	PlaySound(TEXT("Audio/ZDefeat.wav"), NULL, SND_ALIAS);
}