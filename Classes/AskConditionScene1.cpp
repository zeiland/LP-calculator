#include "AskConditionScene1.h"
#include <iostream>
#include <fstream>
#include "AskMinConditionScene.h"
#include "other functions.h"

USING_NS_CC;




Scene* AskConditionScene1::createScene()
{
	auto scene = Scene::create();
	auto layer = AskConditionScene1::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool AskConditionScene1::init()
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
	auto tip1 = Sprite::create("tip1.png");

	// position the sprite on the center of the screen
	tip1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 125));
	auto size_tip1 = tip1->getContentSize();
	tip1->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.2f*visibleSize.height) / size_tip1.height);
	this->addChild(tip1, 0);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(AskConditionScene1::menuCloseCallback, this));


	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));

	// create menu, it's an autorelease object

	Size NumVarSize = CCSizeMake(300, 60);
	EditBox* NumVar = EditBox::create(NumVarSize, Scale9Sprite::create("white_ground.png"));;
	NumVar->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
	this->addChild(NumVar);

	NumVar->setFontName("fonts/Paint Boy.ttf");
	NumVar->setFontSize(30);
	NumVar->setFontColor(Color3B(0,0,0));
	NumVar->setInputMode(EditBox::InputMode::NUMERIC);
	NumVar->setMaxLength(1); //限制字符长度
	NumVar->setDelegate(this);
	NumVar->setTag(101);
	

	auto tip2 = Sprite::create("tip2.png");

	// position the sprite on the center of the screen
	tip2->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ));
	auto size_tip2 = tip2->getContentSize();
	tip2->setScale((0.4f*visibleSize.width) / size_tip2.width, (0.2f*visibleSize.height) / size_tip2.height);
	this->addChild(tip2, 0);


	Size NumConditionSize = CCSizeMake(300, 60);
	EditBox* NumCondition = EditBox::create(NumConditionSize, Scale9Sprite::create("white_ground.png"));;
	NumCondition->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y -50));
	this->addChild(NumCondition);


	NumCondition->setFontName("fonts/Paint Boy.ttf");
	NumCondition->setFontSize(30);
	NumCondition->setFontColor(Color3B(0, 0, 0));
	NumCondition->setInputMode(EditBox::InputMode::NUMERIC);
	NumCondition->setMaxLength(1); //限制字符长度
	NumCondition->setDelegate (this);
	NumCondition->setTag(102);


	auto button_complete = MenuItemImage::create(
		"complete.png",
		"complete.png",
		CC_CALLBACK_1(AskConditionScene1::changeToAskMinConditionScene, this));

	button_complete->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 125));
	auto size_button_complete = button_complete->getContentSize();
	button_complete->setScale((0.27f*visibleSize.width) / size_button_complete.width, (0.15f*visibleSize.height) / size_button_complete.height);

	auto menu = Menu::create(button_complete, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void AskConditionScene1::changeToAskMinConditionScene(cocos2d::Ref* pSender)
{
	if (isValid(NumVar, 1) && isValid(NumCondition, 1))
	{
		std::string input = FileUtils::getInstance()->getWritablePath() + "input.txt";
		std::ofstream out;
		out.open(input.c_str());
		if (out.is_open())
		{
			out << NumVar << ' ' << NumCondition << std::endl;
			out.close();
			Director::getInstance()->replaceScene(AskMinConditionScene::createScene());
		}
		else
		{
			CCLOG("WRONG");
			Director::getInstance()->end();
		}
	}
	else
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();

		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		auto WrongTip = Sprite::create("tip14.png");
		// position the sprite on the center of the screen
		WrongTip->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 93));
		auto size_tip1 = WrongTip->getContentSize();
		WrongTip->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.07f*visibleSize.height) / size_tip1.height);
		this->addChild(WrongTip, 0);
	}
}
void AskConditionScene1::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}