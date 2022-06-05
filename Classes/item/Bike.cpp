#include "cocos2d.h"
#include "Bike.h"
#include "cmath"

USING_NS_CC;

Bike::Bike() :
		_fWheel(NULL), _rWheel(NULL), _fWheelA(NULL), _rWheelA(NULL), _pedaru(NULL), _pointDbg(NULL), _body(
		NULL), _body2(NULL), _body4(NULL), _body5(NULL), _body6(NULL), _body3(NULL), _dmy0(NULL), _gan(
		NULL), _BikeImg(NULL), _chaser(NULL), _tchNode(NULL) {

}
Bike::~Bike() {
	CC_SAFE_RELEASE_NULL(_fWheel);
	CC_SAFE_RELEASE_NULL(_rWheel);
	CC_SAFE_RELEASE_NULL(_fWheelA);
	CC_SAFE_RELEASE_NULL(_rWheelA);
	CC_SAFE_RELEASE_NULL(_pedaru);
	CC_SAFE_RELEASE_NULL(_pointDbg);
	CC_SAFE_RELEASE_NULL(_body);
	CC_SAFE_RELEASE_NULL(_body2);
	CC_SAFE_RELEASE_NULL(_body4);
	CC_SAFE_RELEASE_NULL(_body5);
	CC_SAFE_RELEASE_NULL(_body6);
	CC_SAFE_RELEASE_NULL(_body3);
	CC_SAFE_RELEASE_NULL(_dmy0);
	CC_SAFE_RELEASE_NULL(_gan);
	CC_SAFE_RELEASE_NULL(_BikeImg);
	CC_SAFE_RELEASE_NULL(_chaser);
	CC_SAFE_RELEASE_NULL(_tchNode);
}

Bike* Bike::createB() {
	Bike* bike = new Bike();
	if (bike && bike->initB()) {
		bike->autorelease();
		return bike;
	} else {
		CC_SAFE_DELETE(bike);
		return nullptr;
	}
}

bool Bike::initB() {

	if (!Sprite::initWithFile("riders.png")) {
		return false;
	}
	winSize = Director::getInstance()->getWinSize();
	frameSize = Size(this->getContentSize().width / 7, this->getContentSize().height / 7);
	this->setTextureRect(Rect(frameSize.width * 3, frameSize.height * 3, frameSize.width, frameSize.height));
	this->setAnchorPoint(Vec2(0.7690, 0.1708));
//	0.769042969
//	0.170898438

	this->setBikeImg(Sprite::create("bike2.png"));

	this->getBikeImg()->setPosition(Vec2(147, 92));
	this->addChild(this->_BikeImg);
	this->setChaser(Node::create());
	this->setFWheel(Sprite::create("wheel3.png"));
	this->setRWheel(Sprite::createWithTexture(this->getFWheel()->getTexture()));
//	this->getFWheel()->setVisible(false);
//	this->getRWheel()->setVisible(false);

//	this->setPointDbg(Sprite::create("point.png"));
//	_pointDbg->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
//	this->addChild(this->_pointDbg, 5);

	for (int i = 0; i < 4; i++) {
		auto frame = SpriteFrame::createWithTexture(this->getTexture(),
				Rect(frameSize.width * 3, frameSize.height * (i + 3), frameSize.width, frameSize.height));
		_koki1.pushBack(frame);
	}

	for (int i = 0; i < 2; i++) {
		auto frame = SpriteFrame::createWithTexture(this->getTexture(),
				Rect(frameSize.width * 3, frameSize.height * (5 - i), frameSize.width, frameSize.height));
		_koki1.pushBack(frame);
	}

//	this->setPedaru(Sprite::create("pedaru.png"));
//	this->_pedaru->setPosition(Vec2(135, 46));
//	this->_pedaru->setVisible(false);
//	this->addChild(_pedaru);

	this->setGan(Sprite::create("gan.png"));
	this->_gan->setPosition(frameSize.width / 2, frameSize.height / 2);
//	this->_gan->setVisible(false);
//	this->addChild(this->_gan, 2);

//	this->setVisible(false);

	return true;
//	const char *str3 = "initB_fin";
//	log("%s", str3);

}

bool Bike::init() {

	if (!Sprite::initWithFile("wheel2.png")) {
		return false;
	}
	winSize = Director::getInstance()->getWinSize();

	this->setBikeImg(Sprite::create("riders.png"));
	frameSize = Size(this->getBikeImg()->getContentSize().width / 7,
			this->getBikeImg()->getContentSize().height / 7);
	this->_BikeImg->setTextureRect(
			Rect(frameSize.width * 0, frameSize.height * 0, frameSize.width, frameSize.height));
	this->_BikeImg->setAnchorPoint(Vec2(0.76f, 0.17f));
	_BikeImg->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
	this->addChild(_BikeImg, 2);
//	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;
//	material0.restitution = 0.0001f;
//	material0.friction =0.01f;
//	material0.density = 0.001f;
//
//	this->setBody3(PhysicsBody::createCircle(65, material0));
//
//	this->_body3->setGravityEnable(false);
//	this->_body3->setCategoryBitmask(ChrPrm::PLAYERBOUND);
//	this->_body3->setCollisionBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
//	this->_body3->setContactTestBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
//	this->_body3->setDynamic(false);
//	this->_body3->setRotationEnable(true);
//
//	this->_body3->setTag(10);
//	_BikeImg->setPhysicsBody(this->_body3);

//this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0.001f;
	material.friction = 0.9f;
	material.density = 0.4f;

	this->setBody(PhysicsBody::createCircle(this->getContentSize().width / 2, material));
//	this->getBody()->getShape(0)->setMaterial(material);

//this->_body->setPositionOffset(Vec2(-10,10));

	this->setPhysicsBody(this->_body);
	this->_body->setGravityEnable(true);
	this->_body->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body->setCollisionBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body->setContactTestBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body->setTag(11);
	this->_body->setDynamic(true);
	this->_body->setRotationEnable(true);
//	this->_body->setAngularVelocityLimit(0);
//	this->_body->setLinearDamping(0.1f);
	//this->_body->setVelocityLimit(this->maxSpeed);
	//this->_body->setAngularVelocityLimit(maxRotSpeed);
	//this->_body->applyTorque(10);
	_contPt.set(0, 1);

	//chaseer
	this->setChaser(Node::create());

	//this->addChild(_chaser);

	for (int i = 0; i < 4; i++) {
		auto frame = SpriteFrame::createWithTexture(this->_BikeImg->getTexture(),
				Rect(frameSize.width * i, 0, frameSize.width, frameSize.height));
		_nobi1.pushBack(frame);
	}
	for (int i = 2; i > 0; i--) {
		auto frame = SpriteFrame::createWithTexture(this->_BikeImg->getTexture(),
				Rect(frameSize.width * i, 0, frameSize.width, frameSize.height));
		_nobi1.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(_nobi1);
	animation->setDelayPerUnit(0.1f);
//	this->_BikeImg->runAction(RepeatForever::create(Animate::create(animation)));

	this->setPointDbg(Sprite::create("point.png"));
	_pointDbg->setPosition(this->getContentSize().width / 2, this->getContentSize().height / 2);
	this->_BikeImg->addChild(this->_pointDbg, 5);

	return true;
}

void Bike::JumpBtn(bool on_) {
	//TouchOn(Vec2::ZERO);

	this->zimenFlg2 = false;
	//this->_body->setAngularVelocity(_body->getAngularVelocity() - 0.5f);
	this->stopAllActions();
	baluneTime_ = 0;

	//ダミーボデイが広がって、すぐしぼむ
	this->_dmy0->setScale(1.6f);
	this->_BikeImg->setScale(1.3f);
	auto delay_ = DelayTime::create(0.1);
	this->jumpFlg = true;
	this->slideFlg = false;
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->jumpFlg=false;
		//this->slideFlg=true;
			this->_BikeImg->setScale(1);
			this->_dmy0->setScale(1);

		});
	auto delay2_ = DelayTime::create(0.1);
	auto func2_ = CallFuncN::create([this](Node* nd) {

	});

	auto seq_ = Sequence::create(delay_, func_, NULL);

	this->runAction(seq_);

}
void Bike::RotBtn(bool on_) {
	this->_body->setAngularVelocity(this->_body->getAngularVelocity() - 1);
}
void Bike::StopBtn(bool on_) {
	this->_body->setAngularVelocity(0);
	this->_body->setVelocity(Vec2::ZERO);
}

void Bike::Dosn(float dt) {
	//ジャンプ中にボタンを離すとドスンと落ちる
	jumpingFlg = false;
	dosnVelo = 200;
	this->getBody()->setVelocity(Vec2(this->getBody()->getVelocity().x, -dosnVelo));

	dosnFlg = false;
	jumpingFlg = false;

}

void Bike::Slide(float dt) {

//	const char *str3 = "Bike::Slide()";
//	log("%s", str3);

	if (this->zimenFlg) {
		this->_body->setLinearDamping(this->dump_Slide);
		this->_body->setAngularVelocity(-2);
		_contPt.normalize();
		this->setPosition(this->getPosition() + _contPt * 5);
		_contPt.rotate(Vec2::ZERO, -M_PI * 0.5);
		if (x_ > slidePow) {
			this->_body->setVelocity(_contPt * x_);
		} else {
			this->_body->setVelocity(_contPt * slidePow);
		}
		//this->_body->applyImpulse(_contPt * 50000);
		this->jumpFlg = false;
		this->slideFlg = false;
		this->zimenFlg = false;
	}

}
void Bike::Jump2(float dt) {

//	const char *str3 = "Bike::Jump2()";
//	log("%s", str3);

	//this->setPosition(this->getPosition() + _contPt * 5);

	//ダミーボデイが広がって、すぐしぼむ
	this->_BikeImg->setScale(1.1f);
	auto delay_ = DelayTime::create(0.1);
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->_BikeImg->setScale(1);

	});

	auto seq_ = Sequence::create(delay_, func_, NULL);
	this->stopAllActions();
	this->runAction(seq_);
	this->_body->setVelocity(_contPt * jumpSpeed);
	//this->_body->applyImpulse(_contPt * jumpPow);
	this->jumpFlg2 = false;
	//this->jumpingFlg2 = true;
}
void Bike::Jump(float dt) {

//	const char *str3 = "Bike::Jump()";
//	log("%s", str3);

	if (this->zimenFlg) {
		this->_body->setLinearDamping(this->dump_Jump);
		//this->_body->setAngularVelocity(0);
		_contPt.normalize();
		/*
		 if((this->_body->getVelocity().x*_contPt.x+this->_body->getVelocity().y*_contPt.y)>0 ){
		 this->_body->setVelocity(_contPt * jumpPow+this->_body->getVelocity());
		 }else{
		 this->_body->setVelocity(_contPt * jumpPow);
		 }
		 */
		//wClickFlg = true;	//ドスン用
		//this->wClickTime_ = 0;
		this->_body->setVelocity(_contPt * jumpSpeed);
		this->setPosition(this->getPosition() + _contPt * 5);

		//	this->_body->applyImpulse(_contPt * jumpPow);
		this->zimenFlg = false;
		this->zimenFlg2 = false;
		this->jumpFlg = false;
		//	this->jumpFlg2 = false;
		//	this->jumpingFlg = true;
		//	this->slideFlg = false;

	}
}
void Bike::Jump3() {

//	const char *str3 = "Bike::Jump()";
//	log("%s", str3);

	//if (this->zimenFlg) {
	//this->_body->setLinearDamping(this->dump_Jump);

	this->pt_.set(this->_point2 - this->_point1);
	this->pt_.normalize();
	_contPt.normalize();

	//this->_body->setVelocity(_contPt * jumpSpeed);
	//this->setPosition(this->getPosition() + _contPt * 5);

//	this->Action1();
	this->_body->setVelocity(pt_ * swaipSpeed);
	//this->_body->applyImpulse(pt_ * this->swaipPow);
	this->zimenFlg = false;
	this->zimenFlg2 = false;
	this->jumpFlg = false;

	//}
}
//float jumpPow=300f;
//float setchPow=100f;

void Bike::KokiKoki0() {
	//ペダルをこぐアックしょんのみ

//	if (this->_body2->getAngularVelocity() > -KokiVeｌo) {
//		this->_body->setAngularVelocity(this->_body->getAngularVelocity() - KokiPow);
//		this->_body2->setAngularVelocity(this->_body2->getAngularVelocity() - KokiPow);
//	}

	this->_pedaru->stopAllActions();

	this->_pedaru->setRotation(0);
	this->_pedaru->setOpacity(255);
	this->_pedaru->setVisible(true);

	auto rot_ = RotateBy::create(0.2f, 180);
	auto fade_ = FadeOut::create(0.2f);
	auto fnc_ = CallFuncN::create([this](Node* nd ) {
//			nd->setVisible(false);
			this->kokiOn =false;
			this->kokiOn_=false;
			this->kokiCnt_=0;
		});

	auto spn_ = Spawn::create(rot_, fade_, NULL);
	auto seq_ = Sequence::create(spn_, fnc_, NULL);

	this->_pedaru->runAction(seq_);

}

void Bike::KokiKoki(float dt) {
	//ペダルをこぐ

	if (this->_body2->getAngularVelocity() > -KokiVeｌo) {
		this->kokiOn_ = true;
		this->_body->setAngularVelocity(this->_body->getAngularVelocity() - KokiPow);
		this->_body2->setAngularVelocity(this->_body2->getAngularVelocity() - KokiPow);

//		this->stopAllActions();
//		auto animation = Animation::createWithSpriteFrames(_koki1);
//		animation->setDelayPerUnit(0.05f);
//		Animate* animete = Animate::create(animation);
//
//		auto func_ = CallFuncN::create([this](Node *) {
//			kokiOn = false;
//		});
//
//		auto seq_ = Sequence::create(animete, func_, NULL);

		this->_pedaru->stopAllActions();

		this->_pedaru->setRotation(0);
		this->_pedaru->setOpacity(255);
		this->_pedaru->setVisible(true);

		auto rot_ = RotateBy::create(0.2f, 180);
		auto fade_ = FadeOut::create(0.2f);
		auto fnc_ = CallFuncN::create([this](Node* nd ) {
//			nd->setVisible(false);
				this->kokiOn =false;
				this->kokiOn_=false;
				this->kokiCnt_=0;
			});

		auto spn_ = Spawn::create(rot_, fade_, NULL);
		auto seq_ = Sequence::create(spn_, fnc_, NULL);

		this->_pedaru->runAction(seq_);

	} else {
//		this->kokiOn = false;
//		this->kokiOn_ = false;
//		this->kokiCnt_ = 0;
	}

}

void Bike::FJump(Vec2 pt_) {

	//前輪リフト用
	if (this->FtchFlg) {
		this->FtchFlg = false;

		if (pt_.length() > MaxVelo * FjumpPow) {
			pt_.normalize();
			pt_ *= MaxVelo * FjumpPow;

		}

		this->dFJumpPt += pt_;

//		this->_body->setVelocity(this->_body->getVelocity() + pt_);

	} else {

		return;
		if (pt_.length() > MaxVelo / 100) {
			pt_.normalize();
			pt_ *= MaxVelo / 100;

		}
		this->dFJumpPt += pt_;
//		this->_body->setVelocity(this->_body->getVelocity() + pt_);
	}
}
void Bike::RJump(Vec2 pt_) {

//後輪リフト用
	if (this->RtchFlg) {

		this->RtchFlg = false;

		if (pt_.length() > MaxVelo) {
			pt_.normalize();
			pt_ *= MaxVelo;

		}
		this->dRJumpPt += pt_;
//		this->_body2->setVelocity(this->_body2->getVelocity() + pt_);

	} else {
		return;
		if (pt_.length() > MaxVelo / 100) {
			pt_.normalize();
			pt_ *= MaxVelo / 100;

//			const char *str = "Bike::RJump_nojumpmax";
//			log("%s", str);

		}
		this->dRJumpPt += pt_;
//		this->_body2->setVelocity(this->_body2->getVelocity() + pt_);

	}
}

void Bike::FJump2(Vec2 apt_) {
//	const char *str3 = " Bike::FJump2_1";
//	log("%s", str3);
	apt_ *= kJump_;
	//前輪リフト用
	if (this->FtchFlg) {
		this->FtchFlg = false;
//		const char *str4 = " Bike::FJump2_2";
//		log("%s", str4);
		float xxx = this->GetNaisei(apt_, FtchPt);

		if (xxx < -MaxVelo * FjumpPow) {
			xxx = -MaxVelo * FjumpPow;
		} else if (xxx > MaxVelo * FjumpPow) {
			xxx = MaxVelo * FjumpPow;
		}
		this->dFJumpPt += xxx * FtchPt;
//		this->_body->setVelocity(this->_body->getVelocity() - FtchPt * xxx);

	}
}
void Bike::FJump3(Vec2 apt_) {

	return;

//	const char *str3 = " Bike::FJump3_1";
//	log("%s", str3);
	apt_ *= kJump_;
	//前輪リフト用
	if (this->FtchFlg) {
		this->FtchFlg = false;
//		const char *str4 = " Bike::FJump2_2";
//		log("%s", str4);

		//法線方向の速度をゼロにする処理。
		float zzz = this->GetNaisei(this->_body->getVelocity(), this->FnmlPt);
		this->dFJumpPt -= zzz * FnmlPt;

		float xxx = this->GetNaisei(apt_, FnmlPt);

		if (xxx < -MaxVelo * FjumpPow) {
			xxx = -MaxVelo * FjumpPow;
		} else if (xxx > MaxVelo * FjumpPow) {
			xxx = MaxVelo * FjumpPow;
		}
//		this->dFJumpPt += xxx * FnmlPt;
//		if (!this->RtchFlg) {
//			this->dRJumpPt += xxx * FnmlPt;
//		}
//		this->getFWheel()->setPosition( FtchPt+this->getFWheel()->getContentSize().width*FnmlPt);

//		this->_body->setVelocity(this->_body->getVelocity() - FtchPt * xxx);

	}
}

void Bike::RJump3(Vec2 apt_) {

	return;
//	const char *str3 = "Bike::RJump2_1";
//	log("%s", str3);

	apt_ *= kJump_;
//後輪リフト用
	if (this->RtchFlg) {
		this->RtchFlg = false;

//		const char *str4 = "Bike::RJump2_2";
//		log("%s", str4);

		//法線方向の速度をゼロにする処理。
		float zzz = this->GetNaisei(this->_body2->getVelocity(), this->RnmlPt);
		this->dRJumpPt -= zzz * RnmlPt;

		float xxx = this->GetNaisei(apt_, RnmlPt);

		if (xxx < -MaxVelo * RjumpPow) {
			xxx = -MaxVelo * RjumpPow;
		} else if (xxx > MaxVelo * RjumpPow) {
			xxx = MaxVelo * RjumpPow;
		}
//		this->dRJumpPt += xxx * RnmlPt;

//		if (!this->FtchFlg) {
//			this->dFJumpPt += xxx * RnmlPt;
//		}
//		this->getRWheel()->setPosition( RtchPt+this->getRWheel()->getContentSize().width*RnmlPt);

	}
}
void Bike::RJump2(Vec2 apt_, bool backFlg) {

//	const char *str3 = "Bike::RJump2_1";
//	log("%s", str3);

	apt_ *= kJump_;
//後輪リフト用
	if (this->RtchFlg) {
		this->RtchFlg = false;

//		const char *str4 = "Bike::RJump2_2";
//		log("%s", str4);

		float xxx = this->GetNaisei(apt_, RtchPt);

		if (xxx < -MaxVelo * RjumpPow) {
			xxx = -MaxVelo * RjumpPow;
		} else if (xxx > MaxVelo * RjumpPow) {
			xxx = MaxVelo * RjumpPow;
		}
		this->dRJumpPt += xxx * RtchPt;
//		this->_body2->setVelocity(this->_body2->getVelocity() - RtchPt * xxx);

//		if (backFlg) {
//			//前進用
//			RtchPt.rotate(Vec2::ZERO, M_PI / 2);
//
//			xxx = this->GetNaisei(pt_, RtchPt);
//			if (xxx < -MaxVelo) {
//				xxx = -MaxVelo;
//			} else if (xxx > MaxVelo) {
//				xxx = MaxVelo;
//			}
//			this->dRJumpPt += xxx * RtchPt;
////			this->_body2->setVelocity(this->_body2->getVelocity() + RtchPt * xxx);
//		}
	}
}

void Bike::AirRot(Vec2 rotvelo) {

	return;

	rotvelo *= kRot_;
	//半身より上の
	this->AirPt.set(dbGPt + Vec2(0, 300));

	this->AirPt.rotate(Vec2::ZERO, M_PI / 2);

	this->AirPt.normalize();
//内積により求める
	float xxx = this->GetNaisei(rotvelo, this->AirPt);
//	float xxx=(float)sqrt(zzz);

	if (xxx < -this->MaxRotVelo) {
		xxx = -this->MaxRotVelo;
	} else if (xxx > this->MaxRotVelo) {
		xxx = this->MaxRotVelo;
	}
	this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
	this->AirPt.normalize();
	this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
	this->dFJumpPt += xxx * this->AirPt;
	this->dRJumpPt -= xxx * this->AirPt;
//	this->_body->setVelocity(this->_body->getVelocity() + xxx * this->AirPt);
//	this->_body2->setVelocity(this->_body2->getVelocity() - xxx * this->AirPt);

//	const char *str = "Bike::AirRot";
//	log("%s", str);

}

void Bike::JumpAction(Node* nd, Vec2 dct_, float dt) {

//	if (this->jumpFlg) {

	auto move_ = MoveBy::create(dt, dct_ * 100);
	auto func_ = CallFuncN::create([this](Node* nd) {

		this->jumpFlg=false;
	});

	auto seq_ = Sequence::create(move_, func_, NULL);

//	const char *str2 = "Bike::JumpAction";
//	log("%s", str2);

	nd->runAction(move_);

//	}

}

void Bike::ControlVelo2(Vec2 powPt_, float dt) {
	//回転ジャンプ同時制御
	this->dFJumpPt.set(Vec2::ZERO);
	this->dRJumpPt.set(Vec2::ZERO);
	Vec2 ptF;
	Vec2 ptR;
	Vec2 ptFR;

//	縦横で場合分け。

	if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
		jtime_ = 0;
		this->SetTouch(false);
//		現在の速度に対してジャンプ速度を制御
		float xxx = this->GetNaisei(powPt_ * kJump_, FRnmlPt);
		FRnmlPt.set(FnmlPt + RnmlPt);
		FRnmlPt.normalize();
		//		xxx -= yyy;

		if (xxx < -MaxVelo * maxVelo_k) {

//			const char *str = "ControlVelo2_maxjump";
//			log("%s", str);

			xxx = -MaxVelo * maxVelo_k;

//			this->dRJumpPt += xxx * FRnmlPt;
//			this->dFJumpPt += xxx * FRnmlPt;

			this->JumpAction(this->_fWheel, xxx * FRnmlPt, 0.3f);
			this->JumpAction(this->_rWheel, xxx * FRnmlPt, 0.3f);

		} else if (xxx > 0) {
			xxx = 0;
		} else {

//			const char *str2 = "ControlVelo2_jump";
//			log("%s", str2);

//			this->dRJumpPt += xxx * FRnmlPt;
//			this->dFJumpPt += xxx * FRnmlPt;
			this->JumpAction(this->_fWheel, xxx * FRnmlPt, 0.3f);
			this->JumpAction(this->_rWheel, xxx * FRnmlPt, 0.3f);
		}

	}

//	if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
//
//		jtime_ = 0;
//		this->SetTouch(false);
//		FRnmlPt.set(FnmlPt + RnmlPt);
//		FRnmlPt.normalize();
//
//		//現在の速度に対してジャンプ速度を制御
//		ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
//		float yyy = this->GetNaisei(ptFR, FRnmlPt);
//
//		float xxx = this->GetNaisei(powPt_ * kJump_, FRnmlPt);
//
////		xxx -= yyy;
//
//		if (xxx < -MaxVelo * maxVelo_k) {
//
//			const char *str = "ControlVelo2_maxjump";
//			log("%s", str);
//
//			xxx = -MaxVelo * maxVelo_k;
//
//			this->dRJumpPt += xxx * FRnmlPt;
//			this->dFJumpPt += xxx * FRnmlPt;
//
//		} else if (xxx > 0) {
//			xxx = 0;
//		} else {
//
//			const char *str2 = "ControlVelo2_jump";
//			log("%s", str2);
//
//			this->dRJumpPt += xxx * FRnmlPt;
//			this->dFJumpPt += xxx * FRnmlPt;
//
//		}
//
//	} else {
//		FRnmlPt.set(Vec2::ZERO);
//	}

//	this->FtchFlg = false;
//	this->RtchFlg = false;
//	this->_body->setVelocity(this->_body->getVelocity() + this->dFJumpPt);
//	this->_body2->setVelocity(this->_body2->getVelocity() + this->dRJumpPt);
//

	//回転力を得る。
	this->AirPt.set(dbGPt + Vec2(0, 300));

	this->AirPt.rotate(Vec2::ZERO, M_PI / 2);

	this->AirPt.normalize();
//内積により求める
	float zzz = this->GetNaisei(powPt_ * kRot_, this->AirPt);

	if (zzz < -this->MaxRotVelo) {
//		if (zzz < 0) {
		zzz = -this->MaxRotVelo;
//		const char *str3 = "ControlVelo_MaxRotVelo";
//		log("%s", str3);

	} else if (zzz > this->MaxRotVelo) {
//	} else if (zzz > 0) {
		zzz = this->MaxRotVelo;
//		const char *str4 = "ControlVelo_MaxRotVelo";
//		log("%s", str4);
	}

//	const char *str4 = "ControlVelo_RotVelo";
//	log("%s", str4);

	this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
	this->AirPt.normalize();
	this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
	this->dFJumpPt += zzz * this->AirPt;
	this->dRJumpPt -= zzz * this->AirPt;

//	this->_body->setVelocity(this->_body->getVelocity() + this->dFJumpPt);
//	this->_body2->setVelocity(this->_body2->getVelocity() + this->dRJumpPt);
//
//	return;

	ptF.set(this->_body->getVelocity() + this->dFJumpPt);
	ptR.set(this->_body2->getVelocity() + this->dRJumpPt);

	ptFR.set(ptF / 2 + ptR / 2);
	ptF -= ptFR;
	ptR -= ptFR;

	if (ptF.length() > MaxRotVelo || ptF.length() < -MaxRotVelo) {

		ptF.normalize();
		ptR.normalize();
		ptF *= MaxRotVelo;
		ptR *= MaxRotVelo;
	}
	ptF += ptFR;
	ptR += ptFR;

	this->_body->setVelocity(ptF);
	this->_body2->setVelocity(ptR);

}

void Bike::contDush() {
	//前進
	//前方向に進む。
	if (this->FtchFlg && this->RtchFlg && kDush_ > 0) {
		this->dRJumpPt += (ptFR_ * JumpPt.length() * 2 * maxVelo_k * kDush_);
		this->dFJumpPt += (ptFR_ * JumpPt.length() * 2 * maxVelo_k * kDush_);
//		this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
//		this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
		this->KokiKoki0();
	}
}
void Bike::contJump() {
	//ジャンプ
	jumpFlg = false;
	if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
		//現在の速度に対してジャンプ速度を制御
		ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
//		float yyy = this->GetNaisei(ptFR, FRnmlPt);
		float xxx = this->GetNaisei(JumpPt * kJump_, FRnmlPt);
		if (xxx < -MaxVelo * maxVelo_k) {
			xxx = -MaxVelo * maxVelo_k;
			jumpFlg = true;
			this->dRJumpPt += xxx * FRnmlPt;
			this->dFJumpPt += xxx * FRnmlPt;
			jumpFlg = true;
			jtime_ = 0;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump01.mp3");
//			this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
//			this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
		} else if (xxx > 0) {
			xxx = 0;
		} else {
			jumpFlg = true;
			jtime_ = 0;
			this->dRJumpPt += xxx * FRnmlPt;
			this->dFJumpPt += xxx * FRnmlPt;
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("jump01.mp3");
//			this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
//			this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
		}
	} else {
		FRnmlPt.set(Vec2::ZERO);
	}

}

void Bike::contFRot() {
	//F回転
	//回転する
	//前輪タッチで前に進む。

	if (this->FtchFlg && this->RtchFlg) {
		if (this->dushCnt_ > 0) {
			this->_body->setAngularVelocity(this->_body->getAngularVelocity() - KokiPow);
			this->_body2->setAngularVelocity(this->_body2->getAngularVelocity() - KokiPow);
			this->dRJumpPt += (ptFR_ * JumpPt.length() * kDush_);
			this->dFJumpPt += (ptFR_ * JumpPt.length() * kDush_);
			this->dushCnt_--;

//			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("button05.mp3");
		}
	} else {

		if (this->NomlRad(ptFR_.getAngle())
				< CC_DEGREES_TO_RADIANS(90) || this->NomlRad(ptFR_.getAngle()) > 1.5 * M_PI) {
			this->dFRotPt -= (ptFRN_ * JumpPt.length() * kRot_);
		}
//	this->dRJumpPt -= (-ptFRN_ * JumpPt.length() * kRot_);
	}
}
void Bike::contRRot() {
	//R回転
	//回転する

	this->dFRotPt += (ptFRN_ * JumpPt.length() * kRot_);
	this->dRRotPt += (-ptFRN_ * JumpPt.length() * kRot_);

}
void Bike::ControlVelo(Vec2 rotPt_, Vec2 jumpPt_, float dt) {

	if (JumpPt == Vec2::ZERO) {
		return;
	}
	//回転ジャンプ同時制御
	this->dFJumpPt.set(Vec2::ZERO);
	this->dRJumpPt.set(Vec2::ZERO);

	this->dFRotPt.set(Vec2::ZERO); //前輪のジャンプ速度
	this->dRRotPt.set(Vec2::ZERO); //後輪のジャンプ速度

	ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
//	縦横で場合分け。
	FRnmlPt.set(FnmlPt + RnmlPt);
	FRnmlPt.normalize();

	ptFR_ = (this->getFWheel()->getPosition() - this->getRWheel()->getPosition());
	ptFR_.normalize();
	ptFRN_.set(ptFR_);
	ptFRN_.rotate(Vec2::ZERO, M_PI / 2);

	float rad = this->NomlRad(jumpPt_.getAngle());
	int ptn_ = (rad * 6 / M_PI);

	switch (ptn_) {

	case 0: {

		//前進
//		this->contDush();

		//Ｆ回転
		this->contFRot();

		break;
	}
	case 1: {

		//ジャンプ
		this->contJump();

		//Ｆ回転
		this->contFRot();

		break;
	}
	case 2: {

		//ジャンプ
		this->contJump();

		break;
	}
	case 3: {

		//ジャンプ
		this->contJump();

		break;
	}
	case 4: {

		//ジャンプ
		this->contJump();

		//Ｒ回転
		this->contRRot();

		break;
	}
	case 5: {

		//Ｒ回転
		this->contRRot();

		break;
	}
	case 6: {

		//Ｒ回転
		this->contRRot();

		break;
	}
	case 7: {

		//Ｒ回転
		this->contRRot();

		break;
	}
	case 10: {

		//F回転
		this->contFRot();

		break;
	}
	case 11: {

		//前進
//		this->contDush();

		//F回転
		this->contFRot();

		break;
	}

	}

	//最終的に制御する。

//	if(this->dFRotPt.length()> MaxRotVelo*0.3f){
//		this->dFRotPt.normalize();
//		this->dRRotPt.normalize();
//		this->dFRotPt*=(MaxRotVelo*0.3f);
//		this->dRRotPt*=(MaxRotVelo*0.3f);
//
//	}

	ptF.set(this->_body->getVelocity() + this->dFJumpPt + this->dFRotPt);
	ptR.set(this->_body2->getVelocity() + this->dRJumpPt + this->dRRotPt);

	ptFR.set(ptF / 2 + ptR / 2);
	ptF -= ptFR;
	ptR -= ptFR;

//	Vec2 x1_ = this->GetNaisei(ptFR_, ptF);
//	float x2_ = this->GetNaisei(ptFR_, ptR);

	float y1_ = this->GetNaisei(ptFRN_, ptF);
//	float y2_ = this->GetNaisei(ptFRN_, ptR);

	if (y1_ > MaxRotVelo) {

		y1_ = MaxRotVelo;

	} else if (y1_ < -MaxRotVelo) {

		y1_ = -MaxRotVelo;
	}
	ptF.set(ptFR);
	ptR.set(ptFR);

	ptF += (y1_ * ptFRN_);
	ptR -= (y1_ * ptFRN_);

	this->_body->setVelocity(ptF);
	this->_body2->setVelocity(ptR);

//	this->_body->applyImpulse((ptF-this->_body->getVelocity())*this->_body->getMass());
//	this->_body2->applyImpulse((ptR-this->_body2->getVelocity())*this->_body2->getMass());

	//タッチを解除する
	this->FtchFlg = false;
	this->RtchFlg = false;

}

void Bike::ControlVelo3(Vec2 rotPt_, Vec2 jumpPt_, float dt) {

	if (jumpPt_ == Vec2::ZERO) {
		return;
	}
	//回転ジャンプ同時制御
	this->dFJumpPt.set(Vec2::ZERO);
	this->dRJumpPt.set(Vec2::ZERO);
	Vec2 ptF;
	Vec2 ptR;
	Vec2 ptFR;
	ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
//	縦横で場合分け。
	FRnmlPt.set(FnmlPt + RnmlPt);
	FRnmlPt.normalize();

	float rad = this->NomlRad(jumpPt_.getAngle());
	int ptn_ = (rad * 6 / M_PI);

	switch (ptn_) {

	case 0: {

		//前に方向に進む。
		if (this->FtchFlg && this->RtchFlg) {
			Vec2 pt_;
			pt_.set(this->getFWheel()->getPosition() + this->getRWheel()->getPosition());
			pt_.normalize();
			this->dRJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
			this->dFJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
			this->KokiKoki0();
		}

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 1: {

		jumpFlg = false;
		if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
			//現在の速度に対してジャンプ速度を制御
			ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
			float yyy = this->GetNaisei(ptFR, FRnmlPt);
			float xxx = this->GetNaisei(jumpPt_ * kJump_, FRnmlPt);
			if (xxx < -MaxVelo * maxVelo_k) {
				xxx = -MaxVelo * maxVelo_k;
				jumpFlg = true;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				jumpFlg = true;
				jtime_ = 0;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			} else if (xxx > 0) {
				xxx = 0;
			} else {
				jumpFlg = true;
				jtime_ = 0;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			}
		} else {
			FRnmlPt.set(Vec2::ZERO);
		}

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 2: {

		jumpFlg = false;
		if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
			//現在の速度に対してジャンプ速度を制御
			ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
			float yyy = this->GetNaisei(ptFR, FRnmlPt);
			float xxx = this->GetNaisei(jumpPt_ * kJump_, FRnmlPt);
			if (xxx < -MaxVelo * maxVelo_k) {
				xxx = -MaxVelo * maxVelo_k;
				jumpFlg = true;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				jumpFlg = true;
				jtime_ = 0;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			} else if (xxx > 0) {
				xxx = 0;
			} else {
				jumpFlg = true;
				jtime_ = 0;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			}
		} else {
			FRnmlPt.set(Vec2::ZERO);
		}

		break;
	}
	case 3: {

		jumpFlg = false;
		if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
			//現在の速度に対してジャンプ速度を制御
			ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
			float yyy = this->GetNaisei(ptFR, FRnmlPt);
			float xxx = this->GetNaisei(jumpPt_ * kJump_, FRnmlPt);
			if (xxx < -MaxVelo * maxVelo_k) {
				xxx = -MaxVelo * maxVelo_k;
				jumpFlg = true;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				jumpFlg = true;
				jtime_ = 0;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			} else if (xxx > 0) {
				xxx = 0;
			} else {
				jumpFlg = true;
				jtime_ = 0;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			}
		} else {
			FRnmlPt.set(Vec2::ZERO);
		}

		break;
	}
	case 4: {

		jumpFlg = false;
		if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
			//現在の速度に対してジャンプ速度を制御
			ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
			float yyy = this->GetNaisei(ptFR, FRnmlPt);
			float xxx = this->GetNaisei(jumpPt_ * kJump_, FRnmlPt);
			if (xxx < -MaxVelo * maxVelo_k) {
				xxx = -MaxVelo * maxVelo_k;
				jumpFlg = true;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				jumpFlg = true;
				jtime_ = 0;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			} else if (xxx > 0) {
				xxx = 0;
			} else {
				jumpFlg = true;
				jtime_ = 0;
				this->dRJumpPt += xxx * FRnmlPt;
				this->dFJumpPt += xxx * FRnmlPt;
				this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
				this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);
			}
		} else {
			FRnmlPt.set(Vec2::ZERO);
		}

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 5: {

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 6: {

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 7: {

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 10: {

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}
	case 11: {

		//前に方向に進む。
		if (this->FtchFlg && this->RtchFlg) {
			Vec2 pt_;
			pt_.set(this->getFWheel()->getPosition() + this->getRWheel()->getPosition());
			pt_.normalize();
			this->dRJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
			this->dFJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
//			this->KokiKoki0();
		}

		//回転する
		this->FtchFlg = false;
		this->RtchFlg = false;
		//回転力を得る。
		this->AirPt.set(dbGPt + Vec2(0, 300));
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->AirPt.normalize();
//内積により求める
		float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
		if (zzz < -this->MaxRotVelo) {
			zzz = -this->MaxRotVelo;
		} else if (zzz > this->MaxRotVelo) {
			zzz = this->MaxRotVelo;
		}
		this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
		this->AirPt.normalize();
		this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
		this->dFJumpPt += zzz * this->AirPt;
		this->dRJumpPt -= zzz * this->AirPt;

		break;
	}

	}

	//最終的に制御する。

	ptF.set(this->_body->getVelocity() + this->dFJumpPt);
	ptR.set(this->_body2->getVelocity() + this->dRJumpPt);

	ptFR.set(ptF / 2 + ptR / 2);
	ptF -= ptFR;
	ptR -= ptFR;

	if (ptF.length() > MaxRotVelo || ptF.length() < -MaxRotVelo) {

		ptF.normalize();
		ptR.normalize();
		ptF *= MaxRotVelo;
		ptR *= MaxRotVelo;
	}
	ptF += ptFR;
	ptR += ptFR;

//	this->_body->setVelocity(ptF);
//	this->_body2->setVelocity(ptR);
	this->_body->setVelocity(ptF);
	this->_body2->setVelocity(ptR);
}

void Bike::ControlVelo2(Vec2 rotPt_, Vec2 jumpPt_, float dt) {

//	const char *str2 = "Bike::ControlVelo";
//	log("%s", str2);

//	Vec2 JumpPt; //ジャンプ用
//	Vec2 RotPt; //ローテーション用
	//回転ジャンプ同時制御
	this->dFJumpPt.set(Vec2::ZERO);
	this->dRJumpPt.set(Vec2::ZERO);
	Vec2 ptF;
	Vec2 ptR;
	Vec2 ptFR;
	ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
//	縦横で場合分け。

	float rad = this->NomlRad(jumpPt_.getAngle());
	FRnmlPt.set(FnmlPt + RnmlPt);
	FRnmlPt.normalize();
	if (jumpPt_ != Vec2::ZERO) {
		if (rad > M_PI / 6 && rad < M_PI * 5 / 6) {

			jumpFlg = false;
			//ジャンプ方向接地していたらジャンプ力を得る。
//	if ((this->FtchFlg || this->RtchFlg) && !jumpFlg_) {

			if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {

				//現在の速度に対してジャンプ速度を制御
				ptFR.set(this->_body->getVelocity() / 2 + this->_body2->getVelocity() / 2);
				float yyy = this->GetNaisei(ptFR, FRnmlPt);
				float xxx = this->GetNaisei(jumpPt_ * kJump_, FRnmlPt);

//		xxx -= yyy;

				if (xxx < -MaxVelo * maxVelo_k) {
//			if (xxx <0) {
//					const char *str = "ControlVelo_maxjump";
//					log("%s", str);
//			if (cntVelo_ == 0) {
					xxx = -MaxVelo * maxVelo_k;
					jumpFlg = true;
//			this->dRJumpPt -= yyy * FRnmlPt;
//			this->dFJumpPt -= yyy * FRnmlPt;

					this->dRJumpPt += xxx * FRnmlPt;
					this->dFJumpPt += xxx * FRnmlPt;
					jumpFlg = true;
					jtime_ = 0;

					this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
					this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);

//			}
//			cntVelo_++;
//			cntVelo_ = cntVelo_ % cntVelo;

				} else if (xxx > 0) {
					xxx = 0;
				} else {
//			this->dRJumpPt -= yyy * FRnmlPt;
//			this->dFJumpPt -= yyy * FRnmlPt;
//			if (cntVelo_ == 0) {
					jumpFlg = true;
					jtime_ = 0;
					this->dRJumpPt += xxx * FRnmlPt;
					this->dFJumpPt += xxx * FRnmlPt;

					this->_fWheel->setPosition(this->_fWheel->getPosition() - 10 * FRnmlPt);
					this->_rWheel->setPosition(this->_rWheel->getPosition() - 10 * FRnmlPt);

//					const char *str = "ControlVelo_jump";
//					log("%s", str);

//			}
//			cntVelo_++;
//			cntVelo_ = cntVelo_ % cntVelo;

				}

			} else {
				FRnmlPt.set(Vec2::ZERO);
			}

		}

//		else if (rad > M_PI * 3 / 4 && rad < M_PI * 5 / 4) {

		//後ろ方向に進む。
//		Vec2 pt_;
//		pt_.set(FRnmlPt);
//		pt_.rotate(Vec2::ZERO, M_PI / 2);
//
//		float xxx = this->GetNaisei(jumpPt_, pt_);
//		this->dRJumpPt += (xxx * 0.5f * pt_);
//		this->dFJumpPt += (xxx * 0.5f * pt_);
//		this->KokiKoki(0);

//		} else

		if ((rad < M_PI * 1 / 4) || (rad > M_PI * 7 / 4)) {
			if ((this->FtchFlg || this->RtchFlg) && jtime_ > jtime) {
				//前に方向に進む。
				Vec2 pt_;
				pt_.set(this->getFWheel()->getPosition() + this->getRWheel()->getPosition());
				pt_.normalize();

				this->dRJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
				this->dFJumpPt += (pt_ * jumpPt_.length() * maxVelo_k * kDush_);
			}
			this->KokiKoki(0);
		}

	}

	//回転する

	if (rotPt_ != Vec2::ZERO) {
		rad = this->NomlRad(rotPt_.getAngle());

		if ((rad > M_PI * 3 / 4 && rad < M_PI * 5 / 4) || (rad < M_PI * 1 / 4) || (rad > M_PI * 7 / 4)) {

			this->FtchFlg = false;
			this->RtchFlg = false;

			//回転力を得る。
			this->AirPt.set(dbGPt + Vec2(0, 300));

			this->AirPt.rotate(Vec2::ZERO, M_PI / 2);

			this->AirPt.normalize();
//内積により求める
			float zzz = this->GetNaisei(rotPt_ * kRot_, this->AirPt);
//	float xxx=(float)sqrt(zzz);

			if (zzz < -this->MaxRotVelo) {
//		if (zzz < 0) {
				zzz = -this->MaxRotVelo;
//		const char *str3 = "ControlVelo_MaxRotVelo";
//		log("%s", str3);

			} else if (zzz > this->MaxRotVelo) {
//	} else if (zzz > 0) {
				zzz = this->MaxRotVelo;
//		const char *str4 = "ControlVelo_MaxRotVelo";
//		log("%s", str4);
			}

//	const char *str4 = "ControlVelo_RotVelo";
//	log("%s", str4);

			this->AirPt.set(this->_fWheel->getPosition() - this->_rWheel->getPosition());
			this->AirPt.normalize();
			this->AirPt.rotate(Vec2::ZERO, M_PI / 2);
			this->dFJumpPt += zzz * this->AirPt;
			this->dRJumpPt -= zzz * this->AirPt;

//	this->_body->setVelocity(this->_body->getVelocity() + this->dFJumpPt);
//	this->_body2->setVelocity(this->_body2->getVelocity() + this->dRJumpPt);
//
//	return;

		}
	}

	ptF.set(this->_body->getVelocity() + this->dFJumpPt);
	ptR.set(this->_body2->getVelocity() + this->dRJumpPt);

	ptFR.set(ptF / 2 + ptR / 2);
	ptF -= ptFR;
	ptR -= ptFR;

	if (ptF.length() > MaxRotVelo || ptF.length() < -MaxRotVelo) {

		ptF.normalize();
		ptR.normalize();
		ptF *= MaxRotVelo;
		ptR *= MaxRotVelo;
	}
	ptF += ptFR;
	ptR += ptFR;

	this->_body->setVelocity(ptF);
	this->_body2->setVelocity(ptR);

//	}

}

void Bike::FForce(Vec2 pt_) {
//前輪荷重用

	this->_body->applyImpulse(pt_ * this->setchPow);
}
void Bike::RForce(Vec2 pt_) {
//後輪荷重用

	this->_body2->applyImpulse(pt_ * this->setchPow);
}

void Bike::ReSetJoint() {

	if (_joint0) {
		_joint0->removeFormWorld();
		_joint0->setEnable(false);
	}

	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;
	material0.restitution = 0;
	material0.friction = 10.0f;
	material0.density = 1;
	this->getBody3()->removeFromWorld();
	Vec2 ridr[] = { Vec2(25, 99), Vec2(49, 99), Vec2(84, -95), Vec2(-76, -93), Vec2(-45, 2) };
	this->setBody3(PhysicsBody::createPolygon(ridr, 5, material0));
	this->_body3->setGravityEnable(false);
	this->_body3->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body3->setCollisionBitmask(ChrPrm::COURCE);
	this->_body3->setContactTestBitmask(ChrPrm::NONE);
	this->_body3->setDynamic(true);
	this->_body3->setRotationEnable(true);

//	this->_body3->setPositionOffset(Vec2(100,50));
	this->_body3->setTag(10);
	this->setPhysicsBody(this->_body3);
	this->_body3->setGravityEnable(true);

//	this->_body3->setDynamic(false);
	this->FJump(Vec2(0, 100));
	this->RJump2(Vec2(0, 100), true);

}
void Bike::SetPositionBike(Vec2 pt_) {

	this->SetPointPos(pt_);
	this->getFWheel()->setPosition(this->getPosition() + Vec2(81, -100));
	this->getRWheel()->setPosition(this->getPosition() + Vec2(-76, -100));

}
void Bike::SetJointB(PhysicsWorld* PW) {
//メインシーンでボールの初期化時に同時に実行。

//	const char *str3 = "Bike::SetJointB_ st";
//	log("%s", str3);

	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;
	material0.restitution = 0;
	material0.friction = 0;
	material0.density = 0;

	Vec2 ridr[] = { Vec2(9, 32), Vec2(57, 2), Vec2(66, -46), Vec2(-50, -48), Vec2(-45, 2) };

	this->setBody3(PhysicsBody::createPolygon(ridr, 5, material0));
//	this->setBody3(PhysicsBody::createCircle(90, material0));
	this->_body3->setGravityEnable(false);
	this->_body3->setCategoryBitmask(ChrPrm::PLAYERBODY);
	this->_body3->setCollisionBitmask(ChrPrm::NONE);
	this->_body3->setContactTestBitmask(ChrPrm::COURCE);
	this->_body3->setDynamic(true);
	this->_body3->setRotationEnable(true);

//	this->_body3->setPositionOffset(Vec2(100,50));
	this->_body3->setTag(10);
	this->setPhysicsBody(this->_body3);

//	前輪を作成

	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0;
	material.friction = 2.0f;
	material.density = 0.5f;

	auto material2 = PHYSICSBODY_MATERIAL_DEFAULT;
	material2.restitution = 0;
	material2.friction = 0;
	material2.density = 0;

	//前輪を作成
	this->setBody(PhysicsBody::createCircle(this->getFWheel()->getContentSize().width / 2 - 2, material));
	this->_fWheel->setPhysicsBody(this->_body);
	this->_body->setGravityEnable(true);
	this->_body->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body->setCollisionBitmask(ChrPrm::COURCE);
	this->_body->setContactTestBitmask(ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body->setTag(1);
	this->_body->setDynamic(true);
	this->_body->setAngularDamping(wheelRotDump_);
	this->_body->setLinearDamping(veloDump);

	this->_body->setRotationEnable(true);

//前輪の接触感知用
	this->setBody4(PhysicsBody::createCircle(this->getFWheel()->getContentSize().width / 2, material2));
	this->_body4->setGravityEnable(false);
	this->_body4->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body4->setCollisionBitmask(ChrPrm::NONE);
	this->_body4->setContactTestBitmask(ChrPrm::COURCE);
	this->_body4->setTag(11);
	this->_body4->setDynamic(true);
	this->_body4->setRotationEnable(false);
	this->_body4->setEnable(true);
	this->setFWheelA(Node::create());
	this->_fWheelA->setPhysicsBody(this->_body4);

//	後輪を作成

	this->setBody2(PhysicsBody::createCircle(this->getRWheel()->getContentSize().width / 2 - 2, material));

	this->_rWheel->setPhysicsBody(this->_body2);
	this->_body2->setGravityEnable(true);
	this->_body2->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body2->setCollisionBitmask(ChrPrm::COURCE);
	this->_body2->setContactTestBitmask(ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body2->setTag(1);
	this->_body2->setDynamic(true);
	this->_body2->setAngularDamping(wheelRotDump_);
	this->_body2->setLinearDamping(veloDump);
	this->_body2->setRotationEnable(true);

//後輪の接触感知用
	this->setBody5(PhysicsBody::createCircle(this->getRWheel()->getContentSize().width / 2, material2));
	this->_body5->setGravityEnable(false);
	this->_body5->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body5->setCollisionBitmask(ChrPrm::NONE);
	this->_body5->setContactTestBitmask(ChrPrm::COURCE);
	this->_body5->setTag(12);
	this->_body5->setDynamic(true);
	this->_body5->setRotationEnable(false);
	this->_body5->setEnable(true);
	this->setRWheelA(Node::create());
	this->_rWheelA->setPhysicsBody(this->_body5);

//riderに前後輪を付ける
//	this->setGlobalZOrder(5);
//	this->_BikeImg->setGlobalZOrder(4);
	this->getFWheel()->setPosition(this->getPosition() + Vec2(81, -100));
//	this->addChild(this->_fWheel, 5);
//	this->_fWheel->setGlobalZOrder(5);
	this->getRWheel()->setPosition(this->getPosition() + Vec2(-76, -100));
//	this->addChild(this->_rWheel, 5);
//	this->_rWheel->setGlobalZOrder(5);

//	this->_pedaru->setGlobalZOrder(8);

	this->setJoint0(PhysicsJointDistance::construct(_body, _body2, Vec2(0.5, 1), Vec2(0.5, 0.5)));
	_joint0->setCollisionEnable(false);
//	this->setJoint1(PhysicsJointPin::construct(_body, _body3, _body->getPosition()));
//	_joint1->setCollisionEnable(false);
//	this->setJoint2(PhysicsJointPin::construct(_body2, _body3, _body2->getPosition()));
//	_joint2->setCollisionEnable(false);

	PW->addJoint(_joint0);
//	PW->addJoint(_joint1);
//	PW->addJoint(_joint2);

//	const char *str4 = "Bike::SetJointB_ fin";
//	log("%s", str4);

}

void Bike::SetJointC(PhysicsWorld* PW) {
//メインシーンでボールの初期化時に同時に実行。

//	const char *str3 = "Bike::SetJointC_ st";
//	log("%s", str3);

	auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;
	material0.restitution = 0.0001f;
	material0.friction = 0.01f;
	material0.density = 0;
	this->setBody3(PhysicsBody::createCircle(10, material0));
	this->_body3->setGravityEnable(false);
	this->_body3->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body3->setCollisionBitmask(ChrPrm::COURCE);
	this->_body3->setContactTestBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body3->setDynamic(true);
	this->_body3->setRotationEnable(true);

//	this->_body3->setPositionOffset(Vec2(100,50));
	this->_body3->setTag(10);
	this->setPhysicsBody(this->_body3);

	//bike本体を生成
	Vec2 bike_[] = { Vec2(81, -34), Vec2(81, -50), Vec2(-82, -50), Vec2(-82, -34) };
	this->setBody6(PhysicsBody::createPolygon(bike_, 4, material0));
	this->_body6->setGravityEnable(false);
	this->_body6->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body6->setCollisionBitmask(ChrPrm::NONE);
	this->_body6->setContactTestBitmask(ChrPrm::NONE);
	this->_body6->setDynamic(true);
	this->_body6->setRotationEnable(true);
	this->_BikeImg->setPhysicsBody(this->_body6);

//	前輪を作成

	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0.0f;
	material.friction = 3.0f;
	material.density = 0.5f;

	auto material2 = PHYSICSBODY_MATERIAL_DEFAULT;
	material2.restitution = 0;
	material2.friction = 0;
	material2.density = 0;

	this->setBody(PhysicsBody::createCircle(this->getFWheel()->getContentSize().width / 2, material));
	this->_fWheel->setPhysicsBody(this->_body);
	this->_body->setGravityEnable(true);
	this->_body->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body->setCollisionBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body->setContactTestBitmask(ChrPrm::NONE);
	this->_body->setTag(1);
	this->_body->setDynamic(true);
	this->_body->setAngularDamping(wheelRotDump_);
	this->_body->setLinearDamping(veloDump);

	this->_body->setRotationEnable(true);

//前輪の接触感知用
	this->setBody4(PhysicsBody::createCircle(this->getFWheel()->getContentSize().width / 2 + 2, material2));
	this->_body4->setGravityEnable(false);
	this->_body4->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body4->setCollisionBitmask(ChrPrm::NONE);
	this->_body4->setContactTestBitmask(ChrPrm::COURCE);
	this->_body4->setTag(11);
	this->_body4->setDynamic(true);
	this->_body4->setRotationEnable(false);
	this->_body4->setEnable(false);
	this->setFWheelA(Node::create());
	this->_fWheelA->setPhysicsBody(this->_body4);

//	後輪を作成

	this->setBody2(PhysicsBody::createCircle(this->getRWheel()->getContentSize().width / 2, material));

	this->_rWheel->setPhysicsBody(this->_body2);
	this->_body2->setGravityEnable(true);
	this->_body2->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body2->setCollisionBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body2->setContactTestBitmask(ChrPrm::NONE);
	this->_body2->setTag(1);
	this->_body2->setDynamic(true);
	this->_body2->setAngularDamping(wheelRotDump_);
	this->_body2->setLinearDamping(veloDump);
	this->_body2->setRotationEnable(true);

//後輪の接触感知用
	this->setBody5(PhysicsBody::createCircle(this->getRWheel()->getContentSize().width / 2 + 2, material2));
	this->_body5->setGravityEnable(false);
	this->_body5->setCategoryBitmask(ChrPrm::PLAYERBOUND);
	this->_body5->setCollisionBitmask(ChrPrm::NONE);
	this->_body5->setContactTestBitmask(ChrPrm::COURCE);
	this->_body5->setTag(12);
	this->_body5->setDynamic(true);
	this->_body5->setRotationEnable(false);
	this->_body5->setEnable(false);
	this->setRWheelA(Node::create());
	this->_rWheelA->setPhysicsBody(this->_body5);

//riderに前後輪を付ける
	this->setGlobalZOrder(12);
	this->_BikeImg->setGlobalZOrder(11);
	this->getFWheel()->setPosition(this->getPosition() + Vec2(81, -100));
//	this->addChild(this->_fWheel, 5);
	this->_fWheel->setGlobalZOrder(10);
	this->getRWheel()->setPosition(this->getPosition() + Vec2(-76, -100));
//	this->addChild(this->_rWheel, 5);
	this->_rWheel->setGlobalZOrder(10);

//	this->setJoint0(PhysicsJointDistance::construct(_body, _body2, Vec2(0.5, 1), Vec2(0.5, 0.5)));
//	_joint0->setCollisionEnable(false);
	this->setJoint1(PhysicsJointPin::construct(_body6, _body, _body->getPosition()));
	_joint1->setCollisionEnable(false);
	this->setJoint2(PhysicsJointPin::construct(_body6, _body2, _body2->getPosition()));
	_joint2->setCollisionEnable(false);

//	PW->addJoint(_joint0);
	PW->addJoint(_joint1);
	PW->addJoint(_joint2);

//	const char *str4 = "Bike::SetJointB_ fin";
//	log("%s", str4);

}

void Bike::SetJoint(PhysicsWorld* PW) {
//メインシーンでボールの初期化時に同時に実行。
	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0.001f;
	material.friction = 0.9f;
	material.density = 0.5f;

	this->setDmy0(Sprite::createWithTexture(this->getTexture()));
	this->setBody2(PhysicsBody::createCircle(this->getContentSize().width / 2, material));
	this->_body2->setGravityEnable(true);
	this->_body2->setCategoryBitmask(ChrPrm::PLAYER);
	this->_body2->setCollisionBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body2->setContactTestBitmask(ChrPrm::COURCE | ChrPrm::ENEMY | ChrPrm::ITEM);
	this->_body2->setDynamic(true);
	this->_body2->setRotationEnable(true);
	this->_body2->setTag(12);
//	this->getBody2()->setLinearDamping(0);
//	this->getBody2()->setAngularDamping(1);
//	this->_body2->setAngularVelocityLimit(0);
	_dmy0->setPhysicsBody(_body2);
	_dmy0->setPosition(
			Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2) + Vec2(-152, 0));
	this->addChild(_dmy0);
	this->setJoint0(PhysicsJointDistance::construct(_body, _body2, Vec2(0.5, 0.5), Vec2(0.5, 0.5)));
	_joint0->setCollisionEnable(false);
//	this->setJoint1(PhysicsJointPin::construct(_body, _body3, _body->getPosition()));
//	_joint1->setCollisionEnable(false);
//	this->setJoint2(PhysicsJointPin::construct(_body2, _body3, _body2->getPosition()));
//	_joint2->setCollisionEnable(false);

	PW->addJoint(_joint0);
//	PW->addJoint(_joint1);
//	PW->addJoint(_joint2);
}

void Bike::setContactAction(std::function<void(Bike*)> action) {

	this->onContactListener = action;

}
void Bike::setUpdateAction(std::function<void(Bike*)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	updateFlg = true;
	this->scheduleUpdate();

}
void Bike::update(float dt) {

//	if (!updateFlg) {
//		return;
//	}

//Bタイプの時
//	this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
//	this->setRotation(this->ChgKaku(this->rot_));
//	this->pt_.set(-78, 96);
//	this->pt_.rotate(Vec2::ZERO, this->rot_);
//	this->setPosition(this->getFWheel()->getPosition()+this->pt_);
//Aタイプのとき
//	this->x_ = this->ChgKaku((this->getBody2()->getPosition() - this->getBody()->getPosition()).getAngle());
//	this->getBikeImg()->setRotation(-this->getRotation() + this->x_ + 180);
//	_BikeImg->setPosition(Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));

	this->spd_ = this->spd_ * 0.8 + (this->getPosition() - beforePos_).length() / dt / 15 * 0.2;
	beforePos_.set(this->getPosition());

	_chaser->setPosition(this->ChaseA(chPt + this->getPosition(), _chaser->getPosition(), 20000, dt));

//	wClickTime_ += dt;
//	if (wClickTime_ >= wClickTime) {
//
//		wClickFlg = false;
//	}

	switch (this->getBikeState()) {
	case BikeState::READY: {

		//const char *str3 = "Bike::update";
		//log("%s", str3);

		this->onReady(dt);
		break;
	}
	case BikeState::NOML: {

		//const char *str3 = "Bike::update";
		//log("%s", str3);

		this->onNoml2(dt);
		break;
	}
	case BikeState::BREAK: {
		this->onBreak(dt);
		break;
	}
	case BikeState::GOAL: {
		this->onStop(dt);
		break;
	}
//	case BikeState::BIG: {
//		this->onBig(dt);
//		break;
//	}
//	case BikeState::BALUNE: {
//		this->onBalune(dt);
//		break;
//	}
//	case BikeState::SCOPE: {
//		this->onScope(dt);
//		break;
//	}
//	case BikeState::ALLOW: {
//		this->onAllow(dt);
//		break;
//	}
//	case BikeState::SLIDE: {
//		this->onSlide(dt);
//		break;
//	}
//	case BikeState::STOP: {
//		this->onStop(dt);
//		break;
//	}
//	case BikeState::JUMP: {
//		this->onJump(dt);
//		break;
//	}
//	case BikeState::JUMP2: {
//		this->onJump2(dt);
//		break;
//	}

	}

}

void Bike::SetSiseiState(SiseiState sis) {

	this->setSiseiState(sis);

	switch (this->getSiseiState()) {

	case SiseiState::MM: {
		maxVelo_k = 1.0f;

		kDush_ = 0.6f; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump1);
		this->_body2->setLinearDamping(kazeDump1);
		this->_body->setVelocityLimit(WheelVelo1);
		this->_body2->setVelocityLimit(WheelVelo1);
		break;
	}

	case SiseiState::MD: {
		maxVelo_k = 1.5f;

		kDush_ = 0.6f; //前進の操作感度係数
		kRot_ = 0; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump0);
		this->_body2->setLinearDamping(kazeDump0);
		this->_body->setVelocityLimit(WheelVelo0);
		this->_body2->setVelocityLimit(WheelVelo0);

		break;
	}
	case SiseiState::MU: {
		maxVelo_k = 0.5f;

		kDush_ = 0; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 0; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump2);
		this->_body2->setLinearDamping(kazeDump2);
		this->_body->setVelocityLimit(WheelVelo2);
		this->_body2->setVelocityLimit(WheelVelo2);
		break;
	}
	case SiseiState::BM: {
		maxVelo_k = 1.5f;

		kDush_ = 0.7f; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump1);
		this->_body2->setLinearDamping(kazeDump1);
		this->_body->setVelocityLimit(WheelVelo1);
		this->_body2->setVelocityLimit(WheelVelo1);
		break;
	}
	case SiseiState::BD: {
		maxVelo_k = 2.0f;

		kDush_ = 1.0f; //前進の操作感度係数
		kRot_ = 0; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelStopDump_);
		this->_body->setLinearDamping(kazeDump0);
		this->_body2->setLinearDamping(kazeDump0);
		this->_body->setVelocityLimit(WheelVelo0);
		this->_body2->setVelocityLimit(WheelVelo0);
		break;
	}
	case SiseiState::BU: {
		maxVelo_k = 0.5f;

		kDush_ = 0; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 0; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump2);
		this->_body2->setLinearDamping(kazeDump2);
		this->_body->setVelocityLimit(WheelVelo2);
		this->_body2->setVelocityLimit(WheelVelo2);
		break;
	}
	case SiseiState::FM: {
		maxVelo_k = 1.0f;

		kDush_ = 0.6f; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump1);
		this->_body2->setLinearDamping(kazeDump1);
		this->_body->setVelocityLimit(WheelVelo1);
		this->_body2->setVelocityLimit(WheelVelo1);
		break;
	}
	case SiseiState::FD: {
		maxVelo_k = 1.2f;

		kDush_ = 0.6f; //前進の操作感度係数
		kRot_ = 0; //回転の操作感度係数
		kJump_ = 100.0f; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump0);
		this->_body2->setLinearDamping(kazeDump0);
		this->_body->setVelocityLimit(WheelVelo0);
		this->_body2->setVelocityLimit(WheelVelo0);
		break;
	}
	case SiseiState::FU: {
		maxVelo_k = 0.5f;

		kDush_ = 0; //前進の操作感度係数
		kRot_ = 1.5f; //回転の操作感度係数
		kJump_ = 0; //ジャンプのの操作感度係数

		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setLinearDamping(kazeDump2);
		this->_body2->setLinearDamping(kazeDump2);
		this->_body->setVelocityLimit(WheelVelo2);
		this->_body2->setVelocityLimit(WheelVelo2);
		break;
	}

	default: {
		this->getBody2()->setAngularDamping(wheelRotDump_);
		this->_body->setVelocityLimit(WheelVelo0);
		this->_body2->setVelocityLimit(WheelVelo0);
		break;
	}

	}

}

void Bike::SetSisei(Vec2 pt_) {
//ptの位置で、形状を変える。

	int w = sosaLength;

	int x = pt_.x / w;
	int y = pt_.y / w;

	if (x > 3) {
		x = 3;
	} else if (x < -3) {
		x = -3;
	}

	if (y > 3) {
		y = 3;
	} else if (y < -3) {
		y = -3;
	}

	x += 3;
	y *= -1;
	y += 3;

	if (x < 2) {

		switch (y) {

		case 0: {
			this->SetSiseiState(SiseiState::BU);

			break;
		}
		case 1: {
			this->SetSiseiState(SiseiState::BU);
			break;
		}
		case 2: {
			this->SetSiseiState(SiseiState::BM);

			break;
		}
		case 3: {
			this->SetSiseiState(SiseiState::BM);
			break;
		}
		case 4: {
			this->SetSiseiState(SiseiState::BM);
			break;
		}
		case 5: {
			this->SetSiseiState(SiseiState::BD);
			break;
		}
		case 6: {
			this->SetSiseiState(SiseiState::BD);
			break;
		}

		}

	} else if (x >= 2 && x < 5) {
		switch (y) {

		case 0: {
			this->SetSiseiState(SiseiState::MU);
			break;
		}
		case 1: {
			this->SetSiseiState(SiseiState::MU);
			break;
		}
		case 2: {
			this->SetSiseiState(SiseiState::MM);
			break;
		}
		case 3: {
			this->SetSiseiState(SiseiState::MM);
			break;
		}
		case 4: {
			this->SetSiseiState(SiseiState::MM);
			break;
		}
		case 5: {
			this->SetSiseiState(SiseiState::MD);
			break;
		}
		case 6: {
			this->SetSiseiState(SiseiState::MD);
			break;
		}

		}
	} else {

		switch (y) {

		case 0: {
			this->SetSiseiState(SiseiState::FU);
			break;
		}
		case 1: {
			this->SetSiseiState(SiseiState::FU);
			break;
		}
		case 2: {
			this->SetSiseiState(SiseiState::FM);
			break;
		}
		case 3: {
			this->SetSiseiState(SiseiState::FM);
			break;
		}
		case 4: {
			this->SetSiseiState(SiseiState::FM);
			break;
		}
		case 5: {
			this->SetSiseiState(SiseiState::FD);
			break;
		}
		case 6: {
			this->SetSiseiState(SiseiState::FD);
			break;
		}
		}
	}

//	this->_BikeImg->setTextureRect(
//			Rect(frameSize.width * x, frameSize.height * y, frameSize.width, frameSize.height));

//Bタイプのとき
	this->setTextureRect(Rect(frameSize.width * x, frameSize.height * y, frameSize.width, frameSize.height));

}

void Bike::Boyon(Vec2 pt_) {
//ptの位置で、形状を変える。

//	Vec2 rPt;
//	rPt.set(pt_);
//	rPt.normalize();
//
//	this->_BikeImg->setScaleX(rPt.x);
//	this->_BikeImg->setScaleY(rPt.y);
//	return;

	float X_f = dbGptv_max / 3.0f;
	float L_f = pt_.length() / X_f;
	int L = (int) L_f;
	if (L > 3) {
		L = 3;
	}
	float deg = this->NomlRad(pt_.getAngle() + (M_PI * 1) / 8);
	float K_f = deg / (M_PI / 4);
	int K = (int) K_f;
	int n = K + L * 8;

	int i;
	int k;

	switch (n) {

	case 0: {
		i = 0;
		k = 0;
		break;
	}

	case 1: {
		i = 0;
		k = 0;
		break;
	}
	case 2: {
		i = 0;
		k = 0;
		break;
	}
	case 3: {
		i = 0;
		k = 0;
		break;
	}
	case 4: {
		i = 0;
		k = 0;
		break;
	}
	case 5: {
		i = 0;
		k = 0;
		break;
	}
	case 6: {
		i = 0;
		k = 0;
		break;
	}
	case 7: {
		i = 0;
		k = 0;
		break;
	}
	case 8: {
		i = 1;
		k = 0;
		break;
	}
	case 9: {
		i = 1;
		k = 2;
		break;
	}
	case 10: {
		i = 0;
		k = 1;
		break;
	}
	case 11: {
		i = 1;
		k = 1;
		break;
	}
	case 12: {
		i = 1;
		k = 0;
		break;
	}
	case 13: {
		i = 1;
		k = 2;
		break;
	}
	case 14: {
		i = 0;
		k = 1;
		break;
	}
	case 15: {
		i = 1;
		k = 1;
		break;
	}
	case 16: {
		i = 2;
		k = 0;
		break;
	}
	case 17: {
		i = 2;
		k = 2;
		break;
	}
	case 18: {
		i = 0;
		k = 2;
		break;
	}
	case 19: {
		i = 2;
		k = 1;
		break;
	}
	case 20: {
		i = 2;
		k = 0;
		break;
	}
	case 21: {
		i = 2;
		k = 2;
		break;
	}
	case 22: {
		i = 0;
		k = 2;
		break;
	}
	case 23: {
		i = 2;
		k = 1;
		break;
	}
	case 24: {
		i = 3;
		k = 0;
		break;
	}
	case 25: {
		i = 3;
		k = 2;
		break;
	}
	case 26: {
		i = 0;
		k = 3;
		break;
	}
	case 27: {
		i = 3;
		k = 1;
		break;
	}
	case 28: {
		i = 3;
		k = 0;
		break;
	}
	case 29: {
		i = 3;
		k = 2;
		break;
	}
	case 30: {
		i = 0;
		k = 3;
		break;
	}
	case 31: {
		i = 3;
		k = 1;
		break;
	}
	default: {
		i = 3;
		k = 3;

		break;
	}

	}

	this->_BikeImg->setTextureRect(
			Rect(frameSize.width * i, frameSize.height * k, frameSize.width, frameSize.height));

}
void Bike::onNoml2(float dt) {

	switch (this->fstFlg) {

	case true: {
		fstFlg = false;
		dbGPtv.set(Vec2::ZERO);

		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);

//		this->setVisible(true);

//		this->setOpacity(255);
//		this->getBikeImg()->setOpacity(255);
//		this->getFWheel()->setOpacity(255);
//		this->getRWheel()->setOpacity(255);

		break;
	}
	case false: {

		//本体の回転制御
		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);

		//ホイールを追従
//		this->_fWheelA->setPosition(this->_fWheel->getPosition());
//		this->_rWheelA->setPosition(this->_rWheel->getPosition());

		//gameover
		if (deadFlg_ && !goalFlg_) {
			this->fstFlg = true;
			this->setBikeState(BikeState::BREAK);
			return;
		}
		//ゴール
		if (goalFlg_) {
			this->fstFlg = true;
			this->setBikeState(BikeState::GOAL);
			return;
		}
		//姿勢によりダンピング制御
		this->SetSisei(this->_point2 - this->_point1);

		jtime_ += dt;
		if (swaipFlg_) {

//			Vec2 JumpPt; //ジャンプ用
//			Vec2 RotPt; //ローテーション用
			this->ControlVelo(RotPt, JumpPt, dt);
			this->JumpPt.set(Vec2::ZERO);
			this->SetTouch(false);
			swaipFlg_ = false;
		}

		//ダッシュカウント回復処理
		dushTime_ += dt;
		if (dushTime_ > dushTime) {
			dushTime_ -= dushTime;
			if (dushCnt_ < dushCnt) {
				dushCnt_++;
			}
		}

//pointDbgの処理
		dbGPt.set(this->ChaseA(this->_point2 - this->_point1, dbGPt, dbGPtSpeed_, dt));

		//コキコキする。
//		KokiTime_ += dt;
//		if (kokiOn && !kokiOn_) {
//			this->KokiKoki(dt);
//		}
		break;
	}

	}
}

void Bike::onNoml(float dt) {

	if (this->fstFlg) {

		fstFlg = false;
		dbGPtv.set(Vec2::ZERO);

	} else {

		//前後の配分決める

//		if (this->RtchFlg) {
//
//			if (this->FtchFlg) {
//				FjumpPow = 0.5f;		//前後輪の力の配分
//				RjumpPow = 0.5f;
//			} else {
//				FjumpPow = 0;		//前後輪の力の配分
//				RjumpPow = 1.5f;
//			}
//
//		} else {
//			if (this->FtchFlg) {
//				FjumpPow = 1.5f;		//前後輪の力の配分
//				RjumpPow = 0;
//			} else {
//				FjumpPow = 0;		//前後輪の力の配分
//				RjumpPow = 0;
//			}
//		}

		//本体の回転制御
		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);

		//ホイールを追従
		this->_fWheelA->setPosition(this->_fWheel->getPosition());
		this->_rWheelA->setPosition(this->_rWheel->getPosition());

		//gameover
		if (deadFlg_) {
			this->fstFlg = true;
			this->setBikeState(BikeState::BREAK);
			return;
		}
		//ゴール
		if (goalFlg_) {
			this->fstFlg = true;
			this->setBikeState(BikeState::GOAL);
			return;
		}
		//姿勢によりダンピング制御
//		if (this->getSiseiState() != this->getSiseiStateA()) {
		switch (this->getSiseiState()) {
		case SiseiState::MM: {
			maxVelo_k = 1.0f;

			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump1);
			this->_body2->setLinearDamping(kazeDump1);
			this->_body->setVelocityLimit(WheelVelo1);
			this->_body2->setVelocityLimit(WheelVelo1);
			break;
		}

		case SiseiState::MD: {
			maxVelo_k = 1.2f;
			RotPt.set(Vec2::ZERO);

			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump0);
			this->_body2->setLinearDamping(kazeDump0);
			break;
		}
		case SiseiState::MU: {
			maxVelo_k = 0.5f;
			JumpPt.set(Vec2::ZERO);
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump2);
			this->_body2->setLinearDamping(kazeDump2);
			this->_body->setVelocityLimit(WheelVelo2);
			this->_body2->setVelocityLimit(WheelVelo2);
			break;
		}
		case SiseiState::BM: {
			maxVelo_k = 1.0f;
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump1);
			this->_body2->setLinearDamping(kazeDump1);
			this->_body->setVelocityLimit(WheelVelo1);
			this->_body2->setVelocityLimit(WheelVelo1);
			break;
		}
		case SiseiState::BD: {
			maxVelo_k = 1.5f;
			RotPt.set(Vec2::ZERO);
			this->getBody2()->setAngularDamping(wheelStopDump_);
			this->_body->setLinearDamping(kazeDump0);
			this->_body2->setLinearDamping(kazeDump0);
			this->_body->setVelocityLimit(WheelVelo0);
			this->_body2->setVelocityLimit(WheelVelo0);
			break;
		}
		case SiseiState::BU: {
			maxVelo_k = 0.5f;
			JumpPt.set(Vec2::ZERO);
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump2);
			this->_body2->setLinearDamping(kazeDump2);
			this->_body->setVelocityLimit(WheelVelo2);
			this->_body2->setVelocityLimit(WheelVelo2);
			break;
		}
		case SiseiState::FM: {
			maxVelo_k = 1.0f;
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump1);
			this->_body2->setLinearDamping(kazeDump1);
			this->_body->setVelocityLimit(WheelVelo1);
			this->_body2->setVelocityLimit(WheelVelo1);
			break;
		}
		case SiseiState::FD: {
			maxVelo_k = 1.2f;
			RotPt.set(Vec2::ZERO);
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump0);
			this->_body2->setLinearDamping(kazeDump0);
			this->_body->setVelocityLimit(WheelVelo0);
			this->_body2->setVelocityLimit(WheelVelo0);
			break;
		}
		case SiseiState::FU: {
			maxVelo_k = 0.5f;
			JumpPt.set(Vec2::ZERO);
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setLinearDamping(kazeDump2);
			this->_body2->setLinearDamping(kazeDump2);
			this->_body->setVelocityLimit(WheelVelo2);
			this->_body2->setVelocityLimit(WheelVelo2);
			break;
		}

		default: {
			this->getBody2()->setAngularDamping(wheelRotDump_);
			this->_body->setVelocityLimit(WheelVelo0);
			this->_body2->setVelocityLimit(WheelVelo0);
			break;
		}

		}

//			this->setSiseiStateA(this->getSiseiState());
//
//		}

		//自動復帰時にジャンプする場合
//		if (!this->touchFlg) {
//			if ((dbGPt - dbGPt_).length() >= swaipLength && !swaipFlg_) {
//
//				const char *str2 = "Bike::Swaip";
//				log("%s", str2);
//				JumpPt.set(dbGPt - dbGPt_);
//				dbGPt_.set(dbGPt);
//				//			JumpPt *= ((_point2 - _point1).length() / swaipLength);		//中心より遠い場合強くする。
//				swaipFlg_ = true;
//				this->SetTouch(true);
//
//			}
//		}

		jtime_ += dt;
		if (swaipFlg_) {

//			Vec2 JumpPt; //ジャンプ用
//			Vec2 RotPt; //ローテーション用
			this->ControlVelo(RotPt, JumpPt, dt);
			this->SetTouch(false);
			swaipFlg_ = false;
		}
//		sosaPt_.set(sosaPt);		//ひとつ前の操作ポイント
//		sosaPt.set(this->_point2 - this->_point1);		//操作ポイント
//		sosaVelo.set((sosaPt - sosaPt_) / dt);
//		jtime_ += dt;
		//操作速度
//		if (sosaVelo.length() > 1) {
//			this->SetTouch(true);
//		this->ControlVelo2(sosaVelo, dt);
//		} else {
//		this->SetTouch(false);
//		}

//		if (swaipFlg_) {
//
//			this->dFJumpPt.set(Vec2::ZERO);
//			this->dRJumpPt.set(Vec2::ZERO);
//
//			switch (this->getSiseiState()) {
//
//			case SiseiState::MM: {
//				maxVelo_k = 0.5f;
////				this->AirRot(JumpPt);
////				this->FJump3(JumpPt * 0.5);
////				this->RJump3(JumpPt * 0.5);
//				break;
//			}
//
//			case SiseiState::MD: {
//				maxVelo_k = 1.0f;
////				this->AirRot(JumpPt);
////				this->FJump3(JumpPt);
////				this->RJump3(JumpPt);
//				break;
//			}
//			case SiseiState::MU: {
//				maxVelo_k = 0.25f;
////				this->AirRot(JumpPt);
////				this->FJump3(JumpPt * 0.25);
////				this->RJump3(JumpPt * 0.25);
//				break;
//			}
//			case SiseiState::BM: {
//				maxVelo_k = 2.0f;
////				this->AirRot(JumpPt);
////				this->RJump3(JumpPt * 2);
//				break;
//			}
//			case SiseiState::BD: {
//				maxVelo_k = 3.0f;
////				this->AirRot(JumpPt);
////				this->RJump3(JumpPt * 4);
//				break;
//			}
//			case SiseiState::BU: {
//				maxVelo_k = 0.25f;
////				this->AirRot(JumpPt);
////				this->RJump3(JumpPt);
//				break;
//			}
//			case SiseiState::FM: {
//				maxVelo_k = 1.0f;
////				this->FJump3(JumpPt * 2);
////				this->AirRot(JumpPt);
////				this->RJump(JumpPt / 3);
//				break;
//			}
//			case SiseiState::FD: {
//				maxVelo_k = 2.0f;
////				this->FJump3(JumpPt * 3);
////				this->AirRot(JumpPt);
//				break;
//			}
//			case SiseiState::FU: {
//				maxVelo_k = 0.25f;
////				this->FJump3(JumpPt);
////				this->AirRot(JumpPt);
//				break;
//			}
//
//			}
//
//			this->ControlVelo(JumpPt);
////			SaveRotaion();
//
////			this->_body->setVelocity(this->_body->getVelocity() + this->dFJumpPt * dt * 50);
////			this->_body2->setVelocity(this->_body2->getVelocity() + this->dRJumpPt * dt * 50);
//
//			this->SetTouch(false);
//			swaipFlg_ = false;
//		}

		//動くものに乗った時に移動する
//		if (this->getTchNode()) {
//			this->setPosition(this->getPosition() + this->getTchNode()->getPosition() - ntchPt_);
//			ntchPt_.set(this->getTchNode()->getPosition());
//		}

//pointDbgの処理
		dbGPt.set(this->ChaseA(this->_point2 - this->_point1, dbGPt, dbGPtSpeed_, dt));

//		Vec2 dbGPtv;//移動速度
//		Vec2 dbGPta;//加速度
//		float dgGPtb=2;//ばね力
//		float dgGPtz=0.1f;//減衰
//		int dbGptv_max=100;//最大速度
//		dbGPta.set(this->getPosition() - dbGPt);
//		dbGPta *= dgGPtb;
//		dbGPtv += (dbGPta * dt);
//		dbGPtv *= (1 - dgGPtz);
//		dbGPt += (dbGPtv * dt);
//		if ((dbGPt - this->getPosition()).length() > dbGptv_max) {
//			dbGPt.set(dbGPt - this->getPosition());
//			dbGPt.normalize();
//			dbGPt *= dbGptv_max;
//			dbGPt += this->getPosition();
//		}

//		_pointDbg->setPosition(
//				dbGPt + Vec2(this->getContentSize().width / 2, this->getContentSize().height / 2));
		this->SetSisei(this->_point2 - this->_point1);

		//コキコキする。
		KokiTime_ += dt;
		if (kokiOn) {
			this->KokiKoki(dt);
		}

	}
}

void Bike::SaveRotaion() {
	//MaxRotVelo以内になるように回転制御

//	this->FtchFlg=false;
//	this->RtchFlg=false;

	Vec2 ptF;
	ptF.set(this->_body->getVelocity() + this->dFJumpPt);
	Vec2 ptR;
	ptR.set(this->_body2->getVelocity() + this->dRJumpPt);
	Vec2 ptFR;
	ptFR.set(ptF / 2 + ptR / 2);
	ptF -= ptFR;
	ptR -= ptFR;

	if (ptF.length() > MaxRotVelo || ptF.length() < -MaxRotVelo) {

		ptF.normalize();
		ptR.normalize();
		ptF *= MaxRotVelo;
		ptR *= MaxRotVelo;
	}
	ptF += ptFR;
	ptR += ptFR;
	ptF -= this->_body->getVelocity();
	ptR -= this->_body2->getVelocity();
	this->_body->setVelocity(this->_body->getVelocity() + ptF);
	this->_body2->setVelocity(this->_body2->getVelocity() + ptR);
//	this->_body->applyImpulse(ptF);
//	this->_body2->applyImpulse(ptR);
}

void Bike::onBig(float dt) {

	if (this->fstFlg) {
		fstFlg = false;

	} else {

	}

}
void Bike::onBreak(float dt) {

	if (this->fstFlg) {

		this->ReSetJoint();

//		this->_gan->setPosition(this->ganPt_);
//		this->_gan->setPosition(this->getPosition());
		this->_gan->setRotation(-CC_RADIANS_TO_DEGREES(this->ganNml.getAngle()));

		auto fade_ = FadeOut::create(0.3f);
		auto big_ = ScaleTo::create(0.3f, 2);
		auto spn_ = Spawn::create(fade_, big_, NULL);
		this->_gan->runAction(spn_);

		this->addChild(this->_gan, 2);

//		this->_gan->setVisible(true);
		fstFlg = false;

	} else {

	}

}

void Bike::onReady(float dt) {

	switch (this->fstFlg) {

	case true: {
		this->fstFlg = false;
		//本体の回転制御
		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);
//		this->setVisible(true);
//		this->getFWheel()->setVisible(true);
//		this->getRWheel()->setVisible(true);

		break;
	}
	case false: {

		//本体の回転制御
		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);
		break;
	}

	}

}

void Bike::SetPause() {

	this->_body->setAngularDamping(100);
	this->_body2->setAngularDamping(100);
	this->_body->setLinearDamping(10);
	this->_body2->setLinearDamping(10);
	this->_body->setVelocityLimit(0.5);
	this->_body2->setVelocityLimit(0.5);
}

void Bike::onStop(float dt) {

	if (this->fstFlg) {

		this->getBody2()->setAngularDamping(wheelStopDump_);
		this->_body->setLinearDamping(kazeDump0);
		this->_body2->setLinearDamping(kazeDump0);
		this->_body->setVelocityLimit(WheelVelo0);
		this->_body2->setVelocityLimit(WheelVelo0);

		fstFlg = false;

	} else {

		//本体の回転制御
		this->rot_ = (this->getBody()->getPosition() - this->getBody2()->getPosition()).getAngle();
		this->setRotation(this->ChgKaku(this->rot_));
		this->pt_.set(-78, 96);
		this->pt_.rotate(Vec2::ZERO, this->rot_);
		this->setPosition(this->getFWheel()->getPosition() + this->pt_);

		if (deadFlg_) {
			this->fstFlg = true;
			this->setBikeState(BikeState::BREAK);
			return;
		}

//		this->getBody()->setVelocity(Vec2(0, this->getBody()->getVelocity().y));
//		this->getBody()->setAngularVelocity(0);
		//	this->setPosition(
		//		Vec2(this->stopPt.x, this->getPosition().y));

		//動くものに乗った時に移動する
//		if (this->getTchNode()) {
//			this->setPosition(this->getPosition() + this->getTchNode()->getPosition() - ntchPt_);
//			ntchPt_.set(this->getTchNode()->getPosition());
//		}
//
//		if (!this->touchFlg) {
//
//			this->fstFlg = true;
//			this->setBikeState(BikeState::NOML);
//			this->jumpFlg = false;
//			this->jumpFlg2 = false;
//
//		}

	}

}

void Bike::onBalune(float dt) {

	if (this->fstFlg) {
		this->_body->setAngularVelocity(0);
		this->_body->setVelocity(Vec2::ZERO);
		this->setScale(1);
		this->stopAllActions();
		fstFlg = false;
		auto big_ = ScaleTo::create(0.1, 1.3f);
		this->runAction(big_);
		baluneMoveTime_ = 0;
	} else {

		if (touchFlg) {
			BaluneMove(dt);
		} else {

			this->stopAllActions();

			auto big_ = ScaleTo::create(0.1, 1.0f);
			this->runAction(big_);
			this->fstFlg = true;
			this->setBikeState(BikeState::NOML);
		}

	}

}

void Bike::BaluneMove(float dt) {

	baluneMoveTime_ += dt;

	if (baluneMoveTime_ < baluneMoveTime) {

		this->pt_.set(this->_point2 - this->_point1);
		this->pt_.normalize();
		this->pt_.set(0, 1);
		this->getBody()->applyImpulse(this->pt_ * BaluneVelo * dt);
	} else {
		touchFlg = false;
		baluneMoveTime_ = 0;
	}
}

void Bike::onScope(float dt) {

	if (this->fstFlg) {
		fstFlg = false;
		this->_body->setAngularVelocity(0);
		this->_body->setVelocity(Vec2::ZERO);
		this->pt_.set(this->getPosition());

	} else {

		if (touchFlg) {
			this->setPosition(this->pt_);
			this->_body->setVelocity(Vec2::ZERO);
			this->pt2_.set(this->_point1 - this->_point2);

		} else {
			this->fstFlg = true;
			this->setBikeState(BikeState::ALLOW);

		}

	}

}
void Bike::onAllow(float dt) {

	if (this->fstFlg) {
		fstFlg = false;

		//this->pt2_.set(this->_point1 - this->_point2);
		this->pt2_.normalize();

		if (allowSpeed > x_) {
			this->pt2_ *= allowSpeed;
		} else {
			this->pt2_ *= x_;
		}

		//

		//this->getBody()->applyImpulse(this->pt2_);
		this->getBody()->setVelocity(this->pt2_);
		this->getBody2()->setEnable(false);
		//this->getBody2()->setVelocity(this->pt2_);
	} else {

		fstFlg = true;
		this->setBikeState(BikeState::NOML);

	}

}
void Bike::onSlide(float dt) {

	if (this->fstFlg) {
		fstFlg = false;

		this->_body->setLinearDamping(this->dump_Slide);
		this->slideTime_ = 0;
	} else {

		this->slideTime_ += dt;
		if (this->slideTime_ >= this->slideTime) {
			this->fstFlg = true;
			this->setBikeState(BikeState::NOML);
		}

	}

}
void Bike::onJump(float dt) {

	if (this->fstFlg) {
		fstFlg = false;
		this->zimenFlg = false;
		this->zimenFlg2 = false;
		this->jumpFlg = false;
		this->_body->setLinearDamping(this->dump_Jump);
		jumpTime_ = 0;
		jumpPt2.set(this->_point2);
		jumpPt1.set(this->_point2);
		jumpPt_.set(this->_point2);
		JumpSosaFlg = false;
		JumpSosaFinFlg = false;		//ジャンプ操作完了
	} else {

		jumpTime_ += dt;

		if (jumpTime_ >= jumpTime) {
			this->_body->setLinearDamping(this->dump_Nomal);
		}
		//タッチをし続けた時
		if (this->touchFlg) {

			if (this->zimenFlg2) {
				this->fstFlg = true;
				this->setBikeState(BikeState::STOP);
			} else {

				//ジャンプ中に少し操作可能

				if (JumpSosaFlg && !JumpSosaFinFlg) {
					//	this->getBody()->setVelocity(
					//			Vec2(0, this->getBody()->getVelocity().y));
					this->getBody()->applyImpulse(this->jumpPt / dt);
					JumpSosaFlg = false;
					JumpSosaFinFlg = true;
				} else {
					this->jumpPt_.set(this->ChaseA(jumpPt2, this->jumpPt_, 300, dt));
					this->jumpPt.set(this->jumpPt_ - jumpPt1);
					this->setPosition(this->getPosition() + this->jumpPt);
					this->getBody()->applyImpulse(this->jumpPt / dt);
					this->jumpPt1.set(this->jumpPt_);

				}

				/*
				 //this->pt_.normalize();
				 if (pt_.x > -1 && pt_.x < 1) {
				 this->getBody()->applyImpulse(Vec2(0, BaluneVelo * dt));
				 } else if (pt_.x <= -1) {
				 this->_body->setLinearDamping(this->dump_Nomal);
				 //this->getBody()->applyImpulse(Vec2(-BaluneVelo*2 * dt, 0));
				 this->getBody()->setVelocity(this->getBody()->getVelocity()+Vec2(-this->jumpSpeed/1 , 0));
				 this->fstFlg = true;
				 this->setBikeState(BikeState::NOML);

				 } else {
				 this->_body->setLinearDamping(this->dump_Nomal);
				 //this->getBody()->applyImpulse(Vec2(BaluneVelo*2 * dt, 0));
				 this->getBody()->setVelocity(this->getBody()->getVelocity()+Vec2(this->jumpSpeed/1, 0));
				 this->fstFlg = true;
				 this->setBikeState(BikeState::NOML);
				 }
				 */
			}

		} else {
			this->fstFlg = true;
			this->setBikeState(BikeState::NOML);
		}

	}

}
void Bike::onJump2(float dt) {

	if (this->fstFlg) {
		fstFlg = false;

	} else {

		if (this->zimenFlg2) {
			if (this->touchFlg) {
				this->fstFlg = true;
				this->setBikeState(BikeState::STOP);
			} else {
				this->fstFlg = true;
				this->setBikeState(BikeState::NOML);
			}
		}

		if (this->touchFlg) {
			//ジャンプ中に少し操作可能
			this->pt_.set(this->_point2 - this->_point1);
			//this->pt_.normalize();
			if (pt_.x > -1 && pt_.x < 1) {
				this->getBody()->applyImpulse(Vec2(0, BaluneVelo * dt));
			} else if (pt_.x <= -1) {
				this->getBody()->applyImpulse(Vec2(-BaluneVelo * dt, 0));
			} else {
				this->getBody()->applyImpulse(Vec2(BaluneVelo * dt, 0));
			}
		}

	}

}

void Bike::Action1() {
//ジャンプ時のアクション
//ダミーボデイが広がって、すぐしぼむ
	this->_dmy0->setScale(1.6f);
	this->_BikeImg->setScale(1.3f);
	auto delay_ = DelayTime::create(0.1);
	this->jumpFlg = true;
	this->slideFlg = false;
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->jumpFlg=false;
		//this->slideFlg=true;
			this->_BikeImg->setScale(1);
			this->_dmy0->setScale(1);

		});
	auto delay2_ = DelayTime::create(0.1);
	auto func2_ = CallFuncN::create([this](Node* nd) {

	});

	auto seq_ = Sequence::create(delay_, func_, NULL);

	this->runAction(seq_);

}
void Bike::Action2() {
//ストップ時のアクション
//ダミーボデイが広がって、すぐしぼむ
	this->_dmy0->setScale(1.6f);
	this->_BikeImg->setScale(1.3f);
	auto delay_ = DelayTime::create(0.1);
	this->jumpFlg = true;
	this->slideFlg = false;
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->jumpFlg=false;
		//this->slideFlg=true;
			this->_BikeImg->setScale(1);
			this->_dmy0->setScale(1);

		});
	auto delay2_ = DelayTime::create(0.1);
	auto func2_ = CallFuncN::create([this](Node* nd) {

	});

	auto seq_ = Sequence::create(delay_, func_, NULL);

	this->runAction(seq_);
}

void Bike::TouchOn(Vec2 pt) {

	if (this->goalFlg_) {
		return;
	}

	this->_point1.set(pt);
	this->_point2.set(pt);
	dbGPt.set(Vec2::ZERO);
	dbGPt_.set(Vec2::ZERO);
	touchFlg = true;
	jumpFlg = false;
	cntVelo_ = 0;
	swaipFlg_ = false;
	swaipFlg = false;
	this->JumpPt.set(Vec2::ZERO);

//	sosaPt.set(Vec2::ZERO);					//操作ポイント
//	sosaPt_.set(Vec2::ZERO);					//ひとつ前の操作ポイント
//	sosaVelo.set(Vec2::ZERO);					//操作速度

	if (KokiTime_ < KokiTime && !this->kokiOn_) {
		KokiTime_ = 0;
		kokiCnt_++;
		if (kokiCnt_ > kokiCnt) {
			kokiOn = true;
		}
	} else {
		kokiCnt_ = 0;

	}

	KokiTime_ = 0;

	switch (this->getBikeState()) {

	case BikeState::NOML: {

		swaipFlg = false;
		swaipFlg_ = false;

		break;
	}

	case BikeState::BIG: {

		break;
	}
	case BikeState::BALUNE: {

		break;
	}
	case BikeState::SCOPE: {

		break;
	}
	case BikeState::ALLOW: {

		break;
	}
	case BikeState::SLIDE: {
		this->fstFlg = true;
		this->setBikeState(BikeState::NOML);
		break;
	}
	case BikeState::STOP: {

		break;
	}
	case BikeState::JUMP: {

		this->stopAllActions();
		baluneTime_ = 0;

		//ダミーボデイが広がって、すぐしぼむ
		this->_dmy0->setScale(1.4f);
		this->_BikeImg->setScale(1.1f);
		auto delay_ = DelayTime::create(0.1);
		this->jumpFlg = true;
		this->slideFlg = false;
		auto func_ = CallFuncN::create([this](Node* nd) {
			this->jumpFlg=false;
			//this->slideFlg=true;
				this->_BikeImg->setScale(1);
				this->_dmy0->setScale(1);
			});
		auto delay2_ = DelayTime::create(0.1);
		auto func2_ = CallFuncN::create([this](Node* nd) {
		});

		auto seq_ = Sequence::create(delay_, func_, NULL);

		this->runAction(seq_);

		break;
	}
	case BikeState::JUMP2: {

		break;
	}
	}

}

void Bike::SetTouch(bool flg) {
//タイヤが接地しているか確認用

//	if (setTouchFlg == flg) {
//		return;
//	}

//	setTouchFlg = flg;
//	switch (setTouchFlg) {
//
//	case true: {
//		this->_fWheelA->setScale(1.0f);
//		this->_rWheelA->setScale(1.0f);
//		break;
//	}
//
//	case false: {
//		this->_fWheelA->setScale(0.8f);
//		this->_rWheelA->setScale(0.8f);
//		break;
//	}
//
//	}
//
//	return;

	setTouchFlg = flg;

	switch (setTouchFlg) {
	case true: {

		this->_body4->setEnable(true);
		this->_body5->setEnable(true);
		this->_fWheelA->setPosition(this->_fWheel->getPosition());
		this->_rWheelA->setPosition(this->_rWheel->getPosition());
		break;
	}
	case false: {
		this->_body4->setEnable(false);
		this->_body5->setEnable(false);
		this->_fWheelA->setPosition(Vec2::ZERO);
		this->_rWheelA->setPosition(Vec2::ZERO);
		break;
	}
	}

}

void Bike::Swaip(Vec2 pt1, Vec2 pt2) {

	this->_point1.set(pt1);
	this->_point2.set(pt2);

	switch (this->getBikeState()) {

	case BikeState::NOML: {

//		if (sosaVelo.length() > 1) {
//
////			const char *str2 = "Bike::Swaip_sosaVelo.length() > 1";
////			log("%s", str2);
//
//			this->SetTouch(true);
//		}

		if ((_point2 - _point1 - dbGPt).length() >= swaipLength && !swaipFlg_) {

//			const char *str2 = "Bike::Swaip";
//			log("%s", str2);

			JumpPt.set(_point2 - _point1 - dbGPt);

			RotPt.set(JumpPt);

			dbGPt += JumpPt;
//			JumpPt *= ((_point2 - _point1).length() / swaipLength);		//中心より遠い場合強くする。
			swaipFlg_ = true;

			this->SetTouch(true);

		}

		break;
	}
	case BikeState::JUMP: {

		if ((this->jumpPt_ - this->jumpPt1).length() < jumpSosa && !JumpSosaFinFlg) {

			this->jumpPt2.set(this->_point2);
		} else {
			JumpSosaFlg = true;
			//JumpSosaFinFlg=true;
		}
		break;
	}
	case BikeState::BIG: {

		break;
	}
	case BikeState::BALUNE: {

		break;
	}
	case BikeState::SCOPE: {

		break;
	}
	case BikeState::ALLOW: {

		break;
	}
	case BikeState::SLIDE: {

		break;
	}

	}

}
void Bike::TouchOff() {

	if (_point2.x - _point1.x > 0) {
		leftSwaip_ = false;
	} else {
		leftSwaip_ = true;
	}

	this->_point1.set(Vec2::ZERO);
	this->_point2.set(Vec2::ZERO);

	touchFlg = false;

	switch (this->getBikeState()) {

	case BikeState::NOML: {

//		JumpPt.set(_point2 - _point1 - dbGPt);
//		dbGPt.set(_point2 - _point1);
//
//		swaipFlg_ = true;
//
//		this->SetTouch(true);

		//jumpingFlg = false;

		//	this->leftFlg = false;
		//	this->rightFlg = false;
		//	this->stopFlg = false;
		//	this->jumpFlg = false;
		//	this->jumpFlg2 = false;

		/*//ドスン関係
		 if (jumpingFlg && !this->wClickFlg) {
		 this->dosnFlg = true;
		 }
		 */
		break;
	}

	case BikeState::BIG: {

		break;
	}
	case BikeState::BALUNE: {

		break;
	}
	case BikeState::SCOPE: {

		break;
	}
	case BikeState::ALLOW: {

		break;
	}
	case BikeState::SLIDE: {

		this->fstFlg = true;
		this->setBikeState(BikeState::NOML);

		break;
	}
	case BikeState::STOP: {
		//	this->stopFlg = false;
		//	this->leftFlg = false;
		//	this->rightFlg = false;
		//	this->stopFlg = false;
		//	this->jumpFlg = false;
		//	this->jumpFlg2 = false;
		break;
	}
	}

}

void Bike::Fin() {

	if (this->onFinishListener) {
		onFinishListener(this);
	}

}

void Bike::AccellMove(Acceleration* acc) {

	auto mpt = Vec2((float) acc->x * 1000, (float) acc->y * 1000);

	this->getBody()->applyImpulse(mpt);

}

void Bike::AccellMove(Vec2 dctpt) {

	dctpt.normalize();
//this->getBody()->applyImpulse(dctpt*50);
//this->getBody()->setVelocity(dctpt * this->veloLimit);
//	this->getBody()->applyForce(dctpt);

}

void Bike::FadeInBike(float delay, float dt) {

	auto fade_ = FadeIn::create(dt);
	auto delay_ = DelayTime::create(delay);
	auto seq_ = Sequence::create(delay_->clone(), fade_->clone(), NULL);

	this->runAction(seq_->clone());
	this->getFWheel()->runAction(seq_->clone());
	this->getRWheel()->runAction(seq_->clone());
	this->getBikeImg()->runAction(seq_->clone());

}
void Bike::FadeOutBike(float delay, float dt) {

	if (delay == 0 || dt == 0) {

		this->setOpacity(0);
		this->getFWheel()->setOpacity(0);
		this->getRWheel()->setOpacity(0);
		this->getBikeImg()->setOpacity(0);

	} else {

		auto fade_ = FadeOut::create(dt);
		auto delay_ = DelayTime::create(delay);
		auto seq_ = Sequence::create(delay_->clone(), fade_->clone(), NULL);

		this->runAction(seq_->clone());
		this->getFWheel()->runAction(seq_->clone());
		this->getRWheel()->runAction(seq_->clone());
		this->getBikeImg()->runAction(seq_->clone());

	}
}
void Bike::SetOpacityBike(int opc) {

	this->setOpacity(opc);
	this->getBikeImg()->setOpacity(0);
	this->getFWheel()->setOpacity(opc);
	this->getRWheel()->setOpacity(opc);

}

void Bike::sameBody2() {
	this->getBody2()->setLinearDamping(this->getBody()->getLinearDamping());
	this->getBody2()->setAngularDamping(this->getBody()->getAngularDamping());
	this->getBody2()->setVelocityLimit(this->getBody()->getVelocityLimit());

}

void Bike::Action3() {
	/*
	 this->setBike(BikeState::T4);

	 auto delay_ = DelayTime::create(0.8);
	 auto do1_ = CallFuncN::create([this](Node* node) {

	 auto bl=dynamic_cast<Bike*>(node);
	 bl->setBike(BikeState::T1);

	 });
	 auto seq_=Sequence::create(delay_,do1_,NULL);
	 this->runAction(seq_);
	 */
}
void Bike::Action4() {

}
