//
//  GameOverScene.hpp
//  Twoworld
//
//  Created by Test on 2017. 1. 18..
//
//

#ifndef GameOverScene_h
#define GameOverScene_h

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene : public Layer
{
private:
    int turnScore;
    float mapRatio;
    float gameOverRatio;
    
    bool ishumanwin;
    bool isorkwin;
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(GameOverScene);
    
    Layer* GameOverLayer;
    Layer* ButtonUILayer;
    char _str[100];
    
    void GameOverDraw();
    void ButtonDraw();
    void Blackfx(Ref *sender);
    void ChangeScene(Ref* sender);
    
    Size VisibleSize = Director::getInstance()->getVisibleSize();
};


#endif /* GameOverScene_h */
