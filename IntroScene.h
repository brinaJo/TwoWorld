//
//  IntroScene.hpp
//  Twoworld
//
//  Created by Test on 2017. 1. 18..
//
//

#ifndef IntroScene_h
#define IntroScene_h

#include <stdio.h>

#include "cocos2d.h"
USING_NS_CC;

class IntroScene : public Layer
{
private:
    
public:
    static Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(IntroScene);
    
    Layer* IntroLayer;
    
    char _str[100];
    
    void IntroDraw();
    void changeScene(Ref* sender);
    void Blackfx(Ref *sender);
    void StartBlackfx();
    Size VisibleSize = Director::getInstance()->getVisibleSize();
};



#endif /* IntroScene_hpp */
