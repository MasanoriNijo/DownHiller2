#include "cocos2d.h"
#include "Item.h"
#include "cmath"
USING_NS_CC;

// on "init" you need to initialize your instance

Item::Item() :
		fstTch(false), endTch(false), _madeNo(0), moveFlg(false), _itemState(ItemState::GATE1), _lifePoint(0), _scorePoint(
				0), delFlg(false), _img(NULL), _img2(NULL), _txter1(NULL), _txter2(NULL), _txter3(NULL), _txter4(
		NULL), _txter5(NULL), _txter6(NULL), _body(NULL), _body2(NULL), _body3(NULL), _body4(NULL) {
}
Item::~Item() {
	CC_SAFE_RELEASE_NULL(_img);
	CC_SAFE_RELEASE_NULL(_img2);
	CC_SAFE_RELEASE_NULL(_txter1);
	CC_SAFE_RELEASE_NULL(_txter2);
	CC_SAFE_RELEASE_NULL(_txter3);
	CC_SAFE_RELEASE_NULL(_txter4);
	CC_SAFE_RELEASE_NULL(_txter5);
	CC_SAFE_RELEASE_NULL(_txter6);

	CC_SAFE_RELEASE_NULL(_body);
	CC_SAFE_RELEASE_NULL(_body2);
	CC_SAFE_RELEASE_NULL(_body3);
	CC_SAFE_RELEASE_NULL(_body4);
}
bool Item::init() {

	frameSize = Size(this->getContentSize().width / 5, this->getContentSize().height / 1);

	auto director = Director::getInstance();
	winSize = director->getWinSize();

	return true;
}

void Item::setUpdateAction(std::function<void(Item*, float dt)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	//updateFlg = true;
	this->scheduleUpdate();
}
void Item::update(float dt) {

	if (onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void Item::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}
bool Item::PassChk() {

	if (delFlg) {
		return false;
	}

	if (fstTch && endTch) {
		delFlg = true;
		return true;
	} else {
		return false;
	}

}

void Item::FadeIn(float dt,float s){
	if (dt== 0 || s == 0) {
		this->getImg()->setOpacity(0);
	} else {
		auto fade_ = FadeIn::create(s);
		auto delay_ = DelayTime::create(dt);
		auto seq_ = Sequence::create(delay_->clone(), fade_->clone(), NULL);
		this->getImg()->runAction(seq_->clone());
	}
}
void Item::FadeOut(float dt,float s){

	if (dt== 0 || s == 0) {
		this->getImg()->setOpacity(0);
	} else {
		auto fade_ = FadeOut::create(s);
		auto delay_ = DelayTime::create(dt);
		auto seq_ = Sequence::create(delay_->clone(), fade_->clone(), NULL);
		this->getImg()->runAction(seq_->clone());
	}
}


void Item::setRndState(int _Lvl) {

	int rnd;

	int rndA = arc4random() % static_cast<int>(6);

}

void Item::setRndState() {

	int rnd = arc4random() % static_cast<int>(30);

	rnd++;

	switch (rnd) {

	case 1: {
		this->setItemState(ItemState::GATE1);
		break;
	}

	}

}

void Item::SetState(ItemState x) {

	this->setItemState(x);

	//Vec2(-4,50),Vec2(5,50),Vec2(4,38),Vec2(-5,38)
//	Count:4

	int x_ = 0;
	int y_ = 0;

	switch (x) {

	case ItemState::GATE1: {

		this->setImg(Sprite::createWithTexture(this->getTxter1()));
		frameSize = Size(this->getImg()->getContentSize().width / 5,
				this->getImg()->getContentSize().height / 2);
		this->getImg()->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
		Vec2 PointsT[] = { Vec2(5, 79), Vec2(5, 60), Vec2(-5, 60), Vec2(-5, 79), Vec2(5, 79) };
		Vec2 PointsT_a[] = { Vec2(0, 50), Vec2(0, -50) };
		Vec2 PointsT_y[] = { Vec2(-5, -79), Vec2(-5, -60), Vec2(5, -60), Vec2(5, -79), Vec2(-5, -79) };
		Vec2 PointsT_b[] = { Vec2(36, 29), Vec2(59, 29), Vec2(59, -29), Vec2(36, -29), Vec2(36, 29) };

		this->setBody(PhysicsBody::createEdgeChain(PointsT, 5));
		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
		this->setBody3(PhysicsBody::createCircle(50));
//		this->setBody4(PhysicsBody::createEdgeChain(PointsT_b, 5));
		_body->addShape(this->getBody2()->getShape(0));

		this->_body3->getShape(0)->setTag(20);
//		this->_body4->getShape(0)->setTag(21);
//		this->_body3->addShape(this->getBody4()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.restitution = 1.0f;
		material.friction = 1.0f;

		this->setImg2(Sprite::createWithTexture(this->_img->getTexture()));
		this->getImg2()->setTextureRect(Rect(0, frameSize.height, frameSize.width, frameSize.height));
		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER);
		this->getBody()->setCategoryBitmask(ChrPrm::ITEM);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		this->addChild(this->getImg());
		this->getImg2()->setPosition(frameSize.width / 2, frameSize.height / 2);

		_body3->setGravityEnable(false);
		_body3->setDynamic(true);
		_body3->setEnable(true);
		this->getBody3()->setCollisionBitmask(ChrPrm::NONE);
		this->getBody3()->setCategoryBitmask(ChrPrm::ITEM);
		this->getBody3()->setContactTestBitmask(ChrPrm::PLAYER);
		this->getBody3()->setTag(20);

		this->getImg2()->setPhysicsBody(this->_body3);
		this->getImg()->addChild(this->getImg2());
		this->_img2->setGlobalZOrder(20);
		auto move_ = MoveBy::create(2, Vec2(300, 0));
		auto seq_ = Sequence::create(move_, move_->reverse(), NULL);
		auto rpt_ = RepeatForever::create(seq_);

		this->getImg()->runAction(rpt_);

		this->setUpdateAction([this](Item* itm,float dt) {
			if(this->fstTch && this->endTch ) {
				this->fstTch=false;
				this->endTch=false;

				this->fstPt-=this->_img->getPosition();
				this->lstPt-=this->_img->getPosition();
				this->fstPt.rotate(Vec2::ZERO,CC_DEGREES_TO_RADIANS(this->_img->getRotation()));
				this->lstPt.rotate(Vec2::ZERO,CC_DEGREES_TO_RADIANS(this->_img->getRotation()));

				if(this->fstPt.x<0 && this->lstPt.x>0) {
					this->getImg()->setPosition(this->getImg()->getPosition()+Vec2(0,300));
				}

			}});

		x_ = 0;
		y_ = 0;
		_lifePoint = 1;
		_scorePoint = 0;
		_itemName = "Life Up!";
		break;
	}
	case ItemState::GATE2: {
		this->setImg(Sprite::createWithTexture(this->getTxter1()));
		frameSize = Size(this->getImg()->getContentSize().width / 5, this->getImg()->getContentSize().height);
		this->getImg()->setTextureRect(Rect(frameSize.width * 1, 0, frameSize.width, frameSize.height));
		Vec2 PointsT[] = { Vec2(5, 79), Vec2(5, 60), Vec2(-5, 60), Vec2(-5, 79) };
		Vec2 PointsT_x[] = { Vec2(5, 79), Vec2(5, 60), Vec2(-5, 60), Vec2(-5, 79) };
		Vec2 PointsT_y[] = { Vec2(-5, -79), Vec2(-5, -60), Vec2(5, -60), Vec2(5, -79) };
		Vec2 PointsT_xy[] = { Vec2(-5, -79), Vec2(-5, -60), Vec2(5, -60), Vec2(5, -79) };

		this->setBody(PhysicsBody::createEdgeChain(PointsT, 4));
		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 4));
		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.restitution = 1.0f;
		material.friction = 1.0f;

		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER);
		this->getBody()->setCategoryBitmask(ChrPrm::ITEM);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		this->addChild(this->getImg());

		x_ = 0;
		y_ = 0;
		_lifePoint = 1;
		_scorePoint = 0;
		_itemName = "Life Up!";
		break;
	}
	case ItemState::MARUTA1: {

		this->setImg(Sprite::createWithTexture(this->getTxter2()));

		Vec2 PointsT[] = { Vec2(-13, 64), Vec2(12, 64), Vec2(23, 52), Vec2(23, -54), Vec2(12, -64), Vec2(-11,
				-64), Vec2(-24, -54), Vec2(-24, 50) };
		Vec2 PointsT_x[] = { Vec2(5, 40), Vec2(-5, 40), Vec2(-5, 50), Vec2(5, 50), Vec2(5, 40) };
		Vec2 PointsT_y[] = { Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40) };
		Vec2 PointsT_xy[] = { Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50) };

		this->setBody(PhysicsBody::createEdgeChain(PointsT, 8));
//		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
//		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.restitution = 1.0f;
		material.friction = 1.0f;

		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER);
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		auto move_ = MoveBy::create(5, Vec2(500, 0));
		auto seq_ = Sequence::create(move_, move_->reverse(), NULL);
		auto rpt_ = RepeatForever::create(seq_);

		this->getImg()->runAction(rpt_);

		this->addChild(this->getImg());

		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		_itemName = "Life Down!";

		break;
	}

	case ItemState::MARUTA2: {

		this->setImg(Sprite::createWithTexture(this->getTxter4()));

		Vec2 PointsT[] = { Vec2(10, 156), Vec2(24, 144), Vec2(24, -144), Vec2(9, -156), Vec2(-10, -156), Vec2(
				-24, -144), Vec2(-24, 142), Vec2(-10, 156) };
		Vec2 PointsT_x[] = { Vec2(5, 40), Vec2(-5, 40), Vec2(-5, 50), Vec2(5, 50), Vec2(5, 40) };
		Vec2 PointsT_y[] = { Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40) };
		Vec2 PointsT_xy[] = { Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50) };

		this->setBody(PhysicsBody::createEdgeChain(PointsT, 8));
//		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
//		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.restitution = 1.0f;
		material.friction = 1.0f;

//		 this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER);
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER | ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		auto move_ = MoveBy::create(5, Vec2(0, 500));
		auto rot_ = RotateBy::create(1, 45);
		auto rot2_ = Sequence::create(rot_, rot_->reverse(), NULL);
		auto seq_ = Sequence::create(move_, move_->reverse(), NULL);
		auto spwn_ = Spawn::create(rot2_, seq_, NULL);
		auto rpt_ = RepeatForever::create(seq_);

		this->getImg()->runAction(rpt_);

		this->addChild(this->getImg());

		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		_itemName = "Life Down!";

		break;
	}

	case ItemState::ISHI1: {

		this->setImg(Sprite::createWithTexture(this->getTxter3()));

		Vec2 PointsT[] = { Vec2(11, 47), Vec2(38, 24), Vec2(60, -6), Vec2(42, -51), Vec2(-41, -51), Vec2(-58,
				-9), Vec2(-36, 28), Vec2(-5, 48) };
		Vec2 PointsT_x[] = { Vec2(5, 40), Vec2(-5, 40), Vec2(-5, 50), Vec2(5, 50), Vec2(5, 40) };
		Vec2 PointsT_y[] = { Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40) };
		Vec2 PointsT_xy[] = { Vec2(5, -50), Vec2(-5, -50), Vec2(-5, -40), Vec2(5, -40), Vec2(5, -50) };

		this->setBody(PhysicsBody::createPolygon(PointsT, 8));
//		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
//		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.density = 0.01f;
		material.restitution = 1.0f;
		material.friction = 1.0f;

		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(true);
		_body->setDynamic(true);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER | ChrPrm::COURCE);
		this->getBody()->setCategoryBitmask(ChrPrm::ENEMY);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYERBOUND);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		this->addChild(this->getImg());

		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		_itemName = "Life Down!";

		break;
	}
	case ItemState::START: {

		this->setImg(Sprite::createWithTexture(this->getTxter5()));

		Vec2 PointsT[] = { Vec2(-46, -42), Vec2(-57, -42), Vec2(-57, 74), Vec2(-46, 74) };

		this->setBody(PhysicsBody::createPolygon(PointsT, 4));
//		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
//		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.density = 0.01f;
		material.restitution = 1.0f;
		material.friction = 1.0f;

		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::PLAYER );
		this->getBody()->setCategoryBitmask(ChrPrm::COURCE);
		this->getBody()->setContactTestBitmask(ChrPrm::NONE);
		this->getBody()->setTag(1);
		this->getImg()->setPhysicsBody(_body);

		this->addChild(this->getImg());
		this->SetPt.set(-50, -64);
		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		_itemName = "Life Down!";

		break;
	}

	case ItemState::GOAL: {

		this->setImg(Sprite::createWithTexture(this->getTxter6()));

		Vec2 PointsT[] = { Vec2(-46, -42), Vec2(-57, -42), Vec2(-57, 74), Vec2(-46, 74) };

		this->setBody(PhysicsBody::createPolygon(PointsT, 4));
//		this->setBody2(PhysicsBody::createEdgeChain(PointsT_y, 5));
//		_body->addShape(this->getBody2()->getShape(0));

		auto material = PHYSICSBODY_MATERIAL_DEFAULT;
		material.density = 0.01f;
		material.restitution = 1.0f;
		material.friction = 1.0f;
		//this->setBody(PhysicsBody::createCircle(32, material));
		_body->setGravityEnable(false);
		_body->setDynamic(false);
		_body->setEnable(true);
		this->getBody()->setCollisionBitmask(ChrPrm::NONE);
		this->getBody()->setCategoryBitmask(ChrPrm::ITEM);
		this->getBody()->setContactTestBitmask(ChrPrm::PLAYER);
		this->getBody()->setTag(20);
		this->getImg()->setPhysicsBody(_body);
		this->addChild(this->getImg());
		this->SetPt.set(-50, -64);
		x_ = 2;
		y_ = 0;
		_lifePoint = -1;
		_scorePoint = 0;
		_itemName = "";

		break;
	}

	}

}

void Item::SetPoint(Vec2 pt_, float rad) {
	//指定のポイントpt_に、SetPtと回転rad
//	Vec2 SetPt;//セットポイントアイテム自身のセットポイント位置
	Vec2 tpt_;
	tpt_.set(SetPt);
	tpt_.rotate(Vec2::ZERO, rad);
	this->setPosition(pt_ - tpt_);
	this->setRotation(-CC_RADIANS_TO_DEGREES(rad));

}

Vec2 Item::GetImgPosition() {
	//現在のimgの親ノード上のポジションを返す。

	Vec2 pt_;
	pt_.set(this->getImg()->getPosition());
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(this->getRotation()));
	pt_ += this->getPosition();

	return pt_;

}

void Item::Action1() {

	auto fade_ = FadeOut::create(0.5f);
	if (this->getImg()) {
		this->getImg()->runAction(fade_);
	}

}
void Item::Action2() {

}
void Item::Action3() {

}
void Item::Action4() {

}
