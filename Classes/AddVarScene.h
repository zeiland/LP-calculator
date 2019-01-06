#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class AddVarScene :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //ѯ�ʱ�������������
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //��ʼ�༭
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //�����༭
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text)
	{
		if (editBox->getTag() == 101)
		{
			target_coefficient = text;
		}
		if (editBox->getTag() == 102)
		{
			condition_coefficient = text;
		}
	}; //�༭�����ָı�
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //����return��

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AddVarScene);
	void menuCloseCallback(cocos2d::Ref* pSender);
private:
	std::string target_coefficient;
	std::string condition_coefficient;
	int NumCondition;
	void changeToShowPageScene(cocos2d::Ref* pSender);
};