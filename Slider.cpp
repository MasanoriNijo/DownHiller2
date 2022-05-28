#include "Slider.h"

#include "cocos2d.h"
#include "cmath"
USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int SliderCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
Slider::Slider() :
		_tumami(NULL), _atai(NULL), _namae(NULL),  _namae1(NULL), _namae2(NULL),_plusBtn(NULL), _minusBtn(NULL), _plusBtnImg(NULL), _minusBtnImg(
		NULL), _menu1(NULL), _menu2(NULL), _memori(NULL) {
}
Slider::~Slider() {
	CC_SAFE_RELEASE_NULL(_tumami);
	CC_SAFE_RELEASE_NULL(_atai);
	CC_SAFE_RELEASE_NULL(_namae);
	CC_SAFE_RELEASE_NULL(_namae1);
	CC_SAFE_RELEASE_NULL(_namae2);

	CC_SAFE_RELEASE_NULL(_plusBtn);
	CC_SAFE_RELEASE_NULL(_minusBtn);
	CC_SAFE_RELEASE_NULL(_plusBtnImg);
	CC_SAFE_RELEASE_NULL(_minusBtnImg);
	CC_SAFE_RELEASE_NULL(_menu1);
	CC_SAFE_RELEASE_NULL(_menu2);
	CC_SAFE_RELEASE_NULL(_memori);
}
bool Slider::init() {

	if (!Sprite::initWithFile("sliderback2.png")) {
		return false;
	}
	this->setScale(1.0f);
	this->setAnchorPoint(Vec2(0.5, 0.5)); //右端を基準ポイントにする。

	this->setMemori(Sprite::create("memori2.png"));
	this->_memori->setPosition(this->getContentSize().width / 2, 40);
	this->addChild(this->_memori, 1);

	frameSize = Size(this->_memori->getContentSize().width, this->_memori->getContentSize().height);

	varLength = frameSize.width;

	this->setTumami(Sprite::create("tumami2.png"));
	this->_memori->addChild(_tumami, 1);

	TTFConfig ttfConfig3("HGRPP1.TTC", 50, GlyphCollection::DYNAMIC);
	this->setAtai(Label::createWithTTF(ttfConfig3, "123"));
	this->getAtai()->setColor(Color3B::WHITE);
	_atai->setAnchorPoint(Vec2(0.5, 1));
//_atai->setAnchorPoint(Vec2::ZERO);
	_atai->setAlignment(TextHAlignment::CENTER);
	//_atai->enableOutline(Color4B::BLACK, 2);
	//_atai->setVisible(false);
	_atai->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height +50));
	this->addChild(_atai, 1);

	this->setNamae(Label::createWithTTF(ttfConfig3, "NAMAE"));
	this->getNamae()->setColor(Color3B::WHITE);
	_namae->setAnchorPoint(Vec2(0.5, 1));
//_atai->setAnchorPoint(Vec2::ZERO);
	_namae->setAlignment(TextHAlignment::CENTER);
	//_namae->enableOutline(Color4B::BLACK, 2);
	//_namae->setVisible(false);
	_namae->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height - 15));
	this->addChild(_namae, 1);

	TTFConfig ttfConfig2("HGRPP1.TTC", 30, GlyphCollection::DYNAMIC);

	this->setNamae1(Label::createWithTTF(ttfConfig2, "NAMAE1"));
	this->getNamae1()->setColor(Color3B::WHITE);
	_namae1->setAnchorPoint(Vec2(0, 0));
//_atai->setAnchorPoint(Vec2::ZERO);
	_namae1->setAlignment(TextHAlignment::LEFT);
	//_namae->enableOutline(Color4B::BLACK, 2);
	//_namae->setVisible(false);
	_namae1->setPosition(Vec2(30,  68));
	this->addChild(_namae1, 1);

	this->setNamae2(Label::createWithTTF(ttfConfig2, "NAMAE2"));
	this->getNamae2()->setColor(Color3B::WHITE);
	_namae2->setAnchorPoint(Vec2(1, 0));
//_atai->setAnchorPoint(Vec2::ZERO);
	_namae2->setAlignment(TextHAlignment::RIGHT);
	//_namae->enableOutline(Color4B::BLACK, 2);
	//_namae->setVisible(false);
	_namae2->setPosition(Vec2(this->getContentSize().width-30,  68));
	this->addChild(_namae2, 1);





	this->setPlusBtn(MenuItemImage::create("plusbtn2.png", "tumami2.png", [this](Ref* ref) {
		this->AddAtai(1);
	}));
	this->setMenu1(Menu::create(_plusBtn, NULL));
	this->getMenu1()->setPosition(this->getContentSize().width -60, 40);
	this->addChild(_menu1, 1);
//	this->setPlusBtnImg(Sprite::create("plusbtn2.png"));
//	this->_plusBtnImg->setPosition(this->_menu1->getPosition());
//	this->addChild(_plusBtnImg, 2);

	this->setMinusBtn(MenuItemImage::create("minusbtn2.png", "tumami2.png", [this](Ref* ref) {
		this->AddAtai(-1);
	}));
	this->setMenu2(Menu::create(_minusBtn, NULL));
	this->getMenu2()->setPosition(60, 40);
	this->addChild(_menu2, 1);
//	this->setMinusBtnImg(Sprite::create("minusbtn2.png"));
//	this->_minusBtnImg->setPosition(this->_menu2->getPosition());
//	this->addChild(_minusBtnImg, 2);

//	this->scheduleUpdate();

	this->SlideMove(50);

	return true;
}
Vec2 Slider::GetLocalPt(Vec2 pt) {
	//ペアレントノードでの座標点を、このローカル座標に変換する。

	Vec2 pt_;
	Vec2 pt2_;

	if (this->getParent()) {
		Node* nd = this->getParent();

		pt2_.set(this->getContentSize().width * this->getAnchorPoint().x,
				this->getContentSize().height * this->getAnchorPoint().y);
		pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(this->getRotation()));
		pt_.set(pt - this->getPosition());
		pt_ += pt2_;
		pt_.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(this->getRotation()));
	}

	return pt_;

}
void Slider::SetNamaeTag(std::string namae_) {

	this->getNamae()->setString("" + namae_);

}

void Slider::SlideMove(cocos2d::Vec2 pt) {

	//スライダーを動かす。
	if (this->selFlg) {

		Vec2 ptp;
		ptp.set(pt - this->getPosition() + Vec2(frameSize.width / 2, 0));
		float k = (float) ptp.x / (float) this->varLength;
		float xx = (float) (MaxValue - MinValue) * k + (float) MinValue;

		if ((int) xx < this->MinValue) {
			xx = (float) this->MinValue;
		}
		if ((int) xx > this->MaxValue) {
			xx = (float) this->MaxValue;
		}

		this->SlideMove((int) xx);

	}

}
void Slider::SlideMove(int xx) {

	this->Value_ = xx;

	float k = float(xx - MinValue) / (float) (MaxValue - MinValue);

	this->_tumami->setPosition((float) varLength * k, frameSize.height / 2);
	//this->_atai->setString("aaa");
	this->getAtai()->setString("" + StringUtils::toString((int) xx));

}
void Slider::AddAtai(int x) {
	//値を増減する

	this->Value_ += x;

	if (this->Value_ > MaxValue) {
		this->Value_ = MaxValue;
	}
	if (this->Value_ < MinValue) {
		this->Value_ = MinValue;
	}
	SlideMove(this->Value_);
//	this->getAtai()->setString("" + StringUtils::toString((int) this->Value_));

}

//void Slider::AddChildSub() {
//	//通常のaddChildとセットで使用
//	if (this->getParent()) {
//		this->_memori->setPosition(this->getPosition()+Vec2(this->getContentSize().width / 2, 80));
//		this->getParent()->addChild(this->_memori, this->getZOrder()+1);
//	}
//
//}

bool Slider::SelectTumami(Vec2 pt_) {
	//つまみを選択しているかどうかチェック。
	Vec2 ptp;
	ptp.set(this->GetLocalPt(pt_));

	Rect rect = this->_memori->getBoundingBox();

	//touch->getworldPosition();
	if (rect.containsPoint(ptp)) {
		this->selFlg = true;
		const char *str = "Slider::SelectTumami";
		log("%s", str);
	} else {
		const char *str1 = "Slider::SelectTumami_not";
		log("%s", str1);
		this->selFlg = false;

//		this->getTumami()->setPosition(ptp);
	}

	Rect rect2 = this->getBoundingBox();

	//touch->getworldPosition();
	if (rect2.containsPoint(pt_)) {
		this->selFlg2 = true;

	} else {



		this->selFlg2 = false;
//		this->setPosition(-200,-200);
//		this->getTumami()->setPosition(ptp);
	}

//	SelectMinusBtn(GetLocalPt(pt_));
//	SelectPlusBtn(GetLocalPt(pt_));
	return selFlg;

}
bool Slider::SelectPlusBtn(Vec2 pt_) {
	//つまみを選択しているかどうかチェック。
	Vec2 ptp;
	ptp.set(pt_);

	Rect rect = this->getPlusBtnImg()->getBoundingBox();

	//touch->getworldPosition();
	if (rect.containsPoint(ptp)) {
		this->plusFlg = true;
		tchTime_ = 0;
	} else {
		this->plusFlg = false;
	}
	return plusFlg;
}

bool Slider::SelectMinusBtn(Vec2 pt_) {
	//つまみを選択しているかどうかチェック。
	Vec2 ptp;
	ptp.set(pt_);

	Rect rect = this->getMinusBtnImg()->getBoundingBox();

	//touch->getworldPosition();
	if (rect.containsPoint(ptp)) {
		this->minusFlg = true;
		tchTime_ = 0;
	} else {
		this->minusFlg = false;
	}
	return minusFlg;
}

void Slider::TchOff() {
	//タッチパラメータを初期化

//	plusFlg = false;
	minusFlg = false;
	tchTime_ = 0;
	addTime_ = 0;
}
void Slider::update(float dt) {

//	const char *str0 = "Slider::update";
//	log("%s", str0);

//	if (plusFlg) {
//		tchTime_ += dt;
//
//		const char *str = "Slider::update tchTime_ += dt";
//		log("%s", str);
//
//		if (tchTime_ > TchTime) {
//			addTime_ += dt;
//
//			const char *str1 = "Slider::update addTime_ += dt";
//			log("%s", str1);
//
//			if (addTime_ > AddTime) {
//				addTime_ -= AddTime;
//				this->AddAtai(1);
//			}
//		}
//	}
//	if (minusFlg) {
//		tchTime_ += dt;
//		if (tchTime_ > TchTime) {
//			addTime_ += dt;
//
//			if (addTime_ > AddTime) {
//				addTime_ -= AddTime;
//				this->AddAtai(-1);
//			}
//		}
//	}
}

