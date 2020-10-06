//
//  GameScene.cpp
//  Twoworld
//
//  Created by Test on 2017. 1. 2..
//
//

#include "GameScene.h"
#include "GameOverScene.h"
#include "IntroScene.h"
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

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    GM::Getinstance()->highScore = UserDefault::getInstance()->getIntegerForKey("HighScore");
    TileLayer = Layer::create();
    this->addChild(TileLayer, 1);
    UILayer = Layer::create();
    this->addChild(UILayer, 1);
    PinLayer = Layer::create();
    this->addChild(PinLayer,1);
    
    topPinLayer = Layer::create();
    this->addChild(topPinLayer,1);
    BubbleLayer = Layer::create();
    this->addChild(BubbleLayer,1);
    GameOverLayer = Layer::create();
    this->addChild(GameOverLayer, 1);
    TutorialLayer = Layer::create();
    this->addChild(TutorialLayer,3);
    
    auto sprite = Sprite::create("twoworld/bg1.png");
    sprite->setPosition(VisibleSize.width/2, VisibleSize.height/2);
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    PinDraw();
    
    isTouchEnable = true;
    if(!UserDefault::getInstance()->getBoolForKey("isTutorial"))
    {
        nextDesicion = 5;
        this->TutorialMapInit();
        this->TutorialGuide();
        UserDefault::getInstance()->setBoolForKey("isTutorial",true);
        NextBlockDecision();
        AddNewNum(MAXCOL);
        
    }
    else
    {
        
        nextDesicion = 0;
        this->MapInit();
        NextBlockDecision();
        AddNewNum(MAXCOL);
    }
    
    CreateTile();
    
    this->StartBlackfx();
    
    return true;
}
void GameScene::TutorialMapInit()
{
    
    newNum = 0;
    touchcount = 0;
    killcount = 0;
    curBestNum = 0;
    mapRatio = 0;
    guideMapRatio = 0;
    killScore = 0;
    newBlockScore = 0;
    turnScore = 0;
    gameOverRatio = 100;
    isTouchEnd = false;
    beforeBlock = BLUE;
    for(int i=0;i<MAXROW;i++)
    {
        for(int j=0;j<MAXCOL;j++)
        {
            map[i][j].num = 0;
            map[i][j].tileScore = 0;
        }
    }
    map[0][0].color = RED;
    map[0][0].unitState = idle;
    map[0][0].num = 1;
    map[0][0].tileScore = 3;
        
    map[1][1].color = BLUE;
    map[1][1].unitState = idle;
    map[1][1].num = 1;
    map[1][1].tileScore = 3;
    
    map[3][1].color = BLUE;
    map[3][1].unitState = idle;
    map[3][1].num = 1;
    map[3][1].tileScore = 3;
    
    
}
void GameScene::TutorialGuide()
{
    TutorialLayer->removeAllChildren();
    
    isTouchEnable = false;
    sprintf(_str,"twoworld/tuto_text.png");
    
    auto img_textbg = Sprite::create(_str);
    img_textbg->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 376);
    TutorialLayer->addChild(img_textbg,0);
    
    if(nextDesicion == 5)
    {
        std::string str_text = StringUtils::format("이 세계에는 두개의 종족이 있습니다.");
        auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel1->setOpacity(0);
        TutorialLayer->addChild(textLabel1,1);
        
        auto actionfdIn = FadeIn::create(1.0);
        auto actionDel = DelayTime::create(2.0);
        auto actionfdOut = FadeOut::create(1.0);
        
        auto seq = Sequence::create(actionfdIn,actionDel,actionfdOut,NULL);
        textLabel1->runAction(seq);
        
        str_text = StringUtils::format("그리고 당신은 이 세계의 균형을 관장하는 신입니다.\n당신의 손짓으로 세상을 움직일 수 있지요.");
        auto textLabel2 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel2->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel2->setOpacity(0);
        textLabel2->setTag(LABELTAG);
        TutorialLayer->addChild(textLabel2,1);
        
        auto actionDel2 = DelayTime::create(3.0);
        auto actiontouch = CallFunc::create(CC_CALLBACK_0(GameScene::TouchEnable, this));
        auto actionarrow = CallFunc::create(CC_CALLBACK_0(GameScene::RightArrow, this));
        auto seq2 = Sequence::create(actionDel2, actionfdIn, actiontouch, actionarrow, NULL);
        textLabel2->runAction(seq2);
        
        
    }
    else if(nextDesicion == 3)
    {
        std::string str_text = StringUtils::format("같은 힘의 동족은 뭉쳐서 힘을 키웁니다.");
        auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel1->setTag(LABELTAG);
        textLabel1->setOpacity(0);
        TutorialLayer->addChild(textLabel1,1);
        
        auto actionfdIn = FadeIn::create(1.0);
        auto actiontouch = CallFunc::create(CC_CALLBACK_0(GameScene::TouchEnable, this));
        auto actionarrow = CallFunc::create(CC_CALLBACK_0(GameScene::RightArrow, this));
        auto seq2 = Sequence::create(actionfdIn, actiontouch, actionarrow, NULL);
        textLabel1->runAction(seq2);
    }
    else if(nextDesicion == 2)
    {
        std::string str_text = StringUtils::format("힘이 없다면 적을 쓰러뜨릴 수 없지만");
        auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel1->setTag(LABELTAG);
        textLabel1->setOpacity(0);
        TutorialLayer->addChild(textLabel1,1);
        
        auto actionfdIn = FadeIn::create(1.0);
        auto actiontouch = CallFunc::create(CC_CALLBACK_0(GameScene::TouchEnable, this));
        auto actionarrow = CallFunc::create(CC_CALLBACK_0(GameScene::LeftArrow, this));
        auto seq2 = Sequence::create(actionfdIn, actiontouch, actionarrow, NULL);
        textLabel1->runAction(seq2);
        
    }
    else if(nextDesicion == 1)
    {
        std::string str_text = StringUtils::format("강한 자는 힘없는 타 종족을 쓰러뜨릴 수 있습니다. ");
        auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel1->setTag(LABELTAG);
        textLabel1->setOpacity(0);
        TutorialLayer->addChild(textLabel1,1);
        
        auto actionfdIn = FadeIn::create(1.0);
        auto actiontouch = CallFunc::create(CC_CALLBACK_0(GameScene::TouchEnable, this));
        auto actionarrow = CallFunc::create(CC_CALLBACK_0(GameScene::UpArrow, this));
        auto seq2 = Sequence::create(actionfdIn, actiontouch, actionarrow, NULL);
        textLabel1->runAction(seq2);
    }
    else if(nextDesicion == 0)
    {
        std::string str_text = StringUtils::format("이런 일들로 인해 세계의 균형이 깨어집니다.\n종말의 화살표는 우세한 종족으로 이동합니다.");
        auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
        textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
        textLabel1->setTag(LABELTAG2);
        textLabel1->setOpacity(0);
        TutorialLayer->addChild(textLabel1,1);
        
        auto actionfdIn = FadeIn::create(1.0);
        auto actionDel = DelayTime::create(2.0);
        auto seq = Sequence::create(actionfdIn,actionDel,NULL);
        textLabel1->runAction(seq);
        
        sprintf(_str,"twoworld/tuto_touch1.png");
        auto spr_hand = Sprite::create(_str);
        spr_hand->setTag(HAND);
        auto spr_bar = (Sprite*)topPinLayer->getChildByTag(1000);
        Size BarSize = spr_bar->getContentSize();
        float ratio = (BarSize.width/2) / 100;
        
        spr_hand->setPosition(spr_bar->getPositionX() - (mapRatio * ratio),spr_bar->getPositionY());
        auto handMoveto = MoveTo::create(0.2, Point(spr_bar->getPositionX() - (mapRatio * ratio),spr_bar->getPositionY()-20));
        auto handMoveto2 = MoveTo::create(0.2, Point(spr_bar->getPositionX() - (mapRatio * ratio),spr_bar->getPositionY()));
        auto seqhand = Sequence::create(handMoveto,handMoveto2, NULL);
        auto repeathand = RepeatForever::create(seqhand);
        TutorialLayer->addChild(spr_hand);
        spr_hand->runAction(repeathand);
        
        sprintf(_str,"twoworld/tuto_taptocon.png");
        auto spr_continue = Sprite::create(_str);
        spr_continue->setPosition(VisibleSize.width/2,VisibleSize.height/2);
        spr_continue->setVisible(false);
        spr_continue->setOpacity(0);
        spr_continue->setTag(CONTINUEBUTTON);
        
        TutorialLayer->addChild(spr_continue);
        
        auto Deltime = DelayTime::create(3.0);
        auto showMenu = Show::create();
        auto setTab = CallFunc::create(CC_CALLBACK_0(GameScene::SetTabTouch, this));
        auto fdIn = FadeIn::create(1.0);
        auto menuseq = Sequence::create(Deltime,setTab,showMenu,fdIn, NULL);
        spr_continue->runAction(menuseq);
        
    }
}
void GameScene::SetTabTouch()
{
    isTutorialTab = true;
}
void GameScene::TutorialEnd()
{
    auto rlabel = (Label*)TutorialLayer->getChildByTag(LABELTAG2);
    auto fd = FadeOut::create(1.0);
    rlabel->runAction(fd);
    
    auto conbutton = (Menu*)TutorialLayer->getChildByTag(CONTINUEBUTTON);
    auto fd2 = FadeOut::create(1.0);
    conbutton->runAction(fd2);
    
    auto hand = (Sprite*)TutorialLayer->getChildByTag(HAND);
    auto fd3 = FadeOut::create(1.0);
    hand->runAction(fd3);
    std::string str_text = StringUtils::format("종말의 화살표가 한 종족의 승리를 알리는 순간\n세계는 무너지고 맙니다.\n이 세계를 위해서  균형을 유지해 주세요.");
    auto textLabel1 = Label::createWithTTF(str_text, fontList[0], 28, Size::ZERO, TextHAlignment::CENTER, TextVAlignment::CENTER);
    textLabel1->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 377));
    textLabel1->setOpacity(0);
    TutorialLayer->addChild(textLabel1,1);
    
    auto actionfdIn = FadeIn::create(1.0);
    auto actionDel = DelayTime::create(2.0);
    auto actionfdOut = FadeOut::create(1.0);
    auto actiontouch = CallFunc::create(CC_CALLBACK_0(GameScene::TutorialReset, this));
    auto seq = Sequence::create(DelayTime::create(1.0), actionfdIn, actionDel, actionfdOut, actiontouch, NULL);
    textLabel1->runAction(seq);
}
void GameScene::TutorialReset()
{
    TutorialLayer->removeAllChildren();
    isTouchEnable = true;
}
void GameScene::TouchEnable()
{
    isTouchEnable = true;
}
void GameScene::RightArrow()
{
    sprintf(_str,"twoworld/tuto_arrow.png");
    auto spr_arrow = Sprite::create(_str);
    spr_arrow->setPosition(VisibleSize.width/2,VisibleSize.height/2 - 232);
    TutorialLayer->addChild(spr_arrow);
    
    sprintf(_str,"twoworld/tuto_touch1.png");
    auto spr_touch = Sprite::create(_str);
    spr_touch->setPosition(VisibleSize.width/2 - 240,VisibleSize.height/2 - 232);
    spr_touch->setTag(HANDTOUCH);
    TutorialLayer->addChild(spr_touch);
    
    auto setPositionAction = Place::create(Point(VisibleSize.width/2 - 240,VisibleSize.height/2 - 232));
    auto delAction = DelayTime::create(0.2);
    auto setArrow = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite, this));
    auto moveAction = MoveTo::create(1.0, Point(VisibleSize.width/2 + 240, VisibleSize.height/2 - 232));
    auto setArrow2 = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite2, this));
    auto seq = Sequence::create(setPositionAction,delAction,setArrow,moveAction,setArrow2,delAction, NULL);
    auto rpAction = RepeatForever::create(seq);
    spr_touch->runAction(rpAction);
}
void GameScene::LeftArrow()
{
    sprintf(_str,"twoworld/tuto_arrow.png");
    auto spr_arrow = Sprite::create(_str);
    spr_arrow->setPosition(VisibleSize.width/2,VisibleSize.height/2 - 232);
    spr_arrow->setRotation(180);
    TutorialLayer->addChild(spr_arrow);
    
    sprintf(_str,"twoworld/tuto_touch1.png");
    auto spr_touch = Sprite::create(_str);
    spr_touch->setPosition(VisibleSize.width/2 + 240,VisibleSize.height/2 - 232);
    spr_touch->setTag(HANDTOUCH);
    TutorialLayer->addChild(spr_touch);
    
    auto setPositionAction = Place::create(Point(VisibleSize.width/2 + 240,VisibleSize.height/2 - 232));
    auto delAction = DelayTime::create(0.2);
    auto setArrow = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite, this));
    auto moveAction = MoveTo::create(1.0, Point(VisibleSize.width/2 - 240, VisibleSize.height/2 - 232));
    auto setArrow2 = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite2, this));
    auto seq = Sequence::create(setPositionAction,delAction,setArrow,moveAction,setArrow2,delAction, NULL);
    auto rpAction = RepeatForever::create(seq);
    spr_touch->runAction(rpAction);
}
void GameScene::UpArrow()
{
    sprintf(_str,"twoworld/tuto_arrow.png");
    auto spr_arrow = Sprite::create(_str);
    spr_arrow->setPosition(VisibleSize.width/2,VisibleSize.height/2 - 232);
    spr_arrow->setRotation(270);
    TutorialLayer->addChild(spr_arrow);
    
    sprintf(_str,"twoworld/tuto_touch1.png");
    auto spr_touch = Sprite::create(_str);
    spr_touch->setPosition(VisibleSize.width/2,VisibleSize.height/2 - 472);
    spr_touch->setTag(HANDTOUCH);
    TutorialLayer->addChild(spr_touch);
    
    auto setPositionAction = Place::create(Point(VisibleSize.width/2,VisibleSize.height/2 - 472));
    auto delAction = DelayTime::create(0.2);
    auto setArrow = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite, this));
    auto moveAction = MoveTo::create(1.0, Point(VisibleSize.width/2, VisibleSize.height/2 + 8));
    auto setArrow2 = CallFunc::create(CC_CALLBACK_0(GameScene::SetTouchSprite2, this));
    auto seq = Sequence::create(setPositionAction,delAction,setArrow,moveAction,setArrow2,delAction, NULL);
    auto rpAction = RepeatForever::create(seq);
    spr_touch->runAction(rpAction);
}
void GameScene::LabelRemove()
{
    auto rlabel = (Label*)TutorialLayer->getChildByTag(LABELTAG);
    auto fd = FadeOut::create(1.0);
    auto callTuto = CallFunc::create(CC_CALLBACK_0(GameScene::TutorialGuide, this));
    auto seq = Sequence::create(fd, callTuto, NULL);
    rlabel->runAction(seq);
}
void GameScene::SetTouchSprite()
{
    auto spr_touch = (Sprite*)TutorialLayer->getChildByTag(HANDTOUCH);
    
    sprintf(_str,"twoworld/tuto_touch2.png");
    spr_touch->setTexture(_str);
    
}
void GameScene::SetTouchSprite2()
{
    auto spr_touch = (Sprite*)TutorialLayer->getChildByTag(HANDTOUCH);
    
    sprintf(_str,"twoworld/tuto_touch1.png");
    spr_touch->setTexture(_str);
    
}
void GameScene::MapInit()
{
    int loopCount = 0;
    newNum = 0;
    touchcount = 0;
    curBestNum = 0;
    mapRatio = 0;
    guideMapRatio = 0;
    killScore = 0;
    newBlockScore = 0;
    turnScore = 0;
    gameOverRatio = 100;
    isTouchEnd = false;
    for(int i=0;i<MAXROW;i++)
    {
        for(int j=0;j<MAXCOL;j++)
        {
            map[i][j].num = 0;
            map[i][j].tileScore = 0;
        }
    }
    for(int i=0;i<MAXROW;i++)
    {
        for(int j=0;j<MAXCOL;j++)
        {
            loopCount++;
            if(loopCount>=9)
                break;
            while(loopCount)
            {
                int ranRow;
                int ranCol;
                while(1)
                {
                    ranRow = random(0,MAXROW-1);
                    ranCol = random(0,MAXCOL-1);
                    if(map[ranRow][ranCol].num==0)
                    {
                        break;
                    }
                }
                if(loopCount<=4)
                {
                    map[ranRow][ranCol].color = RED;
                    map[ranRow][ranCol].unitState = idle;
                    map[ranRow][ranCol].num = 1;
                    map[ranRow][ranCol].tileScore = 3;
                    break;
                }
                else if(loopCount<=8)
                {
                    map[ranRow][ranCol].color = BLUE;
                    map[ranRow][ranCol].unitState = idle;
                    map[ranRow][ranCol].num = 1;
                    map[ranRow][ranCol].tileScore = 3;
                    break;
                }
            }
        }
    }
    
}
void GameScene::StartBlackfx()
{
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setPosition(VisibleSize.width/2,VisibleSize.height/2);
    this->addChild(sp_black,10);
    
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2 - 888,VisibleSize.height/2));
    
    sp_black->runAction(action);
}

void GameScene::Blackfx(Ref *sender)
{
    SoundManager::PlaySound("twoworld_snd/button.wav");
    auto a = (MenuItem*)sender;
    
    sprintf(_str,"twoworld/bg_black.png");
    auto sp_black = Sprite::create(_str);
    sp_black->setTag(a->getTag());
    sp_black->setPosition(VisibleSize.width + 888,VisibleSize.height/2);
    this->addChild(sp_black,10);
    auto action = MoveTo::create(0.5, Point(VisibleSize.width/2,VisibleSize.height/2));
    auto changeaction = CallFuncN::create(CC_CALLBACK_1(GameScene::ChangeScene, this));
    
    
    auto seq = Sequence::create(action, changeaction, NULL);
    sp_black->runAction(seq);

}
void GameScene::PinDraw()
{
    PinLayer->removeAllChildren();
    sprintf(_str,"twoworld/gauge_bar.png");
    
    auto img_gaugeBar = Sprite::create(_str);
    img_gaugeBar->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 196);
    img_gaugeBar->setAnchorPoint(Point(0.5,0.0));
    img_gaugeBar->setOpacity(0);
    PinLayer->addChild(img_gaugeBar,1);
    
    Size BarSize = img_gaugeBar->getContentSize();
    float ratio = (BarSize.width/2) / 100;
    
    sprintf(_str,"twoworld/gauge_pin.png");
    auto img_gaugePin = Sprite::create(_str);
    img_gaugePin->setPosition(Point(BarSize.width/2 - (beforeMapRatio * ratio),BarSize.height/2 - 29));
    img_gaugePin->setOpacity(0);
    img_gaugeBar->addChild(img_gaugePin);
    
   
    if(beforeMapRatio - guideMapRatio > 1
       || beforeMapRatio - guideMapRatio < -1)
    {
        if(moveMap)
        {
            sprintf(_str,"twoworld/guide_pin.png");
            auto img_guidePin = Sprite::create(_str);
            img_guidePin->setPosition(Point(BarSize.width/2 - (guideMapRatio * ratio),BarSize.height/2));
            
            img_gaugeBar->addChild(img_guidePin,1);
            auto actionout = FadeTo::create(0.2, 128);
            auto actionin = FadeTo::create(0.2, 255);
            auto seq = Sequence::create(actionout,actionin,actionout,actionin,actionout,actionin,actionout,actionin,actionout,actionin, NULL);
            img_guidePin->runAction(seq);
        }
    }
    
    
}

void GameScene::removePinLayer()
{
    PinLayer->removeAllChildren();
    
    isTouchEnd = false;
    isTouchCancel = false;
}
void GameScene::CreateTile()
{
    int dontmove = 0;
    if(isGameOver)
    {
        SoundManager::PlaySound("twoworld_snd/button.wav");
        sprintf(_str,"twoworld/bg_black.png");
        auto sp_black = Sprite::create(_str);
        sp_black->setPosition(VisibleSize.width + 888,VisibleSize.height/2);
        this->addChild(sp_black,5);
        auto Delaction = DelayTime::create(0.3);
        auto action = MoveTo::create(0.5, Point(VisibleSize.width/2,VisibleSize.height/2));
        auto changeaction = CallFunc::create(CC_CALLBACK_0(GameScene::GameOverView,this));
        auto seq = Sequence::create(Delaction,action, changeaction, NULL);
        sp_black->runAction(seq);
    }
    else
    {
        TileLayer->removeAllChildren();
        for(int i = 0 ; i < MAXROW; i++)
        {
            for(int j = 0 ; j < MAXCOL; j++)
            {
                if(map[i][j].num == 0 && map[i][j].isMove == false)
                {
                    dontmove++;
                }
                if(map[i][j].num > 0 && map[i][j].num <=12)
                {
                    if(map[i][j].color == RED)
                    {
                        if(map[i][j].unitState == idle)
                            sprintf(_str, "twoworld/red_tile%d_1.png", map[i][j].num);
                        else if(map[i][j].unitState == attack)
                            sprintf(_str, "twoworld/red_tile%d_2.png", map[i][j].num);
                        else if(map[i][j].unitState == damage)
                            sprintf(_str, "twoworld/red_tile%d_3.png", map[i][j].num);
                    }
                    else if(map[i][j].color == BLUE)
                    {
                        if(map[i][j].unitState == idle)
                            sprintf(_str, "twoworld/blue_tile%d_1.png", map[i][j].num);
                        else if(map[i][j].unitState == attack)
                            sprintf(_str, "twoworld/blue_tile%d_2.png", map[i][j].num);
                        else if(map[i][j].unitState == damage)
                            sprintf(_str, "twoworld/blue_tile%d_3.png", map[i][j].num);
                    }
                    else if(map[i][j].color == OBSTACLE)
                    {
                        if(map[i][j].unitState == idle)
                            sprintf(_str, "twoworld/gray_tile%d_1.png", map[i][j].num);
                        else if(map[i][j].unitState == damage)
                            sprintf(_str, "twoworld/gray_tile%d_3.png", map[i][j].num);
                    }
                    float _x;
                    float _y;
                    
                    float _tempX;
                    float _tempY;
                    
                    auto img_Tile = Sprite::create(_str);
                    if(moveMap)
                    {
                        if(map[i][j].isMove)
                        {
                            _x = VisibleSize.width/2 - TIlESIZE/2 - followPos.x + i * TIlESIZE;
                            _y = VisibleSize.height/2 - TILESETY - TIlESIZE + TIlESIZE/2 + followPos.y - j * TIlESIZE;
                            
                            img_Tile->setPosition(_x, _y);
                            TileLayer->addChild(img_Tile, 3);
                        }
                        else
                        {
                            
                            
                            _x = VisibleSize.width/2 - TIlESIZE - TIlESIZE/2 + i * TIlESIZE;
                            _y = VisibleSize.height/2 - TILESETY + TIlESIZE/2 - j * TIlESIZE;
                            img_Tile->setPosition(_x, _y);
                            TileLayer->addChild(img_Tile, 2);
                            if(map[i][j].is_fxfusion)
                            {
                                sprintf(_str,"twoworld/fx_fusion.png");
                                auto img_Fusion = Sprite::create(_str);
                                img_Fusion->setPosition(img_Tile->getPosition());
                                TileLayer->addChild(img_Fusion,10);
                                img_Fusion->runAction(FadeOut::create(0.3));
                                map[i][j].is_fxfusion = false;
                            }
                            if(map[i][j].is_fxattack)
                            {
                                sprintf(_str,"twoworld/fx_attack.png");
                                auto img_Attack = Sprite::create(_str);
                                img_Attack->setPosition(img_Tile->getPosition());
                                TileLayer->addChild(img_Attack,1);
                                img_Attack->runAction(ScaleTo::create(0.3,0.6));
                                map[i][j].is_fxattack = false;
                            }
                        }
                    }
                    else
                    {
                        if(map[i][j].isMove)
                        {
                            if(!isAddMoveMap)
                            {
                                
                                _x = VisibleSize.width/2 - followPos.x - TIlESIZE/2 + i * TIlESIZE;
                                _y = VisibleSize.height/2 - TILESETY - TIlESIZE + followPos.y + TIlESIZE/2 - j * TIlESIZE;
                                
                                img_Tile->setPosition(_x, _y);
                                TileLayer->addChild(img_Tile, 2);
                                
                                _tempX = VisibleSize.width/2  - TIlESIZE/2 - TIlESIZE + i * TIlESIZE;
                                _tempY = VisibleSize.height/2  - TILESETY + TIlESIZE/2 - j * TIlESIZE;
                                
                                auto TileAction = MoveTo::create( 0.1, Point(_tempX,_tempY));
                                img_Tile->runAction(TileAction);
                                
                                if(touchDirection == 0)
                                {
                                    if(!isTouchCancel)
                                        isTouchCancel = true;
                                }
                            }
                            else
                            {
                                _x = VisibleSize.width/2  - TIlESIZE/2 - followPos.x + i * TIlESIZE;
                                _y = VisibleSize.height/2 - TILESETY - TIlESIZE + TIlESIZE/2 + followPos.y - j * TIlESIZE;
                                
                                img_Tile->setPosition(_x, _y);
                                TileLayer->addChild(img_Tile, 2);
                                
                                _tempX = VisibleSize.width/2 - TIlESIZE/2 - otherPos.x + i * TIlESIZE;
                                _tempY = VisibleSize.height/2 - TILESETY - TIlESIZE + TIlESIZE/2 + otherPos.y - j * TIlESIZE;
                                
                              
                               
                                auto tileAction = MoveTo::create(0.1, Point(_tempX, _tempY));
                                auto tileSet= CallFunc::create(CC_CALLBACK_0(GameScene::DirectionMap,this));
                                
                                auto actionSeq = Sequence::create(tileAction,tileSet, NULL);
                                
                                img_Tile->runAction(actionSeq);
                            }
                            
                            
                        }
                        else
                        {
                            dontmove ++;
                            if(dontmove >= 16)
                            {
                                SoundManager::PlaySound("twoworld_snd/dontmove.wav");
                                dontmove = 0;
                            }
                            _x = VisibleSize.width/2 - TIlESIZE/2 - TIlESIZE + i * TIlESIZE;
                            _y = VisibleSize.height/2 - TILESETY + TIlESIZE/2 - j * TIlESIZE;
                            
                            img_Tile->setPosition(_x, _y);
                            TileLayer->addChild(img_Tile, 1);
                            
                            if(touchDirection == 0)
                            {
                                if(!isTouchCancel)
                                    isTouchCancel = true;
                            }
                            
                        }
                    }
                }
            }
        }
        
        UIView();
    }
    
}
void GameScene::UIView()
{
    UILayer->removeAllChildren();
    topPinLayer->removeAllChildren();
    if(nextBlock == RED)
        sprintf(_str,"twoworld/next_orc.png");
    if(nextBlock == BLUE)
        sprintf(_str,"twoworld/next_human.png");
    if(nextBlock == OBSTACLE)
        sprintf(_str,"twoworld/gray_tile1_1.png");
    
    auto img_nextBlock = Sprite::create(_str);
    float _x = VisibleSize.width/2 + NEXTTILESIZE/2;
    float _y = VisibleSize.height - NEXTTILESIZE * 2;
    
    img_nextBlock->setAnchorPoint(Point(1.0,0.5));
    if(isUINext)
    {
        if(beforeBlock == RED)
            sprintf(_str,"twoworld/next_orc.png");
        if(beforeBlock == BLUE)
            sprintf(_str,"twoworld/next_human.png");
        if(beforeBlock == OBSTACLE)
            sprintf(_str,"twoworld/gray_tile1_1.png");
        auto img_beforBlock = Sprite::create(_str);
        img_beforBlock->setAnchorPoint(Point(1.0,0.5));
        img_beforBlock->setPosition(_x,_y);
        UILayer->addChild(img_beforBlock,1);
        auto slideAction = ScaleTo::create(0.0,0.0,1.0);
        auto slideAction2 = ScaleTo::create(0.2,1.0,1.0);
        auto seq = Sequence::create(slideAction,slideAction2, NULL);
        img_nextBlock->runAction(seq);
        isUINext = false;
        
        BubbleLayer->removeAllChildren();
        if((int)mapRatio > 0)
        {
            sprintf(_str,"twoworld/bubble_orc.png");
            auto img_orcBubble = Sprite::create(_str);
            img_orcBubble->setAnchorPoint(Point(0.5,0.0));
            img_orcBubble->setPosition(Point(VisibleSize.width/2 - 246,VisibleSize.height/2 + 256));
            BubbleLayer->addChild(img_orcBubble,1);
            
            auto actionScale = ScaleTo::create(0.0, 1.0,0.0);
            auto actionScale2 = ScaleTo::create(0.2, 1.0,1.0);
            
            auto actionDelay = DelayTime::create(1.0);
            auto actionScale3 = ScaleTo::create(0.1, 1.0,0.0);
            auto seq = Sequence::create(actionScale,actionScale2,actionDelay,actionScale3, NULL);
            img_orcBubble->runAction(seq);
        }
        if((int)mapRatio < 0)
        {
            sprintf(_str,"twoworld/bubble_human.png");
            auto img_humanBubble = Sprite::create(_str);
            img_humanBubble->setAnchorPoint(Point(0.5,0.0));
            img_humanBubble->setPosition(Point(VisibleSize.width/2 + 246,VisibleSize.height/2 + 256));
            BubbleLayer->addChild(img_humanBubble,1);
            
            auto actionScale = ScaleTo::create(0.0, 1.0,0.0);
            auto actionScale2 = ScaleTo::create(0.2, 1.0,1.0);
            auto actionDelay = DelayTime::create(1.0);
            auto actionScale3 = ScaleTo::create(0.1, 1.0,0.0);
            auto seq = Sequence::create(actionScale,actionScale2,actionDelay,actionScale3, NULL);
            img_humanBubble->runAction(seq);
        }
    }
    img_nextBlock->setPosition(_x, _y);
    UILayer->addChild(img_nextBlock,1);
    
    std::string str_score = StringUtils::format("Score : %d", turnScore);
    auto underscoreLabel = Label::createWithTTF(str_score, fontList[0], 40);
    underscoreLabel->setAnchorPoint(Point(0.5,0.0));
    underscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 393));
    underscoreLabel->setColor(Color3B(0,0,0));
    UILayer->addChild(underscoreLabel,1);
    
    auto scoreLabel = Label::createWithTTF(str_score, fontList[0], 40);
    scoreLabel->setAnchorPoint(Point(0.5,0.0));
    scoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 397));
    UILayer->addChild(scoreLabel,1);
    
    std::string str_highscore = StringUtils::format("High score : %d", GM::Getinstance()->highScore);
    auto underhighscoreLabel = Label::createWithTTF(str_highscore, fontList[0], 30);
    underhighscoreLabel->setAnchorPoint(Point(0.5,0.0));
    underhighscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 444));
    underhighscoreLabel->setColor(Color3B(0,0,0));
    UILayer->addChild(underhighscoreLabel,1);
    
    auto highscoreLabel = Label::createWithTTF(str_highscore, fontList[0], 30);
    highscoreLabel->setAnchorPoint(Point(0.5,0.0));
    highscoreLabel->setPosition(Point(VisibleSize.width/2,VisibleSize.height/2 + 448));
    highscoreLabel->setColor(Color3B(255,76,76));
    UILayer->addChild(highscoreLabel,1);
    
    sprintf(_str,"twoworld/gauge_bar.png");
    
    auto img_gaugeBar = Sprite::create(_str);
    img_gaugeBar->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 196);
    img_gaugeBar->setAnchorPoint(Point(0.5,0.0));
    img_gaugeBar->setOpacity(0);
    img_gaugeBar->setTag(1000);
    topPinLayer->addChild(img_gaugeBar,1);
    
    auto img_gaugeBar2 = Sprite::create(_str);
    img_gaugeBar2->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 196);
    img_gaugeBar2->setAnchorPoint(Point(0.5,0.0));
    UILayer->addChild(img_gaugeBar2,1);
    
    sprintf(_str,"twoworld/orcgauge_bar.png");
    auto img_orcbar = Sprite::create(_str);
    BarSize = img_gaugeBar2->getContentSize();
    float ratio = (BarSize.width/2) / 100;
    img_orcbar->setAnchorPoint(Point(0,0));
    img_orcbar->setScaleX((BarSize.width/2 - gameOverRatio * ratio)/(BarSize.width/2));
    img_orcbar->setPosition(0,0);
    img_gaugeBar2->addChild(img_orcbar);
    
    sprintf(_str,"twoworld/humangauge_bar.png");
    auto img_humanbar = Sprite::create(_str);
    img_humanbar->setAnchorPoint(Point(1.0,0));
    img_humanbar->setScaleX((BarSize.width/2 - gameOverRatio * ratio)/(BarSize.width/2));
    img_humanbar->setPosition(BarSize.width,0);
    img_gaugeBar2->addChild(img_humanbar);
    
    
    sprintf(_str,"twoworld/gauge_pin.png");
    auto img_gaugePin = Sprite::create(_str);
    img_gaugePin->setPosition(Point(BarSize.width/2 - (beforeMapRatio * ratio),BarSize.height/2 - 29));
    img_gaugePin->setTag(PINTAG);
    auto action = MoveTo::create(0.2, Point(BarSize.width/2 - (mapRatio * ratio),BarSize.height/2 - 29));
    if(isTouchEnd)
    {
        auto removeAction = CallFunc::create(CC_CALLBACK_0(GameScene::removePinLayer,this));
        auto actionSeq = Sequence::create(NULL);
        if(mapRatio <= - gameOverRatio || mapRatio >= gameOverRatio)     //휴먼
        {
            auto removeAction = CallFunc::create(CC_CALLBACK_0(GameScene::removePinLayer,this));
            
           
            auto pinAction = CallFunc::create(CC_CALLBACK_0(GameScene::GameOverPinPlus,this));
            actionSeq = Sequence::create(action,pinAction,removeAction, NULL);
        }
        else
        {
            actionSeq = Sequence::create(action,removeAction, NULL);
        }
        
        img_gaugePin->runAction(actionSeq);
    }
    if(isTouchCancel)
    {
        removePinLayer();
    }

    img_gaugeBar->addChild(img_gaugePin,2);

    std::string str_ratio = StringUtils::format("%d", (int)mapRatio * -1);
    auto ratioLabel = Label::createWithTTF(str_ratio, fontList[0], 20);
    Size PinSize = img_gaugePin->getContentSize();
    ratioLabel->setAnchorPoint(Point(0.5,0.0));
    ratioLabel->setPosition(Point(PinSize.width/2,22));
    ratioLabel->setColor(Color3B(0,0,0));
    img_gaugePin->addChild(ratioLabel);
    
    sprintf(_str,"twoworld/orcface1.png");
    auto img_orcFace = Sprite::create(_str);
    
    sprintf(_str,"twoworld/humanface1.png");
    auto img_humanFace = Sprite::create(_str);
    if(gameOverRatio/3 > gameOverRatio - mapRatio)
    {
        if(!isbgmcheck)
        {
            SoundManager::ResumeBGM(GM::Getinstance()->BGM3);
            SoundManager::PauseBGM(GM::Getinstance()->BGM1);
            
            isbgmcheck = true;
            isobgm = true;
            ishbgm = false;
        }
        sprintf(_str,"twoworld/orcface2.png");
        img_orcFace = Sprite::create(_str);
        sprintf(_str,"twoworld/humanface3.png");
        img_humanFace = Sprite::create(_str);
    }
    
    else if(- gameOverRatio/3 < - mapRatio - gameOverRatio)
    {
        if(!isbgmcheck)
        {
            SoundManager::ResumeBGM(GM::Getinstance()->BGM2);
            SoundManager::PauseBGM(GM::Getinstance()->BGM1);
            isbgmcheck = true;
            ishbgm = true;
            isobgm = false;
        }
        sprintf(_str,"twoworld/humanface2.png");
        img_humanFace = Sprite::create(_str);
        sprintf(_str,"twoworld/orcface3.png");
        img_orcFace = Sprite::create(_str);
    }
    else
    {
        if(isbgmcheck)
        {
            SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
            
            if(isobgm)
            {
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
                isobgm = false;
            }
            if(ishbgm)
            {
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
                ishbgm = false;
            }
            isbgmcheck = false;
        }
    }
    img_orcFace->setAnchorPoint(Point(0.5,0.0));
    img_orcFace->setPosition(Point(VisibleSize.width/2 - 246,VisibleSize.height/2 + 164));
    UILayer->addChild(img_orcFace,1);
    img_humanFace->setAnchorPoint(Point(0.5,0.0));
    img_humanFace->setPosition(Point(VisibleSize.width/2 + 246,VisibleSize.height/2 + 164));
    UILayer->addChild(img_humanFace,1);
    
    auto RetryButton = MenuItemImage::create("twoworld/b_retry.png","twoworld/b_retry_push.png",CC_CALLBACK_1(GameScene::Blackfx, this));
    RetryButton->setTag(START);
    auto pRetryMenu = Menu::create(RetryButton,NULL);
    RetryButton->setAnchorPoint(Point(0.0,0.0));
    pRetryMenu->setPosition(VisibleSize.width/2 + 158,VisibleSize.height/2 + 480);
    UILayer->addChild(pRetryMenu);
    
    auto BackButton = MenuItemImage::create("twoworld/b_back.png","twoworld/b_back_push.png",CC_CALLBACK_1(GameScene::Blackfx, this));
    BackButton->setTag(INTRO);
    auto pBackMenu = Menu::create(BackButton,NULL);
    BackButton->setAnchorPoint(Point(0.0,0.0));
    pBackMenu->setPosition(VisibleSize.width/2 - 304,VisibleSize.height/2 + 480);
    UILayer->addChild(pBackMenu);
    
}
void GameScene::GameOverPinPlus()
{
    float ratio = (BarSize.width/2) / 100;
    
    auto img_gaugeBar = (Sprite*)topPinLayer->getChildByTag(1000);
    img_gaugeBar->setPosition(VisibleSize.width/2,VisibleSize.height/2 + 196);
    sprintf(_str,"twoworld/fx_pin1.png");
    auto img_fxPin = Sprite::create(_str);
    img_fxPin->setAnchorPoint(Point(0.5,0.5));
    img_fxPin->setPosition(Point(BarSize.width/2 - (mapRatio * ratio),BarSize.height/2 - 22));
    img_gaugeBar->addChild(img_fxPin,3);
    auto animation = Animation::create();
    animation->setDelayPerUnit(0.06);
    for(int i=1;i<=6;i++)
    {
        animation->addSpriteFrameWithFile(StringUtils::format("twoworld/fx_pin%d.png",i));
    }
     auto animate = Animate::create(animation);
    img_fxPin->runAction(animate);
}
void GameScene::GameOverView()
{
    GM::Getinstance()->turnScore = this->turnScore;
    GM::Getinstance()->mapRatio = this->mapRatio;
    GM::Getinstance()->gameOverRatio = this->gameOverRatio;
    
    Director::getInstance()->replaceScene(GameOverScene::createScene());
}
void GameScene::ChangeScene(Ref *sender)
{
    auto menuItem = (MenuItem*)sender;
    switch (menuItem->getTag())
    {
        case INTRO:
        {
            Director::getInstance()->replaceScene(IntroScene::createScene());
            
            if(ishbgm)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
            }
            if(isobgm)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
            }
            
        }
            break;
        case START:
        {
            Director::getInstance()->replaceScene(GameScene::createScene());
            if(ishbgm)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM2);
            }
            if(isobgm)
            {
                SoundManager::ResumeBGM(GM::Getinstance()->BGM1);
                SoundManager::PauseBGM(GM::Getinstance()->BGM3);
            }
        }
            break;
    }
}
void GameScene::TouchDirectionCheck(Vec2 touchPoint)
{
    if(dir != UP && dir != LEFT && dir != RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 2 && nextDesicion!= 1)
    {
        if(beforeTouch.y-touchPoint.y >= TIlESIZE/2)
        {
            touchDirection = DOWN;
            isAddMoveMap = true;
            
            otherPos.x = TIlESIZE;
            otherPos.y = 0;
        }
        else
        {
            isAddMoveMap = false;
            touchDirection = NULL;
        }
    }
    
    if(dir != DOWN && dir != LEFT && dir !=RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 2)
    {
        if(touchPoint.y-beforeTouch.y >= TIlESIZE/2)
        {
            touchDirection = UP;
            isAddMoveMap = true;
            
            otherPos.x = TIlESIZE;
            otherPos.y = TIlESIZE*2;
        }
        else
        {
            touchDirection = NULL;
            isAddMoveMap = false;
        }
    }
    
    if(dir != DOWN && dir != UP && dir !=RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 1)
    {
        if(beforeTouch.x-touchPoint.x >= TIlESIZE/2)
        {
            touchDirection = LEFT;
            isAddMoveMap = true;
            
            otherPos.x = TIlESIZE*2;
            otherPos.y = TIlESIZE;
        }
        else
        {
            touchDirection = NULL;
            isAddMoveMap = false;
        }
    }
    
    if(dir != DOWN && dir != UP && dir != LEFT
       && nextDesicion!= 2 && nextDesicion!= 1)
    {
        if(touchPoint.x-beforeTouch.x >= TIlESIZE/2)
        {
            touchDirection = RIGHT;
            isAddMoveMap = true;
            
            otherPos.x = 0;
            otherPos.y = TIlESIZE;
        }
        else
        {
            touchDirection = NULL;
            isAddMoveMap = false;
        }
    }
    
}
void GameScene::MoveTouchDirectionCheck(Vec2 touchPoint)
{
    if(dir != UP && dir != LEFT && dir != RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 2 && nextDesicion!= 1)
    {
        if(beforeTouch.y-touchPoint.y >= TIlESIZE/4)
        {
            followPos.y = -(beforeTouch.y-touchPoint.y) + TIlESIZE;
            if(followPos.y < 0)
                followPos.y = 0;
            followPos.x = TIlESIZE;
            touchDirection = DOWN;
            dir = DOWN;
        }
        else
        {
            followPos.x = 0; followPos.y = 0;
            
            touchDirection = NULL;
        }
    }
    if(dir != DOWN && dir != LEFT && dir !=RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 2)
    {
        if(touchPoint.y-beforeTouch.y >= TIlESIZE/4)
        {
            followPos.y = touchPoint.y-beforeTouch.y + TIlESIZE;
            if(followPos.y > TIlESIZE*2)
                followPos.y = TIlESIZE*2;
            followPos.x = TIlESIZE;
            touchDirection = UP;
            dir = UP;
        }
        else
        {
            followPos.x = 0; followPos.y = 0;
            touchDirection = NULL;
        }
    }
    if(dir != DOWN && dir != UP && dir !=RIGHT
       && nextDesicion!= 4 && nextDesicion!= 3 && nextDesicion!= 1)
    {
        if(beforeTouch.x-touchPoint.x >= TIlESIZE/4)
        {
            followPos.x = beforeTouch.x-touchPoint.x + TIlESIZE;
            if(followPos.x > TIlESIZE*2)
                followPos.x = TIlESIZE*2;
            followPos.y = TIlESIZE;
            touchDirection = LEFT;
            dir = LEFT;
        }
        else
        {
            followPos.x = 0; followPos.y = 0;
            touchDirection = NULL;
        }
    }
    if(dir != DOWN && dir != UP && dir !=LEFT
       && nextDesicion!= 2 && nextDesicion!= 1)
    {
        if(touchPoint.x-beforeTouch.x >= TIlESIZE/4)
        {
            followPos.x = -(touchPoint.x-beforeTouch.x) + TIlESIZE;
            if(followPos.x < 0)
                followPos.x = 0;
            followPos.y = TIlESIZE;
            touchDirection = RIGHT;
            dir = RIGHT;
        }
        else
        {
            followPos.x = 0; followPos.y = 0;
            touchDirection = NULL;
        }
    }

}

void GameScene::NotAddDirectionMap()
{
    isMoveAdd = false;
    memcpy(&movemap[0],&map[0],sizeof(map));

    for(int i = 0; i<MAXROW;i++)
    {
        for(int j=0;j<MAXCOL;j++)
        {
            map[i][j].isMove = false;
        }
    }
    switch (touchDirection)
    {
        case RIGHT:
        {
            for(int i = MAXROW-2; i >= 0; i--)
            {
                for(int j = 0; j < MAXCOL; j++)
                {
                    if(movemap[i + 1][j].num == 0
                       && movemap[i][j].num != 0)
                    {
                        movemap[i + 1][j].num = movemap[i][j].num;
                        movemap[i + 1][j].color = movemap[i][j].color;
                        movemap[i][j].num = 0;
                        movemap[i][j].color = NULL;
                        map[i][j].isMove = true;
                        isMoveAdd = true;
                    }
                    if(movemap[i + 1][j].num > 0)
                    {
                        if(movemap[i + 1][j].num < map[i][j].num
                           && movemap[i + 1][j].color == OBSTACLE
                           && movemap[i][j].color != OBSTACLE
                           && (movemap[i + 1][j].num + 1) <= MAXNUM)
                        {
                            map[i + 1][j].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i + 1][j].num = movemap[i][j].num;
                            movemap[i + 1][j].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                        }
                        else if(movemap[i + 1][j].num == movemap[i][j].num
                           && movemap[i + 1][j].color == movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i + 1][j].color != OBSTACLE
                           && (movemap[i + 1][j].num + 1) <= MAXNUM)
                        {
                            movemap[i + 1][j].num = movemap[i][j].num + 1;
                            movemap[i + 1][j].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                        else if(movemap[i + 1][j].num < movemap[i][j].num
                           && movemap[i + 1][j].color != movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i + 1][j].color != OBSTACLE
                           && (movemap[i + 1][j].num + 1) <= MAXNUM)
                        {
                            movemap[i + 1][j].num = movemap[i][j].num;
                            movemap[i + 1][j].color = movemap[i][j].color;
                            map[i + 1][j].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                    }
                    
                }
            }
        }
            break;
        case LEFT:
        {
            for(int i = 1; i < MAXROW; i++)
            {
                for(int j = 0; j < MAXCOL; j++)
                {
                    if(movemap[i - 1][j].num == 0
                       && movemap[i][j].num != 0)
                    {
                        movemap[i - 1][j].num = movemap[i][j].num;
                        movemap[i - 1][j].color = movemap[i][j].color;
                        movemap[i][j].num = 0;
                        movemap[i][j].color = NULL;
                        map[i][j].isMove = true;
                        isMoveAdd = true;
                    }
                    if(movemap[i - 1][j].num > 0)
                    {
                        if(movemap[i - 1][j].num < movemap[i][j].num
                                && movemap[i - 1][j].color == OBSTACLE
                                && movemap[i][j].color != OBSTACLE
                                && (movemap[i - 1][j].num + 1) <= MAXNUM)
                        {
                            map[i - 1][j].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i - 1][j].num = movemap[i][j].num;
                            movemap[i - 1][j].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                        }
                        else if(movemap[i - 1][j].num == movemap[i][j].num
                           && movemap[i - 1][j].color == movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i - 1][j].color != OBSTACLE
                           && (movemap[i - 1][j].num + 1) <= MAXNUM)
                        {
                            movemap[i - 1][j].num = movemap[i][j].num + 1;
                            movemap[i - 1][j].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                        else if(movemap[i - 1][j].num < movemap[i][j].num
                           && movemap[i - 1][j].color != movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i - 1][j].color != OBSTACLE
                           && (movemap[i - 1][j].num + 1) <= MAXNUM)
                        {
                            map[i - 1][j].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i - 1][j].num = movemap[i][j].num;
                            movemap[i - 1][j].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                    }
                }
            }
        }
            break;
        case UP:
        {
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = 1; j < MAXCOL; j++)
                {
                    if(movemap[i][j - 1].num == 0 && movemap[i][j].num != 0)
                    {
                        movemap[i][j - 1].num = movemap[i][j].num;
                        movemap[i][j - 1].color = movemap[i][j].color;
                        movemap[i][j].num = 0;
                        movemap[i][j].color = NULL;
                        map[i][j].isMove = true;
                        isMoveAdd = true;
                    }
                    if(movemap[i][j - 1].num > 0)
                    {
                        if(movemap[i][j - 1].num < movemap[i][j].num
                           && movemap[i][j - 1].color == OBSTACLE
                           && movemap[i][j].color != OBSTACLE
                           && (movemap[i][j - 1].num + 1) <= MAXNUM)
                        {
                            map[i][j - 1].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i][j - 1].num = movemap[i][j].num;
                            movemap[i][j - 1].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                        }
                        else if(movemap[i][j - 1].num == movemap[i][j].num
                           && movemap[i][j - 1].color == movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i][j - 1].color != OBSTACLE
                           && (movemap[i][j - 1].num + 1) <= MAXNUM)
                        {
                            movemap[i][j - 1].num = movemap[i][j].num + 1;
                            movemap[i][j - 1].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                        else if(movemap[i][j - 1].num < movemap[i][j].num
                           && movemap[i][j - 1].color != movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i][j - 1].color != OBSTACLE
                           && (movemap[i][j - 1].num + 1) <= MAXNUM)
                        {
                            map[i][j - 1].unitState = damage;
                            map[i][j].unitState = attack;                            movemap[i][j - 1].num = movemap[i][j].num;
                            movemap[i][j - 1].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                    }
                    
                }
            }
        }
            break;
            
        case DOWN:
        {
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = MAXCOL-2; j >= 0; j--)
                {
                    if(movemap[i][j + 1].num == 0
                       && movemap[i][j].num != 0)
                    {
                        movemap[i][j + 1].num = movemap[i][j].num;
                        movemap[i][j + 1].color = movemap[i][j].color;
                        movemap[i][j].num = 0;
                        movemap[i][j].color = NULL;
                        map[i][j].isMove = true;
                        isMoveAdd = true;
                    }
                    if(movemap[i][j + 1].num > 0)
                    {
                        if(movemap[i][j + 1].num < movemap[i][j].num
                           && movemap[i][j + 1].color == OBSTACLE
                           && movemap[i][j].color != OBSTACLE
                           && (movemap[i][j + 1].num + 1) <= MAXNUM)
                        {
                            map[i][j + 1].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i][j + 1].num = movemap[i][j].num;
                            movemap[i][j + 1].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                        }
                        else if(movemap[i][j + 1].num == movemap[i][j].num
                           && movemap[i][j + 1].color == movemap[i][j].color
                           && map[i][j].color != OBSTACLE && movemap[i][j + 1].color != OBSTACLE
                           && (movemap[i][j + 1].num + 1) <= MAXNUM)
                        {
                            movemap[i][j + 1].num = movemap[i][j].num + 1;
                            movemap[i][j + 1].color = movemap[i][j].color;
                            movemap[i][j + 1].unitState = idle;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                        else if(movemap[i][j + 1].num < movemap[i][j].num
                           && movemap[i][j + 1].color != movemap[i][j].color
                           && movemap[i][j].color != OBSTACLE && movemap[i][j + 1].color != OBSTACLE
                           && (movemap[i][j + 1].num + 1) <= MAXNUM)
                        {
                            map[i][j + 1].unitState = damage;
                            map[i][j].unitState = attack;
                            movemap[i][j + 1].num = movemap[i][j].num;
                            movemap[i][j + 1].color = movemap[i][j].color;
                            movemap[i][j].num = 0;
                            movemap[i][j].color = NULL;
                            map[i][j].isMove = true;
                            isMoveAdd = true;
                        }
                    }
                }
            }
        }
            break;
        default:
            break;
    }
    MoveTileScoreCarc();
    GuideOccupancyRatio();
    if(touchDirection)
    {
        if(!isPin)
            PinDraw();
        
        isPin = true;
    }
}
void GameScene::DirectionMap()
{
    bool isCheck = true;
    bool isAdd = false;
    switch (touchDirection)
    {
        case RIGHT:
        {
            for(int i = MAXROW-2; i >= 0; i--)
            {
                for(int j = 0; j < MAXCOL; j++)
                {
                    if(map[i + 1][j].num == 0
                       && map[i][j].num != 0)
                    {
                        map[i + 1][j].num = map[i][j].num;
                        map[i + 1][j].color = map[i][j].color;
                        map[i + 1][j].unitState = idle;
                        map[i][j].unitState = idle;
                        map[i][j].num = 0;
                        map[i][j].color = NULL;
                        isAdd = true;
                    }
                    if(map[i + 1][j].num > 0)
                    {
                        if(map[i + 1][j].num < map[i][j].num
                           && map[i + 1][j].color == OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i + 1][j].num + 1) <= MAXNUM)       //장애물
                        {
                            map[i + 1][j].num = map[i][j].num;
                            map[i + 1][j].color = map[i][j].color;
                            map[i + 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            isAdd = true;
                        }
                        else if(map[i + 1][j].num == map[i][j].num
                           && map[i + 1][j].color == map[i][j].color
                           && map[i + 1][j].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i + 1][j].num + 1) <= MAXNUM)      //같은수더하는구
                        {
                            map[i + 1][j].num = map[i][j].num + 1;
                            map[i + 1][j].color = map[i][j].color;
                            map[i + 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            newBlockScore += pow(3.0,map[i + 1][j].num - 1);
                            isAdd = true;
                            map[i + 1][j].is_fxfusion = true;
                            if(map[i + 1][j].color == RED)
                                SoundManager::PlaySound("twoworld_snd/oadd.WAV");
                            else
                                SoundManager::PlaySound("twoworld_snd/hadd.wav");
                        }
                        else if(map[i + 1][j].num < map[i][j].num
                           && map[i + 1][j].color != map[i][j].color
                           && map[i + 1][j].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i + 1][j].num + 1) <= MAXNUM)    //작은수
                        {
                            map[i + 1][j].num = map[i][j].num;
                            map[i + 1][j].color = map[i][j].color;
                            map[i + 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            killScore += pow(2.0,map[i + 1][j].num - 1);
                            killcount++;
                            isAdd = true;
                            map[i + 1][j].is_fxattack = true;
                            if(map[i + 1][j].color == RED)
                                SoundManager::PlaySound("twoworld_snd/hdie.wav");
                            else
                                SoundManager::PlaySound("twoworld_snd/odie.wav");
                        }
                    }
                    
                }
            }
            if(isAdd)
            {
                if(touchDirection!=0)
                    NextBlockDecision();
                while(isCheck)
                {
                    AddNewNum(MAXCOL);
                    if(map[0][newNumPos].num == 0)
                    {
                        isCheck=false;
                        break;
                    }
                    else
                        continue;
                }
                map[0][newNumPos].num = beforeNum;
                map[0][newNumPos].color = beforeBlock;
                isUINext = true;
                isTouchEnd = true;
                
                SoundManager::PlaySound("twoworld_snd/swipe.wav");
            }
            else
            {
                SoundManager::PlaySound("twoworld_snd/dontmove.wav");
            }
        }
            break;
        case LEFT:
        {
            for(int i = 1; i < MAXROW; i++)
            {
                for(int j = 0; j < MAXCOL; j++)
                {
                    if(map[i - 1][j].num == 0
                       && map[i][j].num != 0)
                    {
                        map[i - 1][j].num = map[i][j].num;
                        map[i - 1][j].color = map[i][j].color;
                        map[i - 1][j].unitState = idle;
                        map[i][j].unitState = idle;
                        map[i][j].num = 0;
                        map[i][j].color = NULL;
                        isAdd = true;
                    }
                    if(map[i - 1][j].num > 0)
                    {
                        if(map[i - 1][j].num < map[i][j].num
                           && map[i - 1][j].color == OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i - 1][j].num + 1) <= MAXNUM)
                        {
                            map[i - 1][j].num = map[i][j].num;
                            map[i - 1][j].color = map[i][j].color;
                            map[i - 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            isAdd = true;
                        }
                        else if(map[i - 1][j].num == map[i][j].num
                           && map[i - 1][j].color == map[i][j].color
                           && map[i - 1][j].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i - 1][j].num + 1) <= MAXNUM)
                        {
                            map[i - 1][j].num = map[i][j].num + 1;
                            map[i - 1][j].color = map[i][j].color;
                            map[i - 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            newBlockScore += pow(3.0,map[i - 1][j].num - 1);
                            isAdd = true;
                            
                            map[i - 1][j].is_fxfusion = true;
                            if(map[i - 1][j].color == RED)
                                SoundManager::PlaySound("twoworld_snd/oadd.WAV");
                            else
                                SoundManager::PlaySound("twoworld_snd/hadd.wav");
                        }
                        else if(map[i - 1][j].num < map[i][j].num
                           && map[i - 1][j].color != map[i][j].color
                           && map[i - 1][j].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i - 1][j].num + 1) <= MAXNUM)
                        {
                            map[i - 1][j].num = map[i][j].num;
                            map[i - 1][j].color = map[i][j].color;
                            map[i - 1][j].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            killScore += pow(2.0,map[i - 1][j].num - 1);
                            killcount++;
                            isAdd = true;
                            
                            map[i - 1][j].is_fxattack = true;
                            if(map[i - 1][j].color == RED)
                                SoundManager::PlaySound("twoworld_snd/hdie.wav");
                            else
                                SoundManager::PlaySound("twoworld_snd/odie.wav");
                        }
                    }
                }
            }
            if(isAdd)
            {
                if(touchDirection!=0)
                    NextBlockDecision();
                while(isCheck)
                {
                    AddNewNum(MAXCOL);
                    if(map[MAXROW - 1][newNumPos].num == 0)
                    {
                        isCheck=false;
                        break;
                    }
                    else
                        continue;
                }
                map[MAXROW - 1][newNumPos].num = beforeNum;
                map[MAXROW - 1][newNumPos].color = beforeBlock;
                isUINext = true;
                isTouchEnd = true;
                SoundManager::PlaySound("twoworld_snd/swipe.wav");
            }
            else
            {
                SoundManager::PlaySound("twoworld_snd/dontmove.wav");
            }
        }
            break;
        case UP:
        {
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = 1; j < MAXCOL; j++)
                {
                    if(map[i][j - 1].num == 0
                       && map[i][j].num != 0)
                    {
                        map[i][j - 1].num = map[i][j].num;
                        map[i][j - 1].color = map[i][j].color;
                        map[i][j - 1].unitState = idle;
                        map[i][j].unitState = idle;
                        map[i][j].num = 0;
                        map[i][j].color = NULL;
                        isAdd = true;
                    }
                    if(map[i][j - 1].num > 0)
                    {
                        if(map[i][j - 1].num < map[i][j].num
                           && map[i][j - 1].color == OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j - 1].num + 1) <= MAXNUM)
                        {
                            map[i][j - 1].num = map[i][j].num;
                            map[i][j - 1].color = map[i][j].color;
                            map[i][j - 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            isAdd = true;
                        }
                        else if(map[i][j - 1].num == map[i][j].num
                           && map[i][j - 1].color == map[i][j].color
                           && map[i][j - 1].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j - 1].num + 1) <= MAXNUM)
                        {
                            map[i][j - 1].num = map[i][j].num + 1;
                            map[i][j - 1].color = map[i][j].color;
                            map[i][j - 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            newBlockScore += pow(3.0,map[i][j - 1].num - 1);
                            isAdd = true;
                            
                            map[i][j - 1].is_fxfusion = true;
                            if(map[i][j - 1].color == RED)
                                SoundManager::PlaySound("twoworld_snd/oadd.WAV");
                            else
                                SoundManager::PlaySound("twoworld_snd/hadd.wav");
                        }
                        else if(map[i][j - 1].num < map[i][j].num
                           && map[i][j - 1].color != map[i][j].color
                           && map[i][j - 1].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j - 1].num + 1) <= MAXNUM)
                        {
                            map[i][j - 1].num = map[i][j].num;
                            map[i][j - 1].color = map[i][j].color;
                            map[i][j - 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            killScore += pow(2.0,map[i][j - 1].num - 1);
                            killcount++;
                            isAdd = true;
                            map[i][j - 1].is_fxattack = true;
                            if(map[i][j - 1].color == RED)
                                SoundManager::PlaySound("twoworld_snd/hdie.wav");
                            else
                                SoundManager::PlaySound("twoworld_snd/odie.wav");
                        }
                    }
                    
                }
            }
            if(isAdd)
            {
                if(touchDirection!=0)
                    NextBlockDecision();
                while(isCheck)
                {
                    AddNewNum(MAXROW);
                    if(map[newNumPos][MAXCOL-1].num == 0)
                    {
                        isCheck=false;
                        break;
                    }
                    else
                        continue;
                }
                map[newNumPos][MAXCOL-1].num = beforeNum;
                map[newNumPos][MAXCOL-1].color = beforeBlock;
                isUINext = true;
                isTouchEnd = true;
                
                SoundManager::PlaySound("twoworld_snd/swipe.wav");
            }
            else
                SoundManager::PlaySound("twoworld_snd/dontmove.wav");
        }
            break;
            
        case DOWN:
        {
            for(int i = 0; i < MAXROW; i++)
            {
                for(int j = MAXCOL-2; j >= 0; j--)
                {
                    if(map[i][j + 1].num == 0
                       && map[i][j].num != 0)
                    {
                        map[i][j + 1].num = map[i][j].num;
                        map[i][j + 1].color = map[i][j].color;
                        map[i][j + 1].unitState = idle;
                        map[i][j].unitState = idle;
                        map[i][j].num = 0;
                        map[i][j].color = NULL;
                        isAdd = true;
                    }
                    if(map[i][j + 1].num > 0)
                    {
                        if(map[i][j + 1].num < map[i][j].num
                           && map[i][j + 1].color == OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j + 1].num + 1) <= MAXNUM)
                        {
                            map[i][j + 1].num = map[i][j].num;
                            map[i][j + 1].color = map[i][j].color;
                            map[i][j + 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            isAdd = true;
                        }
                        else if(map[i][j + 1].num == map[i][j].num
                           && map[i][j + 1].color == map[i][j].color
                           && map[i][j + 1].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j + 1].num + 1) <= MAXNUM)
                        {
                            map[i][j + 1].num = map[i][j].num + 1;
                            map[i][j + 1].color = map[i][j].color;
                            map[i][j + 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            newBlockScore += pow(3.0,map[i][j + 1].num - 1);
                            
                            map[i][j + 1].is_fxfusion = true;
                            isAdd = true;
                            if(map[i][j + 1].color == RED)
                                SoundManager::PlaySound("twoworld_snd/oadd.WAV");
                            else
                                SoundManager::PlaySound("twoworld_snd/hadd.wav");
                        }
                        else if(map[i][j + 1].num < map[i][j].num
                           && map[i][j + 1].color != map[i][j].color
                           && map[i][j + 1].color != OBSTACLE
                           && map[i][j].color != OBSTACLE
                           && (map[i][j + 1].num + 1) <= MAXNUM)
                        {
                            map[i][j + 1].num = map[i][j].num;
                            map[i][j + 1].color = map[i][j].color;
                            map[i][j + 1].unitState = idle;
                            map[i][j].unitState = idle;
                            map[i][j].num = 0;
                            map[i][j].color = NULL;
                            
                            killScore += pow(2.0,map[i][j + 1].num - 1);
                            killcount++;
                            isAdd = true;
                            
                            map[i][j + 1].is_fxattack = true;
                            if(map[i][j + 1].color == RED)
                                SoundManager::PlaySound("twoworld_snd/hdie.wav");
                            else
                                SoundManager::PlaySound("twoworld_snd/odie.wav");
                        }
                    }
                    
                }
            }
            if(isAdd)
            {
                if(touchDirection!=0)
                    NextBlockDecision();
                while(isCheck)
                {
                    AddNewNum(MAXROW);
                    if(map[newNumPos][0].num == 0)
                    {
                        isCheck=false;
                        break;
                    }
                    else
                        continue;
                }
                map[newNumPos][0].num = beforeNum;
                map[newNumPos][0].color = beforeBlock;
                isUINext = true;
                isTouchEnd = true;
                
                SoundManager::PlaySound("twoworld_snd/swipe.wav");
            }
            else
                SoundManager::PlaySound("twoworld_snd/dontmove.wav");
        }
            break;
        default:
            break;
    }
    for(int i = 0; i<MAXROW;i++)
    {
        for(int j=0;j<MAXCOL;j++)
        {
            if(map[i][j].isMove == true)
                map[i][j].isMove = false;
        }
    }
    moveMap = true;
    TileScoreCarc();
    OccupancyRatio();
    TurnScore();
    CreateTile();
    GameOverCheck();
}
void GameScene::TurnScore()
{
    turnScore = killScore + newBlockScore;
    if(GM::Getinstance()->highScore < turnScore)
    {
        GM::Getinstance()->highScore = turnScore;
        UserDefault::getInstance()->setIntegerForKey("HighScore", GM::Getinstance()->highScore);
    }
}
void GameScene::OccupancyRatio()
{
    mapRatio = 100 * (humanScore-orcScore) / (humanScore + orcScore);
    gameOverRatio = 100 - (killcount / (killcount + 10.0)) * 100.0;
}
void GameScene::GuideOccupancyRatio()
{
    guideMapRatio = 100 * (movehumanScore-moveorcScore) / (movehumanScore + moveorcScore);
}
//뗏을때 그다음에 움직일수 있는지 없는지 확인할수있어야댐
void GameScene::GameOverCheck()
{
    if(mapRatio <= - gameOverRatio)     //휴먼
    {
        isGameOver = true;
        CreateTile();
        return;
    }
    if(mapRatio >= gameOverRatio)       //오크
    {
        isGameOver = true;
        CreateTile();
        return;
    }
    for(int i = MAXROW-2; i >= 0; i--)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(map[i + 1][j].num == 0
               && map[i][j].num != 0)
            {
                return;
            }
            else if(map[i + 1][j].num > 0)
            {
                if(map[i + 1][j].num < map[i][j].num
                   && map[i + 1][j].color == OBSTACLE
                   && map[i][j].color != OBSTACLE
                   && (map[i + 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i + 1][j].num == map[i][j].num
                        && map[i + 1][j].color == map[i][j].color
                        && map[i + 1][j].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i + 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i + 1][j].num < map[i][j].num
                        && map[i + 1][j].color != map[i][j].color
                        && map[i + 1][j].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i + 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
            }
            
        }
    }
    for(int i = 1; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(map[i - 1][j].num == 0
               && map[i][j].num != 0)
            {
                return;
            }
            if(map[i - 1][j].num > 0)
            {
                if(map[i - 1][j].num < map[i][j].num
                   && map[i - 1][j].color == OBSTACLE
                   && map[i][j].color != OBSTACLE
                   && (map[i - 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i - 1][j].num == map[i][j].num
                        && map[i - 1][j].color == map[i][j].color
                        && map[i - 1][j].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i - 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i - 1][j].num < map[i][j].num
                        && map[i - 1][j].color != map[i][j].color
                        && map[i - 1][j].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i - 1][j].num + 1) <= MAXNUM)
                {
                    return;
                }
            }
        }
    }
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 1; j < MAXCOL; j++)
        {
            if(map[i][j - 1].num == 0
               && map[i][j].num != 0)
            {
                return;
            }
            if(map[i][j - 1].num > 0)
            {
                if(map[i][j - 1].num < map[i][j].num
                   && map[i][j - 1].color == OBSTACLE
                   && map[i][j].color != OBSTACLE
                   && (map[i][j - 1].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i][j - 1].num == map[i][j].num
                        && map[i][j - 1].color == map[i][j].color
                        && map[i][j - 1].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i][j - 1].num + 1) <= MAXNUM)
                {
                  
                }
                else if(map[i][j - 1].num < map[i][j].num
                        && map[i][j - 1].color != map[i][j].color
                        && map[i][j - 1].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i][j - 1].num + 1) <= MAXNUM)
                {
                    return;
                }
            }
            
        }
    }
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = MAXCOL-2; j >= 0; j--)
        {
            if(map[i][j + 1].num == 0
               && map[i][j].num != 0)
            {
                return;
            }
            if(map[i][j + 1].num > 0)
            {
                if(map[i][j + 1].num < map[i][j].num
                   && map[i][j + 1].color == OBSTACLE
                   && map[i][j].color != OBSTACLE
                   && (map[i][j + 1].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i][j + 1].num == map[i][j].num
                        && map[i][j + 1].color == map[i][j].color
                        && map[i][j + 1].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i][j + 1].num + 1) <= MAXNUM)
                {
                    return;
                }
                else if(map[i][j + 1].num < map[i][j].num
                        && map[i][j + 1].color != map[i][j].color
                        && map[i][j + 1].color != OBSTACLE
                        && map[i][j].color != OBSTACLE
                        && (map[i][j + 1].num + 1) <= MAXNUM)
                {
                    return;
                }
            }
        }
    }
    isGameOver = true;
}
void GameScene::CurBestNum()
{
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(map[i][j].color != OBSTACLE
               && curBestNum < map[i][j].num)
            {
                curBestNum = map[i][j].num;
            }
        }
    }
}
void GameScene::NextBlockDecision()
{
    
    beforeBlock = nextBlock;
    
    if(nextDesicion == 5)
    {
        nextBlock = BLUE;
        isTouchEnable = false;
    }
    else if(nextDesicion == 4)
    {
        nextBlock = RED;
        isTouchEnable = false;
    }
    else if(nextDesicion == 3)
    {
        nextBlock = BLUE;
        isTouchEnable = false;
    }
    else if(nextDesicion == 2)
    {
        nextBlock = BLUE;
        isTouchEnable = false;
    }
    else if(nextDesicion == 1)
    {
        nextBlock = RED;
        isTouchEnable = false;
    }
    else
    {
        
        int ranNum = random(0,100);
        
        if(ranNum<=100)
        {
            int ranColor = random(0,100);
            if(ranColor < 50)
                nextBlock = RED;
            else
                nextBlock = BLUE;
        }
        else
            nextBlock = OBSTACLE;
    }
}
void GameScene::AddNewNum(int MAXRAN)
{
    beforeNum = newNum;
    if(nextDesicion == 5)
    {
        newNumPos = 0;
        newNum = 1;
    }
    else if(nextDesicion == 4)
    {
        newNumPos = 0;
        newNum = 1;
    }
    else if(nextDesicion == 3)
    {
        newNumPos = 0;
        newNum = 1;
    }
    else if(nextDesicion == 2)
    {
        newNumPos = 3;
        newNum = 1;
    }
    else if(nextDesicion == 1)
    {
        newNumPos = 1;
        newNum = 1;
    }
    else
    {
        newNumPos = random(0,MAXRAN - 1);
        touchcount++;
        if(beforeBlock == OBSTACLE)
        {
            MAXLEVEL = touchcount*0.03+1;
            MINLEVEL = touchcount*0.01+1;
            
            newNum = random(MINLEVEL,MAXLEVEL);
            if(newNum>MAXNUM)
                newNum = MAXNUM;
        }
        else
        {
            int randNum = random(0,100);
            if(randNum<70)
            {
                newNum = 1;
            }
            else if(randNum<90)
            {
                newNum = 2;
            }
            else
            {
                newNum = curBestNum/2;
            }
        }
    }
    
    nextDesicion--;
    if(nextDesicion < 4 && nextDesicion >= 0)
    {
        this->LabelRemove();
    }
    
}

void GameScene::TileScoreCarc()
{
    totalScore = 0;
    orcScore = 0;
    humanScore = 0;
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(map[i][j].num == 0 || map[i][j].color == OBSTACLE)
            {
                map[i][j].tileScore = 0;
            }
            else
            {
                if(map[i][j].num == 1)
                    map[i][j].tileScore = 3;
                if(map[i][j].num == 2)
                    map[i][j].tileScore = 8;
                if(map[i][j].num == 3)
                    map[i][j].tileScore = 20;
                if(map[i][j].num == 4)
                    map[i][j].tileScore = 53;
                if(map[i][j].num == 5)
                    map[i][j].tileScore = 137;
                if(map[i][j].num == 6)
                    map[i][j].tileScore = 356;
                if(map[i][j].num == 7)
                    map[i][j].tileScore = 926;
                if(map[i][j].num == 8)
                    map[i][j].tileScore = 2407;
                if(map[i][j].num == 9)
                    map[i][j].tileScore = 6260;
                if(map[i][j].num == 10)
                    map[i][j].tileScore = 16277;
                if(map[i][j].num == 11)
                    map[i][j].tileScore = 42321;
                if(map[i][j].num == 12)
                    map[i][j].tileScore = 110035;
                //pow(3.0,map[i][j].num) * map[i][j].num;
                totalScore += map[i][j].tileScore;
                if(map[i][j].color == RED)
                    humanScore += map[i][j].tileScore;
                else if(map[i][j].color == BLUE)
                    orcScore += map[i][j].tileScore;
            }
            
        }
    }
}
void GameScene::MoveTileScoreCarc()
{
    movetotalScore = 0;
    moveorcScore = 0;
    movehumanScore = 0;
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j = 0; j < MAXCOL; j++)
        {
            if(movemap[i][j].num == 0 || movemap[i][j].color == OBSTACLE)
            {
                movemap[i][j].tileScore = 0;
            }
            else
            {
                if(movemap[i][j].num == 1)
                    movemap[i][j].tileScore = 3;
                if(movemap[i][j].num == 2)
                    movemap[i][j].tileScore = 8;
                if(movemap[i][j].num == 3)
                    movemap[i][j].tileScore = 20;
                if(movemap[i][j].num == 4)
                    movemap[i][j].tileScore = 53;
                if(movemap[i][j].num == 5)
                    movemap[i][j].tileScore = 137;
                if(movemap[i][j].num == 6)
                    movemap[i][j].tileScore = 356;
                if(movemap[i][j].num == 7)
                    movemap[i][j].tileScore = 926;
                if(movemap[i][j].num == 8)
                    movemap[i][j].tileScore = 2407;
                if(movemap[i][j].num == 9)
                    movemap[i][j].tileScore = 6260;
                if(movemap[i][j].num == 10)
                    movemap[i][j].tileScore = 16277;
                if(movemap[i][j].num == 11)
                    movemap[i][j].tileScore = 42321;
                if(movemap[i][j].num == 12)
                    movemap[i][j].tileScore = 110035;
                //pow(3.0,map[i][j].num) * map[i][j].num;
                movetotalScore += movemap[i][j].tileScore;

                movetotalScore += movemap[i][j].tileScore;
                if(movemap[i][j].color == RED)
                    movehumanScore += movemap[i][j].tileScore;
                else if(movemap[i][j].color == BLUE)
                    moveorcScore += movemap[i][j].tileScore;
            }
            
        }
    }
    if((followPos.x != 0 || followPos.y != 0) && isMoveAdd)
    {
        if(nextBlock == RED)
        {
            if(newNum == 1)
                movehumanScore += 3;
            else if(newNum == 2)
                 movehumanScore += 8;
            else if(newNum == 3)
                movehumanScore += 20;
            else if(newNum == 4)
                movehumanScore += 53;
            else if(newNum == 5)
                movehumanScore += 137;
            else if(newNum == 6)
                movehumanScore += 356;
        }
        if(nextBlock == BLUE)
        {
            if(newNum == 1)
                moveorcScore += 3;
            else if(newNum == 2)
                moveorcScore += 8;
            else if(newNum == 3)
                moveorcScore += 20;
            else if(newNum == 4)
                moveorcScore += 53;
            else if(newNum == 5)
                moveorcScore += 137;
            else if(newNum == 6)
                moveorcScore += 356;
        }
    }
}
void GameScene::onEnter()
{
    Layer::onEnter();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan,this);
    listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded,this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
}
void GameScene::onExit()
{
    //_eventDispatcher->removeAllEventListeners();
    Layer::onExit();
}



void GameScene::EndMapMove()
{
    moveMap = false;
    isSetMove = false;
    //DirectionMap();
    CurBestNum();
    for(int i=0;i<MAXROW;i++)
    {
        for(int j=0;j<MAXROW;j++)
            map[i][j].unitState = idle;
    }
    CreateTile();
}
void GameScene::TouchMapMove()
{
    moveMap = true;
    NotAddDirectionMap();
    CreateTile();
}

bool GameScene::onTouchBegan(Touch* touch, cocos2d::Event* event)
{
    if(isTutorialTab)
    {
        this->TutorialEnd();
        isTutorialTab = false;
    }
    if(isTouchEnable)
    {
        auto touchPoint = touch->getLocation();
        beforeTouch = touchPoint;
        beforeMapRatio = mapRatio;
        dir = NULL;
    }
    return true;
}

void GameScene::onTouchMoved(Touch* touch, cocos2d::Event* event)
{
    auto touchPoint = touch->getLocation();
    if(isTouchEnable)
    {
        if(!isGameOver)
        {
            this->MoveTouchDirectionCheck(touchPoint);
            this->TouchMapMove();
        }
    }
}

void GameScene::onTouchEnded(Touch* touch, cocos2d::Event* event)
{
    auto touchPoint = touch->getLocation();
    if(isTouchEnable)
    {
        if(!isGameOver)
        {
            this->TouchDirectionCheck(touchPoint);
            this->EndMapMove();
        }
        isPin = false;
    }
}
void GameScene::onTouchCancelled(Touch* touch, cocos2d::Event* event)
{
    
}

