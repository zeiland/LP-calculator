#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d::extension;

class IntProgrammingInputScene :public cocos2d::Layer, cocos2d::extension::EditBoxDelegate          //询问变量和条件个数
{
public:

	virtual void editBoxEditingDidBegin(EditBox* editBox) {};                      //开始编辑
	virtual void editBoxEditingDidEnd(EditBox* editBox) {};                        //结束编辑
	virtual void editBoxTextChanged(EditBox* editBox, const std::string& text)
	{
		
		if (tag == 0)
		{
			int_num = text;
		}
		else
		{
			int_position = text;
		}

	}; //编辑框文字改变
	virtual void editBoxReturn(EditBox* editBox)
	{};                               //触发return后

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(IntProgrammingInputScene);
	void menuCloseCallback(cocos2d::Ref* pSender);

	static bool  tag;
	static std::string int_num;
private:
	

	std::string int_position;
	int NumVar;
	void changeToNextScene(cocos2d::Ref* pSender);
	void begin_cal();
};