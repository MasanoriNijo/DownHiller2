#include "TestScene.h"
#include "TitleScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* TestScene::createScene() {

	auto scene = Scene::create();

	auto layer = TestScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;

}
TestScene::TestScene() :
		_productTitle(NULL), _slider(NULL), _slider2(NULL), _slider3(NULL), _slider4(
		NULL), _slider5(NULL), _slider6(NULL), _slider7(NULL), _slider8(
		NULL), _slider9(NULL), _slider10(NULL), _slider11(NULL), _slider12(NULL), _touchlistener(
		NULL), _prmBtn(NULL), _menuPrm(NULL), _plusBtn(NULL), _plusMenu(NULL), _minusBtn(NULL), _minusMenu(
		NULL), _indexLavel(NULL) {

}

TestScene::~TestScene() {
	CC_SAFE_RELEASE_NULL(_menuPrm);
	CC_SAFE_RELEASE_NULL(_prmBtn);
	CC_SAFE_RELEASE_NULL(_productTitle);
	CC_SAFE_RELEASE_NULL(_slider);
	CC_SAFE_RELEASE_NULL(_slider2);
	CC_SAFE_RELEASE_NULL(_slider3);
	CC_SAFE_RELEASE_NULL(_slider4);
	CC_SAFE_RELEASE_NULL(_slider5);
	CC_SAFE_RELEASE_NULL(_slider6);
	CC_SAFE_RELEASE_NULL(_slider7);
	CC_SAFE_RELEASE_NULL(_slider8);
	CC_SAFE_RELEASE_NULL(_slider9);
	CC_SAFE_RELEASE_NULL(_slider10);
	CC_SAFE_RELEASE_NULL(_slider11);
	CC_SAFE_RELEASE_NULL(_slider12);

	CC_SAFE_RELEASE_NULL(_touchlistener);

	CC_SAFE_RELEASE_NULL(_plusBtn);
	CC_SAFE_RELEASE_NULL(_plusMenu);
	CC_SAFE_RELEASE_NULL(_minusBtn);
	CC_SAFE_RELEASE_NULL(_minusMenu);
	CC_SAFE_RELEASE_NULL(_indexLavel);
}

// on "init" you need to initialize your instance
bool TestScene::init() {

	if (!Layer::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto director = Director::getInstance();
	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();
	auto winSize = director->getWinSize();
//	this->setProductTitle(Sprite::create("kotokotobokanmark.png")); //��Ŗ߂��Bdebugwaku.png back.png
//	_productTitle->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
//	_productTitle->setOpacity(0);
//	auto fadein_ = FadeIn::create(1.0f);
//	auto delaytime_ = DelayTime::create(1.0f);
//	auto fadeout_ = FadeOut::create(1.0f);
//	auto start_ = CallFuncN::create([this](Node* node_) {
//		auto scene=TitleScene::createScene();
//		auto transition=TransitionCrossFade::create(0.5,scene);
//		Director::getInstance()->replaceScene(transition);
//	});

//	this->_productTitle->runAction(
//			Sequence::create(fadein_, delaytime_, fadeout_, start_, NULL));

//
	auto udf = UserDefault::getInstance();
//	udf->getIntegerForKey("LEVEL", 1));

	int hh = 95;

	this->setSlider(Slider::create());
	this->_slider->setPosition(winSize.width / 2, winSize.height - 100);
	this->addChild(_slider, 1);
	this->_slider->MinValue = 1;
	this->_slider->MaxValue = 5;
	this->_slider->SlideMove(udf->getIntegerForKey("MADER_CNT", 5));
	this->_slider->SetNamaeTag("同時に生成する壁の数");
	_touchSpritepool.pushBack(_slider);

	this->setSlider2(Slider::create());
	this->_slider2->setPosition(_slider->getPosition() - Vec2(0, hh));
	this->addChild(_slider2, 1);
	this->_slider2->MinValue = 2;
	this->_slider2->MaxValue = 100;
	this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU", 5));
	this->_slider2->SetNamaeTag("TYOKU");
	_touchSpritepool.pushBack(_slider2);

	this->setSlider3(Slider::create());
	this->_slider3->setPosition(_slider2->getPosition() - Vec2(0, hh));
	this->addChild(_slider3, 1);
	this->_slider3->MinValue = 1;
	this->_slider3->MaxValue = 100;
	this->_slider3->SlideMove(udf->getIntegerForKey("EDA", 5));
	this->_slider3->SetNamaeTag("EDA");
	_touchSpritepool.pushBack(_slider3);

	this->setSlider4(Slider::create());
	this->_slider4->setPosition(_slider3->getPosition() - Vec2(0, hh));
	this->addChild(_slider4, 1);
	this->_slider4->MinValue = 2;
	this->_slider4->MaxValue = 100;
	this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU", 5));
	this->_slider4->SetNamaeTag("ZIZOKU");
	_touchSpritepool.pushBack(_slider4);

	this->setSlider5(Slider::create());
	this->_slider5->setPosition(_slider4->getPosition() - Vec2(0, hh));
	this->addChild(_slider5, 1);
	this->_slider5->MinValue = 1;
	this->_slider5->MaxValue = 100;
	this->_slider5->SlideMove(udf->getIntegerForKey("KABE", 5));
	this->_slider5->SetNamaeTag("KABE");
	_touchSpritepool.pushBack(_slider5);

	this->setSlider6(Slider::create());
	this->_slider6->setPosition(_slider5->getPosition() - Vec2(0, hh));
	this->addChild(_slider6, 1);
	this->_slider6->MinValue = 1;
	this->_slider6->MaxValue = 100;
	this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI", 5));
	this->_slider6->SetNamaeTag("SYOKI");
	_touchSpritepool.pushBack(_slider6);

	this->setSlider7(Slider::create());
	this->_slider7->setPosition(_slider6->getPosition() - Vec2(0, hh));
	this->addChild(_slider7, 1);
	this->_slider7->MinValue = 2;
	this->_slider7->MaxValue = 100;
	this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2", 5));
	this->_slider7->SetNamaeTag("TYOKU2");
	_touchSpritepool.pushBack(_slider7);

	this->setSlider8(Slider::create());
	this->_slider8->setPosition(_slider7->getPosition() - Vec2(0, hh));
	this->addChild(_slider8, 1);
	this->_slider8->MinValue = 1;
	this->_slider8->MaxValue = 100;
	this->_slider8->SlideMove(udf->getIntegerForKey("EDA2", 5));
	this->_slider8->SetNamaeTag("EDA2");
	_touchSpritepool.pushBack(_slider8);

	this->setSlider9(Slider::create());
	this->_slider9->setPosition(_slider8->getPosition() - Vec2(0, hh));
	this->addChild(_slider9, 1);
	this->_slider9->MinValue = 2;
	this->_slider9->MaxValue = 100;
	this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2", 5));
	this->_slider9->SetNamaeTag("ZIZOKU2");
	_touchSpritepool.pushBack(_slider9);

	this->setSlider10(Slider::create());
	this->_slider10->setPosition(_slider9->getPosition() - Vec2(0, hh));
	this->addChild(_slider10, 1);
	this->_slider10->MinValue = 1;
	this->_slider10->MaxValue = 100;
	this->_slider10->SlideMove(udf->getIntegerForKey("KABE2", 5));
	this->_slider10->SetNamaeTag("KABE2");
	_touchSpritepool.pushBack(_slider10);

	this->setSlider11(Slider::create());
	this->_slider11->setPosition(_slider10->getPosition() - Vec2(0, hh));
	this->addChild(_slider11, 1);
	this->_slider11->MinValue = 1;
	this->_slider11->MaxValue = 200;
	this->_slider11->SlideMove(udf->getIntegerForKey("COURCE_X", 5));
	this->_slider11->SetNamaeTag("CourceSize X");
	_touchSpritepool.pushBack(_slider11);

	this->setSlider12(Slider::create());
	this->_slider12->setPosition(_slider11->getPosition() - Vec2(0, hh));
	this->addChild(_slider12, 1);
	this->_slider12->MinValue = 1;
	this->_slider12->MaxValue = 200;
	this->_slider12->SlideMove(udf->getIntegerForKey("COURCE_Y", 5));
	this->_slider12->SetNamaeTag("CourceSize Y");
	_touchSpritepool.pushBack(_slider12);
	this->setPrmBtn(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {
//		this->SetPrm();
			this->SetPrm(this->index);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
			auto scene = TitleScene::createScene();
			auto transition = TransitionCrossFade::create(0.5, scene);
			Director::getInstance()->replaceScene(transition);

		}));
	this->_prmBtn->setScale(1.0f);
	this->setMenuPrm(Menu::create(this->_prmBtn, NULL));
	_menuPrm->setPosition(Vec2(winSize.width - this->_prmBtn->getContentSize().width / 2 - 30, 60));
	this->addChild(this->_menuPrm, 10);

	TTFConfig ttfConfig3("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);

	this->setIndexLavel(Label::createWithTTF(ttfConfig3, "Index:" + StringUtils::toString(this->index)));
	this->_indexLavel->setPosition(160, 60);
	this->_indexLavel->setScale(1.0f);
	this->_indexLavel->setColor(Color3B::WHITE);
	this->_indexLavel->setAnchorPoint(Vec2(0, 0));
	this->_indexLavel->setAlignment(TextHAlignment::CENTER);
	this->addChild(this->_indexLavel, 10);

	this->setPlusBtn(MenuItemImage::create("yazi_r.png", "yazi_rp.png", [this](Ref* ref) {
//		this->SetPrm();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
			this->SetPrm(this->index);
			if(this->index<5) {
				this->index++;
				this->GetPrm(this->index);
				this->_indexLavel->setString("Index:" + StringUtils::toString(this->index));
			}

		}));
	this->setPlusMenu(Menu::create(this->_plusBtn, NULL));
	this->_plusMenu->setPosition(Vec2(winSize.width / 2, 60));
	this->addChild(this->_plusMenu, 10);

	this->setMinusBtn(MenuItemImage::create("yazi_l.png", "yazi_lp.png", [this](Ref* ref) {
//		this->SetPrm();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
			this->SetPrm(this->index);
			if(this->index>0) {
				this->index--;
				this->GetPrm(this->index);
				this->_indexLavel->setString("Index:" + StringUtils::toString(this->index));
			}
		}));
	this->setMinusMenu(Menu::create(this->_minusBtn, NULL));
	this->_minusMenu->setPosition(Vec2(60, 60));
	this->addChild(this->_minusMenu, 10);

	this->GetPrm(this->index);

	this->SetTouchListenner();
	return true;
}

void TestScene::SetPrm() {

	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("MADER_CNT", this->_slider->Value_);
	udf->setIntegerForKey("TYOKU", this->_slider2->Value_);
	udf->setIntegerForKey("EDA", this->_slider3->Value_);
	udf->setIntegerForKey("ZIZOKU", this->_slider4->Value_);
	udf->setIntegerForKey("KABE", this->_slider5->Value_);
	udf->setIntegerForKey("SYOKI", this->_slider6->Value_);
	udf->setIntegerForKey("TYOKU2", this->_slider7->Value_);
	udf->setIntegerForKey("EDA2", this->_slider8->Value_);
	udf->setIntegerForKey("ZIZOKU2", this->_slider9->Value_);
	udf->setIntegerForKey("KABE2", this->_slider10->Value_);
	udf->setIntegerForKey("COURCE_X", this->_slider11->Value_);
	udf->setIntegerForKey("COURCE_Y", this->_slider12->Value_);
}
void TestScene::SetPrm(int index_) {

	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("MADER_CNT", this->_slider->Value_);
	udf->setIntegerForKey("COURCE_X", this->_slider11->Value_);
	udf->setIntegerForKey("COURCE_Y", this->_slider12->Value_);
	this->index = index_;

	switch (this->index) {

	case 0: {
		udf->setIntegerForKey("TYOKU_0", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_0", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_0", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_0", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_0", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_0", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_0", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_0", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_0", this->_slider10->Value_);
		break;
	}
	case 1: {
		udf->setIntegerForKey("TYOKU_1", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_1", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_1", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_1", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_1", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_1", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_1", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_1", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_1", this->_slider10->Value_);
		break;
	}
	case 2: {
		udf->setIntegerForKey("TYOKU_2", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_2", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_2", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_2", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_2", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_2", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_2", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_2", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_2", this->_slider10->Value_);
		break;
	}
	case 3: {
		udf->setIntegerForKey("TYOKU_3", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_3", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_3", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_3", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_3", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_3", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_3", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_3", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_3", this->_slider10->Value_);
		break;
	}
	case 4: {
		udf->setIntegerForKey("TYOKU_4", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_4", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_4", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_4", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_4", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_4", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_4", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_4", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_4", this->_slider10->Value_);
		break;
	}
	case 5: {
		udf->setIntegerForKey("TYOKU_5", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_5", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_5", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_5", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_5", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_5", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_5", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_5", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_5", this->_slider10->Value_);
		break;
	}
	case 6: {
		udf->setIntegerForKey("TYOKU_6", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_6", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_6", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_6", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_6", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_6", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_6", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_6", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_6", this->_slider10->Value_);
		break;
	}
	case 7: {
		udf->setIntegerForKey("TYOKU_7", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_7", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_7", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_7", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_7", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_7", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_7", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_7", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_7", this->_slider10->Value_);
		break;
	}
	case 8: {
		udf->setIntegerForKey("TYOKU_8", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_8", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_8", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_8", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_8", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_8", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_8", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_8", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_8", this->_slider10->Value_);
		break;
	}
	case 9: {
		udf->setIntegerForKey("TYOKU_9", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_9", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_9", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_9", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_9", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_9", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_9", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_9", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_9", this->_slider10->Value_);
		break;
	}
	case 10: {
		udf->setIntegerForKey("TYOKU_10", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_10", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_10", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_10", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_10", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_10", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_10", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_10", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_10", this->_slider10->Value_);
		break;
	}
	case 11: {
		udf->setIntegerForKey("TYOKU_11", this->_slider2->Value_);
		udf->setIntegerForKey("EDA_11", this->_slider3->Value_);
		udf->setIntegerForKey("ZIZOKU_11", this->_slider4->Value_);
		udf->setIntegerForKey("KABE_11", this->_slider5->Value_);
		udf->setIntegerForKey("SYOKI_11", this->_slider6->Value_);
		udf->setIntegerForKey("TYOKU2_11", this->_slider7->Value_);
		udf->setIntegerForKey("EDA2_11", this->_slider8->Value_);
		udf->setIntegerForKey("ZIZOKU2_11", this->_slider9->Value_);
		udf->setIntegerForKey("KABE2_11", this->_slider10->Value_);
		break;
	}

	}

}

void TestScene::GetPrm(int index_) {

	auto udf = UserDefault::getInstance();
	this->_slider->SlideMove(udf->getIntegerForKey("MADER_CNT", 5));
	this->_slider11->SlideMove(udf->getIntegerForKey("COURCE_X", 5));
	this->_slider12->SlideMove(udf->getIntegerForKey("COURCE_Y", 5));

	this->index = index_;

	switch (this->index) {

	case 0: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_0", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_0", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_0", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_0", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_0", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_0", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_0", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_0", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_0", 5));
		break;
	}
	case 1: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_1", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_1", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_1", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_1", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_1", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_1", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_1", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_1", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_1", 5));
		break;
	}
	case 2: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_2", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_2", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_2", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_2", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_2", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_2", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_2", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_2", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_2", 5));
		break;
	}
	case 3: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_3", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_3", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_3", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_3", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_3", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_3", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_3", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_3", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_3", 5));
		break;
	}
	case 4: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_4", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_4", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_4", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_4", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_4", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_4", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_4", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_4", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_4", 5));
		break;
	}
	case 5: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_5", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_5", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_5", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_5", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_5", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_5", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_5", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_5", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_5", 5));
		break;
	}
	case 6: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_6", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_6", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_6", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_6", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_6", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_6", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_6", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_6", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_6", 5));
		break;
	}
	case 7: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_7", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_7", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_7", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_7", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_7", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_7", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_7", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_7", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_7", 5));
		break;
	}
	case 8: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_8", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_8", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_8", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_8", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_8", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_8", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_8", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_8", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_8", 5));
		break;
	}
	case 9: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_9", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_9", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_9", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_9", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_9", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_9", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_9", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_9", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_9", 5));
		break;
	}
	case 10: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_10", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_10", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_10", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_10", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_10", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_10", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_10", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_10", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_10", 5));
		break;
	}
	case 11: {
		this->_slider2->SlideMove(udf->getIntegerForKey("TYOKU_11", 5));
		this->_slider3->SlideMove(udf->getIntegerForKey("EDA_11", 5));
		this->_slider4->SlideMove(udf->getIntegerForKey("ZIZOKU_11", 5));
		this->_slider5->SlideMove(udf->getIntegerForKey("KABE_11", 5));
		this->_slider6->SlideMove(udf->getIntegerForKey("SYOKI_11", 5));
		this->_slider7->SlideMove(udf->getIntegerForKey("TYOKU2_11", 5));
		this->_slider8->SlideMove(udf->getIntegerForKey("EDA2_11", 5));
		this->_slider9->SlideMove(udf->getIntegerForKey("ZIZOKU2_11", 5));
		this->_slider10->SlideMove(udf->getIntegerForKey("KABE2_11", 5));
		break;
	}

	}

}

void TestScene::SetTouchListenner() {

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		//最初のタッチのみ

			//	this->_slider->setPosition(touch->getLocation());

			for (Slider* tchsp:this->_touchSpritepool) {

				tchsp->SelectTumami(touch->getLocation());
//				tchsp->SelectMinusBtn(touch->getLocation());
//				tchsp->SelectPlusBtn(touch->getLocation());
			}

			this->_point1.set(touch->getLocation());
			this->_point2.set(touch->getLocation());

			return true;

		};

	_touchlistener->onTouchMoved = [this](Touch* touch,Event* event) {
		//this->setPosition(this->getPosition()+touch->getDelta());
		// this->_point1.set(this->_point2);
			this->_point2.set(touch->getLocation());

			for (Slider* tchsp:this->_touchSpritepool) {

				tchsp->SlideMove(touch->getLocation());

			}

		};
	_touchlistener->onTouchEnded = [this](Touch* touch,Event* event) {

//		const char *str4 = "touch4";
//		log("%s", str4);
			this->_point1.set(Vec2::ZERO);
			this->_point2.set(Vec2::ZERO);

			for (Slider* tchsp:this->_touchSpritepool) {

				tchsp->TchOff();

			}

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,
			this);

}

void TestScene::update(float dt) {

//	if (_slider->Value_ == 0 && _slider2->Value_ == 0
//			&& _slider3->Value_ == 0) {
//		this->addChild(_productTitle, 3);
//	}

}

void TestScene::onEnterTransitionDidFinish() {

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("open.mp3", false);

}

