#include "AskConditionScene2.h"
#include <iostream>
#include <fstream>
#include "MainScene.h"
#include "ShowPageScene.h"
#include "UI.h"
#include "other functions.h"

USING_NS_CC;

int AskConditionScene2::NumVar(0);
int AskConditionScene2::NumCondition(0);
bool AskConditionScene2::tag(0);
int AskConditionScene2::count(0);

bool AskConditionScene2::tag_add(0);

Scene* AskConditionScene2::createScene()
{
	auto scene = Scene::create();
	auto layer = AskConditionScene2::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool AskConditionScene2::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// add "HelloWorld" splash screen"

	if (tag == 0)
	{
		std::ifstream in(FileUtils::getInstance()->getWritablePath() + "input.txt");
		if (in.is_open())
		{
			in >> NumVar;
			in >> NumCondition;
			tag = 1;
			in.close();
			CCLOG("RIGHT");
		}
		else
		{
			CCLOG("WRONG!");
			Director::getInstance()->end();
		}
	}
	

	auto tip4 = Sprite::create("tip4.png");

	// position the sprite on the center of the screen
	tip4->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 125));
	auto size_tip4 = tip4->getContentSize();
	tip4->setScale((0.5f*visibleSize.width) / size_tip4.width, (0.2f*visibleSize.height) / size_tip4.height);
	this->addChild(tip4, 0);

	auto tip5 = Sprite::create("tip5.png");

	// position the sprite on the center of the screen
	tip5->setPosition(Vec2(visibleSize.width / 2 + origin.x-100, visibleSize.height / 2 + origin.y ));
	auto size_tip5 = tip5->getContentSize();
	tip5->setScale((0.3f*visibleSize.width) / size_tip5.width, (0.15f*visibleSize.height) / size_tip5.height);
	this->addChild(tip5, 0);

	auto tip6 = Sprite::create("tip6.png");

	// position the sprite on the center of the screen
	tip6->setPosition(Vec2(visibleSize.width / 2 + origin.x+100, visibleSize.height / 2 + origin.y));
	auto size_tip6 = tip6->getContentSize();
	tip6->setScale((0.3f*visibleSize.width) / size_tip6.width, (0.15f*visibleSize.height) / size_tip6.height);
	this->addChild(tip6, 0);


	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(AskConditionScene2::menuCloseCallback, this));


	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));

	// create menu, it's an autorelease object

	Size VarSize = CCSizeMake(300, 60);
	EditBox* Var = EditBox::create(VarSize, Scale9Sprite::create("white_ground.png"));;
	Var->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+75 ));
	this->addChild(Var);

	Var->setFontName("fonts/Paint Boy.ttf");
	Var->setFontSize(30);
	Var->setFontColor(Color3B(0, 0, 0));
	Var->setMaxLength(50); //限制字符长度
	Var->setDelegate(this);
	Var->setTag(101);



	Size RightVarSize = CCSizeMake(100, 60);
	EditBox* RightVar = EditBox::create(RightVarSize, Scale9Sprite::create("white_ground.png"));;
	RightVar->setPosition(Vec2(visibleSize.width / 2 + origin.x+100, visibleSize.height / 2 + origin.y-60));
	this->addChild(RightVar);


	RightVar->setFontName("fonts/Paint Boy.ttf");
	RightVar->setFontSize(30);
	RightVar->setFontColor(Color3B(0, 0, 0));
	RightVar->setInputMode(EditBox::InputMode::NUMERIC);
	RightVar->setMaxLength(5); //限制字符长度
	RightVar->setDelegate(this);
	RightVar->setTag(102);

	Size signSize = CCSizeMake(100, 60);
	EditBox* sign = EditBox::create(signSize, Scale9Sprite::create("white_ground.png"));;
	sign->setPosition(Vec2(visibleSize.width / 2 + origin.x -100, visibleSize.height / 2 + origin.y - 60));
	this->addChild(sign);


	sign->setFontName("fonts/Paint Boy.ttf");
	sign->setFontSize(30);
	sign->setFontColor(Color3B(0, 0, 0));
	sign->setMaxLength(2); //限制字符长度
	sign->setDelegate(this);
	sign->setTag(103);


	
	auto button_complete = MenuItemImage::create(
		"complete.png",
		"complete.png",
		CC_CALLBACK_1(AskConditionScene2::changeToNextScene, this));

	button_complete->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 125));
	auto size_button_complete = button_complete->getContentSize();
	button_complete->setScale((0.27f*visibleSize.width) / size_button_complete.width, (0.15f*visibleSize.height) / size_button_complete.height);

	auto menu = Menu::create(button_complete, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void AskConditionScene2::changeToNextScene(cocos2d::Ref* pSender)
{
	if (tag_add == 0)
	{
		if (isValid(Var, NumVar) && isSign(sign) && isValid(RightVar, 1))
		{
			std::ofstream out(FileUtils::getInstance()->getWritablePath() + "input.txt", std::ios::app);
			if (out.is_open())
			{
				out << Var << std::endl;
				out << sign << std::endl;
				out << RightVar << std::endl;
				out.close();
			}
			else
			{
				CCLOG("WRONG");
				Director::getInstance()->end();
			}
			++count;
			if (count < NumCondition)
			{
				Director::getInstance()->replaceScene(AskConditionScene2::createScene());
			}
			else
			{
				Director::getInstance()->replaceScene(MainScene2::createScene());
			}
		}
		else
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();

			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			auto WrongTip = Sprite::create("tip14.png");
			// position the sprite on the center of the screen
			WrongTip->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y +30));
			auto size_tip1 = WrongTip->getContentSize();
			WrongTip->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.07f*visibleSize.height) / size_tip1.height);
			this->addChild(WrongTip, 0);
		}
	}
	
	else
	{
		if (isValid(Var, NumVar) && isSign(sign) && isValid(RightVar, 1))
		{
			std::ofstream out(FileUtils::getInstance()->getWritablePath() + "add_condition.txt");
			if (out.is_open())
			{
				out << Var << std::endl;
				out << sign << std::endl;
				out << RightVar << std::endl;
				out.close();
			}
			else
			{
				CCLOG("WRONG");
				Director::getInstance()->end();
			}
			tag_add = 0;
			UIgetInstance().Trd_in();
			Director::getInstance()->replaceScene(ShowPageScene::createScene());
		}
		else
		{
			auto visibleSize = Director::getInstance()->getVisibleSize();

			Vec2 origin = Director::getInstance()->getVisibleOrigin();

			auto WrongTip = Sprite::create("tip14.png");
			// position the sprite on the center of the screen
			WrongTip->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 30));
			auto size_tip1 = WrongTip->getContentSize();
			WrongTip->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.07f*visibleSize.height) / size_tip1.height);
			this->addChild(WrongTip, 0);
		}
	}

}
void AskConditionScene2::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	UIgetInstance().deleteLp();
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}