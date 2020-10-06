//
//  SoundManager.cpp
//  FantasyBattleSaga
//
//  Created by Park Yun Seong on 2016. 12. 13..
//
//

#include "SoundManager.h"

SoundManager* SoundManager::instance = NULL;

SoundManager::SoundManager()
{
    
}

SoundManager::~SoundManager()
{
    
}

SoundManager* SoundManager::getInstance()
{
    if(instance == NULL)
        instance = new SoundManager();
    return instance;
}

void SoundManager::releaseInstance()
{
    if(instance)
        delete instance;
}

void SoundManager::PreLoading()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("twoworld_snd/BGM1.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("twoworld_snd/BGM2.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("twoworld_snd/BGM3.mp3");
   
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/button.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/dontmove.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/hadd.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/hdie.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/oadd.WAV");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/odie.wav");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/peace.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("twoworld_snd/swipe.wav");
}

void SoundManager::PlayBGM(const char *_str)
{
    if(GM::GetSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(_str, true);
    }
}

void SoundManager::StopBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    
}
void SoundManager::PlayAllBGM()
{
    if(GM::GetSound())
    {
        GM::Getinstance()->BGM1 = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("twoworld_snd/BGM1.mp3", true);
        GM::Getinstance()->BGM2 = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("twoworld_snd/BGM2.mp3", true);
        GM::Getinstance()->BGM3 = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("twoworld_snd/BGM3.mp3", true);
    }
}

void SoundManager::StopAllBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(GM::Getinstance()->BGM1);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(GM::Getinstance()->BGM2);
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(GM::Getinstance()->BGM3);
}
void SoundManager::PauseBGM(int _id)
{
    if(GM::GetSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseEffect(_id);
    }
}
void SoundManager::ResumeBGM(int _id)
{
    if(GM::GetSound())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->resumeEffect(_id);
    }
}

void SoundManager::PlaySound(const char *_str)
{
    if(GM::GetEffect())
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(_str);
    }
}
