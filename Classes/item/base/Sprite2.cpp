#include "Sprite2.h"

// 衝突判定時のカテゴリ設定　todo 設定方法見直す。
const int zyaraCatg = 1 << 0;
const int handCatg = 1 << 1;
const int pointCatg = 1 << 2;
const int dmgCatg = 1 << 3;
const int nikuCatg = 1 << 4;
const int kabeCatg = 1 << 5;

Sprite2::Sprite2():
_parentSprite(NULL), _body(NULL), _debugPt(NULL),_calc(NULL), _updateListener(NULL), _touch(NULL), _pinPt(Vec2::ZERO), _ctPt(Vec2::ZERO)
{}

Sprite2::~Sprite2() {
    CC_SAFE_RELEASE_NULL(_parentSprite);
    CC_SAFE_RELEASE_NULL(_body);
    CC_SAFE_RELEASE_NULL(_debugPt);
    CC_SAFE_RELEASE_NULL(_calc);
    CC_SAFE_RELEASE_NULL(_touch);
}

Sprite2* Sprite2::create() {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithFile("dumybody.png")) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

Sprite2* Sprite2::create(const std::string& filename) {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithFile(filename)) {
		ret->autorelease();

		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

Sprite2* Sprite2::createWithTexture(Texture2D *texture) {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithTexture(texture)) {
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

Sprite2* Sprite2::createWithTexture(Texture2D *texture, Rect rct_) {
	Sprite2 *ret = new Sprite2();
	if (ret && ret->initWithTexture(texture)) {
		ret->setTextureRect(rct_);
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return ret;
}

bool Sprite2::initWithFile(const std::string& filename){
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    //画面のサイズをセットする
    auto director = Director::getInstance();
    this->winSize = director->getWinSize();
    this->ctPt.set(winSize.width / 2, winSize.height / 2);
    this->setCalc(Calclater::create());
    return true;
}

bool Sprite2::initWithTexture(Texture2D *texture){
    if (!Sprite::initWithTexture(texture)) {
        return false;
    }
    //画面のサイズをセットする
    auto director = Director::getInstance();
    this->winSize = director->getWinSize();
    this->ctPt.set(winSize.width / 2, winSize.height / 2);
    this->setCalc(Calclater::create());
    return true;
}

void Sprite2::setDefaultTouchEvent(){
    this->setTouch(TouchEventHelper::create());
    this->getTouch()->getTouchListenner()->onTouchBegan = [this](Touch* touch,Event* event) {
        _touched = false;
        Rect targetBox = this->getBoundingBox();
        if(targetBox.containsPoint(touch->getLocation())){
            _touched = true;
            this->setPosition(touch->getLocation());
//            NJLOG(ST_NODE(this));
        }
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchMoved = [this](Touch* touch,Event* event) {
        if(_touched){
            this->setPosition(touch->getLocation());
        }
        return true;
    };
    this->getTouch()->getTouchListenner()->onTouchEnded = [this](Touch* touch,Event* event) {
        _touched = false;
        return true;
    };    
    this->getTouch()->applyTouchListenner(this);
}

void Sprite2::update(float dt) {
	if (this->_updateListener) {
		this->_updateListener(this, dt);
	}
}

//操作方法をセット
void Sprite2::SetMoveTypeA(float velo_) {
	this->setScale(0.4f);
	_velo = velo_;
	pt_.set(0, _velo);
	pt_.rotate(Vec2::ZERO, -_calc->chgRad(this->getRotation()));

	this->setBody(PhysicsBody::createCircle(this->getContentSize().width / 2 * 0.4));
	this->setPhysicsBody(this->getBody());

	_body->setGravityEnable(false);
	_body->setDynamic(true);
	_body->setTag(zyaraCatg);
	_body->setCategoryBitmask(zyaraCatg);
	_body->setContactTestBitmask(handCatg | dmgCatg | nikuCatg | kabeCatg | pointCatg);
	_body->setCollisionBitmask(handCatg | dmgCatg | nikuCatg | kabeCatg | pointCatg);
	_body->setRotationEnable(false);
	this->setTag(zyaraCatg);

	this->setUpDateListener([this](Sprite2* sp ,float dt) {
		if(this->_trnLeft) {
			pt_.rotate(Vec2::ZERO,M_PI*dt*1.5);
		}
		if(this->_trnRight) {
			pt_.rotate(Vec2::ZERO,-M_PI*dt*1.5);
		}
		this->setPosition(this->getPosition()+pt_*dt);
		this->setRotation(90+_calc->chgKaku(pt_.getAngle()));
	});
	this->scheduleUpdate();
}

void Sprite2::SetMoveTypeB(float velo_) {

	this->setScale(0.4f);
	_velo = velo_;
	pt_.set(0, _velo);
	pt_.rotate(Vec2::ZERO, -_calc->chgRad(this->getRotation()));

	this->setBody(PhysicsBody::createCircle(this->getContentSize().width / 2 * 0.4));
	this->setPhysicsBody(this->getBody());

	_body->setGravityEnable(false);
	_body->setDynamic(true);
	_body->setTag(zyaraCatg);
	_body->setCategoryBitmask(zyaraCatg);
	_body->setContactTestBitmask(handCatg | dmgCatg | nikuCatg | kabeCatg | pointCatg);
	_body->setCollisionBitmask(handCatg | dmgCatg | nikuCatg | kabeCatg | pointCatg);
	_body->setRotationEnable(false);
	this->setTag(zyaraCatg);

	this->setUpDateListener([this](Sprite2* sp ,float dt) {
		pt_.rotate(Vec2::ZERO,-M_PI*dt*(_point2-_point1).x*0.02);
		this->setPosition(this->getPosition()+pt_*dt);
		this->setRotation(90+_calc->chgKaku(pt_.getAngle()));
	});
	this->scheduleUpdate();
}

void Sprite2::MadePoint() {
    this->setDebugPt(Sprite2::create("point2.png"));
	for (int i = 0; i < 4; ++i) {
		auto frame = SpriteFrame::createWithTexture(_debugPt->getTexture(), Rect(60 * i, 0, 60, 60));
		_pointFrame.pushBack(frame);

	}
	for (int i = 2; i >= 1; i--) {
		auto frame = SpriteFrame::createWithTexture(_debugPt->getTexture(), Rect(60 * i, 0, 60, 60));
        _pointFrame.pushBack(frame);

	}
    _debugPt->setTextureRect(Rect(0, 0, 60, 60));

	auto animation = Animation::createWithSpriteFrames(_pointFrame);
	animation->setDelayPerUnit(0.1f);
	auto rot_ = RepeatForever::create(RotateBy::create(1, 180));
	auto rept = RepeatForever::create(Animate::create(animation));

	//_debugPt->runAction(rot_);
    _debugPt->runAction(rept);

	this->setBody(PhysicsBody::createCircle(15));
	_body->setGravityEnable(false);
	_body->setDynamic(true);
	_body->setEnabled(true);
	_body->setRotationEnable(false);
	_body->setCollisionBitmask(zyaraCatg | kabeCatg | handCatg);
	_body->setCategoryBitmask(pointCatg);
	_body->setContactTestBitmask(zyaraCatg | kabeCatg | handCatg);
	_body->setTag(pointCatg);
    _debugPt->setPhysicsBody(_body);
	//_body->setVelocity(Vec2(100,100));

	this->addChild(_debugPt);

}

void Sprite2::ShowPoint(bool flg) {

	if (!_debugPt) {
		return;
	}

	pointFlg = flg;
    _debugPt->setVisible(flg);
//    _debugPt->enabled(flg)
}

void Sprite2::DelShow(Vec2 pt_) {
	//return;
	if (!_debugPt) {
		return;
	}
//エフェクトで消える。
	int c = arc4random() % static_cast<int>(360);
	Vec2 pt;

	pt.set(pt_);
	pt.normalize();
	this->getBody()->setVelocity(pt * 100);
	/*
	 auto move_ = MoveBy::create(0.5, pt * 300);
	 auto func_ = CallFuncN::create([this](Node* nd) {

	 this->ShowPoint(false);

	 });

	 auto seq_ = Sequence::create(move_, func_, move_->reverse(), NULL);
	 _debugPt->runAction(seq_);
	 */
}

void Sprite2::DelShow() {
	return;
	if (!_debugPt) {
		return;
	}
	//エフェクトで消える。
	int c = arc4random() % static_cast<int>(360);
	Vec2 pt;

	pt.set(1, 0);
	pt.rotate(Vec2::ZERO, c);
	auto move_ = MoveBy::create(0.5, pt * 300);
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->ShowPoint(false);
	});
	auto seq_ = Sequence::create(move_, func_, move_->reverse(), NULL);
    _debugPt->runAction(seq_);

}

void Sprite2::SetPointPos(Vec2 pt) {
//比率
	if (!_debugPt) {
		return;
	}
	pt.x *= this->getContentSize().width;
	pt.y *= this->getContentSize().height;
    _debugPt->setPosition(pt);
}

void Sprite2::SetRot(float kaku_) {
	pt_.set(_ctPt);
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));
	this->setPosition(_pinPt - pt_);
	this->setRotation(kaku_);
}

void Sprite2::SetPos(Vec2 pt_) {
	this->setPinPt(pt_);
	this->SetRot(this->getRotation());
}

void Sprite2::SetRotPos(float kaku_, Vec2 pt_) {
	this->setPinPt(pt_);
	this->SetRot(kaku_);
}

void Sprite2::SetRot2(float kaku_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	pt_.set(_ctPt);
	kaku_ += _parentSprite->getRotation();
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));

	pt2_.set(_pinPt - Vec2(_parentSprite->getContentSize().width / 2, _parentSprite->getContentSize().height / 2));
	pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(_parentSprite->getRotation()));
	pt2_ += _parentSprite->getPosition();

	this->setPosition(pt2_ - pt_);
	this->setRotation(kaku_);
}

void Sprite2::SetPos2(Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot2(this->getRotation());
}

void Sprite2::SetRotPos2(float kaku_, Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot2(kaku_);
}

void Sprite2::SetRot3(float kaku_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	pt_.set(_ctPt);
	kaku_ += _parentSprite->getRotation();
	kaku_ += _parentSprite->getParent()->getRotation();
	pt_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(kaku_));

	pt2_.set(_pinPt - Vec2(_parentSprite->getContentSize().width / 2, _parentSprite->getContentSize().height / 2));
	pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(_parentSprite->getRotation()));
	pt2_ += _parentSprite->getPosition();

	pt3_.set(pt2_ - Vec2(_parentSprite->getParent()->getContentSize().width / 2,
							_parentSprite->getParent()->getContentSize().height / 2));
	pt3_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(_parentSprite->getParent()->getRotation()));
	pt3_ += _parentSprite->getParent()->getPosition();
	this->setPosition(pt3_ - pt_);
	this->setRotation(kaku_);
}

void Sprite2::SetPos3(Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot3(this->getRotation());
}
void Sprite2::SetRotPos3(float kaku_, Vec2 pt_) {
	//ピン止めするように回転する.親ノードの親ノードの親ノードに所属している場合
	this->setPinPt(pt_);
	this->SetRot3(kaku_);
}

Vec2 Sprite2::GetLocalPt(Vec2 pt) {
	if (this->getParent()) {
		Node* nd = this->getParent();
		pt2_.set(this->getContentSize().width * this->getAnchorPoint().x,
				this->getContentSize().height * this->getAnchorPoint().y);
		pt2_.rotate(Vec2::ZERO, -CC_DEGREES_TO_RADIANS(this->getRotation()));
		pt_.set(pt - this->getPosition());
		pt_ -= pt2_;
		pt_.rotate(Vec2::ZERO, CC_DEGREES_TO_RADIANS(this->getRotation()));
	}	return pt_;

}

void Sprite2::setVisible(bool flg) {
	Sprite::setVisible(flg);
	if (_body) {
		if (pointFlg) {
			_debugPt->setVisible(flg);
			_body->setEnabled(flg);
		} else {
			if (!flg) {
				_debugPt->setVisible(flg);
				_body->setEnabled(flg);
			}
		}
	}
}

bool Sprite2::GetTouch(Vec2 pt_) {
	//画像内であったら真
	Vec2 off_;
	off_.set(this->getAnchorPoint());
	Rect rct;
	Vec2 xx;
	xx.set(this->getPosition());
	xx -= Vec2(this->getContentSize().width * off_.x, this->getContentSize().height * off_.y);
	rct.setRect(xx.x, xx.y, this->getContentSize().width, this->getContentSize().height);
	return rct.containsPoint(pt_);
}

float Sprite2::ChaseRad(float rad1_, float rad2_, float velo_, float dt) {
	//rad1_へ向かって、rad2_から回転する。角度の増分を出力
	rad1_ = _calc->nomlRad(rad1_);
	rad2_ = _calc->nomlRad(rad2_);

	if (rad1_ - rad2_ > -velo_ * dt && rad1_ - rad2_ < velo_ * dt) {
		return 0;
	}
	float drad_;
	if (rad1_ >= rad2_) {
		if (rad1_ - rad2_ <= M_PI) {
			drad_ = rad1_ - rad2_;
			if (drad_ > velo_ * dt) {
				drad_ = velo_ * dt;
			}
			const char *str0 = "R0";
			log("%s", str0);
			return drad_;
		} else {
			drad_ = rad2_ + 2 * M_PI - rad1_;
			if (drad_ > velo_ * dt) {
				drad_ = velo_ * dt;
			}
			const char *str1 = "R1";
			log("%s", str1);
			return -drad_;
		}
	} else {
		if (rad2_ - rad1_ <= M_PI) {
			drad_ = rad2_ - rad1_;
			if (drad_ > velo_ * dt) {
				drad_ = velo_ * dt;
			}
			const char *str2 = "R2";
			log("%s", str2);
			return -drad_;
		} else {
			drad_ = rad1_ + 2 * M_PI - rad2_;
			if (drad_ > velo_ * dt) {
				drad_ = velo_ * dt;
			}
			const char *str3 = "R3";
			log("%s", str3);
			return drad_;
		}
	}
}

bool Sprite2::ChaseA(float dt) {
	//chaser_をAに近づける。速度v_　時間dt_
	chsFlg = true;
	if ((AutoPt - pt_).length() > AutoV * dt) {
		chsFlg = false;
		pt_ += pt2_ * AutoV * dt;
	} else {
		pt_.set(AutoPt);

	}
	this->setPosition(pt_);
	return chsFlg;
}

void Sprite2::ChaseA(Vec2 A, float v_, float dt) {
	AutoPt.set(A);
	AutoV=v_;
	this->setPosition(this->ChaseA(A, this->getPosition(), v_, dt));
}

Vec2 Sprite2::ChaseA(Vec2 A, Vec2 chaser_, float v_, float dt) {
	//chaser_をAに近づける。速度v_　時間dt_
	AutoPt.set(A);
	AutoV=v_;

	pt_.set(chaser_);
	pt2_.set(A - chaser_);
	pt2_.normalize();
	chsFlg = true;
	if ((A - pt_).length() > v_ * dt) {
		chsFlg = false;
		pt_ += pt2_ * v_ * dt;
	} else {
		pt_.set(A);
	}
	return pt_;
}

float Sprite2::ChaseA(float A, float chaser_, float v_, float dt) {
	//chaser_をAに近づける。速度v_　時間dt_
	x_ = chaser_;
	chsFlg = true;
	if (A - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
	}
	if (A - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
	}
	return x_;
}

float Sprite2::ChaseB(float A, float vA, float chaser_, float v_, float dt) {
	//移動予測して追う
	x_ = chaser_;
	chsFlg = true;
	if (A + vA * dt - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
	}
	if (A + vA * dt - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
	}
	return x_;
}

Vec2 Sprite2::ChaseB(Vec2 A, Vec2 vA, Vec2 chaser_, float v_, float dt) {
	//移動予測して追う
	pt_.set(chaser_);
	pt2_.set(A + vA * dt - chaser_);
	pt2_.normalize();
	chsFlg = true;
	if ((A - pt_).length() > v_ * dt) {
		chsFlg = false;
		pt_ += pt2_ * v_ * dt;
	}
	return pt_;
}

//Vec2 rndR_; //ランダム回転半径
//Vec2 rndrad_; //ランダム回転速度ラジアン
float Sprite2::ChaseC(float A, float chaser_, float v_, float dt) {
	rndR_.rotate(Vec2::ZERO, rndrad_ * dt);
	x_ = chaser_;
	chsFlg = true;
	if (A + rndR_.x - x_ > v_ * dt) {
		chsFlg = false;
		x_ += v_ * dt;
	}
	if (A + rndR_.x - x_ < -v_ * dt) {
		chsFlg = false;
		x_ -= v_ * dt;
	}
	return x_;
}

Vec2 Sprite2::ChaseC(Vec2 A, Vec2 chaser_, float v_, float dt) {
	pt_.set(chaser_);
	rndR_.rotate(Vec2::ZERO, rndrad_ * dt);
	pt2_.set(A + rndR_ - chaser_);
	pt2_.normalize();
	//chsFlg = true;
//	if ((A - pt_).length() > v_ * dt) {
	chsFlg = false;
	pt_ += pt2_ * v_ * dt;
//	}
	return pt_;
}

/** パラメータサンプル
this->setParentSprite(Sprite::create());
this->getParentSprite();
this->setBody(PhysicsBody::create());
this->getBody();
this->setDebugPt(Sprite::create());
this->getDebugPt();
this->setCalc(Calclater::create());
this->getCalc();
*/
