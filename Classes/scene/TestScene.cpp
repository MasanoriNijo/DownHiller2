#include "TestScene.h"
#include "TitleScene.h"
#include "audio/include/AudioEngine.h"
USING_NS_CC;

Scene* TestScene::createScene() {
	auto scene = Scene::create();
	auto layer = TestScene::create();
    scene->addChild(layer);
	// return the scene
	return scene;
}
TestScene::TestScene():_productTitle(NULL){}

TestScene::~TestScene() {
	CC_SAFE_RELEASE_NULL(_productTitle);
}

// on "init" you need to initialize your instance
bool TestScene::init() {

	if (!Layer::init()) {
		return false;
	}
	this->scheduleUpdate();
	auto director = Director::getInstance();
	auto winSize = director->getWinSize();

	auto udf = UserDefault::getInstance();

	int hh = 95;


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

}

void TestScene::SetTouchListenner() {

	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {
        
        CCLOG("");
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



		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,this);

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

