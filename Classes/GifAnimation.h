/****************************************************************************
Copyright (c) 2015 Zhangpanyi
Created by Zhangpanyi on 2015
zhangpanyi@live.com
****************************************************************************/
#ifndef __GIFANIMATION_H__
#define __GIFANIMATION_H__

#include "cocos2d.h"
#include "Singleton.h"

typedef std::vector<cocos2d::Texture2D *> TextureArray;

/**
* Gif��������
*/
struct GifAnimationDef
{
	std::string  filePath;                         // �ļ�·��
	unsigned int loops;                            // ѭ������
	float        delayPerUnit;                     // ���ʱ��
	bool         restoreOriginalFrame;             // �Ƿ�ԭ��ʼ֡
	GifAnimationDef() : loops(-1), delayPerUnit(0.1f), restoreOriginalFrame(false) {};
};

class GifAnimation : public Singleton < GifAnimation >
{
	GifAnimation() {};
	~GifAnimation() {};
	friend class Singleton < GifAnimation >;

public:
	/**
	* ��������
	* @ ���� GifAnimationDef ��������
	*/
	cocos2d::Animation* createAnimation(const GifAnimationDef &def);

	/**
	* ��ȡ��һ������
	* @ ���� std::string �ļ�·��
	*/
	cocos2d::Texture2D* getFristTexture(const std::string &filePath);

	/**
	* �Ƴ�Gif����
	* @ ���� std::string ��������
	* @ ����ֵ void
	*/
	void removeAnimation(const std::string &name);

	/**
	* �Ƴ�����Gif����
	* @ ���� void
	* @ ���� void
	*/
	void removeAllAnimation();

private:
	/**
	* ��ȡ�����б�
	* @ ���� std::string ͼƬ·��, TextureArray ��������
	* @ ����ֵ ����
	*/
	int getTextureList(const std::string &filePath, TextureArray &textureArray);

private:
	TextureArray m_textureArray;
	std::multimap<std::string, cocos2d::Texture2D *> m_animation;
};

#endif