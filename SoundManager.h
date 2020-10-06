//
//  SoundManager.hpp
//  FantasyBattleSaga
//
//  Created by Park Yun Seong on 2016. 12. 13..
//
//

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GM.h"

class SoundManager
{
private:
    static SoundManager* instance;
    SoundManager();
    ~SoundManager();
public:
    static SoundManager* getInstance();
    static void releaseInstance();
    
    static void PreLoading();
    static void PlaySound(const char* _str);
    static void StopBGM();
    static void PlayBGM(const char* _str);
    static void PlayAllBGM();
    static void StopAllBGM();
    static void PauseBGM(int _id);
    static void ResumeBGM(int _id);
    
};

#endif /* SoundManager_hpp */
