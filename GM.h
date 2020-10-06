#ifndef __GM_H__
#define __GM_H__

#include "cocos2d.h"


USING_NS_CC;

class GM : public cocos2d::Layer
{
private:
	static GM* instance;

	GM();
	~GM() {};

public:
    bool isIntroOnce;
    
    int highScore;
    int turnScore;
    float mapRatio;
    float gameOverRatio;
    
    int BGM1;
    int BGM2;
    int BGM3;
    
	static GM* Getinstance();
    static bool GetSound();
    static bool GetEffect();
};

#endif
