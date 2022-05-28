#include "cocos2d.h"
#include "Dot.h"
#include "cmath"
USING_NS_CC;

Dot::Dot() :
		_body(NULL), _body2(NULL), _cLabel(NULL), _DotState(DotState::START), speed_(1.0f), speed2_(1.0f) {
}
Dot::~Dot() {

	CC_SAFE_RELEASE_NULL(_body);
	CC_SAFE_RELEASE_NULL(_body2);
	CC_SAFE_RELEASE_NULL(_cLabel);
}

Dot* Dot::create(const std::string& filename) {
	Dot *sprite = new Dot();
	if (sprite && sprite->initWithFile(filename)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	sprite = NULL;
	return NULL;
}

void Dot::ResetDot() {
	dspCnt = 0;
	dpCnt = 0;
	dsCnt = 0;
	rndState = 0;
//
//	this->setBody(NULL);
//	this->getBody()->removeAllShapes(true);
//	this->getBody()->removeFromWorld();

	if (this->getBody()) {
		this->getBody()->removeAllShapes(true);
		this->getBody()->removeFromWorld();
	}
	if (this->getBody2()) {
		this->getBody2()->removeAllShapes(true);
		this->getBody2()->removeFromWorld();
	}
//	this->getChildren()

//	Node * nd = NULL;

//	CCARRAY_FOREACH_REVERSE(this->getChildren(), nd) {
//
//		nd->removeFromParentAndCleanup(true);
//
//	}

//this->removeChildByTag(1,true);

//	this->removeAllChildrenWithCleanup(true);

}

bool Dot::initWithFile(const std::string& filename) {

	if (!Sprite::initWithFile(filename)) {
		return false;
	}
	auto director = Director::getInstance();
	winSize = director->getWinSize();

	frameSize = Size(this->getContentSize().width, this->getContentSize().height);
	this->cPt_.set(frameSize.width / 2, frameSize.height / 2);

	this->setOpacity(0);

	return true;
}

bool Dot::init() {

	if (!Node::init()) {
		return false;
	}
	auto director = Director::getInstance();
	winSize = director->getWinSize();

	frameSize = Size(this->getContentSize().width, this->getContentSize().height);

	this->cPt_.set(frameSize.width / 2, frameSize.height / 2);
	this->cPt_.set(18, 18);
//	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

//	this->setBody(PhysicsBody::createCircle(frameSize.width / 2));
//	this->setPhysicsBody(this->_body);
//	this->_body->setDynamic(false);
//	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
//	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
//	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
//	this->getBody()->setTag(0);
	this->setOpacity(0);

	return true;
}
void Dot::rndMade(int prm1, int prm2, int prm3, int cnt_) {

	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, -M_PI / 6);

	int k;
	rndState = 1;
	int rndA = arc4random() % static_cast<int>(prm1);
	int rndB = arc4random() % static_cast<int>(prm2);
	int rndC = arc4random() % static_cast<int>(prm3);
	while (dpCnt < 60 or k < cnt_) {

		if (rndA == 0) {
			rndB = arc4random() % static_cast<int>(prm2) - prm2 / 2;
			rndC = arc4random() % static_cast<int>(prm3) + 100;
			this->madeKobu(rndC, rndB);

//			madePt.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(rndB));
		}

//		const char *str4 = "Dot::rndMade";
//		log("%s", str4);

		this->AddDot(madePt + SetPt);
		rndA = arc4random() % static_cast<int>(prm1);
		k++;
	}

	if (dpCnt >= 60) {
		rndState = 2;
		SetShape();

	}
}

void Dot::ShowCourceOrder(int No, int MaxNo) {

	if (!this->getCLabel()) {
		TTFConfig ttfConfig("HGRSGU.TTC", 40, GlyphCollection::DYNAMIC);
		this->setCLabel(Label::createWithTTF(ttfConfig, "経過時間:"));
		_cLabel->setColor(Color3B::WHITE);
		_cLabel->setAnchorPoint(Vec2::ZERO);
		_cLabel->setAlignment(TextHAlignment::LEFT);
		_cLabel->setPosition(20, winSize.height - 60);
		this->addChild(_cLabel, 1);
	}

	Vec2 dct;
	dct.set(this->_dotG.at(1)->getPosition() - this->_dotG.at(0)->getPosition());
	dct.normalize();
//	this->_cLabel->setRotation(-CC_RADIANS_TO_DEGREES(dct.getAngle()));
	dct.rotate(Vec2::ZERO, M_PI / 2);
	dct *= 100;
	dct += this->_dotG.at(0)->getPosition();
	this->_cLabel->setPosition(dct);
	this->_cLabel->setString(StringUtils::toString(No) + "/" + StringUtils::toString(MaxNo));
}

void Dot::ShowCourceName(int cNo) {

	if (!this->getCLabel()) {
		TTFConfig ttfConfig("HGRSGU.TTC", 40, GlyphCollection::DYNAMIC);
		this->setCLabel(Label::createWithTTF(ttfConfig, "C1"));
		_cLabel->setColor(Color3B::WHITE);
		_cLabel->setAnchorPoint(Vec2::ZERO);
		_cLabel->setAlignment(TextHAlignment::LEFT);
		_cLabel->setPosition(20, winSize.height - 60);
		this->addChild(_cLabel, 1);
	}

	Vec2 dct;
	dct.set(this->_dotG.at(1)->getPosition() - this->_dotG.at(0)->getPosition());
	dct.normalize();
//	this->_cLabel->setRotation(-CC_RADIANS_TO_DEGREES(dct.getAngle()));
	dct.rotate(Vec2::ZERO, M_PI / 2);
	dct *= 100;
	dct += this->_dotG.at(0)->getPosition();
	this->_cLabel->setPosition(dct);
	this->_cLabel->setString("C" + StringUtils::toString(cNo));
}
void Dot::CPtn1() {
//	source_C01_0_10_0
	cNo =1 ;
	cLvl=0 ;
	this->madeMaruR(1000, CC_DEGREES_TO_RADIANS(-5));
	this->Masugu(1000);
	this->SetShape();
}
void Dot::CPtn2() {
//	source_C02_0__
	cNo =2 ;
	cLvl=0 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 6;
	this->madeMaru(0.8, -M_PI / 6);
	this->Masugu(1000);
	this->SetShape();
}
void Dot::CPtn3() {
//	source_C03_1__
	cNo =3 ;
	cLvl=1 ;
	this->RecPos();
	this->madeMaruR_k(350, -30);
	this->Masugu(400);
	this->madeMaruR_k(350, 0);
	this->Masugu(280);
	this->SetShape();
}
void Dot::CPtn4() {
//	source_C04_1__
	cNo =4 ;
	cLvl=1 ;
	this->RecPos();
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-45));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-10));
	this->madeMaruR(450, CC_DEGREES_TO_RADIANS(-55));
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-8));
	this->SetShape();
}
void Dot::CPtn5() {
//	source_C05_1__
	cNo =5 ;
	cLvl=1 ;
	this->RecPos();
	this->madeMaruR_k(50, -10);
	this->Masugu(150);
	this->madeKobu(60, -30);
	this->madeKobu(30, -30);
	this->madeKobu(30, -30);
	this->madeKobu(60, -30);
	this->madeKobu(30, -30);
	this->madeKobu(50, -30);
	this->madeKobu(40, -30);
	this->madeKobu(30, -30);
	this->madeKobu(60, -30);
	this->madeKobu(30, -30);
	this->madeKobu(70, -30);
	this->madeKobu(30, -30);
	this->SetShape();
}
void Dot::CPtn6() {
//	source_C06_1__
	cNo =6 ;
	cLvl=1 ;
	this->RecPos();
	this->madeMaruR_k(350, 0);
	this->madeMaruR_k(1000, -30);
	this->madeKobu(80, 50);
	this->madeMaruR_k(850, -45);
	this->madeMaruR_k(350, 0);
	this->Masugu(400);
	this->SetShape();
}
void Dot::CPtn7() {
//	source_C07_1__
	cNo =7 ;
	cLvl=1 ;
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.03, -M_PI / 3);
	this->madeMaru(0.02, 0);
	this->madeMaru(0.08, -M_PI / 2);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn8() {
//	source_C08_1__
	cNo =8 ;
	cLvl=1 ;
	this->Masugu(100, -M_PI / 6);
	this->madeDansa(800, 200, 2 * M_PI);
	this->madeMaru(0.01, -M_PI / 4);
	this->SetShape();
}
void Dot::CPtn9() {
//	source_C09_2__
	cNo =9 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR_k(100, -30);
	this->madeMaruR_k(90, 10);
	this->madeMaruR_k(80, -80);
	this->madeMaruR_k(120, -10);
	this->madeMaruR_k(80, -80);
	this->madeMaruR_k(180, -10);
	this->madeMaruR_k(80, -80);
	this->madeMaruR_k(180, -10);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn10() {
//	source_C10_2__
	cNo =10 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR_k(50, -30);
	this->madeDansa(600, -150, 3 * M_PI);
	this->madeMaruR_k(250, -5);
	this->SetShape();
}
void Dot::CPtn11() {
//	source_C11_2__
	cNo =11 ;
	cLvl=2 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 3;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(800);
	this->madeMaru(0.02, 0);
	this->madeMaru(0.04, M_PI / 3);
	this->madeMaru(0.04, -M_PI / 3);
	this->SetShape();
}
void Dot::CPtn12() {
//	source_C12_2__
	cNo =12 ;
	cLvl=2 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(600);
	this->madeMaru(0.1, 0);
	this->Masugu(200);
	this->madeKobu(30, 30);
	this->Masugu(100);
	this->madeMaru(0.1, M_PI / 4);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn13() {
//	source_C13_2__
	cNo =13 ;
	cLvl=2 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 4;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(100);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, M_PI / 4);
	this->madeMaru(0.1, -M_PI / 4);
	this->Masugu(100);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(100);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, M_PI / 4);
	this->madeMaru(0.1, -M_PI / 4);
	this->Masugu(100);
	this->SetShape();
}
void Dot::CPtn14() {
//	source_C14_2__
	cNo =14 ;
	cLvl=2 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.05, -M_PI / 4);
	this->Masugu(200);
	this->madeMaru(0.05, M_PI / 5);
	this->Masugu(80);
	this->madeMaru(0.07, -M_PI / 4);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn15() {
//	source_C15_2__
	cNo =15 ;
	cLvl=2 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 5;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.007, -M_PI / 4);
	this->madeKobu(400, 200);
	this->madeMaru(0.008, 0);
	this->Masugu(400);
	this->SetShape();
}
void Dot::CPtn16() {
//	source_C16_2__
	cNo =16 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR(400, CC_DEGREES_TO_RADIANS(-70));
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(-30));
	this->madeMaruR(650, CC_DEGREES_TO_RADIANS(-85));
	this->madeMaruR(400, CC_DEGREES_TO_RADIANS(-10));
	this->SetShape();
}
void Dot::CPtn17() {
//	source_C17_2__
	cNo =17 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-85));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-10));
	this->madeMaruR(450, CC_DEGREES_TO_RADIANS(-65));
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-8));
	this->SetShape();
}
void Dot::CPtn18() {
//	source_C18_2__
	cNo =18 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-90));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(5));
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(-65));
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(0));
	this->SetShape();
}
void Dot::CPtn19() {
//	source_C19_2__
	cNo =19 ;
	cLvl=2 ;
	this->RecPos();
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(15));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(15));
	this->SetShape();
}
void Dot::CPtn20() {
//	source_C20_2__
	cNo =20 ;
	cLvl=2 ;
	this->Masugu(400, -M_PI / 6);
	this->madeDansa(500, 200, 2 * M_PI);
	this->madeMaru(0.01, -M_PI / 12);
	this->SetShape();
}
void Dot::CPtn21() {
//	source_C21_3__
	cNo =21 ;
	cLvl=3 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(400);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, M_PI / 4);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.05, -M_PI / 4);
	this->madeMaru(0.05, 0);
	this->madeMaru(0.08, M_PI / 4);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn22() {
//	source_C22_3__
	cNo =22 ;
	cLvl=3 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 6;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(600);
	this->madeMaru(0.8, -M_PI / 6 + M_PI / 2);
	this->madeMaru(0.8, -M_PI / 6 - M_PI / 2);
	this->madeMaru(0.8, -M_PI / 6);
	this->Masugu(800);
	this->madeMaru(0.5, -M_PI / 6 + M_PI / 2);
	this->madeMaru(0.4, -M_PI / 6 - M_PI / 2);
	this->madeMaru(0.5, -M_PI / 6);
	this->Masugu(600);
	this->madeMaru(0.3, -M_PI / 6 + M_PI / 2);
	this->madeMaru(0.9, -M_PI / 6 - M_PI / 2);
	this->madeMaru(0.1, -M_PI / 6);
	this->SetShape();
}
void Dot::CPtn23() {
//	source_C23_3__
	cNo =23 ;
	cLvl=3 ;
	this->RecPos();
	this->Masugu(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(150, 0);
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-85));
	this->Masugu(150, 0);
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-85));
	this->Masugu(150, 0);
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-85));
	this->Masugu(250, 0);
	this->SetShape();
}
void Dot::CPtn24() {
//	source_C24_3__
	cNo =24 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu(250);
	this->Masugu_k(80, -90);
	this->Masugu_k(250, 0);
	this->Masugu_k(90, -90);
	this->Masugu_k(150, 0);
	this->Masugu_k(80, -90);
	this->Masugu_k(150, 0);
	this->Masugu_k(80, -90);
	this->Masugu_k(250, 0);
	this->Masugu_k(80, -90);
	this->Masugu_k(150, 0);
	this->SetShape();
}
void Dot::CPtn25() {
//	source_C25_3__
	cNo =25 ;
	cLvl=3 ;
	this->Masugu_k(400, -30);
	this->Masugu_k(30, -120);
	this->Masugu_k(400, -30);
	this->Masugu_k(30, 60);
	this->Masugu_k(400, -15);
	this->Masugu_k(60, -105);
	this->Masugu_k(400, -15);
	this->Masugu_k(50, 75);
	this->Masugu_k(400, -15);
	this->SetShape();
}
void Dot::CPtn26() {
//	source_C26_3__
	cNo =26 ;
	cLvl=3 ;
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.01, -M_PI / 12);
	this->madeKobu(30, 30);
	this->madeMaru(0.01, -M_PI * 2 / 12);
	this->madeKobu(30, 30);
	this->madeMaru(0.01, -M_PI * 4 / 12);
	this->madeKobu(30, 30);
	this->madeMaru(0.01, -M_PI * 5 / 12);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn27() {
//	source_C27_3__
	cNo =27 ;
	cLvl=3 ;
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(100);
	madePt.set(w, 0);
	mrad_ = -M_PI / 2 + M_PI / 8;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(150);
	madePt.set(w, 0);
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(150);
	madePt.set(w, 0);
	mrad_ = -M_PI / 2 + M_PI / 8;
	;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(200);
	madePt.set(w, 0);
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(200);
	madePt.set(w, 0);
	mrad_ = -M_PI / 2 + M_PI / 8;
	;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(250);
	madePt.set(w, 0);
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(200);
	madePt.set(w, 0);
	mrad_ = -M_PI / 2 + M_PI / 8;
	;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(250);
	madePt.set(w, 0);
	this->SetShape();
}
void Dot::CPtn28() {
//	source_C28_3__
	cNo =28 ;
	cLvl=3 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4 - M_PI / 8);
	this->Masugu(100);
	this->madeMaru(0.2, M_PI / 4 - M_PI / 5);
	this->Masugu(100);
	this->madeMaru(0.2, -M_PI / 4 - M_PI / 9);
	this->Masugu(200);
	this->madeMaru(0.2, M_PI / 4 - M_PI / 4);
	this->Masugu(100);
	this->madeMaru(0.2, -M_PI / 4 - M_PI / 8);
	this->Masugu(100);
	this->madeMaru(0.2, M_PI / 4 - M_PI / 10);
	this->Masugu(200);
	this->SetShape();
}
void Dot::CPtn29() {
//	source_C29_3__
	cNo =29 ;
	cLvl=3 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(200);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, -M_PI / 4);
	this->Masugu(150);
	this->madeMaru(0.1, M_PI / 4);
	this->madeMaru(0.1, -M_PI / 4);
	this->Masugu(300);
	this->madeMaru(0.1, M_PI / 4);
	this->SetShape();
}
void Dot::CPtn30() {
//	source_C30_3__
	cNo =30 ;
	cLvl=3 ;
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-10));
	this->Masugu(150);
	this->RecPos();
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn31() {
//	source_C31_3__
	cNo =31 ;
	cLvl=3 ;
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(150);
	this->RecPos();
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->madeDansa(50, -50);
	this->Masugu(150);
	this->madeDansa(50, 50);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn32() {
//	source_C32_3__
	cNo =32 ;
	cLvl=3 ;
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-5));
	this->Masugu(150);
	this->madeKobuR(30, true);
	this->RecPos();
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->SetShape();
}
void Dot::CPtn33() {
//	source_C33_3__
	cNo =33 ;
	cLvl=3 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-25));
	this->Masugu(150);
	this->madeKobuR(30, true);
	this->RecPos();
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->Masugu(350);
	this->madeKobuR(30, true);
	this->SetShape();
}
void Dot::CPtn34() {
//	source_C34_3__
	cNo =34 ;
	cLvl=3 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-30));
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->RecPos();
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->Masugu(350);
	this->SetShape();
}
void Dot::CPtn35() {
//	source_C35_3__
	cNo =35 ;
	cLvl=3 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-45));
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->RecPos();
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->madeDansa(100, 100);
	this->madeDansa(100, -100);
	this->Masugu(350);
	this->SetShape();
}
void Dot::CPtn36() {
//	source_C36_3__
	cNo =36 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(400);
	this->Masugu(200, -M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(200, -M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(200, -M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(200, -M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn37() {
//	source_C37_3__
	cNo =37 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(300);
	this->Masugu(100, -M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(100, -M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(100, -M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(100, -M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn38() {
//	source_C38_3__
	cNo =38 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(550, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(15));
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(-65));
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(20));
	this->SetShape();
}
void Dot::CPtn39() {
//	source_C39_3__
	cNo =39 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(15));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(15));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-75));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(15));
	this->SetShape();
}
void Dot::CPtn40() {
//	source_C40_3__
	cNo =40 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-40));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(40));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-40));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(40));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-40));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(40));
	this->SetShape();
}
void Dot::CPtn41() {
//	source_C41_3__
	cNo =41 ;
	cLvl=3 ;
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-30));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-70));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-110));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(30));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(250);
	this->SetShape();
}
void Dot::CPtn42() {
//	source_C42_3__
	cNo =42 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-45));
	this->madeDansa(250, -50, 2 * M_PI);
	this->madeDansa(350, -50, 2 * M_PI);
	this->madeDansa(250, -50, 2 * M_PI);
	this->madeDansa(350, -50, 2 * M_PI);
	this->madeDansa(250, -50, 2 * M_PI);
	this->SetShape();
}
void Dot::CPtn43() {
//	source_C43_3__
	cNo =43 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-15));
	this->madeDansa(250, -50, 2 * M_PI);
	this->madeDansa(350, -50, M_PI);
	this->madeDansa(250, -50, M_PI / 2);
	this->madeDansa(350, -50, 2.5 * M_PI);
	this->madeDansa(250, -50, 2 * M_PI);
	this->madeDansa(250, -50, M_PI);
	this->madeDansa(250, -50, M_PI / 2);
	this->SetShape();
}
void Dot::CPtn44() {
//	source_C44_3__
	cNo =44 ;
	cLvl=3 ;
	this->RecPos();
	this->Masugu(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(350, CC_DEGREES_TO_RADIANS(-45));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(45));
	this->Masugu(350, CC_DEGREES_TO_RADIANS(-45));
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(45));
	this->Masugu(250, 0);
	this->SetShape();
}
void Dot::CPtn45() {
//	source_C45_3__
	cNo =45 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR_k(50, -30);
	this->madeDansa(400, -150, 6 * M_PI);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn46() {
//	source_C46_3__
	cNo =46 ;
	cLvl=3 ;
	this->Masugu(400, -M_PI / 3);
	this->madeMaru(0.015, 0);
	this->Masugu(400);
	this->madeKobu(400, -200);
	this->Masugu(200);
	this->madeKobu(400, -150);
	this->Masugu(100);
	this->SetShape();
}
void Dot::CPtn47() {
//	source_C47_3__
	cNo =47 ;
	cLvl=3 ;
	this->RecPos();
	this->madeMaruR_k(50, 0);
	this->Masugu(250);
	this->Masugu_k(50, -90);
	this->Masugu_k(150, -35);
	this->madeMaruR_k(150, 0);
	this->Masugu_k(80, -90);
	this->Masugu_k(150, -25);
	this->madeMaruR_k(150, 0);
	this->Masugu_k(60, -90);
	this->Masugu_k(150, -15);
	this->Masugu_k(60, -90);
	this->madeMaruR_k(150, 45);
	this->Masugu_k(60, -90);
	this->madeMaruR_k(250, 0);
	this->SetShape();
}
void Dot::CPtn48() {
//	source_C48_4__
	cNo =48 ;
	cLvl=4 ;
	this->RecPos();
	this->Masugu(250, CC_DEGREES_TO_RADIANS(-20));
	mrad_ = CC_DEGREES_TO_RADIANS(45);
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-45));
	mrad_ = CC_DEGREES_TO_RADIANS(45);
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(-45));
	mrad_ = CC_DEGREES_TO_RADIANS(45);
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(250, 0);
	this->SetShape();
}
void Dot::CPtn49() {
//	source_C49_4__
	cNo =49 ;
	cLvl=4 ;
	this->RecPos();
	this->Masugu(250, CC_DEGREES_TO_RADIANS(-20));
	mrad_ = CC_DEGREES_TO_RADIANS(-45);
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(45));
	mrad_ = CC_DEGREES_TO_RADIANS(-45);
	this->madeMaruR(200, CC_DEGREES_TO_RADIANS(45));
	mrad_ = CC_DEGREES_TO_RADIANS(-45);
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(45));
	this->Masugu(250, 0);
	this->SetShape();
}
void Dot::CPtn50() {
//	source_C50_4__
	cNo =50 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu(400);
	this->madeMaruR_k(200, 65);
	this->Masugu(10);
	this->madeMaruR_k(200, 0);
	this->madeMaruR_k(550, -45);
	this->Masugu(400);
	this->madeMaruR_k(250, 0);
	this->SetShape();
}
void Dot::CPtn51() {
//	source_C51_4__
	cNo =51 ;
	cLvl=4 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 4);
	this->Masugu(400);
	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, M_PI / 4);
	this->Masugu(80);
	this->madeMaru(0.05, 0);
	this->madeMaru(0.05, -M_PI / 4);
	this->madeMaru(0.05, 0);
	this->SetShape();
}
void Dot::CPtn52() {
//	source_C52_4__
	cNo =52 ;
	cLvl=4 ;
	this->madeMaru(0.02, -M_PI / 3);
	this->Masugu(800);
	this->madeMaru(0.06, 0);
	this->Masugu(150);
	this->madeMaru(0.08, M_PI / 3);
	this->Masugu(80);
	this->madeMaru(0.1, 0);
	this->SetShape();
}
void Dot::CPtn53() {
//	source_C53_4__
	cNo =53 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR_k(120, 0);
	this->Masugu(250);
	this->madeMaruR_k(250, 80);
	this->Masugu(150, 0);
	this->madeMaruR_k(-80, 250, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn54() {
//	source_C54_4__
	cNo =54 ;
	cLvl=4 ;
	this->RecPos();
	this->Masugu_k(400, -45);
	this->Masugu_k(80, -120);
	this->Masugu_k(350, -30);
	this->Masugu_k(30, 60);
	this->Masugu_k(400, -15);
	this->Masugu_k(160, -105);
	this->Masugu_k(450, -15);
	this->Masugu_k(90, 75);
	this->Masugu_k(400, -15);
	this->SetShape();
}
void Dot::CPtn55() {
//	source_C55_4__
	cNo =55 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-50));
	this->Masugu(1000);
	this->madeMaruR(400, CC_DEGREES_TO_RADIANS(1));
	this->Masugu(160);
	this->Masugu(150, -M_PI / 2);
	this->Masugu(850, CC_DEGREES_TO_RADIANS(-35));
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(500);
	this->SetShape();
}
void Dot::CPtn56() {
//	source_C56_4__
	cNo =56 ;
	cLvl=4 ;
	this->RecPos();
	this->RecPos();
	this->madeMaruR_k(50, -30);
	this->madeKobu(120, -80);
	this->madeKobu(60, -30);
	this->madeKobu(250, -100);
	this->madeKobu(100, -50);
	this->madeKobu(150, -70);
	this->SetShape();
}
void Dot::CPtn57() {
//	source_C57_4__
	cNo =57 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR_k(150, -20);
	this->Masugu(350);
	this->madeKobuR(200, false);
	this->Masugu_k(450, -45);
	this->madeMaruR_k(250, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn58() {
//	source_C58_4__
	cNo =58 ;
	cLvl=4 ;
	madePt.set(w, 0);
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.2, -M_PI / 2);
	this->Masugu(120);
	this->madeMaru(0.08, M_PI / 2);
	this->Masugu(10);
	this->madeMaru(0.2, -M_PI / 12);
	this->Masugu(400);
	this->SetShape();
}
void Dot::CPtn59() {
//	source_C59_4__
	cNo =59 ;
	cLvl=4 ;
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaru(0.02, -M_PI * 4 / 12);
	this->Masugu(500);
	this->madeMaru(0.03, 0);
	this->Masugu(200);
	this->madeMaru(0.1, M_PI / 2);
	this->madeMaru(0.8, 0);
	this->SetShape();
}
void Dot::CPtn60() {
//	source_C60_4__
	cNo =60 ;
	cLvl=4 ;
	this->Masugu_k(400, -45);
	this->madeKobu(30, 30);
	this->Masugu_k(300, -30);
	this->madeKobu(50, 50);
	this->Masugu_k(250, -50);
	this->madeKobu(80, 80);
	this->Masugu_k(300, 0);
	this->madeKobu(50, 50);
	this->Masugu_k(100, -60);
	this->madeMaruR_k(150, 0);
	this->SetShape();
}
void Dot::CPtn61() {
//	source_C61_4__
	cNo =61 ;
	cLvl=4 ;
	this->Masugu(400, -M_PI / 3);
	this->madeMaru(0.01, 0);
	this->Masugu(400);
	this->madeDansa(20, 200, M_PI / 2);
	this->Masugu(200);
	this->SetShape();
}
void Dot::CPtn62() {
//	source_C62_4__
	cNo =62 ;
	cLvl=4 ;
	this->Masugu(400, -M_PI / 3);
	this->madeMaruR(400, -M_PI / 5);
	this->madeKobu(50, 50);
	this->madeMaru(0.01, 0);
	this->Masugu(400);
	this->madeDansa(20, 200, M_PI / 2);
	this->Masugu(200);
	this->SetShape();
}
void Dot::CPtn63() {
//	source_C63_4__
	cNo =63 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR_k(50, -10);
	this->Masugu(150);
	this->madeKobuR(120, false);
	this->Masugu_k(250, -30);
	this->madeKobuR(50, true);
	this->Masugu(250);
	this->madeKobuR(120, false);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn64() {
//	source_C64_4__
	cNo =64 ;
	cLvl=4 ;
	this->madeMaruR(400, CC_DEGREES_TO_RADIANS(-20));
	this->madeKobuR(50, true);
	this->RecPos();
	this->madeMaruR(400, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(150);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-30));
	this->madeKobuR(150, false);
	this->Masugu(300);
	this->SetShape();
}
void Dot::CPtn65() {
//	source_C65_4__
	cNo =65 ;
	cLvl=4 ;
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(400);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(0));
	this->RecPos();
	this->Masugu(350);
	this->madeDansa(5, 60);
	this->Masugu(150);
	this->madeDansa(5, 30);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn66() {
//	source_C66_4__
	cNo =66 ;
	cLvl=4 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-25));
	this->Masugu(350);
	this->RecPos();
	this->madeKobuR(300, false);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn67() {
//	source_C67_4__
	cNo =67 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(250);
	this->Masugu(250, CC_DEGREES_TO_RADIANS(-90));
	this->Masugu(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(300, CC_DEGREES_TO_RADIANS(90));
	this->Masugu(150, CC_DEGREES_TO_RADIANS(0));
	this->SetShape();
}
void Dot::CPtn68() {
//	source_C68_4__
	cNo =68 ;
	cLvl=4 ;
	this->RecPos();
	this->madeMaruR_k(100, -45);
	this->Masugu(400);
	this->Masugu_k(1000, -90);
	this->Masugu_k(500, 0);
	this->Masugu_k(600, 90);
	this->Masugu_k(300, -45);
	this->madeMaruR_k(150, 0);
	this->Masugu_k(300, 0);
	this->SetShape();
}
void Dot::CPtn69() {
//	source_C69_5__
	cNo =69 ;
	cLvl=5 ;
	this->RecPos();
	this->Masugu_k(400, -45);
	this->Masugu_k(80, -120);
	this->Masugu_k(350, -30);
	this->Masugu_k(80, 60);
	this->Masugu_k(400, -35);
	this->Masugu_k(160, -95);
	this->Masugu_k(800, -15);
	this->Masugu_k(120, 75);
	this->Masugu_k(400, -15);
	this->SetShape();
}
void Dot::CPtn70() {
//	source_C70_5__
	cNo =70 ;
	cLvl=5 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu(350);
	this->madeKobu(50, 50);
	this->Masugu(450, CC_DEGREES_TO_RADIANS(-35));
	this->madeMaruR_k(250, 30);
	this->Masugu_k(250, -90);
	this->Masugu(200, 0);
	this->Masugu_k(250, 90);
	this->Masugu(400, 0);
	this->SetShape();
}
void Dot::CPtn71() {
//	source_C71_5__
	cNo =71 ;
	cLvl=5 ;
	madePt.set(w, 0);
	mrad_ = -M_PI / 6;
	madePt.rotate(Vec2::ZERO, mrad_);
	this->Masugu(100);
	this->madeMaru(0.05, -M_PI / 2);
	this->Masugu(100);
	this->madeMaru(0.2, 0);
	this->Masugu(100);
	this->madeMaru(0.2, M_PI / 2);
	this->Masugu(100);
	this->madeMaru(0.2, 0);
	this->Masugu(100);
	this->madeMaru(0.05, -M_PI / 2);
	this->Masugu(100);
	this->madeMaru(0.2, 0);
	this->Masugu(100);
	this->SetShape();
}
void Dot::CPtn72() {
//	source_C72_5__
	cNo =72 ;
	cLvl=5 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-5));
	this->Masugu(150);
	this->madeKobuR(150, false);
	this->RecPos();
	this->madeKobuR(60, true);
	this->Masugu_k(450, -20);
	this->madeKobuR(150, false);
	this->Masugu_k(250, 0);
	this->SetShape();
}
void Dot::CPtn73() {
//	source_C73_5__
	cNo =73 ;
	cLvl=5 ;
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(400);
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(150);
	this->madeKobu(200, -300);
	this->RecPos();
	this->Masugu(350);
	this->madeDansa(5, 90);
	this->SetShape();
}
void Dot::CPtn74() {
//	source_C74_5__
	cNo =74 ;
	cLvl=5 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(350);
	this->madeKobu(20, 60);
	this->Masugu(450);
	this->madeKobu(20, 60);
	this->Masugu(450);
	this->madeKobu(20, 60);
	this->Masugu(350);
	this->SetShape();
}
void Dot::CPtn75() {
//	source_C75_5__
	cNo =75 ;
	cLvl=5 ;
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(-10));
	this->madeKobu(20, 60);
	this->madeMaruR(1800, CC_DEGREES_TO_RADIANS(-20));
	this->madeKobu(20, 60);
	this->madeMaruR(1800, CC_DEGREES_TO_RADIANS(-30));
	this->madeKobu(20, 40);
	this->madeMaruR(1800, CC_DEGREES_TO_RADIANS(-20));
	this->madeKobu(20, 20);
	this->madeMaruR(1800, CC_DEGREES_TO_RADIANS(-10));
	this->SetShape();
}
void Dot::CPtn76() {
//	source_C76_5__
	cNo =76 ;
	cLvl=5 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(450);
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(45));
	this->Masugu(250, -M_PI / 2);
	this->Masugu(450, 0);
	this->Masugu(250, M_PI / 2);
	this->Masugu(50, -M_PI / 4);
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(0));
	this->SetShape();
}
void Dot::CPtn77() {
//	source_C77_5__
	cNo =77 ;
	cLvl=5 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(-30));
	this->Masugu(150);
	this->madeKobuR(50, true);
	this->Masugu(500);
	this->madeKobuR(400, false);
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(350);
	this->madeDansa(20, 60);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn78() {
//	source_C78_5__
	cNo =78 ;
	cLvl=5 ;
	this->RecPos();
	this->madeMaruR_k(50, 0);
	this->Masugu(250);
	this->Masugu_k(250, -90);
	this->Masugu_k(300, 0);
	this->Masugu_k(30, 90);
	this->madeMaruR_k(150, -45);
	this->Masugu(500);
	this->SetShape();
}
void Dot::CPtn79() {
//	source_C79_5__
	cNo =79 ;
	cLvl=5 ;
	this->madeMaruR_k(150, -30);
	this->Masugu_k(200, -30);
	this->madeKobuR(200, false);
	this->Masugu_k(200, 0);
	this->madeKobuR(150, false);
	this->Masugu_k(200, -45);
	this->madeKobuR(200, false);
	this->Masugu_k(200, 0);
	this->SetShape();
}
void Dot::CPtn80() {
//	source_C80_6__
	cNo =80 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(-45));
	this->Masugu(450);
	this->madeMaruR(500, CC_DEGREES_TO_RADIANS(45));
	this->Masugu(250, -M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(400, M_PI / 2);
	this->madeMaruR(20, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(300, 0);
	this->SetShape();
}
void Dot::CPtn81() {
//	source_C81_6__
	cNo =81 ;
	cLvl=6 ;
	this->Masugu(150);
	this->RecPos();
	this->madeMaruR(10, CC_DEGREES_TO_RADIANS(-10));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(-90));
	this->Masugu(150, 0);
	this->mrad_ = M_PI / 2;
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn82() {
//	source_C82_6__
	cNo =82 ;
	cLvl=6 ;
	this->RecPos();
	// madePt.set(w, 0);
	// mrad_ = -M_PI / 3;
	// madePt.rotate(Vec2::ZERO, mrad_);
	this->madeMaruR_k(10, 0);
	this->Masugu(150);
	this->madeMaruR_k(250, 80);
	this->Masugu_k(300, 0);
	this->madeMaruR_k(-80, 200, 0);
	this->Masugu(20);
	this->RecPos();
	this->madeMaruR_k(0, 200, 80);
	this->Masugu_k(150, 0);
	this->madeMaruR_k(-80, 250, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn83() {
//	source_C83_6__
	cNo =83 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(150, CC_DEGREES_TO_RADIANS(45));
	this->madeMaruR(350, CC_DEGREES_TO_RADIANS(-90));
	this->madeMaruR(250, CC_DEGREES_TO_RADIANS(75));
	this->Masugu(150, 0);
	this->SetShape();
}
void Dot::CPtn84() {
//	source_C84_6__
	cNo =84 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(250);
	this->Masugu(250, CC_DEGREES_TO_RADIANS(-90));
	this->Masugu(250, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(250, CC_DEGREES_TO_RADIANS(90));
	this->madeMaruR_k(50, -45);
	this->Masugu(500);
	this->SetShape();
}
void Dot::CPtn85() {
//	source_C85_6__
	cNo =85 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR_k(50, 0);
	this->Masugu(250);
	this->Masugu_k(50, -90);
	this->Masugu_k(150, 0);
	this->Masugu_k(50, -90);
	this->Masugu_k(250, 0);
	this->Masugu_k(50, 90);
	this->Masugu_k(150, 0);
	this->Masugu_k(50, 90);
	this->Masugu_k(250, 0);
	this->SetShape();
}
void Dot::CPtn86() {
//	source_C86_6__
	cNo =86 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu(250);
	this->Masugu_k(80, -90);
	this->Masugu_k(250, 0);
	this->Masugu_k(90, -90);
	this->Masugu_k(450, 0);
	this->Masugu_k(80, 90);
	this->Masugu_k(100, 0);
	this->SetShape();
}
void Dot::CPtn87() {
//	source_C87_6__
	cNo =87 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu_k(350, 0);
	this->madeMaruR_k(20, 85);
	this->madeMaruR_k(120, -85);
	this->madeMaruR_k(450, 0);
	this->madeMaruR_k(20, 85);
	this->madeMaruR_k(120, -85);
	this->madeMaruR_k(200, -20);
//	this->Masugu_k(200, -20);
	this->SetShape();
}
void Dot::CPtn88() {
//	source_C88_6__
	cNo =88 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(50, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(350);
	this->madeKobu(20, 80);
	this->Masugu(450);
	this->madeKobu(20, 80);
	this->Masugu(450);
	this->madeKobu(20, 80);
	this->Masugu(350);
	this->SetShape();
}
void Dot::CPtn89() {
//	source_C89_6__
	cNo =89 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(400);
	this->Masugu(600, -M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(600, M_PI / 2);
	this->Masugu(400, 0);
	this->Masugu(150);
	this->SetShape();
}
void Dot::CPtn90() {
//	source_C90_6__
	cNo =90 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(300);
	this->Masugu(50, M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(50, M_PI / 2);
	this->Masugu(300, 0);
	this->Masugu(50, M_PI / 2);
	this->Masugu(300, 0);
	this->SetShape();
}
void Dot::CPtn91() {
//	source_C91_6__
	cNo =91 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(0));
	this->Masugu(450);
	this->Masugu(80, M_PI / 2);
	this->Masugu(450, 0);
	this->Masugu(80, M_PI / 2);
	this->Masugu(300, 0);
	this->SetShape();
}
void Dot::CPtn92() {
//	source_C92_6__
	cNo =92 ;
	cLvl=6 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu_k(350, 0);
	this->Masugu_k(100, 85);
	this->Masugu_k(120, -85);
	this->Masugu_k(450, 0);
	this->Masugu_k(100, 85);
	this->Masugu_k(120, -85);
	this->Masugu_k(350, 0);
	this->SetShape();
}
void Dot::CPtn93() {
//	source_C93_7__
	cNo =93 ;
	cLvl=7 ;
	this->RecPos();
	this->madeMaruR(100, CC_DEGREES_TO_RADIANS(-70));
	this->Masugu(1000, CC_DEGREES_TO_RADIANS(-70));
	this->madeMaruR(300, CC_DEGREES_TO_RADIANS(70));
	this->Masugu(700);
	this->Masugu(400, 0);
	this->SetShape();
}
void Dot::CPtn94() {
//	source_C94_7__
	cNo =94 ;
	cLvl=7 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu_k(350, 0);
	this->Masugu_k(100, 90);
	this->madeMaruR_k(-90, 300, 90);
	this->Masugu_k(100, -90);
	this->Masugu_k(200, 0);
	this->SetShape();
}
void Dot::CPtn95() {
//	source_C95_7__
	cNo =95 ;
	cLvl=7 ;
	this->RecPos();
	this->madeMaruR_k(150, 0);
	this->Masugu_k(450, 0);
	this->Masugu_k(100, 85);
	this->Masugu_k(100, -85);
	this->Masugu_k(750, -30);
	this->madeMaruR_k(-30, 150, 30);
	this->Masugu_k(100, 90);
	this->Masugu_k(250, 0);
	this->SetShape();
}
void Dot::CPtn96() {
//	source_C96_7__
	cNo =96 ;
	cLvl=7 ;
	this->madeMaruR_k(10, 0);
	this->Masugu(450);
	this->madeMaruR_k(150, 80);
	this->Masugu_k(250, 0);
	this->Masugu_k(150, -80);
	this->madeMaruR_k(-80, 150, 80);
	this->Masugu_k(150, 80);
	this->Masugu_k(250, 0);
	this->madeMaruR_k(-80, 150, 0);
	this->Masugu(350);
	this->SetShape();
}
void Dot::CPtn97() {
//	source_C97_7__
	cNo =97 ;
	cLvl=7 ;
	this->madeMaruR_k(10, 0);
	this->Masugu(450);
	this->Masugu_k(150, -90);
	this->madeMaruR_k(-90, 80, 90);
	this->Masugu_k(150, 90);
	this->Masugu_k(150, 0);
	this->Masugu_k(150, -90);
	this->madeMaruR_k(-90, 100, 90);
	this->Masugu_k(150, 90);
	this->Masugu_k(250, 0);
	this->Masugu_k(150, -90);
	this->madeMaruR_k(-90, 100, 90);
	this->Masugu_k(150, 90);
	this->Masugu_k(100, 0);
	this->Masugu(250);
	this->SetShape();
}
void Dot::CPtn98() {
//	source_C98_7__
	cNo =98 ;
	cLvl=7 ;
	this->RecPos();
	this->madeMaruR_k(150, -45);
	this->Masugu_k(650, -45);
	this->madeMaruR_k(-45, 250, 45);
	this->Masugu_k(150, 45);
	this->Masugu_k(400, -90);
	this->Masugu_k(500, 0);
	this->Masugu_k(400, 90);
	this->Masugu(250, 0);
	this->SetShape();
}

void Dot::CPtn99() {
//	source_C99_7__
	cNo = 99;
	cLvl = 7;
	this->RecPos();
	this->Masugu_k(500, 0);
	this->Masugu_k(80, 120);
	this->madeMaruR_k(120, 20, 0);
	this->Masugu_k(400, 0);
	this->Masugu_k(100, 85);
	this->Masugu_k(120, -85);
	this->Masugu_k(400, 0);
	this->Masugu_k(250, -90);
	this->Masugu_k(250, 0);
	this->Masugu_k(250, 90);
	this->Masugu(250, 0);
	this->SetShape();
}

void Dot::rndMade2() {

	madePt.set(w, 0);
	mrad_ = -M_PI / 6;
	madePt.rotate(Vec2::ZERO, mrad_);

	this->madeMaru(0.1, 0);
	this->madeMaru(0.1, -M_PI / 3);
	this->Masugu(250);
	this->madeMaru(0.1, M_PI / 3);

	this->SetShape();

}
void Dot::rndMade3() {

	madePt.set(w, 0);
	mrad_ = -M_PI / 12;
	madePt.rotate(Vec2::ZERO, mrad_);

	int k;
	rndState = 1;
	int rndA = 10;
//	int rndB = arc4random() % static_cast<int>(prm2);
//	int rndC = arc4random() % static_cast<int>(prm3);
//	while (dpCnt < 60 or k < 10) {
//
//		if (rndA == 10) {
//			rndB = arc4random() % static_cast<int>(prm2) - prm2 / 2;
//			rndC = arc4random() % static_cast<int>(prm3) + 100;
	this->Masugu(400);
	this->RecPos();

	this->madeMaru(0.02, -M_PI / 2);
	this->Masugu(200);
	this->madeMaru(0.03, M_PI / 3);
	SetShape();

	this->JumpCource(Vec2(200, -50));

	rndA = 0;
//			madePt.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(rndB));
//		}
//
//		const char *str4 = "Dot::rndMade";
//		log("%s", str4);
//		madePt.set(w, 0);
//		mrad_ =0;
//		madePt.rotate(Vec2::ZERO, mrad_);
//
//		rndA++;
//		this->AddDot(madePt + SetPt);
//
//		k++;
//	}

//	if (dpCnt >= 60) {
//		rndState = 2;
//		SetShape();
//
//	}

//	this->SetPt+=Vec2(300,0);

}

void Dot::JumpCource(Vec2 pt) {
//ptの穴を作成
	SetShape();
	this->SetPt += pt;

}

void Dot::StartLine() {

	this->setDotState(DotState::START);

	this->cNo = 0;
	this->cLvl = 0;
	madePt.set(w, 0);
	mrad_ = -M_PI / 48;
	madePt.rotate(Vec2::ZERO, mrad_);

	this->Masugu(600);
	this->RecPos();
	this->Masugu(150);

//	this->rndMade2();
	SetShape();
}
void Dot::GoalLine() {
	this->setDotState(DotState::GOAL);
	this->cNo = 100;
	this->cLvl = 0;
	madePt.set(w, 0);
	mrad_ = 0;
	madePt.rotate(Vec2::ZERO, mrad_);

	this->Masugu(400);
	this->RecPos();

	this->Masugu(220);
	this->madeMaru(0.2, M_PI / 2);
	this->Masugu(100);
	this->madeMaru(0.2, -M_PI / 2);
	SetShape();
}

void Dot::Masugu(int dL) {
//真っ直ぐ
//	madePt.set(w, 0);

	int x = 0;

	bool fstFlg = true;

	while (dL > x) {

		if (fstFlg) {
			this->AddDot(SetPt + madePt, true);
			fstFlg = false;
		} else {
			this->AddDot(SetPt + madePt, false);
		}
		x += w;
	}
	Vec2 pt;
	pt.set(madePt);
	pt.normalize();
	pt *= (x - dL);
	this->AddDot(SetPt + pt, true);

}

void Dot::Masugu(int dL, float _mrad_) {
	//傾きを指定して真っ直ぐ

	madePt.set(w, 0);
	mrad_ = _mrad_;
	madePt.rotate(Vec2::ZERO, mrad_);
	int x = 0;

	bool fstFlg = true;

	while (dL > x) {

		if (fstFlg) {
			this->AddDot(SetPt + madePt, true);
			fstFlg = false;
		} else {
			this->AddDot(SetPt + madePt, false);
		}
		x += w;
	}
	Vec2 pt;
	pt.set(madePt);
	pt.normalize();
	pt *= (x - dL);
	this->AddDot(SetPt + pt, true);

}

void Dot::rndMade(int prm1, int prm2) {

	madePt.set(w, 0);
	mrad_ = -M_PI / 6;
	madePt.rotate(Vec2::ZERO, mrad_);

	int rndA = arc4random() % static_cast<int>(prm1);
	int rndB = arc4random() % static_cast<int>(prm2);
	int rndC = arc4random() % static_cast<int>(prm2);
	while (dpCnt < 80) {

		if (rndA == 0) {
			rndB = arc4random() % static_cast<int>(prm2) - prm2 / 2;
			rndC = arc4random() % static_cast<int>(prm2) + 100;
			this->madeKobu(rndC, rndB);

//			madePt.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(rndB));
		}

//		const char *str4 = "Dot::rndMade";
//		log("%s", str4);

		this->AddDot(madePt + SetPt);
		rndA = arc4random() % static_cast<int>(prm1);

	}

	SetShape();

}

void Dot::RecPos() {
//SetPt2,mrad2_に保持する。

	this->SetPt2.set(this->SetPt);
	this->mrad2_ = this->mrad_;

}

void Dot::madeDansa(int w, int h) {
//幅ｗ、高さhの段差を作る。

	this->madeDansa(w * 4, h, M_PI);

}

void Dot::madeKobu(int w, int h) {
//幅ｗ、高さhのコブ、穴を作る。

	this->madeDansa(w * 2, h, 2 * M_PI);

}

void Dot::madeDansa(int w, int h, float endRad) {
//幅ｗ、高さhのコブ、穴を作る。drad曲率
	rad2 = 0;
	int ccc = 0;
	trgPt1.set(this->SetPt);
	while (rad2 < endRad) {
		trgPt2.set(this->SinLength(h / 2, w, rad2, this->w, endRad));
		trgPt2.rotate(Vec2::ZERO, madePt.getAngle());
		ccc++;
		//２回に１回にする
		if (ccc == 3) {
			this->AddDot(trgPt1 + trgPt2, true);
			ccc = 0;
//			const char *str3 = "Dot::madeKobu";
//			log("%s", str3);
		} else {
			this->AddDot(trgPt1 + trgPt2, false);
		}
	}

}

void Dot::madeKobuR(int R, float upFlg_) {
	//半径Ｒのコブ、穴を作る。

	if (upFlg_) {

		mrad_ += M_PI / 2;
		this->madeMaruR(R, mrad_ - M_PI);
		madePt.set(w, 0);
		mrad_ += M_PI / 2;
		madePt.rotate(Vec2::ZERO, mrad_);
	} else {
		mrad_ -= M_PI / 2;
		this->madeMaruR(R, mrad_ + M_PI);
		madePt.set(w, 0);
		mrad_ -= M_PI / 2;
		madePt.rotate(Vec2::ZERO, mrad_);
	}

}

void Dot::madeMaruR(int R, float endrad) {
	//半径Ｒでの丸を描く

	float drad = (float) w / (float) R;

	this->madeMaru(drad, endrad);

}

void Dot::madeMaruR_k(int R, float endkaku) {
	//半径Ｒでの丸を描く,角度指定
	this->madeMaruR(R, CC_DEGREES_TO_RADIANS(endkaku));

}
void Dot::madeMaruR_k(float fstkaku, int R, float endkaku) {
	//半径Ｒでの丸を描く,角度指定
	this->mrad_ = CC_DEGREES_TO_RADIANS(fstkaku);
	this->madeMaruR(R, CC_DEGREES_TO_RADIANS(endkaku));

}
void Dot::Masugu_k(int dL, float kaku) {
	//傾きを指定して真っ直ぐ
	this->Masugu(dL, CC_DEGREES_TO_RADIANS(kaku));

}

void Dot::madeMaru(float drad, float endrad) {

	int ccc = 0;

	if (mrad_ < endrad) {

		ccc = 2;
		while (mrad_ < endrad) {
			madePt.set(w, 0);
			mrad_ += drad;

			if (endrad <= mrad_) {
				mrad_ = endrad;
				madePt.rotate(Vec2::ZERO, mrad_);
				this->AddDot(SetPt + madePt, true);
				return;
//				ccc=2;
			}

			madePt.rotate(Vec2::ZERO, mrad_);
			ccc++;
			//２回に１回にする
			if (ccc == 3) {
				this->AddDot(SetPt + madePt, true);
				ccc = 0;
//				const char *str3 = "Dot::madeMaru";
//				log("%s", str3);
			} else {
				this->AddDot(SetPt + madePt, false);
			}

		}
	} else {
		ccc = 2;
		while (mrad_ > endrad) {
			madePt.set(w, 0);
			mrad_ -= drad;

			if (endrad >= mrad_) {
				mrad_ = endrad;
				madePt.rotate(Vec2::ZERO, mrad_);
				this->AddDot(SetPt + madePt, true);
				return;
//				ccc=2;
			}

			madePt.rotate(Vec2::ZERO, mrad_);
			ccc++;
			//２回に１回にする
			if (ccc == 3) {
				this->AddDot(SetPt + madePt, true);
				ccc = 0;
//				const char *str3 = "Dot::madeMaru";
//				log("%s", str3);
			} else {
				this->AddDot(SetPt + madePt, false);
			}

		}
	}
}
Vec2 Dot::MaruLength(float drad, int dl, float endrad) {

	madePt.set(w, 0);
	mrad_ += drad;
	madePt.rotate(Vec2::ZERO, mrad_);

	if (endrad < mrad_) {
		mrad_ = endrad;
		madePt.rotate(Vec2::ZERO, mrad_);
	}

	return madePt;
}

Vec2 Dot::SinLength(float r, float w, float rad1, int dl, float endrad) {
//１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。
	Vec2 nowPt;
	Vec2 nextPt;
	float drad = 0;
	nowPt.set(w * (rad1 / (2 * M_PI)), r * (-cos(rad1) + 1));
	nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));

	while ((nextPt - nowPt).length() < dl && (rad1 + drad) < endrad) {
		drad += 0.01f;
		nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
	}

	rad2 = rad1 + drad;
	if (rad2 >= endrad) {
		nextPt.set(w * ((endrad) / (2 * M_PI)), r * (-cos(endrad) + 1));
		rad2 = endrad;
	}
	return nextPt;
}

Vec2 Dot::SinLength(float r, float w, float rad1, int dl) {
//１周期幅：w、半径ｒのSinで、現在rad1の位置から、dlだけ遠い位置の点を算出する。

	return this->SinLength(r, w, rad1, dl, 2 * M_PI);

//	Vec2 nowPt;
//	Vec2 nextPt;
//	float drad = 0;
//	nowPt.set(w * (rad1 / (2 * M_PI)), r * (-cos(rad1) + 1));
//	nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
//
//	while ((nextPt - nowPt).length() < dl && (rad1 + drad) < 2 * M_PI) {
//		drad += 0.01f;
//		nextPt.set(w * ((rad1 + drad) / (2 * M_PI)), r * (-cos(rad1 + drad) + 1));
//	}
//
//	rad2 = rad1 + drad;
//	if (rad2 >= 2 * M_PI) {
//		nextPt.set(w, 0);
//		rad2 = 2 * M_PI;
//	}
//
//	return nextPt;
}
//float rad2;
void Dot::AddDot(Vec2 pt_) {
//spFlgポイントを追加するとき。

	this->AddDot(pt_, true);

}
void Dot::AddDot(Vec2 pt_, bool spFlg) {
//spFlgポイントを追加するとき。
//	if (dspCnt < 2000) {

	Sprite* dt_;
	if (this->_dotG.size() <= dspCnt) {
		dt_ = Sprite::createWithTexture(this->getTexture());
		this->_dotG.pushBack(dt_);
		this->addChild(dt_);
		dt_->setPosition(pt_ + cPt_);
		dspCnt++;
		SetPt.set(pt_);

	} else {
		this->_dotG.at(dspCnt)->setPosition(pt_ + cPt_);
		dspCnt++;
		SetPt.set(pt_);
	}

	if (spFlg) {
		dotPoints[dpCnt].set(pt_);
		dpCnt++;
	}
}

void Dot::FadeIn_Dot(float d, float tm_) {

	if (d == 0 || tm_ == 0) {
		for (Sprite* sp : this->_dotG) {

			sp->setOpacity(0);

		}
	} else {

		auto dlay_ = DelayTime::create(d);
		auto fadeIn = FadeIn::create(tm_);
		auto seq_ = Sequence::create(dlay_->clone(), fadeIn->clone(), NULL);

		for (Sprite* sp : this->_dotG) {

			sp->runAction(seq_->clone());

		}

	}

}
void Dot::FadeOut_Dot(float d, float tm_) {

	if (d == 0 || tm_ == 0) {
		for (Sprite* sp : this->_dotG) {

			sp->setOpacity(0);

		}
	} else {

		auto dlay_ = DelayTime::create(d);
		auto fadeIn = FadeOut::create(tm_);
		auto seq_ = Sequence::create(dlay_->clone(), fadeIn->clone(), NULL);

		for (Sprite* sp : this->_dotG) {

			sp->runAction(seq_->clone());

		}

	}
}

void Dot::SetTchPt() {
//タッチポイント用をセット
	this->setBody(PhysicsBody::createCircle(frameSize.width / 2));
	this->setPhysicsBody(this->_body);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
	this->getBody()->setTag(0);
}

void Dot::SetShape2() {
	const char *str3 = "Dot::SetShape2()";
	log("%s", str3);
	this->setBody(PhysicsBody::createEdgeChain(dShape, dsCnt));
	this->setPhysicsBody(this->_body);
	this->_body->setDynamic(false);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYERBOUND | ChrPrm::PLAYERBODY);
	this->getBody()->setTag(0);
	const char *str4 = "Dot::SetShape2()_2";
	log("%s", str4);
	this->setBody2(PhysicsBody::createCircle(_dotG.at(0)->getContentSize().width / 2));
	this->_body2->setDynamic(false);
	this->getBody2()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY);
	this->getBody2()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody2()->setContactTestBitmask(ChrPrm::PLAYERBOUND | ChrPrm::PLAYERBODY);
	this->getBody2()->setTag(0);

//最初にまるをつける
	this->_dotG.at(0)->setPhysicsBody(this->getBody2());
	const char *str5 = "Dot::SetShape2()_3";
	log("%s", str5);
}

void Dot::SetShape() {

	Vec2 dpt1;
	Vec2 dpt2;
	Vec2 npt;
	float drad_;

//始めのセット
	npt.set(dotPoints[1] - dotPoints[0]);
	npt.normalize();
	npt.rotate(Vec2::ZERO, M_PI / 2);
	npt *= cPt_.x;
	dShape[dsCnt].set(npt + dotPoints[0]);
	dsCnt++;
	int i;
	for (i = 0; i < dpCnt - 2; i++) {

		dpt1.set(dotPoints[i + 1] - dotPoints[i]);
		dpt2.set(dotPoints[i + 2] - dotPoints[i + 1]);
		drad_ = dpt2.getAngle(dpt1);

		if (drad_ > M_PI / 2 && drad_ < M_PI) {

			npt.set(dpt1);
			npt.normalize();
			npt.rotate(Vec2::ZERO, M_PI / 2);
			npt *= cPt_.x;
			dShape[dsCnt].set(npt + dotPoints[i + 1]);
			dsCnt++;

			npt.set(dpt1 + dpt2);
			npt.normalize();
			npt.rotate(Vec2::ZERO, M_PI / 2);
			npt *= cPt_.x;
			dShape[dsCnt].set(npt + dotPoints[i + 1]);
			dsCnt++;

			npt.set(dpt2);
			npt.normalize();
			npt.rotate(Vec2::ZERO, M_PI / 2);
			npt *= cPt_.x;
			dShape[dsCnt].set(npt + dotPoints[i + 1]);
			dsCnt++;

		} else if (drad_ != 0) {
			npt.set(dpt1 + dpt2);
			npt.normalize();
			npt.rotate(Vec2::ZERO, M_PI / 2);
			npt *= cPt_.x;
			dShape[dsCnt].set(npt + dotPoints[i + 1]);
			dsCnt++;
		}

	}

//最後のセット
	npt.set(dotPoints[i + 1] - dotPoints[i]);
	npt.normalize();
	npt.rotate(Vec2::ZERO, M_PI / 2);
	npt *= cPt_.x;
	dShape[dsCnt].set(npt + dotPoints[i + 1]);
	dsCnt++;

	this->setBody(PhysicsBody::createEdgeChain(dShape, dsCnt));
	this->setPhysicsBody(this->_body);
	this->_body->setDynamic(false);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
	this->getBody()->setTag(0);

}

void Dot::SetShape(Vec2 shape_[], int k) {

	Vec2 ctptc;
	for (int i = 0; i < k; i++) {
		ctptc += shape_[i];
	}

	float kk;
	kk = (float) (1 / (float(k)));

	ctptc *= -kk;

	Vec2 cc[] = { ctptc + Vec2(-size_, -size_ + 1), ctptc + Vec2(-size_, size_ - 1), ctptc
			+ Vec2(size_, size_ + 1), ctptc + Vec2(size_, -size_ - 1) };

	Vec2 xx[] = { shape_[0] + Vec2(-size_, -size_), shape_[0] + Vec2(-size_, size_), shape_[0]
			+ Vec2(size_, size_), shape_[0] + Vec2(5, -size_) };

	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;

	material0.friction = 0.5f;
	material0.restitution = 0;

	this->setBody(PhysicsBody::createPolygon(cc, 4, material0));
	this->setPhysicsBody(this->_body);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
	this->getBody()->setTag(0);

	for (int i = 1; i < k; i++) {
		auto material_ = PHYSICSBODY_MATERIAL_DEFAULT;

		material_.friction = 0.5f;
		material_.restitution = 0;
		//Vec2 xx[] = { shape_[i] + Vec2(-5, -5), shape_[i] + Vec2(-5, 5),
		//		shape_[i] + Vec2(5, 5), shape_[i] + Vec2(5, -5) };
		Vec2 xx[] = { ctptc + shape_[i] + Vec2(-size_, -size_ + 1), ctptc + shape_[i]
				+ Vec2(-size_, size_ - 1), ctptc + shape_[i] + Vec2(size_, size_ + 1), ctptc + shape_[i]
				+ Vec2(size_, -size_ - 1) };
		PhysicsBody* bdy_ = PhysicsBody::createPolygon(xx, 4, material_);
		this->getBody()->setCollisionBitmask(
				ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(0);
		this->_body->addShape(bdy_->getShape(0), true);

	}

	for (Node* sp : this->getChildren()) {

		sp->setPosition(sp->getPosition() + ctptc);
		sp->setOpacity(255);
	}

	this->setPosition(this->getPosition() - ctptc);
	this->setOpacity(255);

}

void Dot::SetShape2(Vec2 shape_[], int k) {

	Vec2 ctptc;
	for (int i = 0; i < k; i++) {
		ctptc += shape_[i];
	}

	float kk;
	kk = (float) (1 / (float(k)));

	ctptc *= -kk;

	Vec2 cc[] = { ctptc + Vec2(-size_, -size_), ctptc + Vec2(-size_, size_), ctptc + Vec2(size_, size_), ctptc
			+ Vec2(5, -5) };

	Vec2 xx[] = { shape_[0] + Vec2(-size_, -size_), shape_[0] + Vec2(-size_, size_), shape_[0]
			+ Vec2(size_, size_), shape_[0] + Vec2(5, -size_) };

	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;

	material0.friction = 0.5f;
	material0.restitution = 0;

	this->setBody(PhysicsBody::createCircle(frameSize.width / 2, material0, ctptc));
	this->setPhysicsBody(this->_body);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
	this->getBody()->setTag(0);

	for (int i = 1; i < k; i++) {
		auto material_ = PHYSICSBODY_MATERIAL_DEFAULT;

		material_.friction = 0.5f;
		material_.restitution = 0;
		//Vec2 xx[] = { shape_[i] + Vec2(-5, -5), shape_[i] + Vec2(-5, 5),
		//		shape_[i] + Vec2(5, 5), shape_[i] + Vec2(5, -5) };
		Vec2 xx[] = { ctptc + shape_[i] + Vec2(-size_, -size_), ctptc + shape_[i] + Vec2(-size_, size_), ctptc
				+ shape_[i] + Vec2(size_, size_), ctptc + shape_[i] + Vec2(size_, -size_) };
		PhysicsBody* bdy_ = PhysicsBody::createCircle(frameSize.width / 2, material_, ctptc + shape_[i]);
		this->getBody()->setCollisionBitmask(
				ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(0);
		this->_body->getShape(0)->setTag(0);
		//bdy_->setMass(1);
		bdy_->setDynamic(true);
		bdy_->setRotationEnable(true);

		//bdy_->getShape(0)->setMass(1);
		this->_body->addShape(bdy_->getShape(0), true);

	}

	for (Node* sp : this->getChildren()) {

		sp->setPosition(sp->getPosition() + ctptc);

	}

	this->setPosition(this->getPosition() - ctptc);

//this->getBody()->setLinearDamping(0.1f);
//this->getBody()->setAngularDamping(0.1f);
	/*
	 this->setBody(PhysicsBody::createEdgeChain(shape_, k));
	 this->setPhysicsBody(this->_body);
	 this->_body->setGravityEnable(true);
	 this->_body->setCategoryBitmask(dotCatg);
	 this->_body->setCollisionBitmask(courceCatg | dotCatg | kabeCatg);
	 this->_body->setContactTestBitmask(courceCatg | dotCatg | kabeCatg);
	 this->_body->setTag(0);
	 this->_body->setDynamic(true);
	 this->_body->setRotationEnable(true);
	 */

}

void Dot::SetShape3(Vec2 shape_[], int k) {
//四角を隙間なくつなげる
	Vec2 ctptc;
	for (int i = 0; i < k; i++) {
		ctptc += shape_[i];
	}

//丸用のVec2
	Vec2 ptA;
	Vec2 ptB;
	Vec2 ptC;
	Vec2 ptD;
	Vec2 ptE;
	Vec2 ptF;

	Vec2 pt0_;
	Vec2 pt_;
	Vec2 pt1;
	Vec2 pt2;
	Vec2 pt3;
	Vec2 pt4;

	float kk;
	kk = (float) (1 / (float(k)));

	ctptc *= -kk;

	ptA.set(size_, 0);
	ptB.set(size_, 0);
	ptB.rotate(Vec2::ZERO, -M_PI * 1 / 3);
	ptC.set(size_, 0);
	ptC.rotate(Vec2::ZERO, -M_PI * 2 / 3);
	ptD.set(size_, 0);
	ptD.rotate(Vec2::ZERO, -M_PI);
	ptE.set(size_, 0);
	ptE.rotate(Vec2::ZERO, -M_PI * 4 / 3);
	ptF.set(size_, 0);
	ptF.rotate(Vec2::ZERO, -M_PI * 5 / 3);

	Vec2 aa[] = { ctptc + ptA, ctptc + ptB, ctptc + ptC, ctptc + ptD, ctptc + ptE, ctptc + ptF };

//auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;	//端部の状態
//material0_.friction = 1.0f;
//material0_.restitution = 0;

//auto material_ = PHYSICSBODY_MATERIAL_DEFAULT;	//直線部の状態
//material1_.friction = 0.5f;
//material1_.restitution = 0.8f;

	this->setBody(PhysicsBody::createPolygon(aa, 6, material0_));
	this->setPhysicsBody(this->_body);
	this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
	this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
	this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
	this->getBody()->setTag(0);
	this->_body->setTag(1);
	this->_body->getShape(0)->setTag(0);
	this->_body->setDynamic(true);
	this->_body->setRotationEnable(true);

	if (k > 1) {

		Vec2 bb[] = { shape_[k - 1] + ctptc + ptA, shape_[k - 1] + ctptc + ptB, shape_[k - 1] + ctptc + ptC,
				shape_[k - 1] + ctptc + ptD, shape_[k - 1] + ctptc + ptE, shape_[k - 1] + ctptc + ptF };
		PhysicsBody* bdy_ = PhysicsBody::createPolygon(bb, 6, material0_);
		this->getBody()->setCollisionBitmask(
				ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(0);
		bdy_->setTag(0);
		bdy_->getShape(0)->setTag(0);
		//bdy_->setMass(1);
		bdy_->setDynamic(true);
		bdy_->setRotationEnable(true);

		//bdy_->getShape(0)->setMass(1);
		this->_body->addShape(bdy_->getShape(0), true);

	}

	pt1.set(Vec2::ZERO);
	pt2.set(Vec2::ZERO);

	for (int i = 1; i < k; i++) {

		pt4.set(pt1);
		pt3.set(pt2);

		pt0_.set((shape_[i] + shape_[i - 1]) / 2);
		pt_.set((shape_[i] - shape_[i - 1]));
		pt_.normalize();
		pt_ *= size_;
		pt_.rotate(Vec2::ZERO, M_PI / 2);
		pt1.set(pt0_ + pt_);
		pt_.rotate(Vec2::ZERO, M_PI);
		pt2.set(pt0_ + pt_);
		//pt1.set(pt0_+pt1_.)

		if (SikakuChk(pt1, pt2, pt3, pt4)) {

			Vec2 xx[] = { pt1 + ctptc, pt2 + ctptc, pt3 + ctptc, pt4 + ctptc };
			PhysicsBody* bdy_ = PhysicsBody::createPolygon(xx, 4, material1_);

			this->getBody()->setCollisionBitmask(
					ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
			this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
			this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
			this->getBody()->setTag(0);
			bdy_->setTag(0);
			bdy_->getShape(0)->setTag(0);
			bdy_->setDynamic(true);
			bdy_->setRotationEnable(true);
			this->_body->addShape(bdy_->getShape(0), true);

		} else {

			Vec2 cc[] = { shape_[i - 1] + ctptc + ptA, shape_[i - 1] + ctptc + ptB, shape_[i - 1] + ctptc
					+ ptC, shape_[i - 1] + ctptc + ptD, shape_[i - 1] + ctptc + ptE, shape_[i - 1] + ctptc
					+ ptF };
			PhysicsBody* bdy_ = PhysicsBody::createPolygon(cc, 6, material0_);

			this->getBody()->setCollisionBitmask(
					ChrPrm::PLAYER | ChrPrm::ENEMY | ChrPrm::ITEM | ChrPrm::PLAYERBOUND);
			this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
			this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
			this->getBody()->setTag(0);
			bdy_->setTag(0);
			bdy_->getShape(0)->setTag(0);
			bdy_->setDynamic(true);
			bdy_->setRotationEnable(true);
			this->_body->addShape(bdy_->getShape(0), true);

		}

	}

	for (Node* sp : this->getChildren()) {

		sp->setPosition(sp->getPosition() + ctptc);

	}

	this->setPosition(this->getPosition() - ctptc);

}

bool Dot::SikakuChk(Vec2 pt1, Vec2 pt2, Vec2 pt3, Vec2 pt4) {
//時計回りの凸四角かどうか判定。
//	return true;
	/*
	 Vec2 pt1;
	 Vec2 pt2;
	 Vec2 pt3;
	 Vec2 pt4;
	 pt1.set(pt1_);
	 pt2.set(pt2_);
	 pt3.set(pt3_);
	 pt4.set(pt4_);
	 */

	pt2 -= pt1;
	pt3 -= pt1;
	pt4 -= pt1;
	pt1 -= pt1;

	pt3.rotate(Vec2::ZERO, -pt2.getAngle());
	pt4.rotate(Vec2::ZERO, -pt2.getAngle());
	pt2.rotate(Vec2::ZERO, -pt2.getAngle());

	if (pt3.y > 0 || pt4.y > 0) {
		return false;
	}
	if (pt3.y - pt4.y == 0) {
		return true;
	}

	float a = (pt3.x * pt4.y - pt4.x * pt3.y) / (pt4.y - pt3.y);

	if (a > 0 && a < pt2.x) {
		return false;
	} else {
		return true;
	}

}

void Dot::SetUpdateListenner(std::function<void(Dot*, float)> action) {
	this->unscheduleUpdate();
	this->onUpDateListener = action;
	updateFlg = true;
	this->scheduleUpdate();
}
void Dot::update(float dt) {

//各ステートで分岐する。

	if (!updateFlg) {
		return;
	}

	if (this->onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void Dot::Action1() {
	int d = arc4random() % static_cast<int>(1000);
	int t = arc4random() % static_cast<int>(4) + 1;

}
void Dot::Action2() {

}
void Dot::Action3() {

}
void Dot::Action4() {

}

