#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class AskMinConditionScene :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //ѯ�ʱ�������������
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //�����༭
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text)
	{
			MinCondition = text;
	}; //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //����return��

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AskMinConditionScene);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	std::string MinCondition;
	int NumVar;
	void changeToAskConditionScene2(cocos2d::Ref* pSender);
};