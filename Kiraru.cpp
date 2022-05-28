#include "cocos2d.h"
#include "cmath"

#include "Kiraru.h"
USING_NS_CC;

Kiraru::Kiraru() :
		_body(NULL), speed_(1.0f), speed2_(1.0f) {
}
Kiraru::~Kiraru() {
	//CC_SAFE_RELEASE_NULL(_body);
	//CC_SAFE_RELEASE_NULL(_joint1);
}

Kiraru* Kiraru::createWithTexture(Texture2D *texture) {
	Kiraru *sprite = new Kiraru();
	if (sprite && sprite->initWithTexture(texture)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	sprite = NULL;
	return NULL;
}
Kiraru* Kiraru::createWithTexture_NoBound(Texture2D *texture) {
	Kiraru *sprite = new Kiraru();
	if (sprite && sprite->initWithTexture_NoBound(texture)) {
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	sprite = NULL;
	return NULL;
}
bool Kiraru::initWithTexture(Texture2D *texture) {

	if (!Sprite::initWithTexture(texture)) {
		return false;
	}

	auto director = Director::getInstance();
	winSize = director->getWinSize();

	frameSize = Size(this->getContentSize().width / 4,
			this->getContentSize().height / 7);
	this->cPt_.set(frameSize.width / 2, frameSize.height / 2);
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));
	//this->setOpacity(0);

	//auto material0 = PHYSICSBODY_MATERIAL_DEFAULT;	//端部の状態
	material_.friction = 1.0f;
	material_.restitution = 0;

	this->setBody(PhysicsBody::createCircle(25));
	_body->setGravityEnable(true);
	_body->setDynamic(true);
	_body->setEnable(true);
	_body->setRotationEnable(true);

	_body->setCollisionBitmask(ChrPrm::COURCE);
	_body->setCategoryBitmask(ChrPrm::ITEM);
	_body->setContactTestBitmask(ChrPrm::PLAYER);
	_body->setTag(1);
	_body->setVelocityLimit(MaxV);
	this->setPhysicsBody(_body);
	//_body->setVelocity(Vec2(100,100));
	SetKiraruState(KiraruState::A);

	/*
	 this->SetUpdateListenner([this](Kiraru* kr,float dt) {

	 if(kr->getPosition().y<0) {
	 kr->DelKiraru();
	 }

	 ChgInterval_+=dt;
	 if(ChgInterval_>ChgInterval) {
	 ChgInterval_=0;
	 int x = arc4random() % static_cast<int>(winSize.width - 200) + 100;
	 int y = arc4random() % static_cast<int>(winSize.height - 400) + 200;
	 this->TargetPt_.set(x,y);

	 }

	 Force_.set(this->TargetPt_-this->getPosition());
	 Force_.normalize();
	 Force_*=MaxF;
	 //this->getBody()->applyForce(Force_);
	 this->getBody()->applyImpulse(Force_);

	 });
	 */
	return true;

}
void Kiraru::SetKiraruStateRnd() {

	int rnd_ = arc4random() % static_cast<int>(7);
	//rnd_ = 6;	//ためし
	switch (rnd_) {

	case 0: {

		this->SetKiraruState(KiraruState::A);

		break;
	}
	case 1: {
		this->SetKiraruState(KiraruState::B);
		break;
	}
	case 2: {
		this->SetKiraruState(KiraruState::C);
		break;
	}
	case 3: {
		this->SetKiraruState(KiraruState::D);
		break;
	}
	case 4: {
		this->SetKiraruState(KiraruState::E);
		break;
	}
	case 5: {
		this->SetKiraruState(KiraruState::F);
		break;
	}
	case 6: {
		this->SetKiraruState(KiraruState::G);
		break;
	}
	default: {
		this->SetKiraruState(KiraruState::A);
		break;
	}

	}

}
void Kiraru::SetKiraruState(KiraruState ks) {

	this->setKiraruState(ks);
	this->getBody()->setVelocity(Vec2::ZERO);
	this->Lifetime_ = 0;

	this->SetUpdateListenner(NULL);
	this->stopAllActions();
	_pointFrame.clear();

	for (int i = 0; i < 4; ++i) {
		auto frame = SpriteFrame::createWithTexture(this->getTexture(),
				Rect(frameSize.width * i, frameSize.height * (int) ks,
						frameSize.width, frameSize.height));
		_pointFrame.pushBack(frame);

	}
	for (int i = 2; i >= 1; i--) {
		auto frame = SpriteFrame::createWithTexture(this->getTexture(),
				Rect(frameSize.width * i, frameSize.height * (int) ks,
						frameSize.width, frameSize.height));
		_pointFrame.pushBack(frame);

	}

	auto animation = Animation::createWithSpriteFrames(_pointFrame);
	animation->setDelayPerUnit(0.1f);
	auto rot_ = RepeatForever::create(RotateBy::create(1, 180));
	auto rept = RepeatForever::create(Animate::create(animation));

	//_point->runAction(rot_);
	this->runAction(rept);

	//挙動を変える。
	switch (this->getKiraruState()) {

	case KiraruState::A: {
//ランダムにあちこち行く
		this->Lifetime = 5;
		this->SetUpdateListenner(
				[this](Kiraru* kr,float dt) {
					/*
					 if(kr->getPosition().y<0) {
					 kr->DelKiraru();
					 }
					 */
					ChgInterval_+=dt;
					if(ChgInterval_>ChgInterval) {
						ChgInterval_=0;
						int x = arc4random() % static_cast<int>(winSize.width - 200) + 100;
						int y = arc4random() % static_cast<int>(winSize.height - 400) + 200;
						this->TargetPt_.set(x,y);

					}

					Force_.set(this->TargetPt_-this->getPosition());
					Force_.normalize();
					Force_*=MaxF;
					//this->getBody()->applyForce(Force_);
					this->getBody()->applyImpulse(Force_);

					this->Lifetime_+=dt;
					if(this->Lifetime_>this->Lifetime) {
//						this->DelKiraru();
					}

				});

		break;
	}

	case KiraruState::B: {
		//真ん中でふらふら
		this->TargetPt_.set(winSize.width / 2, winSize.height - 200);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {
			/*
			 if(kr->getPosition().y<0) {
			 kr->DelKiraru();
			 }
			 */
			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;
	}
	case KiraruState::C: {

		//くるくる回る
		this->TargetPt_.set(winSize.width / 2, winSize.height - 200);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {
			/*
			 if(kr->getPosition().y<0) {
			 kr->DelKiraru();
			 }
			 */
			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			Force_.rotate(Vec2::ZERO,M_PI/10);
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;

		break;
	}
	case KiraruState::D: {

		//真ん中より右ででふらふら
		this->TargetPt_.set(winSize.width / 2 + 100, winSize.height - 200);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {
			/*
			 if(kr->getPosition().y<0) {
			 kr->DelKiraru();
			 }
			 */
			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;
	}
	case KiraruState::E: {

		//真ん中より左ででふらふら
		this->TargetPt_.set(winSize.width / 2 - 100, winSize.height - 200);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {
			/*
			 if(kr->getPosition().y<0) {
			 kr->DelKiraru();
			 }
			 */
			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;
	}
	case KiraruState::F: {

		//くるくる回る逆
		this->TargetPt_.set(winSize.width / 2, winSize.height - 200);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {
			/*
			 if(kr->getPosition().y<0) {
			 kr->DelKiraru();
			 }
			 */
			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			Force_.rotate(Vec2::ZERO,-M_PI/10);
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;

		break;
	}
	case KiraruState::G: {

		//流れ星
		int x = arc4random() % static_cast<int>(winSize.width - 40) + 20;

		//this->Pt1_.set(x,0);
		this->TargetPt_.set(x, 0);
		this->SetUpdateListenner([this](Kiraru* kr,float dt) {

			if(kr->getPosition().y<30) {
				kr->DelKiraru();
			}

			this->Lifetime=5;

			Force_.set(this->TargetPt_-this->getPosition());
			Force_.normalize();
			Force_*=MaxF;
			Force_*=5;
			Force_.rotate(Vec2::ZERO,-M_PI/10);
			//this->getBody()->applyForce(Force_);
				this->getBody()->applyImpulse(Force_);

				this->Lifetime_ += dt;
				if (this->Lifetime_ > this->Lifetime) {
//					this->DelKiraru();
				}

			});

		break;
	}
	}

}
bool Kiraru::initWithTexture_NoBound(Texture2D *texture) {

	if (!Sprite::initWithTexture(texture)) {
		return false;
	}

	return true;

}

bool Kiraru::init() {

	if (!Sprite::initWithFile("point2.png")) {
		return false;
	}
	auto director = Director::getInstance();
	winSize = director->getWinSize();

	frameSize = Size(this->getContentSize().width,
			this->getContentSize().height);

	this->cPt_.set(frameSize.width / 2, frameSize.height / 2);
	this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

	this->SetUpdateListenner([this](Kiraru* kr,float dt) {

		if(kr->getPosition().y<0) {
			kr->DelKiraru();
		}

	});

	return true;
}

void Kiraru::SetUpdateListenner(std::function<void(Kiraru*, float)> action) {
	this->unscheduleUpdate();
	this->onUpDateListener = action;
	updateFlg = true;
	this->scheduleUpdate();
}
void Kiraru::update(float dt) {

	//各ステートで分岐する。

	if (!updateFlg) {
		return;
	}

	if (this->onUpDateListener) {
		onUpDateListener(this, dt);
	}

}
void Kiraru::ClearKiraru() {


		this->removeFromParent();
		this->onFinishListener(this);


}
void Kiraru::DelKiraru() {



	auto small_ = ScaleTo::create(0.5, 0.1);
	auto func_ = CallFuncN::create([this](Node* nd) {
		this->removeFromParent();
		this->onFinishListener(this);
	});
	auto seq_ = Sequence::create(small_, func_, NULL);

	this->runAction(seq_);

}
void Kiraru::ShowKiraru() {
	//ランダムに出現する。

	this->SetKiraruStateRnd();

	int x = arc4random() % static_cast<int>(winSize.width - 40) + 20;
	float y = arc4random() % static_cast<int>(90) - 45;

	this->setPosition(x, 700);
	this->setScale(0.2);

	auto big_ = ScaleTo::create(0.2, 5);
	auto small_ = ScaleTo::create(0.1, 1);
	this->runAction(Sequence::create(big_, small_, NULL));

}

void Kiraru::Action1() {
	int d = arc4random() % static_cast<int>(1000);
	int t = arc4random() % static_cast<int>(4) + 1;

}
void Kiraru::Action2() {

}
void Kiraru::Action3() {

}
void Kiraru::Action4() {

}

