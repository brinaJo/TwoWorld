//
//  IntroScene.cpp
//  Twoworld
//
//  Created by Test on 2017. 1. 18..
//
//

#include "IntroScene.h"
#include "GameScene.h"
#include "GM.h"
#include "SoundManager.h"
#include "myheader.h"
static std::string fontList[] = {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    "fonts/Spoqa Han Sans Bold_subset.ttf",
#else
    "fonts/Spoqa Han Sans Bold_subset.ttf"
#endif
};
USING_NS_CC;

Scene * IntroScene::createScene()
{
    auto scene = Scene::create();
    auto layer = IntroScene::create();
    scene->addChild(layer);
    return scene;
}

bool IntroScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    IntroLayer = Layer::create();
    this->addChild(IntroLayer);
    
    IntroDraw();
    if(!GM::Getinstance()->isIntroOnce)
    {
        GM::Getinstance()->isIntroOnce = true;
        SoundManager::PreLoading();
        SoundManager::PlayAllBGM();
        SoundManager::PauseBGM(GM::Getinstance()->BGM2);
        SoundManager::PauseBGM(GM::Getinstance()->BGM3);
    }
    else
    {
        this->StartBlackfx();
    }
    return true;
}
void IntroScene::IntroDraw()
{
    IntroLayer->removeAllChildren();
    
    sprintf(_str, "twoworld/bg_main.png");
    auto bgSprite = Sprite::create(_str);
    bgSprite->setPosition(VisibleSize.width/2,VisibleSize.height/2);
    IntroLayer->addChild(bgSprite);
    std::string str_title = StringUtils::format("Two World");
    auto title = Label::createWithTTF(str_title, fontList[0], 80);
    
    title->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 300));
    IntroLayer->addChild(title,1);
    
    auto StartButton = MenuItemImage::create("twoworld/b_start.png","twoworld/b_start_push.png",CC_CALLBACK_1(IntroScene::Blackfx, this));
    StartButton->setTag(START);
    auto pStartMenu = Menu::create(StartButton,NULL);
    StartButton->setAnchorPoint(Point(0.0,0.0));
    pStartMenu->setPosition(VisibleSize.width/2 - 162,VisibleSize.height/2 - 192);
    IntroLayer->addChild(pStartMenu);
    
    auto HowToButton = MenuItemImage::create("twoworld/b_howto.png","twoworld/b_howto_push.png",CC_CALLBACK_1(IntroScene::changeScene, this));
    HowToButton->setTag(HOWTO);
    auto pHowToMenu = Menu::create(HowToButton,NULL);
    HowToButton->setAnchorPoint(Point(0.0,0.0));
    pHowToMenu->setPosition(VisibleSize.width/2 - 266,VisibleSize.height/2 - 424);
    IntroLayer->addChild(pHowToMenu);
    
    auto MoreGameButton = MenuItemImage::create("twoworld/b_moregame.png","twoworld/b_moregame.png",CC_CALLBACK_1(IntroScene::changeScene, this));
    MoreGameButton->setTag(MOREGAME);
    auto pMoreGameMenu = Menu::create(MoreGameButton,NULL);
    MoreGameButton->setAnchorPoint(Point(0.0,0.0));
    pMoreGameMenu->setPosition(VisibleSize.width/2 + 120,VisibleSize.height/2 - 536);
    IntroLayer->addChild(pMoreGameMenu);
    
    std::string _str;
    std::string _str_push;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _str = "twoworld/b_ios_rank.png";
    _str_push = "twoworld/b_ios_rank_push.png";
#else
    _str = "twoworld/b_and_rank.png";
    _str_push = "twoworld/b_and_rank_push.png";
#endif
    
    auto RankButton = MenuItemImage::create(_str,_str_push,CC_CALLBACK_1(IntroScene::changeScene, this));
    RankButton->setTag(RANK);
    auto pRankMenu = Menu::create(RankButton,NULL);
    RankButton->setAnchorPoint(Point(0.0,0.0));
    pRankMenu->setPosition(VisibleSize.width/2 - 266,VisibleSize.height/2 - 536);
    IntroLayer->addChild(pRankMenu);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    _str = "twoworld/b_ios_archivment.png";
    _str_push = "twoworld/b_ios_archivment_push.png";
#else
    _str = "twoworld/b_and_archivment.png";
    _str_push = "twoworld/b_and_archivment_push.png";
#endif
    
    auto archivButton = MenuItemImage::create(_str,_str_push,CC_CALLBACK_1(IntroScene::changeScene, this));
    archivButton->setTag(ARCHIVEMENT);
    auto pArchivMenu = Menu::create(archivButton,NULL);
    archivButton->setAnchorPoint(Point(0.0,0.0));
    pArchivMenu->setPosition(VisibleSize.width/2 - 73,VisibleSize.height/2 - 536);
    IntroLayer->addChild(pArchivMenu);
    
    /////////////
    auto soundOnButton = MenuItemImage::create("twoworld/b_bgm_on.png","twoworld/b_bgm_push.png");
    auto soundOffButton = MenuItemImage::create("twoworld/b_bgm_off.png","twoworld/b_bgm_push.png");
    //soundOnButton->setAnchorPoint(Point(0.0,0.0));
    //soundOffButton->setAnchorPoint(Point(0.0,0.0));
    auto soundToggle = MenuItemToggle::create();
    if(GM::GetSound())
    {
        soundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(IntroScene::changeScene, this),soundOnButton,soundOffButton,NULL);
        soundToggle->setAnchorPoint(Point(0,0));
    }
    else
    {
        soundToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(IntroScene::changeScene, this),soundOffButton,soundOnButton,NULL);
        soundToggle->setAnchorPoint(Point(0,0));
    }
    
    soundToggle->setTag(SOUND);
    auto pSoundMenu = Menu::create(soundToggle,NULL);
    
    pSoundMenu->setPosition(VisibleSize.width/2 + 120,VisibleSize.height/2 - 424);
    IntroLayer->addChild(pSoundMenu);
    
    /////////////
    auto effectOnButton = MenuItemImage::create("twoworld/b_fx_on.png","twoworld/b_fx_push.png");
    auto effectOffButton = MenuItemImage::create("twoworld/b_fx_off.png","twoworld/b_fx_push.png");
    //effectOnButton->setAnchorPoint(Point(0.0,0.0));
    //effectOffButton->setAnchorPoint(Point(0.0,0.0));
    
    auto effectToggle = MenuItemToggle::create();
    if(GM::GetEffect())
    {
        effectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(IntroScene::changeScene, this),effectOnButton,effectOffButton,NULL);
        effectToggle->setAnchorPoint(Point(0,0));
    }
    else
    {
        effectToggle = MenuItemToggle::createWithCallback(CC_CALLBACK_1(IntroScene::changeScene, this),effectOffButton,effectOnButton,NULL);
        effectToggle->setAnchorPoint(Point(0,0));
    }
    effectToggle->setTag(EFFECT);
    auto pEffectMenu = Menu::create(effectToggle,NULL);
    pEffectMenu->setPosition(VisibleSize.width/2 - 73,VisibleSize.height/2 - 424);
    IntroLayer->addChild(pEffectMenu);
    
}

void IntroScene::Blackfx(Ref* sender)
{
    
    SoundManager::PlaySound("twoworld_snd/button.wav");
    auto a = (MenuItem*) sender;
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setTag(a->getTag());
    sp_black->setPosition(VisibleSize.width + 888,VisibleSize.height/2);
    this->addChild(sp_black,5);
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2,VisibleSize.height/2));
    auto changeaction = CallFuncN::create(CC_CALLBACK_1(IntroScene::changeScene, this));
    
    
    auto seq = Sequence::create(action, changeaction, NULL);
    sp_black->runAction(seq);
}
void IntroScene::StartBlackfx()
{
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setPosition(VisibleSize.width/2,VisibleSize.height/2);
    this->addChild(sp_black,2);
    
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2 - 888,VisibleSize.height/2));
    
    sp_black->runAction(action);
}
void IntroScene::changeScene(Ref* sender)
{
    auto menuItem = (MenuItem*)sender;
    switch (menuItem->getTag())
    {
        case START:
        {
            Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
            Director::getInstance()->replaceScene(GameScene::createScene());
        }
        break;
        case HOWTO:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
            UserDefault::getInstance()->setBoolForKey("isTutorial",false);
            Director::getInstance()->replaceScene(GameScene::createScene());
        }
            break;
        case RANK:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
        }
            break;
        case ARCHIVEMENT:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
        }
            break;
        case MOREGAME:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
        }
            break;
        case SOUND:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
            if(GM::GetSound())
            {
                UserDefault::getInstance()->setBoolForKey("SOUNDKEY", false);
                SoundManager::StopAllBGM();
            }
            else if(!GM::GetSound())
            {
                UserDefault::getInstance()->setBoolForKey("SOUNDKEY", true);
                SoundManager::PlayAllBGM();
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
            }
        }
            break;
        case EFFECT:
        {
            SoundManager::PlaySound("twoworld_snd/button.wav");
            if(GM::GetEffect())
            {
                UserDefault::getInstance()->setBoolForKey("EFFECTKEY", false);
            }
            else if(!GM::GetEffect())
            {
                UserDefault::getInstance()->setBoolForKey("EFFECTKEY", true);
            }
        }
            break;
    }
    
}