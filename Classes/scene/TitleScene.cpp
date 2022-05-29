#include "TitleScene.h"
#include "MainScene.h"
#include "TestScene.h"

#include "SelectScene.h"
#include "SimpleAudioEngine.h"

#include "platform/android/jni/JniHelper.h"

#include "AsobiKata.h"
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

USING_NS_CC;
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);
const char* BGM_KEY = "bgmkey";
//const char* BEST_TIME="besttime";
//const char* AD_VIEW_ID="adViewId";

MenuItemImage* musicOnBtn;
MenuItemImage* musicOffBtn;

Scene* TitleScene::createScene() {


//	auto scene = Scene::create();
//
//	auto layer = TitleScene::create();
//
//	scene->addChild(layer);
//
//	// return the scene
//	return scene;

//
//

	auto scene = Scene::createWithPhysics();
	//�����G���W��
	auto world = scene->getPhysicsWorld();
	Vec2 GA;
	GA.set(GRAVITY_ACCERATION * 15);
	//GA.rotate(Vec2::ZERO,M_PI*0.05f);
	world->setGravity(GA);
	//world->setGravity(Vec2::ZERO);
//#if COCOS2D_DEBUG >0
//	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
//#endif
	world->setSpeed(3);
	// 'layer' is an autorelease object
	auto layer = TitleScene::create();
	// add layer as a child to scene
	scene->addChild(layer);
	// return the scene
	return scene;

}
TitleScene::TitleScene() :
		_gameDeta(NULL), _bigWheel(NULL), _backGround(NULL), _title(NULL), _waku(NULL), _wakuBody(NULL), _dot(
		NULL), _dot2(NULL), _dot3(NULL), _bike(NULL), _nomove1(NULL), _nomove2(NULL), _touchlistener(
		NULL), _contactlistener(NULL), _state(GameState::READY) {

}

TitleScene::~TitleScene() {
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_bigWheel);
	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_title);
	CC_SAFE_RELEASE_NULL(_waku);
	CC_SAFE_RELEASE_NULL(_wakuBody);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_dot2);
	CC_SAFE_RELEASE_NULL(_dot3);
	CC_SAFE_RELEASE_NULL(_bike);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_touchlistener);
	CC_SAFE_RELEASE_NULL(_contactlistener);

}
// on "init" you need to initialize your instance
bool TitleScene::init() {

	if (!GameScene::init()) {
		return false;
	}

	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1, 1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 4);

//	this->ChgColorRnd(0.9,1.0);
	this->ChgBeforeColor();
	this->getLayerColor()->removeFromParent();
	_nomove1->addChild(this->getLayerColor(), 1, Vec2::ZERO, this->getLayerColor()->getPosition());

	this->setBackGround(Sprite::create("back5.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
//	_backGround->setOpacity(150);
	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	_backGround->setBlendFunc(blend);
	_nomove1->addChild(_backGround, 2, Vec2::ZERO, _backGround->getPosition());

	this->setTitle(Sprite::create("title5.png"));
	_title->setPosition(Vec2(winSize.width / 2.0, winSize.height - 280));
	_title->setScale(1.0);
	_nomove2->addChild(_title, 4, Vec2::ZERO, _title->getPosition());

//	_nomove1->addChild(_bigWheel, 2, Vec2::ZERO, _bigWheel->getPosition());
	this->setGameDeta(GameDeta::create());

	//start
	MenuItemImage * startp = MenuItemImage::create("start_btn.png", "start_btn_p.png", [this](Ref* ref) {
		this->_gameDeta->SetDebug(false);
		auto scene=SelectScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

//		UserDefault::getInstance()->setBoolForKey("SAMECOURCE", true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		auto scene=MainScene::createScene();
//		auto transition=TransitionCrossFade::create(0.5,scene);
//		Director::getInstance()->replaceScene(transition);

		});

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));
	startp->runAction(rep);

	auto howtp = MenuItemImage::create("howto_btn.png", "howto_btn_p.png", [this](Ref* ref) {

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
		auto scene=AsobiKata::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

	});

	auto menu = Menu::create(startp, howtp, NULL);
	menu->alignItemsVerticallyWithPadding(40);
	menu->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2 - 180));
	_nomove2->addChild(menu, 4, Vec2::ZERO, menu->getPosition());
//	this->addChild(menu, 4);

	auto rankingp = MenuItemImage::create("ranking_btn.png", "ranking_btn_p.png", [this](Ref* ref) {

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
		auto scene=RankScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		this->sendRankParkScore(UserDefault::getInstance()->getIntegerForKey("bestScore",0));
//		this->openRankPark();

		});

	auto menu5 = Menu::create(rankingp, NULL);
	menu5->alignItemsVerticallyWithPadding(20);
	menu5->setPosition(Vec2(winSize.width / 2.0, 250));
	_nomove2->addChild(menu5, 4, Vec2::ZERO, menu5->getPosition());
//	this->addChild(menu5, 4);

	musicOnBtn =
			MenuItemImage::create("music_btn.png", "music_not_p_btn.png",
					[](Ref* ref) {

						UserDefault::getInstance()->setBoolForKey(BGM_KEY,!UserDefault::getInstance()->getBoolForKey(BGM_KEY));
						CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
						musicOnBtn->setVisible(false);
						musicOffBtn->setVisible(true);
					});
	;
	auto menu2 = Menu::create(musicOnBtn, NULL);
	menu2->alignItemsHorizontallyWithPadding(20);
	menu2->setPosition(Vec2(150, 250));
	_nomove2->addChild(menu2, 4, Vec2::ZERO, menu2->getPosition());
//	this->addChild(menu2, 4);

	musicOffBtn =
			MenuItemImage::create("music_not_btn.png", "music_p_btn.png",
					[](Ref* ref) {
						UserDefault::getInstance()->setBoolForKey(BGM_KEY,!UserDefault::getInstance()->getBoolForKey(BGM_KEY));
						//CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
						//	"bgm.mp3", true);

						musicOnBtn->setVisible(true);
						musicOffBtn->setVisible(false);
					});

	auto menu3 = Menu::create(musicOffBtn, NULL);
	menu3->alignItemsHorizontallyWithPadding(20);
	menu3->setPosition(menu2->getPosition());
	_nomove2->addChild(menu3, 4, Vec2::ZERO, menu3->getPosition());
//	this->addChild(menu3, 4);

	if (UserDefault::getInstance()->getBoolForKey(BGM_KEY, true)) {
		musicOffBtn->setVisible(false);
		musicOnBtn->setVisible(true);
	} else {
		musicOffBtn->setVisible(true);
		musicOnBtn->setVisible(false);
	}

	auto tweetp = MenuItemImage::create("mail_btn.png", "mail_p_btn.png", [this](Ref* ref) {
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

//			this->_gameDeta->SetDebug(true);
//			auto scene=SelectScene::createScene();
//			auto transition=TransitionCrossFade::create(0.5,scene);
//			Director::getInstance()->replaceScene(transition);

			this->tweet();//一時的に消し

//#endif

		});

	auto menu4 = Menu::create(tweetp, NULL);
	menu4->alignItemsHorizontallyWithPadding(20);
	menu4->setPosition(Vec2(winSize.width - 150, 250));
	_nomove2->addChild(menu4, 4, Vec2::ZERO, menu4->getPosition());
//	this->addChild(menu4, 4);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(TitleScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->getAD()->AdShow(true, true, false, false, false, false);

	this->setState(GameState::READY);

	return true;
}
void TitleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::sharedDirector()->end();
	}
}

void TitleScene::openRankPark() {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, OPENRNK, "()V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}
void TitleScene::sendRankParkScore(int value) {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, SENDSCR, "(I)V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}
void TitleScene::tweet() {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, TWEET, "(I)V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		int value = this->getGameDeta()->getTotlCoin();
		t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}

}
bool TitleScene::sosaPt(Vec2 pt_, float velo_, float dt) {

	//_point2をptに速度veloで移動させる。_　時間dt_

	if (pt_ == _point2) {
		return true;
	}

	Vec2 dpt_;
	dpt_.set(pt_ - _point2);

	if (dpt_.length() < velo_ * dt) {
		_point2.set(pt_);
		return true;
	} else {
		dpt_.normalize();
		dpt_ *= (velo_ * dt);
		_point2 += dpt_;
		return false;
	}

}
void TitleScene::update(float dt) {

	//各ゲームステートで分岐する。
//
//	if (this->courceCnt_ < this->courceCnt) {
//		if (_bike->getPosition().x - _dot->SetPt.x > 250) {
//			courceCnt_++;
//			this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_,false,false);
//			const char *str = "onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
//			log("%s", str);
//			if (courceCnt_ == courceCnt) {
//			}
//
//		}
//		if (_bike->getPosition().x - _dot2->SetPt.x > 250) {
//			courceCnt_++;
//			this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_,false,false);
//			if (courceCnt_ == courceCnt) {
//			}
//		}
//	}

	switch (this->getState()) {

	case GameState::READY: {
		//string型
//		const char *str = "AsobiKata::GameState::READY";
//		log("%s", str);
		this->onReady(dt);
		break;
	}
	case GameState::PLAY: {
//		const char *str2 = "AsobiKata::GameState::PLAY";
//		log("%s", str2);
		this->onPlay(dt);
		break;
	}
	case GameState::STOP: {
//		const char *str2 = "AsobiKata::GameState::PLAY";
//		log("%s", str2);
		this->onStop(dt);
		break;
	}
	}

//	this->getBike()->update(dt);

}
void TitleScene::onReady(float dt) {

	switch (this->fstFlg) {
	case true: {
		_bigWheel->setPosition(wheelFstPt - this->getPosition());
		_bigWheel->setRotation(this->_bike->getFWheel()->getRotation());
		const char *str = "AsobiKata::GameState::onReady";
		log("%s", str);

		this->_bike->SetPositionBike(Vec2::ZERO);
//		this->_bike->fstFlg = true;
//		this->_bike->setBikeState(Bike::BikeState::READY);
		_bike->scheduleUpdate();
		_bike->updateFlg = true;

		this->fstFlg = false;
		this->sosaCnt_ = 0;
//		this->_setumeiLabel2->setString("画面をスワイプして\n自転車の操作ができるよ！");
		stime_ = 0;
		stime = 0.1f;

		break;
	}
	case false: {
		_bigWheel->setPosition(wheelFstPt - this->getPosition());
		_bigWheel->setRotation(this->_bike->getFWheel()->getRotation());
		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			if (stime_ > stime) {
				this->_bike->fstFlg = true;
				this->_bike->setBikeState(Bike::BikeState::NOML);

				sosaCnt_++;
				stime_ = 0;
				stime = 0.1;
			}
			break;
		}
		case 1: {
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime = 0.1;
			}
			break;
		}
		case 2: {
			stime_ += dt;
			this->_bike->chPt -= Vec2((float) 400 * dt / stime, 0);

			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime = 1;
			}
			break;
		}
		case 3: {
			stime_ += dt;
			if (stime_ > stime) {

				this->_bike->TouchOff();
				this->fstFlg = true;
				this->setState(GameState::PLAY);
			}
			break;
		}
		}
		break;
	}

	}
}
void TitleScene::onPlay(float dt) {

	if (this->courceCnt_ < this->courceCnt) {
		if (_bike->getPosition().x - _dot->lstPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_, false, false);

//			this->_dot->ShowCourceName(_dot->dspCnt);
			this->_waku->setPosition(_dot2->_dotG.at(0)->getPosition());
//			const char *str = "onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
//			log("%s", str);
			if (courceCnt_ == courceCnt) {
			}

		}
		if (_bike->getPosition().x - _dot2->lstPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_, false, false);
//			this->_dot2->ShowCourceName(_dot2->dspCnt);
			this->_waku->setPosition(_dot3->_dotG.at(0)->getPosition());
			if (courceCnt_ == courceCnt) {
			}
		}
		if (_bike->getPosition().x - _dot3->lstPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot3, this->CourceLevel, courceCnt_, false, false);
//			this->_dot3->ShowCourceName(_dot3->dspCnt);
			this->_waku->setPosition(_dot->_dotG.at(0)->getPosition());
			if (courceCnt_ == courceCnt) {
			}
		}

	}

	switch (this->fstFlg) {
	case true: {

		_bigWheel->ChaseA(this->_bike->getFWheel()->getPosition(), (float) 500, dt);
		_bigWheel->setRotation(this->_bike->getFWheel()->getRotation());

		auto scale_ = ScaleTo::create(1.0f, 0.397);
		auto delay_ = DelayTime::create(0.5f);
		auto fade_ = FadeOut::create(0.5f);
		auto seq_ = Sequence::create(scale_, delay_->clone(), fade_, NULL);
		_bigWheel->runAction(seq_);

		this->_bike->FadeInBike(1.0f, 0.5f);
		this->_dot->FadeIn_Dot(1.0f, 0.5f);
		this->_dot2->FadeIn_Dot(1.0f, 0.5f);
		this->_dot3->FadeIn_Dot(1.0f, 0.5f);

		this->fstFlg = false;
		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 2.0f;
		this->sosaCnt_ = 0;
		this->sosaCnt2_ = 0;
		this->sosaCnt2 = 5;
		this->_bike->TouchOn(ctPt);

		break;
	}
	case false: {

		if (_bike->deadFlg_) {

			this->stopAllActions();
//			this->runAction(Follow::create(_bike->getFWheel()));
			_bigWheel->setPosition(this->_bike->getFWheel()->getPosition());
			_bigWheel->setOpacity(255);
			_bike->getFWheel()->setOpacity(0);
			this->fstFlg = true;
			this->setState(GameState::STOP);

		}

		_bigWheel->ChaseA(this->_bike->getFWheel()->getPosition(), (float) 500, dt);
		_bigWheel->setRotation(this->_bike->getFWheel()->getRotation());
		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime = 1;
			}

			break;
		}

		case 1: {
			if (this->sosaPt(ctPt + Vec2(-150, 0), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			break;
		}
		case 2: {
			if (this->sosaPt(ctPt + Vec2(-150, -150), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			break;
		}
		case 3: {
			if (this->sosaPt(ctPt + Vec2(-150, 200), 3000, dt)) {
				sosaCnt_++;
			}
			this->_bike->RtchFlg = true;
			this->_bike->Swaip(_point1, _point2);

			break;
		}
		case 4: {
			if (this->sosaPt(ctPt + Vec2(0, 0), 200, dt)) {
				sosaCnt_++;
				stime = 0.2f;
				stime_ = 0;
			}
			this->_bike->Swaip(_point1, _point2);

			break;
		}
		case 5: {

			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
			}

			break;
		}

		case 6: {
			this->sosaCnt2_++;
			if (this->sosaCnt2_ > this->sosaCnt2) {

				this->_bike->TouchOff();
				this->fstFlg = true;
				this->setState(GameState::STOP);
				_bigWheel->setPosition(this->_bike->getFWheel()->getPosition());
				_bigWheel->setOpacity(255);
				_bike->getFWheel()->setOpacity(0);
				this->stopAllActions();
				this->_bike->FadeOutBike(0.1f, 0.5f);
//				this->runAction(Follow::create(_bike->getFWheel()));

//				this->stopAllActions();
//				this->SetCource();
//				this->setState(GameState::READY);
			} else {
				this->sosaCnt_ = 0;
				this->_bike->TouchOff();
				this->_bike->TouchOn(ctPt);
				_point1.set(ctPt);
				_point2.set(ctPt);
			}

			break;
		}
		}
		break;
	}
	}

}

void TitleScene::onStop(float dt) {

	if (this->courceCnt_ < this->courceCnt) {
		if (_bike->getPosition().x - _dot->SetPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_, false, false);
			this->_waku->setPosition(_dot2->_dotG.at(0)->getPosition());
//			const char *str = "onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
//			log("%s", str);
			if (courceCnt_ == courceCnt) {
			}

		}
		if (_bike->getPosition().x - _dot2->SetPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_, false, false);
			this->_waku->setPosition(_dot3->_dotG.at(0)->getPosition());
			if (courceCnt_ == courceCnt) {
			}
		}
		if (_bike->getPosition().x - _dot3->SetPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot3, this->CourceLevel, courceCnt_, false, false);
			this->_waku->setPosition(_dot->_dotG.at(0)->getPosition());
			if (courceCnt_ == courceCnt) {
			}
		}

	}

	switch (this->fstFlg) {
	case true: {
//		_bigWheel->setPosition(this->_bike->getFWheel()->getPosition());
		_bigWheel->ChaseA(wheelFstPt - this->getPosition(), (float) 500, dt);
		auto rot_ = RepeatForever::create(RotateBy::create(3, 360));
		auto scale_ = ScaleTo::create(0.5f, 1);
		auto delay_ = DelayTime::create(2.0f);
		auto fade_ = FadeIn::create(0.5f);
		auto seq_ = Sequence::create(rot_, delay_->clone(), scale_, NULL);
		_bigWheel->runAction(seq_);

//		this->stopAllActions();
//		this->runAction(Follow::create(_bike->getFWheel()));

		this->_bike->FadeOutBike(1.0f, 0.5f);
		//フェードアウト
		this->_dot->FadeOut_Dot(1.0f, 0.5f);
		this->_dot2->FadeOut_Dot(1.0f, 0.5f);
		this->_dot3->FadeOut_Dot(1.0f, 0.5f);
		this->fstFlg = false;

		stime_ = 0;
		stime = 4.0f;
		this->sosaCnt_ = 0;
		this->sosaCnt2_ = 0;
		this->sosaCnt2 = 10;

		break;
	}
	case false: {

		_bigWheel->ChaseA(wheelFstPt - this->getPosition(), (float) 500, dt);

		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime = 1;
			}

			break;
		}

		case 1: {
			auto scene = TitleScene::createScene();
			auto transition = TransitionCrossFade::create(0.5, scene);
			Director::getInstance()->replaceScene(scene);
			sosaCnt_++;
			break;
		}
		case 2: {
			this->unscheduleUpdate();
			break;
		}
		}
		break;
	}
	}

}

void TitleScene::SetCource() {

	auto scale_ = ScaleTo::create(0.5f, 1.0f);
	auto move_ = MoveTo::create(0.5f, wheelFstPt);
	auto rot_ = RepeatForever::create(RotateBy::create(3, 360));

	auto seq_ = Sequence::create(Spawn::create(scale_, move_, NULL), rot_, NULL);
	_bigWheel->runAction(rot_);

	this->_bike->SetPositionBike(Vec2::ZERO);
	this->_bike->setBikeState(Bike::BikeState::READY);
//	this->_dot->setPosition(Vec2::ZERO);
//	this->_dot2->setPosition(Vec2::ZERO);

	const char *str1 = "TitleScene::SetCource()_1";
	log("%s", str1);

	this->CourceLevel = this->getGameDeta()->GetSelectCourceNo();

//	this->getGameDeta()->MadeCourceFromCourceNo(_dot, this->getGameDeta()->GetSelectCourceNo());
	this->getGameDeta()->MadeCourceTitle(_dot, 0);				//コースナンバーからコースを作成
	this->courceCnt = this->getGameDeta()->GetSelectCourceLength();

	const char *str2 = "TitleScene::SetCource()_2";
	log("%s", str2);

	courceCnt_ = 1;
	this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_, false, false);
//	this->_dot->ShowCourceName(_dot->dspCnt);
	courceCnt_++;
	this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_, false, false);
//	this->_dot2->ShowCourceName(_dot2->dspCnt);
	courceCnt_++;
	this->_gameDeta->ReadDeta2(_dot3, this->CourceLevel, courceCnt_, false, false);
//	this->_dot3->ShowCourceName(_dot3->dspCnt);

	//フェードアウト
	this->_dot->FadeOut_Dot(0, 0);
	this->_dot2->FadeOut_Dot(0, 0);
	this->_dot3->FadeOut_Dot(0, 0);

	//見えない壁を作成
	this->setWaku(Node::create());
	Vec2 kabe[] = { Vec2(0, 0), Vec2(0, 500) };
	this->setWakuBody(PhysicsBody::createEdgeChain(kabe, 2));
	this->_waku->setPhysicsBody(this->_wakuBody);
	this->_waku->setPosition(_dot->_dotG.at(0)->getPosition());
	this->addChild(this->_waku);

//	this->addChild(this->_bike->getPointDbg());
//	this->_bike->getPointDbg()->setGlobalZOrder(50);
//画面フォロー
	if (_bike) {

		_bike->chPt.set(180, -150);
		_bike->chPt += Vec2(400, 0);
		_bike->getChaser()->setPosition(_bike->chPt + _bike->getPosition());
		_bike->SetOpacityBike(0);
		this->runAction(Follow::create(_bike->getChaser()));
		_bigWheel->setPosition(wheelFstPt - this->getPosition());

//		this->_courceMader->setBall(_bike);
	}

//	auto dlay_ = DelayTime::create(1.0f);
//	auto func_ = CallFuncN::create([this](Node* nd) {
	this->SetContactListener();
//	this->SetTouchListener();

//			this->_dot->setVisible(true);
//			this->_dot2->setVisible(true);
	this->scheduleUpdate();
}

void TitleScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
	}

	this->setBigWheel(Sprite2::create("titlewheel.png"));
	wheelFstPt.set(Vec2(winSize.width / 2.0, winSize.height - 530));
	_bigWheel->setPosition(wheelFstPt);
	this->addChild(_bigWheel, 4);

	this->setDot(Dot::create("dot2.png"));
	this->setDot2(Dot::create("dot2.png"));
	this->setDot3(Dot::create("dot2.png"));
	this->addChild(_dot, 2);
	this->addChild(_dot2, 2);
	this->addChild(_dot3, 2);

	//fade
	const char *str1 = "onEnterTransitionDidFinish()";
	log("%s", str1);

	this->setBike(Bike::createB());
	_bike->lifePoint = 1;
	this->addChild(_bike, 3);
	this->addChild(_bike->getChaser(), 3);
	this->addChild(_bike->getFWheel(), 3);
	this->addChild(_bike->getRWheel(), 3);
	_bike->SetJointB(this->getScene()->getPhysicsWorld());

	this->addChild(_bike->getFWheelA());
	this->addChild(_bike->getRWheelA());

	this->SetCource();

//		});
//	auto seq_ = Sequence::create(dlay_, func_, NULL);
//	this->runAction(seq_);

}
void TitleScene::SetContactListener() {

//接触感知
	this->setContactListenner(EventListenerPhysicsContact::create());
	_contactlistener->onContactBegin = [this](PhysicsContact& contact) {

		switch(contact.getShapeA()->getBody()->getTag()) {
			//ゲートをくぐったとき
			case 20: {

				const char *str = "setContactListenner_20";
				log("%s", str);

//				Sprite* sp=dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode());
//				Item* itm=dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->fstPt.set(dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode())->getPosition());
//				itm->fstTch=true;
				this->_bike->goalFlg_=true;

				break;
			}
			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->RtchPt.set(contact.getContactData()->points[1]);
				_bike->RnmlPt.set(contact.getContactData()->normal);
				_bike->RtchFlg=true;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->FtchPt.set(contact.getContactData()->points[1]);
				_bike->FnmlPt.set(contact.getContactData()->normal);
				_bike->FtchFlg=true;
				break;
			}
			//ライダー本体
			case 10: {
				_bike->setTchNode(contact.getShapeB()->getBody()->getNode());
				_bike->ntchPt_.set(contact.getShapeB()->getBody()->getNode()->getPosition());
				_bike->deadFlg_=true;

				break;
			}

		}

		switch(contact.getShapeB()->getBody()->getTag()) {

			//ゴールした時
			case 20: {

				const char *str = "setContactListenner_20";
				log("%s", str);

//				Sprite* sp=dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode());
//				Item* itm=dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->fstPt.set(dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode())->getPosition());
//				itm->fstTch=true;
				this->_bike->goalFlg_=true;

				break;
			}

			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);

				_bike->RtchPt.set(contact.getContactData()->points[1]);
				_bike->RnmlPt.set(-contact.getContactData()->normal);
				_bike->RtchFlg=true;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->FtchPt.set(contact.getContactData()->points[1]);
				_bike->FnmlPt.set(-contact.getContactData()->normal);
				_bike->FtchFlg=true;
				break;
			}
			//ライダー本体
			case 10: {
				_bike->setTchNode(contact.getShapeA()->getBody()->getNode());
				_bike->ntchPt_.set(contact.getShapeA()->getBody()->getNode()->getPosition());
				_bike->deadFlg_=true;

				break;
			}

		}

		return true;

	};

	_contactlistener->onContactPostSolve =
			[this](PhysicsContact& contact, const PhysicsContactPostSolve& solve) {
				switch(contact.getShapeA()->getBody()->getTag()) {
					//コース
					case 1: {

						break;
					}
					//膨らんだボール
					case 11: {

						break;
					}
					//ボール本体
					case 10: {

						break;
					}
					//ダンゴ虫
					case 7: {

						break;
					}
					case 8: {
						//Dango* dg=dynamic_cast<Dango *>(contact.getShapeA()->getBody()->getNode()->getParent());
						//dg->moveFlg=false;
						break;
					}
					case 5: {

						break;
					}
				}

				switch(contact.getShapeB()->getBody()->getTag()) {

					//コース
					case 1: {

						break;
					}

					//膨らんだボール
					case 11: {

						break;
					}
					//ボール本体
					case 10: {

						break;
					}
					//ダンゴ虫
					case 7: {

						break;
					}
					case 8: {
						//	Dango* dg=dynamic_cast<Dango *>(contact.getShapeB()->getBody()->getNode()->getParent());
						//	dg->moveFlg=false;
						break;
					}
					case 5: {

						break;
					}
				}
			};
	_contactlistener->onContactSeperate = [this](PhysicsContact& contact) {
		switch(contact.getShapeA()->getBody()->getTag()) {
			//コース
			//ゲートをくぐったとき
			case 20: {
//				Sprite* sp=dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode());
//				Item* itm=dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->lstPt.set(dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode())->getPosition());
//				itm->endTch=true;
				break;
			}

			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->RtchPt.set(Vec2::ZERO);
				_bike->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->FtchPt.set(Vec2::ZERO);
				_bike->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
				if(contact.getShapeB()->getBody()->getNode()==_bike->getTchNode()) {
					_bike->setTchNode(NULL);
				}

				break;
			}

		}

		switch (contact.getShapeB()->getBody()->getTag()) {

			//コース
			//ゲートをくぐったとき
			case 20: {
//				Sprite* sp = dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode());
//				Item* itm = dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->lstPt.set(dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode())->getPosition());
//				itm->endTch = true;
				break;
			}

			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->RtchPt.set(Vec2::ZERO);
				_bike->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_bike->FtchPt.set(Vec2::ZERO);
				_bike->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
				if (contact.getShapeA()->getBody()->getNode() == _bike->getTchNode()) {
					_bike->setTchNode(NULL);
				}
				break;
			}

		}

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactlistener,
			this);

}

