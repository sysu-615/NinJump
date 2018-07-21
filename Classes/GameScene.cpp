#include "GameScene.h"
#include "GifAnimation.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

using namespace CocosDenshion;

Scene* GameScene::createScene()
{
	return GameScene::create();
}

void GameScene::updateCustom(float dt) {
	auto leftWall1 = walls[0];
	auto leftWall2 = walls[1];
	auto rightWall1 = walls[2];
	auto rightWall2 = walls[3];
	auto moveBy = MoveBy::create(0.1, Vec2(0, -50));

	leftWall1->runAction(MoveBy::create(0.01, Vec2(0, -5)));
	leftWall2->runAction(MoveBy::create(0.01, Vec2(0, -5)));
	rightWall1->runAction(MoveBy::create(0.01, Vec2(0, -5)));
	rightWall2->runAction(MoveBy::create(0.01, Vec2(0, -5)));
	
	if (leftWall1->getPositionY() <= 0 - leftWall1->getContentSize().height * 1.4 / 2) {
		leftWall1->setPosition(Vec2(leftWall1->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	}
	if (leftWall2->getPositionY() <= 0 - leftWall2->getContentSize().height * 1.4 / 2) {
		leftWall2->setPosition(Vec2(leftWall2->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	}
	if (rightWall1->getPositionY() <= 0 - rightWall1->getContentSize().height * 1.4 / 2) {
		rightWall1->setPosition(Vec2(visibleSize.width - rightWall1->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	}
	if (rightWall2->getPositionY() <= 0 - rightWall2->getContentSize().height * 1.4 / 2) {
		rightWall2->setPosition(Vec2(visibleSize.width - rightWall2->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	}

	for (auto roof : roofs) {
		roof->runAction(MoveBy::create(0.01, Vec2(0, -5)));
	}
}

void GameScene::generateRoofs(float dt) {
	int num = random(0, 2);
	if (num == 1) {
		auto leftRoof = Sprite::create("images/left_roof" + std::to_string(random(2, 3)) + ".png");
		leftRoof->setPosition(Vec2(walls[0]->getContentSize().width * 0.6 + leftRoof->getContentSize().width / 3, visibleSize.height));
		roofs.push_back(leftRoof);
		this->addChild(leftRoof, 0);
	}
	if (num == 2) {
		auto rightRoof = Sprite::create("images/right_roof" + std::to_string(random(2, 3)) + ".png");
		rightRoof->setPosition(Vec2(visibleSize.width - walls[0]->getContentSize().width * 0.6 - rightRoof->getContentSize().width / 3, visibleSize.height));
		roofs.push_back(rightRoof);
		this->addChild(rightRoof, 0);
	}
}

void GameScene::generateAttacker(float dt) {
	int num = random(0, 2);
	if (num == 1) {
		attackPlayer();
	}


}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	schedule(schedule_selector(GameScene::updateCustom), 0.01f, kRepeatForever, 0);
	schedule(schedule_selector(GameScene::generateRoofs), 1.0f, kRepeatForever, 0);
	schedule(schedule_selector(GameScene::generateAttacker), 1.0f, kRepeatForever, 0);

	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("images/newBg.jpg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScale(visibleSize.width / bg->getContentSize().width,
		visibleSize.height / bg->getContentSize().height);
	this->addChild(bg, 0);
	
	auto leftWall1 = Sprite::create("images/left_wall.jpg");
	leftWall1->setAnchorPoint(Vec2(0.5,0.5));
	leftWall1->setPosition(Vec2(leftWall1->getContentSize().width * 0.6 / 2, visibleSize.height / 2));
	leftWall1->setScaleY(visibleSize.height / leftWall1->getContentSize().height + 0.1);
	leftWall1->setScaleX(0.6);
	this->addChild(leftWall1, 0);

	auto leftWall2 = Sprite::create("images/left_wall.jpg");
	leftWall2->setAnchorPoint(Vec2(0.5, 0.5));
	leftWall2->setPosition(Vec2(leftWall2->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	leftWall2->setScaleY(visibleSize.height / leftWall2->getContentSize().height + 0.1);
	leftWall2->setScaleX(0.6);
	this->addChild(leftWall2, 0);

	walls.push_back(leftWall1);
	walls.push_back(leftWall2);

	auto rightWall1 = Sprite::create("images/right_wall.jpg");
	rightWall1->setAnchorPoint(Vec2(0.5, 0.5));
	rightWall1->setPosition(Vec2(visibleSize.width - rightWall1->getContentSize().width  * 0.6 / 2, visibleSize.height / 2));
	rightWall1->setScaleY(visibleSize.height / rightWall1->getContentSize().height + 0.1);
	rightWall1->setScaleX(0.6);
	this->addChild(rightWall1, 0);

	auto rightWall2 = Sprite::create("images/right_wall.jpg");
	rightWall2->setAnchorPoint(Vec2(0.5, 0.5));
	rightWall2->setPosition(Vec2(visibleSize.width - rightWall2->getContentSize().width * 0.6 / 2, visibleSize.height / 2 + visibleSize.height));
	rightWall2->setScaleY(visibleSize.height / rightWall2->getContentSize().height + 0.1);
	rightWall2->setScaleX(0.6);
	this->addChild(rightWall2, 0);

	walls.push_back(rightWall1);
	walls.push_back(rightWall2);

	loadMyAnimationsAndSprite();

	player->setPosition(Vec2(leftWall1->getContentSize().width * 0.6 + player->getContentSize().width * 0.7 / 2, visibleSize.height / 3 + origin.y));
	this->addChild(player, 1, 1);

	player->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunAtLeft")));
	loadMyMusic();

	// һ��ֻ�ܲ���һ������
	mutex = false;
	attack = false;
	position = false;

	// ��Ӽ�����
	addTouchListener();

	// ������
	// schedule(schedule_selector(GameScene::attackPlayer), 1.0f, kRepeatForever, 0);

	return true;
}

void GameScene::loadMyAnimationsAndSprite()
{
	GifAnimationDef def;
	def.loops = -1;						  // ѭ������
	def.delayPerUnit = 0.1f;			  // ÿ֡���
	def.restoreOriginalFrame = false;	  // ��ԭ��ʼ״̬

	def.filePath = "images/left_run.gif"; // �ļ�·��
	player = Sprite::createWithTexture(GifAnimation::getInstance()->getFristTexture(def.filePath));
	player->setScale(0.7);
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "RunAtLeft");

	def.filePath = "images/right_run.gif";
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "RunAtRight");

	def.filePath = "images/move.gif";
	def.loops = 1;
	def.delayPerUnit = 0.05f;
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "Move");
	def.loops = -1;
	def.delayPerUnit = 0.1f;

	//������ʿ����ʿ��涯��
	def.filePath = "images/cavalry_left.gif";
	cavalry = Sprite::createWithTexture(GifAnimation::getInstance()->getFristTexture(def.filePath));
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "CavalryLeft");

	def.filePath = "images/cavalry_right.gif";
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "CavalryRight");

	//���غ���ͺ����涯��
	def.filePath = "images/fox_left.gif";
	fox = Sprite::createWithTexture(GifAnimation::getInstance()->getFristTexture(def.filePath));
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "FoxLeft");

	def.filePath = "images/fox_right.gif";
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "FoxRight");

	//�����������ж���
	def.filePath = "images/bird_left.gif";
	def.loops = 1;
	// bird = Sprite::createWithTexture(GifAnimation::getInstance()->getFristTexture(def.filePath));
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "BirdLeft");

	def.filePath = "images/bird_right.gif";
	AnimationCache::getInstance()->addAnimation(GifAnimation::getInstance()->createAnimation(def), "BirdRight");
}

void GameScene::loadMyMusic()
{
	auto audio = SimpleAudioEngine::getInstance();
	
	audio->preloadBackgroundMusic("sounds/background.mp3");
	audio->playBackgroundMusic("sounds/background.mp3", true);
}

// ��Ӵ����¼�������
void GameScene::addTouchListener() {
	// Todo

	//�¼��ַ���
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	//�������㴥��������
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	if (!mutex) {
		mutex = true;
		player->getActionManager()->removeAllActionsFromTarget(this->getChildByTag(1));
		Size visibleSize = Director::getInstance()->getVisibleSize();
		float moveX = -1.0f * (2 * player->getPosition().x - visibleSize.width);
		float backX = player->getPosition().x;
		float backY = player->getPosition().y;

		auto playerMove0 = MoveTo::create(0.1, Vec2(backX + moveX * 1 / 8, backY + 12.0f));
		auto playerMove1 = MoveTo::create(0.1, Vec2(backX + moveX * 2 / 8, backY + 20.0f));
		auto playerMove2 = MoveTo::create(0.1, Vec2(backX + moveX * 3 / 8, backY + 27.0f));
		auto playerMove3 = MoveTo::create(0.1, Vec2(backX + moveX * 4 / 8, backY + 31.5f));
		auto playerMove4 = MoveTo::create(0.1, Vec2(backX + moveX * 5 / 8, backY + 27.0f));
		auto playerMove5 = MoveTo::create(0.1, Vec2(backX + moveX * 6 / 8, backY + 20.0f));
		auto playerMove6 = MoveTo::create(0.1, Vec2(backX + moveX * 7 / 8, backY + 12.0f));
		auto playerMove7 = MoveTo::create(0.1, Vec2(backX + moveX * 8 / 8, backY + 0.0f));


		Animate* moveAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("Move"));
		auto set = CallFunc::create(([this]() {
			position = !position;
			if (position)
				player->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunAtRight")));
			else
				player->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("RunAtLeft")));
			mutex = false;
		}));
		Sequence* moveSeq = Sequence::create(playerMove0, playerMove1, playerMove2, playerMove3, playerMove4, playerMove5, playerMove6, playerMove7, NULL);

		Spawn* spawn = Spawn::create(moveAnimate, moveSeq, NULL);
		Sequence* seq = Sequence::create(spawn, set, NULL);
		player->runAction(seq);
	}
	return true;
}


void GameScene::onTouchEnded(Touch *touch, Event *event) {

}

void GameScene::attackPlayer() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!attack) {
		attack = true;
		Sprite* bird;
		Animate* birdAnimate;
		if (!position) {
			// left
			bird = Sprite::create("images/bird_l.png");
			bird->setScale(0.8);
			bird->setPosition(visibleSize.width * 4 / 5 + 20, visibleSize.height * 3.5 / 4);
			birdAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("BirdLeft"));
		}
		else {
			// right
			bird = Sprite::create("images/bird_r.png");
			bird->setScale(0.8);
			bird->setPosition(visibleSize.width * 1 / 5 - 20, visibleSize.height * 3.5 / 4);
			birdAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("BirdRight"));
		}
		this->addChild(bird, 1);
		auto set = CallFunc::create(([this, bird]() {
			bird->removeFromParentAndCleanup(true);
			attack = false;
		}));
		auto move = MoveTo::create(0.8, Vec2(visibleSize.width - bird->getPositionX(), visibleSize.height / 3));
		Spawn* birdSpawn = Spawn::create(birdAnimate, move, NULL);
		Sequence* birdSeq = Sequence::create(birdAnimate, birdSpawn,set, NULL);
		bird->runAction(birdSeq);
	}
}