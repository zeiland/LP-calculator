#include "AddVarScene.h"
#include <iostream>
#include <fstream>
#include "ShowPageScene.h"
#include "UI.h"
#include "other functions.h"

USING_NS_CC;




Scene* AddVarScene::createScene()
{
	auto scene = Scene::create();
	auto layer = AddVarScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool AddVarScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	std::ifstream input(FileUtils::getInstance()->getWritablePath() + "input.txt");
	if (input.is_open())
	{
		input >> NumCondition;   //NumVar
		input >> NumCondition;
		input.close();
	}
	else
	{
		CCLOG("IntInputWrong!");
		Director::getInstance()->end();
	}



	// add "HelloWorld" splash screen"
	auto tip9 = Sprite::create("tip9.png");

	// position the sprite on the center of the screen
	tip9->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 125));
	auto size_tip9 = tip9->getContentSize();
	tip9->setScale((0.45f*visibleSize.width) / size_tip9.width, (0.15f*visibleSize.height) / size_tip9.height);
	this->addChild(tip9, 0);

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(AddVarScene::menuCloseCallback, this));


	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));

	// create menu, it's an autorelease object

	Size targtarget_coefficientet_size = CCSizeMake(300, 60);
	EditBox* target_coefficient = EditBox::create(targtarget_coefficientet_size, Scale9Sprite::create("white_ground.png"));;
	target_coefficient->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
	this->addChild(target_coefficient);

	target_coefficient->setFontName("fonts/Paint Boy.ttf");
	target_coefficient->setFontSize(30);
	target_coefficient->setFontColor(Color3B(0, 0, 0));
	target_coefficient->setMaxLength(10); //限制字符长度
	target_coefficient->setDelegate(this);
	target_coefficient->setTag(101);


	auto tip10 = Sprite::create("tip10.png");

	// position the sprite on the center of the screen
	tip10->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	auto size_tip10 = tip10->getContentSize();
	tip10->setScale((0.5f*visibleSize.width) / size_tip10.width, (0.12f*visibleSize.height) / size_tip10.height);
	this->addChild(tip10, 0);


	Size condition_coefficient_size = CCSizeMake(300, 60);
	EditBox* condition_coefficient = EditBox::create(condition_coefficient_size, Scale9Sprite::create("white_ground.png"));;
	condition_coefficient->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 50));
	this->addChild(condition_coefficient);


	condition_coefficient->setFontName("fonts/Paint Boy.ttf");
	condition_coefficient->setFontSize(30);
	condition_coefficient->setFontColor(Color3B(0, 0, 0));
	condition_coefficient->setMaxLength(50); //限制字符长度
	condition_coefficient->setDelegate(this);
	condition_coefficient->setTag(102);


	auto button_complete = MenuItemImage::create(
		"complete.png",
		"complete.png",
		CC_CALLBACK_1(AddVarScene::changeToShowPageScene, this));

	button_complete->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 125));
	auto size_button_complete = button_complete->getContentSize();
	button_complete->setScale((0.27f*visibleSize.width) / size_button_complete.width, (0.15f*visibleSize.height) / size_button_complete.height);

	auto menu = Menu::create(button_complete, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void AddVarScene::changeToShowPageScene(cocos2d::Ref* pSender)
{
	if (isValid(target_coefficient, 1) && isValid(condition_coefficient, NumCondition))
	{
		std::string input = FileUtils::getInstance()->getWritablePath() + "add_var.txt";
		std::ofstream out;
		out.open(input.c_str());
		if (out.is_open())
		{
			out << target_coefficient << ' ' << condition_coefficient << std::endl;
			out.close();
			UIgetInstance().Trd_in();
			Director::getInstance()->replaceScene(ShowPageScene::createScene());
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
		WrongTip->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 90));
		auto size_tip1 = WrongTip->getContentSize();
		WrongTip->setScale((0.4f*visibleSize.width) / size_tip1.width, (0.07f*visibleSize.height) / size_tip1.height);
		this->addChild(WrongTip, 0);
	}
}
void AddVarScene::menuCloseCallback(Ref* pSender)
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