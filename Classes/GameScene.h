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

	void killBird();

	void beInvincible();

	CREATE_FUNC(GameScene);

private:
	
	cocos2d::Sprite* player;
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> roofs;
	std::vector<cocos2d::Sprite*> birds;
	Size visibleSize;
	int score;

	// 无敌信号量
	bool invincible;

	// 控制一次只能播放一个动画
	bool mutex;

	// 判断位置
	bool position;

	// 是否存在攻击者
	bool attack;
};