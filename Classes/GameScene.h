#pragma once
#include <stdio.h>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	static PhysicsWorld* world;
	void setPhysicsWorld(PhysicsWorld * world);

	virtual bool init();

	void updateCustom(float dt);

	void generateRoofs(float dt);

	void generateAttacker(float dt);

	void loadMyAnimationsAndSprite();

	void loadMyMusic();

	void addTouchListener();

	bool onTouchBegan(Touch * touch, Event * event);

	void onTouchEnded(Touch * touch, Event * event);

	bool onConcactBegin(PhysicsContact & contact);

	void attackPlayer();

	void gameOver();

	void replayCallback(Ref * pSender);
	void exitCallback(Ref * pSender);
	CREATE_FUNC(GameScene);

private:
	PhysicsWorld * m_world;
	cocos2d::Sprite* player;
	cocos2d::Sprite* cavalry;
	cocos2d::Sprite* fox;
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> roofs;
	Size visibleSize;
	//控制 一次只能播放一个动画
	std::string status;
	bool mutex;
	bool position;
	bool attack;
};