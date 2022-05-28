#include "GameScene.h"
#include "ImovileAd.h"

USING_NS_CC;

Scene* GameScene::createScene() {

	auto scene = Scene::create();

	auto layer = GameScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;
}
GameScene::GameScene() :
		_ad(NULL), _layerColor(NULL) {

}

GameScene::~GameScene() {
	CC_SAFE_RELEASE_NULL(_ad);
	CC_SAFE_RELEASE_NULL(_layerColor);
}

// on "init" you need to initialize your instance
bool GameScene::init() {

	if (!Layer::init()) {
		return false;
	}

	auto director = Director::getInstance();
	winSize = director->getWinSize();
	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	//imovileAdをセットする。
	this->setAD(ImovileAd::create());
	this->getAD()->txtFlg = false;
	this->getAD()->instFlg = false;

	return true;
}

void GameScene::GetRGBFromHSV(float h, float s, float v) {

	float r = v;
	float g = v;
	float b = v;
	if (s > 0.0f) {
		h *= 6.0f;
		int i = (int) h;
		float f = h - (float) i;
		switch (i) {
		default:
		case 0:
			g *= 1 - s * (1 - f);
			b *= 1 - s;
			break;
		case 1:
			r *= 1 - s * f;
			b *= 1 - s;
			break;
		case 2:
			r *= 1 - s;
			b *= 1 - s * (1 - f);
			break;
		case 3:
			r *= 1 - s;
			g *= 1 - s * f;
			break;
		case 4:
			r *= 1 - s * (1 - f);
			g *= 1 - s;
			break;
		case 5:
			g *= 1 - s;
			b *= 1 - s * f;
			break;
		}
	}

	R = r * 255;
	G = g * 255;
	B = b * 255;

}
void GameScene::ChgRGBFromHSV(float h, float s, float v) {

// (float h, float s, float v)
	r = v;
	g = v;
	b = v;
	if (s > 0.0f) {
		h *= 6.0f;
		int i = (int) h;
		float f = h - (float) i;
		switch (i) {
		default:
		case 0:
			g *= 1 - s * (1 - f);
			b *= 1 - s;
			break;
		case 1:
			r *= 1 - s * f;
			b *= 1 - s;
			break;
		case 2:
			r *= 1 - s;
			b *= 1 - s * (1 - f);
			break;
		case 3:
			r *= 1 - s;
			g *= 1 - s * f;
			break;
		case 4:
			r *= 1 - s * (1 - f);
			g *= 1 - s;
			break;
		case 5:
			g *= 1 - s;
			b *= 1 - s * f;
			break;
		}
	}
}
void GameScene::ChgBeforeColor() {
	//前回保存された色にする。
	this->setLayerColor(
			LayerColor::create(
					Color4B(UserDefault::getInstance()->getIntegerForKey("R", r),
							UserDefault::getInstance()->getIntegerForKey("G", g),
							UserDefault::getInstance()->getIntegerForKey("B", b), 255)));
//	this->_layerColor->setColor(
//			Color3B(UserDefault::getInstance()->getIntegerForKey("R", r),
//					UserDefault::getInstance()->getIntegerForKey("G", g),
//					UserDefault::getInstance()->getIntegerForKey("B", b)));

	this->addChild(this->_layerColor);

}

void GameScene::ChgColor(float h, float s, float v) {
	//色相h,彩度ｓ、明度vを指定して、色を変更する。
	this->h_ = h;
	this->s_ = s;
	this->v_ = v;
	this->ChgRGBFromHSV(h, s, v);

	r *= 255;
	g *= 255;
	b *= 255;
	UserDefault::getInstance()->setIntegerForKey("R", r);
	UserDefault::getInstance()->setIntegerForKey("G", g);
	UserDefault::getInstance()->setIntegerForKey("B", b);

	this->setLayerColor(
			LayerColor::create(
					Color4B(UserDefault::getInstance()->getIntegerForKey("R", r),
							UserDefault::getInstance()->getIntegerForKey("G", g),
							UserDefault::getInstance()->getIntegerForKey("B", b), 255)));

	this->addChild(this->_layerColor);

}

void GameScene::ChgColorRnd(float s, float v) {

	int rndh_ = arc4random() % static_cast<int>(255);
	float h_ = (float) rndh_ / (float) 255;
	this->ChgRGBFromHSV(h_, s, v);

	r *= 255;
	g *= 255;
	b *= 255;
	UserDefault::getInstance()->setIntegerForKey("R", r);
	UserDefault::getInstance()->setIntegerForKey("G", g);
	UserDefault::getInstance()->setIntegerForKey("B", b);

	this->setLayerColor(
			LayerColor::create(
					Color4B(UserDefault::getInstance()->getIntegerForKey("R", r),
							UserDefault::getInstance()->getIntegerForKey("G", g),
							UserDefault::getInstance()->getIntegerForKey("B", b), 255)));
//	this->_layerColor->setColor(
//			Color3B(UserDefault::getInstance()->getIntegerForKey("R", r),
//					UserDefault::getInstance()->getIntegerForKey("G", g),
//					UserDefault::getInstance()->getIntegerForKey("B", b)));

	this->addChild(this->_layerColor);

}

