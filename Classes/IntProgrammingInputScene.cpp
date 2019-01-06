#include "IntProgrammingInputScene.h"
#include <iostream>
#include <fstream>
#include "UI.h"
#include "ShowPageScene.h"
#include "other functions.h"

USING_NS_CC;

bool IntProgrammingInputScene::tag(0);
std::string IntProgrammingInputScene::int_num;

Scene* IntProgrammingInputScene::createScene()
{
	auto scene = Scene::create();
	auto layer = IntProgrammingInputScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool IntProgrammingInputScene::init()
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
		input >> NumVar;
		input.close();
	}
	else
	{
		CCLOG("IntInputWrong!");
		Director::getInstance()->end();
	}



	if (tag == 0)
	{		// add "HelloWorld" splash screen"
		auto tip7 = Sprite::create("tip7.png");
		// position the sprite on the center of the screen
		tip7->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
		auto size_tip1 = tip7->getContentSize();
		tip7->setScale((0.7f*visibleSize.width) / size_tip1.width, (0.15f*visibleSize.height) / size_tip1.height);
		this->addChild(tip7, 0);
	}
	else
	{
		auto tip7 = Sprite::create("tip8.png");
		// position the sprite on the center of the screen
		tip7->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 75));
		auto size_tip1 = tip7->getContentSize();
		tip7->setScale((0.7f*visibleSize.width) / size_tip1.width, (0.3f*visibleSize.height) / size_tip1.height);
		this->addChild(tip7, 0);
	}

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(IntProgrammingInputScene::menuCloseCallback, this));



	auto size_closeItem = closeItem->getContentSize();
	closeItem->setScale((0.1f*visibleSize.width) / size_closeItem.width, (0.1f*visibleSize.height) / size_closeItem.height);
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 13,
		origin.y + closeItem->getContentSize().height / 2 + 10));

	// create menu, it's an autorelease object

	Size int_input_size = CCSizeMake(300, 60);
	EditBox* int_input = EditBox::create(int_input_size, Scale9Sprite::create("white_ground.png"));;
	int_input->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 40));
	this->addChild(int_input);

	int_input->setFontName("fonts/Paint Boy.ttf");
	int_input->setFontSize(30);
	int_input->setFontColor(Color3B(0, 0, 0));
	int_input->setMaxLength(30); //限制字符长度
	int_input->setDelegate(this);


	auto button_complete = MenuItemImage::create(
		"complete.png",
		"complete.png",
		CC_CALLBACK_1(IntProgrammingInputScene::changeToNextScene, this));

	button_complete->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 125));
	auto size_button_complete = button_complete->getContentSize();
	button_complete->setScale((0.27f*visibleSize.width) / size_button_complete.width, (0.15f*visibleSize.height) / size_button_complete.height);

	auto menu = Menu::create(button_complete, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	return true;
}

void IntProgrammingInputScene::changeToNextScene(cocos2d::Ref* pSender)
{
	std::string input = FileUtils::getInstance()->getWritablePath() + "IntInput.txt";
	std::ofstream out;
	out.open(input.c_str(), std::ios::app);
	if (out.is_open())
	{
		if (tag == 0)
		{
			if (lessThan(int_num, 1, NumVar))
			{
				out << int_num << std::endl;
				tag = 1;
				out.close();
				std::istringstream input(int_num);
				int a;
				input >> a;
				if (a != NumVar)
				{
					Director::getInstance()->replaceScene(IntProgrammingInputScene::createScene());
				}
				else
				{
					begin_cal();
				}
			}
			else
			{
				out.close();
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
		else
		{
			std::istringstream input(int_num);
			int a;
			input >> a;
			if (lessThan(int_position, a, NumVar))
			{
				out << int_position << std::endl;
				out.close();
				begin_cal();
			}
			else
			{
				out.close();
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
	}
	else
	{
		CCLOG("WRONG");
		Director::getInstance()->end();
	}
}
void IntProgrammingInputScene::menuCloseCallback(Ref* pSender)
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

void IntProgrammingInputScene::begin_cal()
{
	CCLOG("intBeginCal");
	UIgetInstance().Fst_in();
	CCLOG("intBeginCalEnd");
	ShowPageScene::tag = 1;
	Director::getInstance()->replaceScene(ShowPageScene::createScene());
}