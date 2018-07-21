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

	void birdAttackPlayer();

	void cavalryAttackPlayer();

	void gameOver();

	void replayCallback(Ref * pSender);
	void exitCallback(Ref * pSender);

	void killBird();

	void beInvincible();

	CREATE_FUNC(GameScene);

private:
	PhysicsWorld * m_world;
	cocos2d::Sprite* player;
	std::vector<cocos2d::Sprite*> walls;
	std::vector<cocos2d::Sprite*> roofs;
	std::vector<cocos2d::Sprite*> birds;
	Size visibleSize;
	int dtime;
	//���� һ��ֻ�ܲ���һ������
	std::string status;

	int score;
	// �޵��ź���
	bool invincible;
	// ����һ��ֻ�ܲ���һ������
	bool mutex;

	// �ж�λ��
	bool position;

	// �Ƿ���ڹ�����
	bool attack;
};