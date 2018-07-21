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

	// �޵��ź���
	bool invincible;

	// ����һ��ֻ�ܲ���һ������
	bool mutex;

	// �ж�λ��
	bool position;

	// �Ƿ���ڹ�����
	bool attack;
};