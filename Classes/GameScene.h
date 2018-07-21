#pragma once
#include <stdio.h>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void updateCustom(float dt);

	void generateRoofs(float dt);

	void generateAttacker(float dt);

	void loadMyAnimationsAndSprite();

	void loadMyMusic();

	void addTouchListener();

	bool onTouchBegan(Touch * touch, Event * event);

	void onTouchEnded(Touch * touch, Event * event);

	void birdAttackPlayer();

	void cavalryAttackPlayer();

	CREATE_FUNC(GameScene);

private:
	
	cocos2d::Sprite* player;
	cocos2d::Sprite* cavalry;
	cocos2d::Sprite* fox;
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> roofs;
	Size visibleSize;
	//控制 一次只能播放一个动画
	bool mutex;
	bool position;
	bool attack;
};