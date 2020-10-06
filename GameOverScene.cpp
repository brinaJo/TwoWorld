//
//  GameOverScene.cpp
//  Twoworld
//
//  Created by Test on 2017. 1. 18..
//
//

#include "GameOverScene.h"
#include "IntroScene.h"
#include "GameScene.h"
#include "myheader.h"
#include "SoundManager.h"
#include "GM.h"

static std::string fontList[] = {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "fonts/Spoqa Han Sans Bold_subset.ttf",
#else
    "fonts/Spoqa Han Sans Bold_subset.ttf"
#endif
};
USING_NS_CC;

Scene * GameOverScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOverScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameOverScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    this->turnScore = GM::Getinstance()->turnScore;
    this->mapRatio = GM::Getinstance()->mapRatio;
    this->gameOverRatio = GM::Getinstance()->gameOverRatio;
    
    GameOverLayer = Layer::create();
    this->addChild(GameOverLayer);
    ButtonUILayer = Layer::create();
    this->addChild(ButtonUILayer);
    
    GameOverDraw();
    ButtonDraw();
    
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setPosition(VisibleSize.width/2,VisibleSize.height/2);
    this->addChild(sp_black,2);
    
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2 - 888,VisibleSize.height/2));
    
    sp_black->runAction(action);
    return true;
}

void GameOverScene::GameOverDraw()
{
    GameOverLayer->removeAllChildren();
    sprintf(_str,"twoworld/bg_result.png");
    auto bg_under = Sprite::create(_str);
    bg_under->setPosition(VisibleSize.width/2, VisibleSize.height/2);
    GameOverLayer->addChild(bg_under,1);
    
    sprintf(_str,"twoworld/bg_result2.png");
    auto bg_top = Sprite::create(_str);
    bg_top->setPosition(VisibleSize.width/2, VisibleSize.height/2);
    GameOverLayer->addChild(bg_top,10);
    
    sprintf(_str,"twoworld/fx_result.png");
    auto fx_result = Sprite::create(_str);
    fx_result->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 184);
    GameOverLayer->addChild(fx_result,5);
    
    auto rotateAction = RotateBy::create(4.0, 360);
    auto rpAction = RepeatForever::create(rotateAction);
    fx_result->runAction(rpAction);
    
    if(mapRatio <= - gameOverRatio)     //휴먼
    {
        SoundManager::PlaySound("twoworld_snd/hwin.wav");
        sprintf(_str,"twoworld/human_win.png");
        auto humanWin = Sprite::create(_str);
        humanWin->setAnchorPoint(Point(0.5,0.0));
        humanWin->setPosition(VisibleSize.width/2, VisibleSize.height/2 + 120);
        GameOverLayer->addChild(humanWin,11);
        
        ishumanwin = true;
    }
    else if(mapRatio >= gameOverRatio)       //오크
    {
        SoundManager::PlaySound("twoworld_snd/owin.wav");
        sprintf(_str,"twoworld/orc_win.png");
        auto orcWin = Sprite::create(_str);
        orcWin->setAnchorPoint(Point(0.5,0.0));
        orcWin->setPosition(VisibleSize.width/2, VisibleSize.height/2 + 120);
        GameOverLayer->addChild(orcWin,11);
        
        isorkwin = true;
    }
    else
    {
        SoundManager::PlaySound("twoworld_snd/peace.mp3");
        sprintf(_str,"twoworld/peace.png");
        auto Peace = Sprite::create(_str);
        Peace->setAnchorPoint(Point(0.5,0.0));
        Peace->setPosition(VisibleSize.width/2, VisibleSize.height/2 + 120);
        GameOverLayer->addChild(Peace,11);
        
        turnScore *= 1.5;
    }
    
    std::string str_score = StringUtils::format("Score");
    auto underscoreLabel = Label::createWithTTF(str_score, fontList[0], 70);
    underscoreLabel->setAnchorPoint(Point(0.5,0.0));
    underscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 68));
    underscoreLabel->setColor(Color3B(0,0,0));
    GameOverLayer->addChild(underscoreLabel,11);
    
    auto scoreLabel = Label::createWithTTF(str_score, fontList[0], 70);
    scoreLabel->setAnchorPoint(Point(0.5,0.0));
    scoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 64));
    scoreLabel->setColor(Color3B(255,229,102));
    GameOverLayer->addChild(scoreLabel,11);
    
    std::string str_numscore = StringUtils::format("%d", turnScore);
    auto undernumscoreLabel = Label::createWithTTF(str_numscore, fontList[0], 80);
    undernumscoreLabel->setAnchorPoint(Point(0.5,0.0));
    undernumscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 164));
    undernumscoreLabel->setColor(Color3B(0,0,0));
    GameOverLayer->addChild(undernumscoreLabel,11);
    
    auto scorenumLabel = Label::createWithTTF(str_numscore, fontList[0], 80);
    scorenumLabel->setAnchorPoint(Point(0.5,0.0));
    scorenumLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 160));
    GameOverLayer->addChild(scorenumLabel,11);
    
    std::string str_highscore = StringUtils::format("High score");
    auto underhighscoreLabel = Label::createWithTTF(str_highscore, fontList[0], 50);
    underhighscoreLabel->setAnchorPoint(Point(0.5,0.0));
    underhighscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 256));
    underhighscoreLabel->setColor(Color3B(0,0,0));
    GameOverLayer->addChild(underhighscoreLabel,11);
    
    auto highscoreLabel = Label::createWithTTF(str_highscore, fontList[0], 50);
    highscoreLabel->setAnchorPoint(Point(0.5,0.0));
    highscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 252));
    highscoreLabel->setColor(Color3B(255,76,76));
    GameOverLayer->addChild(highscoreLabel,11);
    
    std::string str_highnumscore = StringUtils::format("%d", GM::Getinstance()->highScore);
    auto underhighnumscoreLabel = Label::createWithTTF(str_highnumscore, fontList[0], 60);
    underhighnumscoreLabel->setAnchorPoint(Point(0.5,0.0));
    underhighnumscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 328));
    underhighnumscoreLabel->setColor(Color3B(0,0,0));
    GameOverLayer->addChild(underhighnumscoreLabel,11);
    
    auto highnumscoreLabel = Label::createWithTTF(str_highnumscore, fontList[0], 60);
    highnumscoreLabel->setAnchorPoint(Point(0.5,0.0));
    highnumscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 - 324));
    GameOverLayer->addChild(highnumscoreLabel,11);
       
}
void GameOverScene::ButtonDraw()
{
    ButtonUILayer->removeAllChildren();
    
    auto RetryButton = MenuItemImage::create("twoworld/b_retry.png","twoworld/b_retry_push.png",CC_CALLBACK_1(GameOverScene::Blackfx, this));
    RetryButton->setTag(START);
    auto pRetryMenu = Menu::create(RetryButton,NULL);
    RetryButton->setAnchorPoint(Point(0.0,0.0));
    pRetryMenu->setPosition(VisibleSize.width/2 + 158,VisibleSize.height/2 - 552);
    ButtonUILayer->addChild(pRetryMenu);
    
    auto BackButton = MenuItemImage::create("twoworld/b_back.png","twoworld/b_back_push.png",CC_CALLBACK_1(GameOverScene::Blackfx, this));
    BackButton->setTag(INTRO);
    auto pBackMenu = Menu::create(BackButton,NULL);
    BackButton->setAnchorPoint(Point(0.0,0.0));
    pBackMenu->setPosition(VisibleSize.width/2 - 304,VisibleSize.height/2 - 552);
    ButtonUILayer->addChild(pBackMenu);
    
    auto ShareButton = MenuItemImage::create("twoworld/b_share.png","twoworld/b_share_push.png",CC_CALLBACK_1(GameOverScene::ChangeScene, this));
    ShareButton->setTag(SHARE);
    auto pShareMenu = Menu::create(ShareButton,NULL);
    ShareButton->setAnchorPoint(Point(0.0,0.0));
    pShareMenu->setPosition(VisibleSize.width/2 - 150,VisibleSize.height/2 - 552);
    ButtonUILayer->addChild(pShareMenu);
    
    auto GradeButton = MenuItemImage::create("twoworld/b_grade.png","twoworld/b_grade_push.png",CC_CALLBACK_1(GameOverScene::ChangeScene, this));
    GradeButton->setTag(GRADE);
    auto pGradeMenu = Menu::create(GradeButton,NULL);
    GradeButton->setAnchorPoint(Point(0.0,0.0));
    pGradeMenu->setPosition(VisibleSize.width/2 + 4,VisibleSize.height/2 - 552);
    ButtonUILayer->addChild(pGradeMenu);

}
void GameOverScene::Blackfx(Ref *sender)
{
    SoundManager::PlaySound("twoworld_snd/button.wav");
    auto a = (MenuItem*)sender;
    
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setTag(a->getTag());
    sp_black->setPosition(VisibleSize.width + 888,VisibleSize.height/2);
    this->addChild(sp_black,5);
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2,VisibleSize.height/2));
    auto changeaction = CallFuncN::create(CC_CALLBACK_1(GameOverScene::ChangeScene, this));
   
    
    auto seq = Sequence::create(action, changeaction, NULL);
    sp_black->runAction(seq);
}
void GameOverScene::ChangeScene(Ref *sender)
{
    auto menuItem = (MenuItem*)sender;
    switch (menuItem->getTag())
    {
        case INTRO:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
            Director::getInstance()->replaceScene(IntroScene::createScene());
            
            if(isorkwin)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
            }
            if(ishumanwin)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
            }
        }
            break;
        case START:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
            Director::getInstance()->replaceScene(GameScene::createScene());
            
            if(isorkwin)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
            }
            if(ishumanwin)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
            }
        }
            break;
        case SHARE:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
        }
            break;
        case GRADE:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
        }
            break;
    }
}
