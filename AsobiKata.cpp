#include "AsobiKata.h"
#include "SelectScene.h"
#include "TitleScene.h"

USING_NS_CC;

const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);
AsobiKata::AsobiKata() :
		_state(GameState::READY), _world(NULL), _backGround(NULL), _setumeiLabel(NULL), _setumeiLabel2(NULL), _dot(
		NULL), _dot2(
		NULL), _bike(NULL), _gameDeta(NULL), _nomove1(NULL), _nomove2(NULL), _touchlistener(NULL), _contactlistener(
		NULL), _menuA(NULL), _startBtn(NULL), _modoruBtn(NULL), _fstTch(
		NULL), _yubi(NULL) {

}

AsobiKata::~AsobiKata() {

	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_setumeiLabel);
	CC_SAFE_RELEASE_NULL(_setumeiLabel2);
	CC_SAFE_RELEASE_NULL(_yubi);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_dot2);
	CC_SAFE_RELEASE_NULL(_bike);
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_touchlistener);
	CC_SAFE_RELEASE_NULL(_contactlistener);
	CC_SAFE_RELEASE_NULL(_menuA);
	CC_SAFE_RELEASE_NULL(_startBtn);
	CC_SAFE_RELEASE_NULL(_modoruBtn);
	CC_SAFE_RELEASE_NULL(_fstTch);
}
Scene* AsobiKata::createScene() {

	auto scene = Scene::createWithPhysics();

	//�����G���W��
	auto world = scene->getPhysicsWorld();
	Vec2 GA;
	GA.set(GRAVITY_ACCERATION * 15);
	//GA.rotate(Vec2::ZERO,M_PI*0.05f);
	world->setGravity(GA);
	//world->setGravity(Vec2::ZERO);
//#if COCOS2D_DEBUG >0

//
//	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

//#endif

	world->setSpeed(3);

	// 'layer' is an autorelease object
	auto layer = AsobiKata::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
// on "init" you need to initialize your instance
bool AsobiKata::init() {

	if (!GameScene::init()) {
		return false;
	}

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1, 2);

//	this->ChgColorRnd(0.9,1.0);
	this->ChgBeforeColor();
	this->getLayerColor()->removeFromParent();
	_nomove1->addChild(this->getLayerColor(), 1, Vec2::ZERO, this->getLayerColor()->getPosition());

	this->setBackGround(Sprite::create("back5.png"));
	_backGround->setAnchorPoint(Vec2::ZERO);
	_backGround->setPosition(Vec2::ZERO);
//	_backGround->setOpacity(150);
	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	_backGround->setBlendFunc(blend);

	_nomove1->addChild(_backGround, 1, Vec2::ZERO, _backGround->getPosition());

	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 5);

	TTFConfig ttfConfig("HGRPP1.TTC", 80, GlyphCollection::DYNAMIC);

	this->setSetumeiLabel(Label::createWithTTF(ttfConfig, "遊び方の説明"));
	this->_setumeiLabel->setAnchorPoint(Vec2(0.5, 1));
	this->_setumeiLabel->setAlignment(TextHAlignment::CENTER);
	this->_setumeiLabel->setColor(Color3B::WHITE);

	this->_setumeiLabel->setPosition(Vec2(this->ctPt.x, this->ctPt.y * 2 - 70));
	//	this->_lvlLabel->enableOutline(Color4B::RED, 2);
	//	this->_lvlLabel->enableGlow(Color4B::WHITE);
//	this->_setumeiLabel->setPosition(ctPt);
//	this->_setumeiLabel->setOpacity(0);
	_nomove2->addChild(_setumeiLabel, 2, Vec2::ZERO, _setumeiLabel->getPosition());

	TTFConfig ttfConfig2("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);
	this->setSetumeiLabel2(Label::createWithTTF(ttfConfig2, "坂道のコースを自転車で\n駆け下ろう!\n操作方法の説明だよ。"));
	this->_setumeiLabel2->setAnchorPoint(Vec2(0, 1));
	this->_setumeiLabel2->setAlignment(TextHAlignment::LEFT);
	this->_setumeiLabel2->setColor(Color3B::WHITE);
	this->_setumeiLabel2->setOpacity(0);

	this->_setumeiLabel2->setPosition(Vec2(50, this->winSize.height - 200));
	//	this->_lvlLabel->enableOutline(Color4B::RED, 2);
	//	this->_lvlLabel->enableGlow(Color4B::WHITE);
//	this->_setumeiLabel->setPosition(ctPt);
//	this->_setumeiLabel->setOpacity(0);
	_nomove2->addChild(_setumeiLabel2, 2, Vec2::ZERO, _setumeiLabel2->getPosition());

	//指
	this->setYubi(Sprite::create("yubi.png"));
	this->_yubi->setPosition(ctPt);
	this->_yubi->setVisible(false);
//	_nomove2->addChild(_yubi, 3, Vec2::ZERO, _yubi->getPosition());
	this->addChild(_yubi, 8);

	this->setGameDeta(GameDeta::create());

	this->setDot(Dot::create("dot2.png"));
	this->_dot->setPosition(Vec2::ZERO);
	this->addChild(_dot, 1);

	this->setDot2(Dot::create("dot2.png"));
	this->_dot2->setPosition(Vec2::ZERO);
	this->addChild(_dot2, 1);

	this->setBike(Bike::createB());
	this->_bike->setPosition(Vec2::ZERO);
	this->addChild(_bike, 1);

	this->setStartBtn(MenuItemImage::create("start_btn.png", "start_btn_p.png", [](Ref* ref) {

		auto scene=SelectScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

//		UserDefault::getInstance()->setBoolForKey("SAMECOURCE", true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		auto scene=MainScene::createScene();
//		auto transition=TransitionCrossFade::create(0.5,scene);
//		Director::getInstance()->replaceScene(transition);

		}));

	auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
	auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));
	_startBtn->runAction(rep);

	this->setModoruBtn(MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {

		auto scene=TitleScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

//			auto scene=TitleScene::createScene();
//			Director::getInstance()->purgeCachedData();
//			auto transition=TransitionCrossFade::create(0.5,scene);
//			Director::getInstance()->replaceScene(transition);

		}));

	this->setMenuA(Menu::create(_startBtn, _modoruBtn, NULL));
	this->getMenuA()->alignItemsHorizontally();
	this->getMenuA()->alignItemsHorizontallyWithPadding(70);
	this->getMenuA()->setAnchorPoint(Vec2(0.5, 0));
	this->getMenuA()->setPosition(Vec2(ctPt.x, 250));

	this->_nomove1->addChild(_menuA, 2, Vec2::ZERO, _menuA->getPosition());

	this->setState(GameState::READY);
	this->fstFlg = true;

	this->getAD()->AdShow(false, true, false, false, false, false);

	return true;
}

void AsobiKata::SetWinPos(Sprite* sp, Vec2 pt_) {
	//window枠位置での表示

	sp->setPosition(-this->getPosition() + pt_ + Vec2(0, -100));

}
void AsobiKata::Fdi() {
	//説明のフェードイン
	this->_setumeiLabel2->setOpacity(0);
	auto fadeIn_ = FadeIn::create(0.3f);
	this->_setumeiLabel2->runAction(fadeIn_);

}
void AsobiKata::Fdo() {
	//説明のフェードアウト
	auto fadeOut_ = FadeOut::create(0.3f);
	this->_setumeiLabel2->runAction(fadeOut_);

}
bool AsobiKata::sosaJump(float dt) {

//	_point1.set(ctPt);
//	_point2.set(ctPt);
//	bool sFstFlg = false;
//	float stime = 0;	//終了時間
//	float stime_ = 0;

	bool rtn;

	switch (this->sFstFlg) {
	case true: {

		this->_setumeiLabel2->setString("ウイリージャンプ");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 1.5f;
		this->sosaCnt_ = 0;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		rtn = false;
		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			if (this->sosaPt(ctPt + Vec2(-150, 0), 800, dt)) {
				sosaCnt_++;
			}
//			this->_bike->SetTouch(true);
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 1: {
			if (this->sosaPt(ctPt + Vec2(-100, -200), 800, dt)) {
				sosaCnt_++;
			}
//			this->_bike->SetTouch(true);
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 2: {
			if (this->sosaPt(ctPt + Vec2(0, 100), 2000, dt)) {
				sosaCnt_++;
			}
//			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->RtchFlg = true;
//			if (this->_bike->RtchFlg || this->_bike->FtchFlg) {
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
//			}
			break;
		}
		case 3: {
			sosaCnt_++;
			this->_bike->TouchOff();
			this->_yubi->setVisible(false);

			break;
		}
		case 4: {
			stime_ += dt;
			if (stime_ > stime) {
				return true;
			}

			break;
		}
		}

		break;
	}
	}

	return false;
}
bool AsobiKata::sosaWilyUp(float dt) {

	return true;
}
bool AsobiKata::sosaWilyDown(float dt) {
	return true;
}
bool AsobiKata::sosaKoki(float dt) {
	return true;
}
bool AsobiKata::sosaPt(Vec2 pt_, float velo_, float dt) {

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

void AsobiKata::update(float dt) {

	//各ゲームステートで分岐する。

	if (this->courceCnt_ < this->courceCnt) {
		if (_bike->getPosition().x - _dot->SetPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_, false, true);
			const char *str = "onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
			log("%s", str);
			if (courceCnt_ == courceCnt) {
////					_dot->GoalLine();
//					this->_gFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
//					this->addChild(this->_gFlg, 3);
			}

		}

//		}
//		if (this->courceCnt_ <= this->courceCnt) {
		if (_bike->getPosition().x - _dot2->SetPt.x > 250) {
			courceCnt_++;
			this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_, false, true);
			if (courceCnt_ == courceCnt) {
////					_dot2->GoalLine();
//					this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
//					this->addChild(this->_gFlg, 11);
			}
		}
	}

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
	case GameState::AUTOSOSA: {

		this->onAuto(dt);
		break;
	}
	case GameState::WILLY: {

		this->onWilly(dt);
		break;
	}
	case GameState::JUMP: {

		this->onJump(dt);
		break;
	}
	case GameState::SPEED: {

		this->onSpeed(dt);
		break;
	}
	case GameState::WILLYJUMP: {

		this->onWillyJump(dt);
		break;
	}
	case GameState::STOP: {

		this->onStop(dt);
		break;
	}
	}

//	this->getBike()->update(dt);

}

void AsobiKata::onWilly(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		this->Fdi();
		this->_setumeiLabel2->setString("★ウイリー★\n左右にスワイプすると\nウイリーするよ！");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 0.3f;
		this->sosaCnt_ = 0;
		this->sosaCnt2_ = 0;
		this->sosaCnt2 = 1;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			if (this->sosaPt(ctPt + Vec2(-150, 0), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 1: {
			SetWinPos(_yubi, _point2);
			stime_ += dt;
			if (stime_ > stime) {
				sosaCnt_++;
				stime_ = 0;
			}
			break;
		}
		case 2: {
			if (this->sosaPt(ctPt + Vec2(0, 0), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 3: {
			SetWinPos(_yubi, _point2);
			stime_ += dt;
			if (stime_ > stime) {
				this->_bike->TouchOff();
				sosaCnt_++;
				stime_ = 0;
			}
			break;
		}

		case 4: {
			SetWinPos(_yubi, _point2);
			this->sosaCnt2_++;
			if (this->sosaCnt2_ > this->sosaCnt2) {
				this->_bike->TouchOff();
				this->fstFlg = true;
				this->setState(GameState::JUMP);
			} else {
				this->sosaCnt_ = 0;
				SetWinPos(_yubi, ctPt);
				this->_bike->TouchOn(ctPt);
				this->_yubi->setVisible(true);
			}

			break;
		}
		}

		break;
	}
	}

}
void AsobiKata::onJump(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		this->Fdi();
		this->_setumeiLabel2->setString("★ジャンプ★\n下にスワイプした後\n上にスワイプする\nとジャンプするよ！");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 0.5f;
		this->sosaCnt_ = 0;
		this->sosaCnt2_ = 0;
		this->sosaCnt2 = 1;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			if (this->sosaPt(ctPt + Vec2(0, -150), 400, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 1: {
			if (this->sosaPt(ctPt + Vec2(0, 150), 3000, dt)) {
				sosaCnt_++;
			}
			this->_bike->RtchFlg = true;
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 2: {
			SetWinPos(_yubi, _point2);
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
			}
			break;

			break;
		}
		case 3: {
			SetWinPos(_yubi, _point2);
			this->sosaCnt2_++;
			if (this->sosaCnt2_ > this->sosaCnt2) {
				this->fstFlg = true;
				this->_bike->TouchOff();
				this->setState(GameState::WILLYJUMP);
			} else {
				this->sosaCnt_ = 0;
				this->_bike->TouchOff();
				this->_bike->TouchOn(ctPt);
				_point1.set(ctPt);
				_point2.set(ctPt);
				SetWinPos(_yubi, ctPt);
				this->_yubi->setVisible(true);
			}

			break;
		}

		}

		break;
	}
	}
}
void AsobiKata::onSpeed(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		this->Fdi();
		this->_setumeiLabel2->setString("★スピード調整★\n姿勢を低くするほど\nスピードがつくよ！");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 0.5f;
		this->sosaCnt_ = 0;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			SetWinPos(_yubi, _point2);
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;

			}

			break;
		}
		case 1: {
			if (this->sosaPt(ctPt + Vec2(0, -150), 200, dt)) {
				sosaCnt_++;
			}
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 2: {
			stime_ += dt;
			SetWinPos(_yubi, _point2);
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime_ = 0.5f;
			}

			break;
		}
		case 3: {
			if (this->sosaPt(ctPt + Vec2(0, 150), 200, dt)) {
				sosaCnt_++;
			}
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 4: {
			stime_ += dt;
			SetWinPos(_yubi, _point2);
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				sosaCnt2 = 5;
				sosaCnt2_ = 0;
			}

			break;
		}
		case 5: {
			this->Fdi();
			this->_setumeiLabel2->setString("★ダッシュ★\n前輪がついているとき\n右方向に連続スワイプで、\nダッシュゲージがなくなる\nまで加速するよ！");

			if (this->sosaPt(ctPt, 500, dt)) {
				sosaCnt_++;
				stime = 1.0f;

			}
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}

		case 6: {

			if (this->sosaPt(ctPt + Vec2(200, 0), 2500, dt)) {
				sosaCnt_++;
				stime = 1.0f;

			}
			this->_bike->FtchFlg = true;
			this->_bike->RtchFlg = true;
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}

		case 7: {
			stime_ += dt;
			SetWinPos(_yubi, _point2);
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 1.0f;
				stime_ = 0.5f;
			}

			break;
		}

		case 8: {
			SetWinPos(_yubi, _point2);
			this->_bike->TouchOff();
			sosaCnt_++;

			break;
		}
		case 9: {

			SetWinPos(_yubi, _point2);
			_point1.set(ctPt);
			_point2.set(ctPt);
			this->_bike->TouchOn(ctPt);

			sosaCnt2_++;
			if (sosaCnt2_ >= sosaCnt2) {
				sosaCnt_++;

			} else {
				sosaCnt_ = 6;
			}

			break;
		}

		case 10: {
			stime_ += dt;
			if (stime_ > stime) {

				this->fstFlg = true;
				this->setState(GameState::STOP);

			}
			SetWinPos(_yubi, _point2);
			break;
		}

		}

		break;
	}
	}
}
void AsobiKata::onWillyJump(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		this->Fdi();
		this->_setumeiLabel2->setString("★ウイリージャンプ★\n左右にスワイプした後\n上にスワイプすると\nウイリージャンプするよ！");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 2.0f;
		this->sosaCnt_ = 0;
		this->sosaCnt2_ = 0;
		this->sosaCnt2 = 1;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			if (this->sosaPt(ctPt + Vec2(-150, 0), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 1: {
			if (this->sosaPt(ctPt + Vec2(-150, -150), 500, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}
		case 2: {
			if (this->sosaPt(ctPt + Vec2(-150, 200), 3000, dt)) {
				sosaCnt_++;
			}
			this->_bike->RtchFlg = true;
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}
		case 3: {
			if (this->sosaPt(ctPt + Vec2(0, 0), 200, dt)) {
				sosaCnt_++;
				stime = 0.2f;
				stime_ = 0;
			}
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}
		case 4: {
			SetWinPos(_yubi, _point2);
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
			}

			break;
		}

		case 5: {
			SetWinPos(_yubi, _point2);
			this->sosaCnt2_++;
			if (this->sosaCnt2_ > this->sosaCnt2) {
				this->fstFlg = true;
				this->_bike->TouchOff();
				this->_yubi->setVisible(false);
				this->setState(GameState::SPEED);
			} else {
				this->sosaCnt_ = 0;
				this->_bike->TouchOff();
				this->_bike->TouchOn(ctPt);
				_point1.set(ctPt);
				_point2.set(ctPt);
				SetWinPos(_yubi, ctPt);
				this->_yubi->setVisible(true);
			}

			break;
		}
		}
		break;
	}
	}
}
void AsobiKata::onStop(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		this->Fdi();
		this->_setumeiLabel2->setString("★ストップ★\n左下にスワイプした状態で\nブレーキがかかるよ！");

		this->sFstFlg = false;
		_point1.set(ctPt);
		_point2.set(ctPt);
		stime_ = 0;
		stime = 5.0f;
		this->sosaCnt_ = 0;
		this->_bike->TouchOn(ctPt);
		this->_yubi->setVisible(true);
		SetWinPos(_yubi, _point2);

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			if (this->sosaPt(ctPt + Vec2(-150, -150), 200, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);
			break;
		}

		case 1: {
			stime_ += dt;
			if (stime_ > stime) {
				sosaCnt_++;
				stime_ = 0;
				stime = 3;
			}
			SetWinPos(_yubi, _point2);
			break;
		}
		case 2: {
			this->Fdi();
			this->_setumeiLabel2->setString("★ゲームオーバー★\n体が地面に着くと\nゲームオーバーだよ！");
			if (this->sosaPt(ctPt + Vec2(0, 0), 400, dt)) {
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}
		case 3: {

			if (this->sosaPt(ctPt + Vec2(-300, 0), 1200, dt)) {
				this->_bike->TouchOff();
				this->_yubi->setVisible(false);
				sosaCnt_++;
			}
			this->_bike->SetTouch(!_bike->setTouchFlg);
			this->_bike->Swaip(_point1, _point2);
			SetWinPos(_yubi, _point2);

			break;
		}
		case 4: {
			stime_ += dt;
			if (stime_ > stime) {
				sosaCnt_++;
				stime_ = 0;
			}
			SetWinPos(_yubi, _point2);
			break;
		}
		case 5: {
			stime_ += dt;
			this->Fdi();
			this->_setumeiLabel2->setString(
					"各コースの規定時間をクリヤすると\n次のコースに進めるよ\nコースは"
							+ StringUtils::toString((int) this->getGameDeta()->MaxCourceLevel) + "あるぞ！");
			sosaCnt_++;
			SetWinPos(_yubi, _point2);
			stime = 2;
			break;
		}
		case 6: {
			stime_ += dt;
			if (stime_ > stime) {
				sosaCnt_++;
				stime_ = 0;
				stime = 2;
			}
			SetWinPos(_yubi, _point2);
			break;
		}

		case 7: {
			stime_ += dt;
			this->Fdi();
			this->_setumeiLabel2->setString(
					"★獲得ｺｲﾝとﾗﾝｷﾝｸﾞ★\n好記録をだすとｺｲﾝがもらえるぞ！\nｺｲﾝを多く集めると、\nﾀﾞｯｼｭｹﾞｰｼﾞのﾒﾓﾘが増えるぞ！\nまた獲得したｺｲﾝの数でﾗﾝｷﾝｸﾞするよ!");
			sosaCnt_++;
			SetWinPos(_yubi, _point2);
			stime = 6;
			break;
		}
		case 8: {
			stime_ += dt;
			if (stime_ > stime) {
				sosaCnt_++;
				stime_ = 0;
				stime = 2;
			}
			SetWinPos(_yubi, _point2);
			break;
		}

		case 9: {
			stime_ += dt;
			this->Fdi();
			this->_setumeiLabel2->setString("準備はいいかな？\nはじめるでスタートだよ！");
			sosaCnt_++;
			SetWinPos(_yubi, _point2);
			stime = 2;
			break;
		}
		}
		break;
	}

	}
}
void AsobiKata::onAuto(float dt) {
	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;
		break;
	}
	case false: {

		if (this->courceCnt_ < this->courceCnt) {
			if (_bike->getPosition().x - _dot->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta(_dot, this->CourceLevel, courceCnt_);
				const char *str =
						"onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
				log("%s", str);
				if (courceCnt_ == courceCnt) {
////					_dot->GoalLine();
//					this->_gFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
//					this->addChild(this->_gFlg, 3);
				}

			}

//		}
//		if (this->courceCnt_ <= this->courceCnt) {
			if (_bike->getPosition().x - _dot2->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta(_dot2, this->CourceLevel, courceCnt_);
				if (courceCnt_ == courceCnt) {
////					_dot2->GoalLine();
//					this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
//					this->addChild(this->_gFlg, 11);
				}
			}
		}

		if (this->sosaJump(dt)) {

			this->fstFlg = true;
			this->sFstFlg = true;
			this->setState(GameState::AUTOSOSA);

		}

		break;
	}
	}
}
void AsobiKata::onReady(float dt) {

	switch (this->fstFlg) {
	case true: {

		const char *str = "AsobiKata::GameState::onReady";
		log("%s", str);
//		this->_bike->fstFlg = true;
//		this->_bike->setBikeState(Bike::BikeState::READY);
		_bike->scheduleUpdate();
		_bike->updateFlg = true;

		this->_bike->FadeInBike(1.0f, 0.5f);
		this->_dot->FadeIn_Dot(1.0f, 0.5f);
		this->_dot2->FadeIn_Dot(1.0f, 0.5f);

		this->fstFlg = false;
		this->sosaCnt_ = 0;
//		this->_setumeiLabel2->setString("画面をスワイプして\n自転車の操作ができるよ！");

		stime_ = 0;
		stime = 1.5f;

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			if (stime_ > stime) {
				this->_bike->fstFlg = true;
				this->_bike->setBikeState(Bike::BikeState::NOML);

				sosaCnt_++;
				stime_ = 0;
				stime = 1;
			}
			break;
		}
		case 1: {
			stime_ += dt;
			this->_bike->chPt -= Vec2((float) 400 * dt / stime, 0);

			if (stime_ > stime) {
				this->Fdi();
				this->_setumeiLabel2->setString("画面をスワイプして\n自転車の操作ができるよ！");

				sosaCnt_++;
				stime_ = 0;
				stime = 1;
			}
			break;
		}
		case 2: {
			stime_ += dt;
			if (stime_ > stime) {

				this->_bike->TouchOff();
				this->_yubi->setVisible(false);
				this->fstFlg = true;
				this->setState(GameState::WILLY);
			}
			break;
		}
		}
		break;
	}

	}
}
void AsobiKata::onPlay(float dt) {

	switch (this->fstFlg) {
	case true: {

		this->fstFlg = false;

		break;
	}
	case false: {

		if (this->courceCnt_ < this->courceCnt) {
			if (_bike->getPosition().x - _dot->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta(_dot, this->CourceLevel, courceCnt_);
				const char *str =
						"onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
				log("%s", str);
				if (courceCnt_ == courceCnt) {
////					_dot->GoalLine();
//					this->_gFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
//					this->addChild(this->_gFlg, 3);
				}

			}

//		}
//		if (this->courceCnt_ <= this->courceCnt) {
			if (_bike->getPosition().x - _dot2->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta(_dot2, this->CourceLevel, courceCnt_);
				if (courceCnt_ == courceCnt) {
////					_dot2->GoalLine();
//					this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
//					this->addChild(this->_gFlg, 11);
				}

			}
		}

//		if (_bike->getPosition().x - _dot->SetPt.x > 200) {
//			_dot->ResetDot();
//			_dot->SetPt.set(_dot2->SetPt);
//
//			int rndA = arc4random() % static_cast<int>(5) + 1;
//			int rndB = arc4random() % static_cast<int>(300) + 100;
//			int rndC = arc4random() % static_cast<int>(400) + 50;
//			_dot->rndMade2();
//			//			_dot->rndMade(rndA, rndB, rndC, 10);
//
//		}
//		if (_bike->getPosition().x - _dot2->SetPt.x > 200) {
//			_dot2->ResetDot();
//			_dot2->SetPt.set(_dot->SetPt);
//			int rndA = arc4random() % static_cast<int>(5) + 1;
//			int rndB = arc4random() % static_cast<int>(300) + 100;
//			int rndC = arc4random() % static_cast<int>(400) + 50;
////					_dot->rndMade2();
//			_dot->rndMade(rndA, rndB, rndC, 10);
//
//		}

		break;
	}
	}

}
void AsobiKata::SetTouchListener() {

//jaraのタッチイベントをセットする。
	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(_fstTch==NULL ) {

			this->setFstTch(touch);
			_point1.set(touch->getLocation());
			_point2.set(touch->getLocation());

			this->_bike->TouchOn(touch->getLocation());

			return true;

		} else {
			return false;
		}

	};

	_touchlistener->onTouchMoved = [this](Touch* touch,Event* event) {

		Vec2 delta=touch->getDelta();

		_point2.set(touch->getLocation());

		this->_bike->Swaip(_point1,_point2);

//		if((touch->getLocation()-Vec2(0,500)-_dot->SetPt).length()>5) {
//			_dot->AddDot(touch->getLocation()-Vec2(0,500));
//		}

			delta.set(_point2-_point1);

		};

	_touchlistener->onTouchEnded = [this](Touch* touch,Event* event) {
		_point1.set(Vec2::ZERO);
		_point2.set(Vec2::ZERO);
//		_dot->SetShape();
			this->_bike->TouchOff();
			this->setFstTch(NULL);

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,
			this);
	const char *str = "setTouchListener";
	log("%s", str);
}
void AsobiKata::SetContactListener() {

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

void AsobiKata::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("runk.mp3", true);
	}

	this->getGameDeta()->MadeCourceAsobikata(_dot, 0);				//コースナンバーからコースを作成
	this->courceCnt = this->getGameDeta()->GetSelectCourceLength();

	this->addChild(_dot, 2);
	this->addChild(_dot2, 2);

	courceCnt_ = 1;
	this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_, false, false);
	courceCnt_++;
	this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_, false, false);

	_dot->FadeOut_Dot(0, 0);
	_dot2->FadeOut_Dot(0, 0);

	this->setBike(Bike::createB());
//	_bike->setPosition(this->_courceMader->PlayerPoss);
	_bike->lifePoint = 1;
	this->addChild(_bike, 10);
	this->addChild(_bike->getChaser(), 11);
	this->addChild(_bike->getFWheel(), 11);
	this->addChild(_bike->getRWheel(), 11);
	_bike->SetJointB(this->getScene()->getPhysicsWorld());

	this->addChild(_bike->getFWheelA());
	this->addChild(_bike->getRWheelA());

	const char *str4 = "MainMadeCource_lvl0_2";
	log("%s", str4);

//	this->addChild(this->_bike->getPointDbg());
//	this->_bike->getPointDbg()->setGlobalZOrder(50);
//画面フォロー
	if (_bike) {
		_bike->chPt.set(180, -150);
		_bike->chPt += Vec2(400, 0);
		_bike->getChaser()->setPosition(_bike->chPt + _bike->getPosition());
		this->runAction(Follow::create(_bike->getChaser()));
//		this->_courceMader->setBall(_bike);
	}

//	auto dlay_ = DelayTime::create(1.0f);
//	auto func_ = CallFuncN::create([this](Node* nd) {
	this->SetContactListener();
//	this->SetTouchListener();

//			this->_dot->setVisible(true);
//			this->_dot2->setVisible(true);
	this->scheduleUpdate();

//		});
//	auto seq_ = Sequence::create(dlay_, func_, NULL);
//	this->runAction(seq_);

}
void AsobiKata::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		auto scene = TitleScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);
		this->getAD()->AdShow(false, false, false, true, false, false);

	}

}

