//
//  GameScene.hpp
//  Twoworld
//
//  Created by Test on 2017. 1. 2..
//
//

#ifndef GameScene_h
#define GameScene_h

#include "cocos2d.h"
#include "myheader.h"
#include <map>

USING_NS_CC;


class GameScene : public Layer
{
private:
    Vec2 beforeTouch;
    Size BarSize;
    int touchDirection;
    int dir;
    int nextBlock;
    int beforeBlock;
    int beforeNum;
    int newNumPos;
    int newNum;
    int curBestNum;
    int totalScore;
    int humanScore;
    int orcScore;
    int movetotalScore;
    int movehumanScore;
    int moveorcScore;
    int notMove;
    int nextDesicion;
    long touchcount;
    int killcount;
    
    int turnScore;
    int killScore;
    int newBlockScore;
    
    bool moveMap;
    bool isAddMoveMap;
    bool isSetMove;
    bool isGameOver;
    bool isPin;
    bool isTouchEnd;
    bool isTouchCancel;
    bool isMoveAdd;
    bool isUINext;
    
    bool isbgmcheck;
    bool ishbgm;
    bool isobgm;
    
    bool isTouchEnable;
    bool isTutorial;
    bool isTutorialTab;
    
    int MAXLEVEL;
    int MINLEVEL;
    int beforeMapRatio;
    float mapRatio;
    float guideMapRatio;
    float moveMapRatio;
    float gameOverRatio;
    Vec2 followPos;
    Vec2 otherPos;
public:
    static Scene* createScene();
    Layer* TileLayer;
    Layer* UILayer;
    Layer* GameOverLayer;
    Layer* BubbleLayer;
    Layer* topPinLayer;
    Layer* PinLayer;
    Layer* TutorialLayer;
    virtual bool init();

    CREATE_FUNC(GameScene);
    enum State { idle,attack,damage };
    typedef struct Unit
    {
        State unitState;
        int color;
        int num;
        int tileScore;
        bool isMove;
        bool is_fxfusion;
        bool is_fxattack;
        Sprite* img_Tile;
    }S_Unit;
    S_Unit map[MAXROW][MAXCOL];
    S_Unit movemap[MAXROW][MAXCOL];
    
    void StartBlackfx();
    void Blackfx(Ref *sender);
    
    //////////////tutorial
    void TutorialMapInit();
    void TutorialGuide();
    
    void LabelRemove();
    void SetTouchSprite();
    void SetTouchSprite2();
    void TouchEnable();
    void RightArrow();
    void LeftArrow();
    void UpArrow();
    void SetTabTouch();
    void TutorialEnd();
    void TutorialReset();
    //////////////Ingame
    void MapInit();
    void CreateTile();
    void PinDraw();
    void removePinLayer();
    void UIView();
    void GameOverView();
    void GameOverPinPlus();
    void TileScoreCarc();
    void MoveTileScoreCarc();
    void TouchDirectionCheck(Vec2 touchPoint);
    void MoveTouchDirectionCheck(Vec2 touchPoint);
    void EndMapMove();
    void TouchMapMove();
    void NotAddDirectionMap();
    void DirectionMap();
    void NextBlockDecision();
    void AddNewNum(int MAXRAN);
    void CurBestNum();
    void GameOverCheck();
    void OccupancyRatio();
    void GuideOccupancyRatio();
    void TurnScore();
    void ChangeScene(Ref * sender);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    Size VisibleSize = Director::getInstance()->getVisibleSize();
    char _str[100];
};

#endif /* GameScene_hpp */
