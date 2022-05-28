#include "MainScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "IMobileCocos2dxModule.h"
#include "ParticleSystemPool.h"
#include "Bike.h"
#include "cmath"
#include "Item.h"
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

USING_NS_CC;

//�d�̓x�N�g��
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

int _sec = 0;

const int zyaraCatg = 1 << 0;
const int handCatg = 1 << 1;
const int pointCatg = 1 << 2;
const int dmgCatg = 1 << 3;
const int nikuCatg = 1 << 4;
const int kabeCatg = 1 << 5;

int pcnt = 0;

MainScene::MainScene() :
		_coinLabel(NULL), _coin(NULL), _gaziA(NULL), _gaziB(NULL), _gameOver(NULL), _shogoLabel(NULL), _resultLabel(
		NULL), _result(
		NULL), _modal2(
		NULL), _resultWaku(
		NULL), _kiraBon(NULL), _waku(NULL), _wakuBody(
		NULL), _yoi(
		NULL), _hazime(
		NULL), _contactlistener(
		NULL), _touchlistener(NULL), _asobikata(
		NULL), _menuB(
		NULL), _menuC(
		NULL), _menuA(NULL), _modoru(
		NULL), _saikai(
		NULL), _reTry(NULL), _pauseWaku(NULL), _modal1(NULL), _backGround(
		NULL), _table(NULL), _lvlLabel(NULL), _scoreLabel(NULL), _bestLabel(NULL), _speedLabel(NULL), _msgLabel(
		NULL), _playScore(0), _bestScore(0), _state(GameState::READY), _attackState(AttackState::A), _attackFlg(
				false), _point1(Vec2::ZERO), _point2(Vec2::ZERO), _world(NULL), _level(1), updateFlg(false), _actturn(
				0), _ball(NULL), _nomove1(NULL), _nomove3(NULL), _dot(NULL), _dot2(NULL), _gameDeta(NULL), _itemPool(
		NULL), _sFlg(
		NULL), _gFlg(NULL), _fstTch(NULL), _pause(NULL), _nextStg(NULL) {
}

MainScene::~MainScene() {
	CC_SAFE_RELEASE_NULL(_coinLabel);
	CC_SAFE_RELEASE_NULL(_coin);
	CC_SAFE_RELEASE_NULL(_gaziA);
	CC_SAFE_RELEASE_NULL(_gaziB);
	CC_SAFE_RELEASE_NULL(_gameOver);
	CC_SAFE_RELEASE_NULL(_shogoLabel);
	CC_SAFE_RELEASE_NULL(_resultLabel);
	CC_SAFE_RELEASE_NULL(_result);
	CC_SAFE_RELEASE_NULL(_modal2);
	CC_SAFE_RELEASE_NULL(_resultWaku);
	CC_SAFE_RELEASE_NULL(_kiraBon);
//	CC_SAFE_RELEASE_NULL(_kiraruPool);
	CC_SAFE_RELEASE_NULL(_waku);
	CC_SAFE_RELEASE_NULL(_wakuBody);
	CC_SAFE_RELEASE_NULL(_yoi);
	CC_SAFE_RELEASE_NULL(_hazime);
	CC_SAFE_RELEASE_NULL(_contactlistener);
	CC_SAFE_RELEASE_NULL(_touchlistener);
	CC_SAFE_RELEASE_NULL(_asobikata);
	CC_SAFE_RELEASE_NULL(_menuB);
	CC_SAFE_RELEASE_NULL(_menuA);
	CC_SAFE_RELEASE_NULL(_menuC);
	CC_SAFE_RELEASE_NULL(_modoru);
	CC_SAFE_RELEASE_NULL(_saikai);
	CC_SAFE_RELEASE_NULL(_reTry);
	CC_SAFE_RELEASE_NULL(_pauseWaku);
	CC_SAFE_RELEASE_NULL(_modal1);
	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_table);
	CC_SAFE_RELEASE_NULL(_lvlLabel);
	CC_SAFE_RELEASE_NULL(_scoreLabel);
	CC_SAFE_RELEASE_NULL(_bestLabel);
	CC_SAFE_RELEASE_NULL(_speedLabel);
	CC_SAFE_RELEASE_NULL(_msgLabel);
	//CC_SAFE_RELEASE_NULL(_world);
	CC_SAFE_RELEASE_NULL(_ball);
	CC_SAFE_RELEASE_NULL(_itemPool);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove3);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_dot2);
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_sFlg);
	CC_SAFE_RELEASE_NULL(_gFlg);
	CC_SAFE_RELEASE_NULL(_fstTch);
	CC_SAFE_RELEASE_NULL(_pause);
	CC_SAFE_RELEASE_NULL(_nextStg);

}

Scene* MainScene::createScene() {

	auto scene = Scene::createWithPhysics();

	//�����G���W��
	auto world = scene->getPhysicsWorld();
	Vec2 GA;
	GA.set(GRAVITY_ACCERATION * 15); //defo15
	//GA.rotate(Vec2::ZERO,M_PI*0.05f);
	world->setGravity(GA);
	//world->setGravity(Vec2::ZERO);
//#if COCOS2D_DEBUG >0

//
//	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

//#endif

	world->setSpeed(3);	//defo3

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void MainScene::SetGazi(Vec2 pt) {

	this->setGaziA(Sprite::create("gezi1.png"));
	this->setGaziB(Sprite::create("gezi2.png"));
	this->_gaziA->setAnchorPoint(Vec2(0, 0));
	this->_gaziB->setAnchorPoint(Vec2(0, 0));
	this->_gaziA->setPosition(pt);
	this->_gaziB->setPosition(pt);
	_gaziB->setOpacity(50);
	_gaziB->setTextureRect(Rect(0, 0, this->_gameDeta->GetMaxGazeCnt() * 11, 26));
	_gaziA->setTextureRect(Rect(0, 0, this->_gameDeta->GetMaxGazeCnt() * 11, 26));
	_nomove3->addChild(this->_gaziA, 7, Vec2::ZERO, this->_gaziA->getPosition());
	_nomove3->addChild(this->_gaziB, 6, Vec2::ZERO, this->_gaziB->getPosition());
}
void MainScene::GaziAtai(int x) {

	_gaziA->setTextureRect(Rect(0, 0, x * 11, 26));

}

// on "init" you need to initialize your instance
bool MainScene::init() {

	if (!GameScene::init()) {
		return false;
	}
	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
//	this->setnoMove2(ParallaxNode::create());
//	this->addChild(_nomove2, 6);
	this->setnoMove3(ParallaxNode::create());
	this->addChild(_nomove3, 8);

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
	_nomove1->addChild(_backGround, 2, Vec2::ZERO, _backGround->getPosition());

	//ポーズを追加する
	this->setPause(MenuItemImage::create("pause.png", "pause_p.png", [this](Ref* ref) {

		this->fstFlg=true;
		this->setState(GameState::PAUSE);

	}));

	this->setMenuC(Menu::create(_pause, NULL));
	_menuC->setVisible(false);
	_menuC->setPosition(_pause->getContentSize().width / 2 + 30, _pause->getContentSize().height * 1.6f);
	_nomove3->addChild(_menuC, 1, Vec2::ZERO, _menuC->getPosition());

//	this->setKiraruPool(KiraruPool::create(0));
//	this->setKiraBon(ParticleSystemPool::create("kirabon.plist", 0));

//	const char *str3 = "Main_init";
//	log("%s", str3);

	//this->getJara()->SetTouchListenner(true);

	//this->_cat->getHandL()->SetPosition_();

	this->setGameDeta(GameDeta::create());

	//ベストスコアーを登録
	this->setBestScore(UserDefault::getInstance()->getIntegerForKey("bestScore", 0));

	TTFConfig ttfConfig("HGRPP1.TTC", 45, GlyphCollection::DYNAMIC);

	this->setScoreLabel(
			Label::createWithTTF(ttfConfig, "経過時間:" + StringUtils::format("%.1f", (float) this->restTime_)));
	_scoreLabel->setColor(Color3B::WHITE);
	_scoreLabel->setAnchorPoint(Vec2::ZERO);
	_scoreLabel->setAlignment(TextHAlignment::LEFT);
	_scoreLabel->setPosition(20, winSize.height - 60);

	this->setBestLabel(Label::createWithTTF(ttfConfig, "ﾍﾞｽﾄﾀｲﾑ:"));

	_bestLabel->setColor(Color3B::WHITE);
	_bestLabel->setAnchorPoint(Vec2(1, 0));
	_bestLabel->setAlignment(TextHAlignment::LEFT);
	_bestLabel->setPosition(winSize.width - 20, winSize.height - 60);

	_nomove3->addChild(_bestLabel, 5, Vec2::ZERO, _bestLabel->getPosition());
	_nomove3->addChild(_scoreLabel, 5, Vec2::ZERO, _scoreLabel->getPosition());

	this->setSpeedLabel(
			Label::createWithTTF(ttfConfig,
					"spd:" + StringUtils::format("%.1f", (float) 0) + "km/h\nﾀﾞｯｼｭ:"));

	_speedLabel->setColor(Color3B::WHITE);
	_speedLabel->setAnchorPoint(Vec2(0, 1));
	_speedLabel->setAlignment(TextHAlignment::LEFT);
	_speedLabel->setPosition(_scoreLabel->getPosition() + Vec2(0, -2));

	_nomove3->addChild(_speedLabel, 5, Vec2::ZERO, _speedLabel->getPosition());

	this->setCoinLabel(
			Label::createWithTTF(ttfConfig,
					"ｺｲﾝ:  x" + StringUtils::toString((int) this->_gameDeta->getStageCoin(this->_level))));
	_coinLabel->setColor(Color3B::WHITE);
	_coinLabel->setAnchorPoint(Vec2(0, 1));
	_coinLabel->setAlignment(TextHAlignment::LEFT);
	_coinLabel->setPosition(_bestLabel->getPosition() + Vec2(-235, -2));

	_nomove3->addChild(_coinLabel, 5, Vec2::ZERO, _coinLabel->getPosition());

	//メッセージラベル

	this->setMsgLabel(Label::createWithTTF(ttfConfig, "CMB!"));
	this->getMsgLabel()->setColor(Color3B::BLACK);
	_msgLabel->setColor(Color3B::BLACK);
	_msgLabel->setVisible(false);

	_nomove3->addChild(_msgLabel, 5, Vec2::ZERO, _msgLabel->getPosition());
	this->_actturn = 0;

	//this->MadeKabe();

	//string型
//	const char *str2 = "init2";
//	log("%s", str2);

	//キーボードリスナーをセットする。
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(MainScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->getAD()->AdShow(false, true, false, false, false, false);

	this->setState(GameState::READY);

	return true;
}

void MainScene::MadeKabe() {

	//外枠ボデイをつくる

	int dt_ = 14;

	this->setWaku(Node::create());
	Vec2 sita[] = { Vec2(dt_, winSize.height - dt_), Vec2(dt_, dt_), Vec2(winSize.width - dt_, dt_), Vec2(
			winSize.width - dt_, winSize.height - dt_), Vec2(dt_, winSize.height - dt_) };
	//Vec2 sita[] = { Vec2(0, 0), Vec2(0, winSize.height), Vec2(winSize.width,winSize.height),Vec2(winSize.width,0) };
	//Vec2 sita[] = { Vec2(0, 0), Vec2(0, 30), Vec2(winSize.width,30),Vec2(winSize.width,0) };
	this->setWakuBody(PhysicsBody::createEdgeChain(sita, 5));
	this->_wakuBody->setGravityEnable(false);
	this->_wakuBody->setCategoryBitmask(kabeCatg);
	this->_wakuBody->setCollisionBitmask(pointCatg | zyaraCatg);
	this->_wakuBody->setContactTestBitmask(pointCatg | zyaraCatg);
	this->_wakuBody->setTag(kabeCatg);
	this->_wakuBody->setDynamic(false);
	this->_wakuBody->setRotationEnable(false);
	this->_waku->setPhysicsBody(this->_wakuBody);
	this->_waku->setTag(kabeCatg);
	//this->_waku->setPosition(ctPt/2);
	this->addChild(_waku, 3);

}

void MainScene::SetControll0() {

	//string型
//	const char *str = "SetControll0";
//	log("%s", str);
	this->getAD()->AdShow(false, true, false, false, false, false);
	//一番初めの処理、遊び方を表示する。
	// スプライトフレームキャッシュにスプライトシートを追加
//	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites.plist");

	// ここで指定するファイル名は、各画像のファイル名（plistに設定が保存されている）
	// ここではピンクの敵を選択
	this->setAsobikata(Sprite::create("asobikata.png"));
	_asobikata->setPosition(this->ctPt + Vec2(0, 40));

	this->_nomove3->addChild(_asobikata, 2, Vec2::ZERO, _asobikata->getPosition());

	//初期の画面タッチイベントをセットする。
	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(_state==GameState::READY) {
			//string型
			//	const char *str = "onTouchBegan_false";
			//	log("%s", str);
			return true;
		} else {
			//string型
			//	const char *str = "onTouchBegan_false";
			//	log("%s", str);

			return false;
		}

	};

	_touchlistener->onTouchMoved = [this](Touch* touch,Event* event) {

	};
	_touchlistener->onTouchEnded = [this](Touch* touch,Event* event) {

		//const char *str = "onTouchEnded";
		//log("%s", str);

			this->getAsobikata()->removeAllChildren();
			this->getAsobikata()->removeFromParent();

			auto delay_=DelayTime::create(0.5f);

			auto func_=CallFuncN::create([this](Node* node_) {

						this->scheduleUpdate();
						this->_bestLabel->setVisible(true);
						this->getAD()->AdShow(false,false,false,false,false,false);

					});

			this->runAction(Sequence::create(delay_,func_,NULL));

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,
			this);

}

void MainScene::update(float dt) {

	//各ゲームステートで分岐する。

	switch (this->getState()) {

	case GameState::READY: {
		this->onReady(dt);
		break;
	}
	case GameState::PLAY: {
		this->onPlay(dt);
		break;
	}
	case GameState::PAUSE: {
		this->onPause(dt);
		break;
	}
	case GameState::GAMEOVER: {
		this->onGameOver(dt);
		break;
	}

	case GameState::GAMECLEAR: {
		this->onGameClear(dt);
		break;
	}

	}

	if (this->onUpDateListener && updateFlg) {
		onUpDateListener(this, dt);
	}

}

void MainScene::onScoreUp() {

	if (_state != GameState::PLAY) {
		return;

	}

//	for (Kiraru* ki : this->getKiraruPool()->getMember()) {
//
//		if (ki->delFlg) {
//			_playScore++;
//			ki->ClearKiraru();
//			auto ptcl = this->getKiraBon()->pop();
//			ki->delFlg = false;
//			if (ptcl) {
//				ptcl->setPosition(ki->getPosition());
//				this->addChild(ptcl, 8);
//			}
//		}
//	}

	int score = 0;	//�R���{�ƃV���O���ŏꍇ�킯

	if (score >= 0) {

		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->playEffect("point_combo.mp3");

		_playScore += score;

	} else {

		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->playEffect("heal02.mp3");

	}

	if (_playScore > _bestScore) {

		UserDefault::getInstance()->setIntegerForKey("bestScore", _playScore);

		auto big = ScaleBy::create(0.2, 1.5, 1.5);
		auto big2 = ScaleBy::create(0.2, 1.5, 1.5);
		auto seq = Sequence::create(big, big->reverse(), NULL);
		auto rept = Repeat::create(seq, 3);

		auto tag1 = CallFuncN::create([this](Node *node) {
			node->setTag(1);

		});
		auto tag0 = CallFuncN::create([this](Node *node) {
			node->setTag(0);

		});
		_bestScore = _playScore;
		if (_scoreLabel->getTag() != 1) {
			_scoreLabel->runAction(
					Sequence::create(tag1, Repeat::create(Sequence::create(big, big->reverse(), NULL), 3),
							tag0, NULL));
		}
		if (_bestLabel->getTag() != 1) {
			_bestLabel->runAction(
					Sequence::create(tag1, Repeat::create(Sequence::create(big2, big2->reverse(),
					NULL), 3), tag0, NULL));
		}
	}

	_scoreLabel->setString("A" + StringUtils::toString(_playScore));
	_bestLabel->setString("B" + StringUtils::toString(_bestScore));
}

void MainScene::setAction(AttackState x) {

//	_scoreLabel->setString("Stat");
	/*
	 if (_state != GameState::PLAY) {
	 return;
	 }
	 */
	if (this->getAttackState() == x) {
		return;
	}

	this->setAttackState(x);

	switch (x) {

	case AttackState::A:
		//	_scoreLabel->setString("Stat:A");
		break;
	case AttackState::B:

		break;
	case AttackState::C:

		break;
	case AttackState::D:

		break;
	case AttackState::E:

		break;
	}

}

cocos2d::Vec2 MainScene::madeRndPos() {

	auto winSize = Director::getInstance()->getWinSize();
	float xpos = arc4random() % static_cast<int>(winSize.width);
	float ypos = arc4random() % static_cast<int>(winSize.height);
	return Vec2(xpos, ypos);

}

bool MainScene::inWinSize(Vec2 pos) {
	auto director = Director::getInstance();

	auto winSize = director->getWinSize();
	if (pos.x > 0 && pos.x < winSize.width && pos.y > 0 && pos.y < winSize.height) {
		return true;
	}
	return false;

}

cocos2d::Vec2 MainScene::madeRndPosOuter() {

	auto winSize = Director::getInstance()->getWinSize();

	float xpos = arc4random() % static_cast<int>(winSize.width + 100);
	float ypos = arc4random() % static_cast<int>(winSize.height + 100);
	int men = arc4random() % 4;

	switch (men) {
	case 0:
		return Vec2(xpos - 50, winSize.height + 50);
		break;
	case 1:
		return Vec2(winSize.width + 50, ypos - 50);
		break;
	case 2:
		return Vec2(xpos - 50, -50);
		break;

	case 3:
		return Vec2(-50, ypos - 50);
		break;

	default:
		return Vec2(winSize.width + 50, -50);
		break;
	}

	return Vec2::ZERO;

}

void MainScene::SetTouchListener() {
//jaraのタッチイベントをセットする。
	Director::getInstance()->getEventDispatcher()->removeEventListener(this->getTouchListenner());

//jaraのタッチイベントをセットする。
	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchlistener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(_fstTch==NULL ) {

			this->setFstTch(touch);
			_point1.set(touch->getLocation());
			_point2.set(touch->getLocation());

			this->_ball->TouchOn(touch->getLocation());

//		if(_dot) {
//			_dot->getBody()->removeAllShapes(true);
//			_dot->getBody()->removeFromWorld();
//			_dot->getBody()->release();
//			_dot->removeAllChildrenWithCleanup(true);
//		}

//		this->setDot(Dot::create());
//		this->addChild(_dot);
//		_dot->rndMade(10,30);
//		_dot->AddDot(_point1-Vec2(0,500));
//		_dot->SetPt.set(_point1);

			return true;

		} else {
			return false;
		}

	};

	_touchlistener->onTouchMoved = [this](Touch* touch,Event* event) {

//		Vec2 delta=touch->getDelta();

			_point2.set(touch->getLocation());

			this->_ball->Swaip(_point1,_point2);

//		if((touch->getLocation()-Vec2(0,500)-_dot->SetPt).length()>5) {
//			_dot->AddDot(touch->getLocation()-Vec2(0,500));
//		}

//			delta.set(_point2-_point1);

		};

	_touchlistener->onTouchEnded = [this](Touch* touch,Event* event) {
		_point1.set(Vec2::ZERO);
		_point2.set(Vec2::ZERO);
//		_dot->SetShape();
			this->_ball->TouchOff();
			this->setFstTch(NULL);

		};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchlistener,
			this);

}
void MainScene::SetContactListener() {
//jaraとネコのコンタクトリスナーをセットする。

//接触感知
	this->setContactListenner(EventListenerPhysicsContact::create());
	_contactlistener->onContactBegin = [this](PhysicsContact& contact) {

		switch(contact.getShapeA()->getBody()->getTag()) {
			//ゴールした時
			case 20: {

//				const char *str = "setContactListenner_20";
//				log("%s", str);

//				Sprite* sp=dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode());
//				Item* itm=dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->fstPt.set(dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode())->getPosition());
//				itm->fstTch=true;
				this->_ball->goalFlg_=true;
				this->stop_=true;
				break;
			}
			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_ball->RtchPt.set(contact.getContactData()->points[1]);
				_ball->RnmlPt.set(contact.getContactData()->normal);
				_ball->RtchFlg=true;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_ball->FtchPt.set(contact.getContactData()->points[1]);
				_ball->FnmlPt.set(contact.getContactData()->normal);
				_ball->FtchFlg=true;
				break;
			}
			//ライダー本体
			case 10: {
				_ball->setTchNode(contact.getShapeB()->getBody()->getNode());
				_ball->ntchPt_.set(contact.getShapeB()->getBody()->getNode()->getPosition());
				_ball->ganNml.set(contact.getContactData()->normal);
				_ball->ganPt_.set(contact.getContactData()->points[3]);
				_ball->deadFlg_=true;
				this->gameOverFlg=true;
				break;
			}

		}

		switch(contact.getShapeB()->getBody()->getTag()) {

			//ゴールした時
			case 20: {

//				const char *str = "setContactListenner_20";
//				log("%s", str);

//				Sprite* sp=dynamic_cast<Sprite *>(contact.getShapeB()->getBody()->getNode());
//				Item* itm=dynamic_cast<Item *>(sp->getParent()->getParent());
//				itm->fstPt.set(dynamic_cast<Sprite *>(contact.getShapeA()->getBody()->getNode())->getPosition());
//				itm->fstTch=true;
				this->_ball->goalFlg_=true;
				this->stop_=true;
				break;
			}

			//後輪
			case 12: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);

				_ball->RtchPt.set(contact.getContactData()->points[1]);
				_ball->RnmlPt.set(-contact.getContactData()->normal);
				_ball->RtchFlg=true;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_ball->FtchPt.set(contact.getContactData()->points[1]);
				_ball->FnmlPt.set(-contact.getContactData()->normal);
				_ball->FtchFlg=true;
				break;
			}
			//ライダー本体
			case 10: {
				_ball->setTchNode(contact.getShapeA()->getBody()->getNode());
				_ball->ntchPt_.set(contact.getShapeA()->getBody()->getNode()->getPosition());
				_ball->ganNml.set(-contact.getContactData()->normal);
				_ball->ganPt_.set(contact.getContactData()->points[3]);
				_ball->deadFlg_=true;
				this->gameOverFlg=true;
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
				_ball->RtchPt.set(Vec2::ZERO);
				_ball->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_ball->FtchPt.set(Vec2::ZERO);
				_ball->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
				if(contact.getShapeB()->getBody()->getNode()==_ball->getTchNode()) {
					_ball->setTchNode(NULL);
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
				_ball->RtchPt.set(Vec2::ZERO);
				_ball->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
				_ball->FtchPt.set(Vec2::ZERO);
				_ball->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
				if (contact.getShapeA()->getBody()->getNode() == _ball->getTchNode()) {
					_ball->setTchNode(NULL);
				}
				break;
			}

		}

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactlistener,
			this);

}

void MainScene::BtnSet(Menu* mn, Vec2 pt) {
	mn->setPosition(pt);
	this->_nomove3->addChild(mn, 5, Vec2::ZERO, mn->getPosition());

}

void MainScene::onReady(float dt) {

	if (fstFlg) {

		//this->setScale(0.1f);
		fstFlg = false;

//		_ball->scheduleUpdate();
//		_ball->updateFlg = true;

//		const char *str = "onReady2";
//		log("%s", str);

		//出現
		this->_sFlg->FadeIn(1.0f, 0.5f);
		this->_ball->FadeInBike(1.0f, 0.5f);
		this->_dot->FadeIn_Dot(1.0f, 0.5f);
		this->_dot2->FadeIn_Dot(1.0f, 0.5f);

		TTFConfig ttfConfig2("HGRPP1.TTC", 100, GlyphCollection::DYNAMIC);

		this->setLvlLabel(Label::createWithTTF(ttfConfig2, "LEVELSELECT"));
		this->_lvlLabel->setAnchorPoint(Vec2(0.5, 0.5));
		this->_lvlLabel->setAlignment(TextHAlignment::CENTER);
		this->_lvlLabel->setColor(Color3B::WHITE);
		this->_lvlLabel->setString("コース:" + StringUtils::toString((int) this->CourceLevel));
		//	this->_lvlLabel->enableOutline(Color4B::RED, 2);
		//	this->_lvlLabel->enableGlow(Color4B::WHITE);
		this->_lvlLabel->setPosition(ctPt);
		this->_lvlLabel->setOpacity(0);
		auto fadeIn_ = FadeIn::create(0.5f);
		auto delay_ = DelayTime::create(0.5f);
		auto func_ = CallFuncN::create([this](Node * nd) {
			this->_nomove3->addChild(this->_yoi, 15, Vec2::ZERO, this->_yoi->getPosition());
		});
		auto fadeOut_ = FadeOut::create(0.5f);
		auto rmv_ = RemoveSelf::create();

		auto seq_ = Sequence::create(fadeIn_, delay_, fadeOut_, func_, rmv_, NULL);
		this->_lvlLabel->runAction(seq_);

		this->setHazime(Sprite::create("start.png"));
		_hazime->runAction(
				Sequence::create(CallFuncN::create([this](Node * nd) {
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select02.mp3");
				}), RotateBy::create(0.3, Vec3(0, 90, 0)),
						CCSpawn::create(EaseIn::create(ScaleTo::create(0.5, 5.0), 0.5), FadeOut::create(0.5),
						NULL), RemoveSelf::create(),
						NULL));

		_hazime->setPosition(ctPt);
		this->setYoi(Sprite::create("ready.png"));
		_yoi->setPosition(ctPt);
		_yoi->setScale(0);

		this->_yoi->setGlobalZOrder(18);
		_yoi->runAction(
				Sequence::create(
						CallFunc::create(
								[this] {CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select01.mp3");}),
						DelayTime::create(0.75f),
						ScaleTo::create(0.25, 1),
						CallFunc::create(
								[this] {CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select01.mp3");}),
						DelayTime::create(1.0),
						RotateBy::create(0.3, Vec3(0, 90, 0)),
						CallFunc::create(
								[this] {
									this->_hazime->setRotation3D(Vec3(0, 270, 0));
									this->_nomove3->addChild(this->_hazime,15,Vec2::ZERO,this->_hazime->getPosition());
									this->_hazime->setGlobalZOrder(18);
									this->fstFlg=true;
									this->_state=GameState::PLAY;
									this->_menuC->setVisible(true);
//									CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("select01.mp3");
//						_zyara->moveFlg=true;
								}), RemoveSelf::create(),
						NULL));
		this->_nomove3->addChild(this->_lvlLabel, 20, Vec2::ZERO, this->_lvlLabel->getPosition());
	} else {

		//何もしない

	}
}
void MainScene::onPlay(float dt) {
	if (fstFlg) {

		//	this->_ball->SetMoveTypeB(240);

		fstFlg = false;

		this->_sFlg->getBody()->setEnable(false);
		this->_sFlg->Action1();
		this->_ball->fstFlg = true;
		this->_ball->setBikeState(Bike::BikeState::NOML);
		this->start_ = true;

	} else {

//		this->getCourceMader()->CourceUpdate(this->_ball->getPosition());
//		if (courceCnt_ <= courceCnt) {

		if (this->courceCnt_ < this->courceCnt) {
			if (_ball->getPosition().x - _dot->lstPt.x > 250) {
//			if (_dot2->lstPt.x - _ball->getPosition().x < winSize.width + 100) {
				courceCnt_++;
				this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_);
				this->_waku->setPosition(_dot2->_dotG.at(0)->getPosition());
//				const char *str =
//						"onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
//				log("%s", str);
				if (courceCnt_ == courceCnt) {
					this->_gFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
					this->addChild(this->_gFlg, 3);
				}

			}

			if (_ball->getPosition().x - _dot2->lstPt.x > 250) {
//			if (_dot->lstPt.x - _ball->getPosition().x < winSize.width + 100) {

				courceCnt_++;
				this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_);
				this->_waku->setPosition(_dot->_dotG.at(0)->getPosition());
				if (courceCnt_ == courceCnt) {
					this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
					this->addChild(this->_gFlg, 11);
				}

			}
		}

//		}

//		if (_ball->getPosition().x - _dot->SetPt.x > 200) {
//			_dot->ResetDot();
//			_dot->SetPt.set(_dot2->SetPt);
//
//			int rndA = arc4random() % static_cast<int>(5) + 1;
//			int rndB = arc4random() % static_cast<int>(300) + 100;
//			int rndC = arc4random() % static_cast<int>(400) + 50;
//			_dot->rndMade2();
////			_dot->rndMade(rndA, rndB, rndC, 10);
//
//		}
//		if (_ball->getPosition().x - _dot2->SetPt.x > 200) {
//			_dot2->ResetDot();
//			_dot2->SetPt.set(_dot->SetPt);
//
//			courceCnt_++;
//
//			if (courceCnt_ == courceCnt) {
//				_dot2->GoalLine();
//				this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
//				this->addChild(this->_gFlg, 11);
//
//			} else {
//				_dot2->rndMade2();
//			}
//		}

//
//		_dot->rndMade(10,300);
//		this->setDot2(Dot::create());
//		this->addChild(_dot2);
//		_dot2->SetPt.set(_dot->SetPt);
//		_dot2->rndMade(15,400);

//
//		for (Fly* f : this->getCourceMader()->getFlys()) {
//
//			if (f->getPosition().x < this->getBall()->getPosition().x - 300) {
//				f->setPosition(getBall()->getPosition() + Vec2(800, -100));
//			}
//
//		}
//		for (Dango* d : this->getCourceMader()->getDangos()) {
//
//			if (d->getPosition().x < this->getBall()->getPosition().x - 300) {
//				d->setPosition(getBall()->getPosition() + Vec2(800, -50));
//				d->setDangoState(Dango::DangoState::ROLL);
//				d->fstFlg = true;
//			}
//
//		}
////		for (Geko* d : this->getCourceMader()->getGekos()) {
////
////			if (d->getPosition().x < this->getBall()->getPosition().x - 300) {
////				d->setPosition(getBall()->getPosition() + Vec2(800, -50));
////				d->setGekoState(Geko::GekoState::STAND);
////				d->fstFlg = true;
////			}
////
////		}
//		for (Item* i : this->getCourceMader()->getItems()) {
//
//			if (i->GetImgPosition().x < this->getBall()->getPosition().x - 1000) {
//				i->getImg()->setPosition(getBall()->getPosition() + Vec2(800, -100));
//				i->setPosition(Vec2::ZERO);
////				i->getBody()->setVelocity(0);
////				i->getImg()->setRotation()
//			}
//
//		}

		/*
		 kiraInt_ += dt;

		 if (kiraInt_ > kiraInt) {

		 kiraInt_ = 0;
		 Kiraru* ki = this->getKiraruPool()->pop();
		 if (ki) {
		 //ki->setPosition(Vec2(200, 300));
		 ki->ShowKiraru();
		 this->addChild(ki, 9);
		 //this->getCat()->mouseOpen();
		 }
		 }
		 */
		if (this->gameOverFlg) {

			this->fstFlg = true;
			this->setState(GameState::GAMEOVER);

		}

		//デバック

		if (this->start_ && !this->stop_) {
			this->restTime_ += dt;
			this->getScoreLabel()->setString("経過時間:" + StringUtils::format("%.1f", (float) this->restTime_));
			this->getSpeedLabel()->setString(
					"spd:" + StringUtils::format("%.1f", (float) this->_ball->spd_) + "km/h" + "\nﾀﾞｯｼｭ:");
			this->GaziAtai(this->_ball->dushCnt_);

		}

		if (this->stop_) {
			this->fstFlg = true;
			this->setState(GameState::GAMECLEAR);
		}

//		this->getScoreLabel()->setString(StringUtils::toString((int) this->getBall()->getBikeState()));
//		this->getBestLabel()->setPosition(this->getScoreLabel()->getPosition() + Vec2(0, -50));

		this->getBestLabel()->setString(
				"ﾍﾞｽﾄﾀｲﾑ:"
						+ StringUtils::format("%.1f",
								(float) this->getGameDeta()->getStageTime(this->CourceLevel)));
		//this->getBestLabel()->setString(
		//		StringUtils::toString((int) (this->_point2.x - this->_point1.x))
		//				+ "."
		//				+ StringUtils::toString(
		//						(int) (this->_point2.y - this->_point1.y)));
	}

}
void MainScene::onGameOver(float dt) {

	if (fstFlg) {

		fstFlg = false;
		_menuC->setVisible(false);
		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->playEffect("playerout.mp3");

		auto delay_ = DelayTime::create(0.5f);
		auto func_ = CallFuncN::create([this](Node *) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("miss.mp3");
		});
		auto seq_ = Sequence::create(delay_, func_, NULL);
		this->runAction(seq_);

//		this->setAction(AttackState::E);

		this->setGameOver(Sprite::create("gameover.png"));
		_gameOver->setPosition(Vec2(winSize.width / 2.0, winSize.height - 250));

		_gameOver->setScale(0);
		auto act1 = ScaleTo::create(0.5, 2);
		auto act2 = ScaleTo::create(0.5, 1);
		auto act3 = Sequence::create(act1, act2, DelayTime::create(0.3), CallFuncN::create([this](Node* nd) {
			//this->_gameOver->removeFromParent();
			}), NULL);
		_gameOver->runAction(act3);

		auto delay = DelayTime::create(0.5);
		auto stop = CallFunc::create([this] {

			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->_nomove3->addChild(_gameOver, 5,Vec2::ZERO,_gameOver->getPosition());
			_gameOver->setGlobalZOrder(30);
		});
		auto delay2 = DelayTime::create(1.5);
		auto rst = CallFunc::create([this] {

			this->fstFlg=true;
			this->setState(GameState::PAUSE);

		});
		auto Seq = Sequence::create(delay, stop, delay2, rst, NULL);
		this->runAction(Seq);

	} else {

		if (this->courceCnt_ < this->courceCnt) {
			if (_ball->getPosition().x - _dot->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_);
//				const char *str =
//						"onPlay_this->_gameDeta->ReadDetaFromFile(_dot, this->CourceLevel, courceCnt_);";
//				log("%s", str);
				if (courceCnt_ == courceCnt) {
					this->_gFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
					this->addChild(this->_gFlg, 3);
				}

			}

			if (_ball->getPosition().x - _dot2->SetPt.x > 250) {
				courceCnt_++;
				this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_);
				if (courceCnt_ == courceCnt) {
					this->_gFlg->SetPoint(_dot2->SetPt2, _dot2->mrad2_);
					this->addChild(this->_gFlg, 11);
				}

			}
		}

	}

}

void MainScene::onGameClear(float dt) {

	if (fstFlg) {

		fstFlg = false;
		_menuC->setVisible(false);
		auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();
		audioEngine->playEffect("goal.mp3");

		this->stopAllActions();
//		this->setAction(AttackState::E);

		this->setGameOver(Sprite::create("goal.png"));
		_gameOver->setPosition(Vec2(winSize.width / 2.0, winSize.height - 250));

		_gameOver->setScale(0);
		auto act1 = ScaleTo::create(0.5, 2);
		auto act2 = ScaleTo::create(0.5, 1);
		auto act3 = Sequence::create(act1, act2, DelayTime::create(0.3), CallFuncN::create([this](Node* nd) {
			//this->_gameOver->removeFromParent();
			}), NULL);
		_gameOver->runAction(act3);

		auto delay = DelayTime::create(0.5);
		auto stop = CallFunc::create([this] {

			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			this->_nomove3->addChild(_gameOver, 5,Vec2::ZERO,_gameOver->getPosition());
		});
		auto delay2 = DelayTime::create(1.5);
		auto rst = CallFunc::create([this] {
			this->ShowResult();
		});
		auto Seq = Sequence::create(delay, stop, delay2, rst, NULL);
		this->runAction(Seq);

	} else {

		//何もしない。

	}

}

void MainScene::ShowResult() {

	auto fade_ = FadeOut::create(0.5f);

	this->_gFlg->setVisible(false);

//結果を表示
	bool hiFlg = this->_gameDeta->JudgeClearTime(this->_gameDeta->GetSelectCource(), this->restTime_);
	getCoinA = this->_gameDeta->JudgeCoinGet(this->_gameDeta->GetSelectCource(), this->restTime_);

//	if (!hiFlg) {
//
//		int rnd_ = arc4random() % static_cast<int>(8);
//		if (rnd_ == 0) {
//			auto delay_ = DelayTime::create(1.5f);
//			auto func_ = CallFuncN::create([this](Node* node_) {
//				this->getAD()->AdShow(false,false,false,false,true,false);
//			});
//			this->runAction(Sequence::create(delay_, func_, NULL));
//		}
//		if (rnd_ == 1) {
//			auto delay_ = DelayTime::create(1.5f);
//			auto func_ = CallFuncN::create([this](Node* node_) {
//				this->getAD()->AdShow(false,false,false,false,true,false);
//			});
//			this->runAction(Sequence::create(delay_, func_, NULL));
//		}
//	}

//結果の枠を表示する「
	this->setModal2(ModalLayer::create());
	_nomove3->addChild(this->getModal2(), 5, Vec2::ZERO, this->getModal2()->getPosition());

	this->setResultWaku(Sprite::create("resultwaku2.png"));

	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	this->_resultWaku->setBlendFunc(blend);

	this->_resultWaku->setPosition(this->ctPt);
	this->_resultWaku->setScale(0.1f);
	auto big_ = EaseElasticOut::create(ScaleTo::create(1.2f, 1.0f));
	auto func_ = CallFuncN::create([this](Node* nd) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kekka.mp3");
	});
	auto seq_ = Spawn::create(big_, func_, NULL);
	this->_resultWaku->runAction(seq_);

	if (hiFlg) {
		//this->setNewRec(ParticleSystemPool::create("newrecord.plist", 1));
		this->setShogoLabel(Sprite::create("newrec.png"));

		_shogoLabel->setScale(15);
		_shogoLabel->setPosition(
				Vec2(_resultWaku->getContentSize().width / 2, _resultWaku->getContentSize().height / 2));
		_shogoLabel->setOpacity(30);
		auto move_ = MoveTo::create(0.3f,
				Vec2(_resultWaku->getContentSize().width / 2 + 200,
						_resultWaku->getContentSize().height / 2 + 250));
		auto rot_ = RotateTo::create(0.3f, 30);
		auto mini_ = ScaleTo::create(0.3f, 1);
		auto delay_ = DelayTime::create(0.2f);
		auto fade_ = FadeTo::create(0.3f, 255);
		auto spawn_ = Spawn::create(move_, rot_, mini_, fade_, NULL);
		auto seq_ = Sequence::create(delay_, spawn_, NULL);

		_shogoLabel->runAction(seq_);
		this->getResultWaku()->addChild(_shogoLabel, 3);

	}
	this->setReTry(MenuItemImage::create("tryagain_btn.png", "tryagain_btn_p.png", [this](Ref* ref) {
		int rnd_ = arc4random() % static_cast<int>(4);
		this->getAD()->InstCountShow(5);
		auto scene=MainScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);
	}));

	this->setModoru(MenuItemImage::create("modoru.png", "modoru_p.png", [this](Ref* ref) {

		this->getAD()->InstCountShow(5);

		auto scene=SelectScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

	}));
//	_reTry->setGlobalZOrder(23);
//	_modoru->setGlobalZOrder(23);

	if (this->restTime_ <= this->_gameDeta->getClearTime(this->CourceLevel)
			&& this->CourceLevel < this->getGameDeta()->MaxCourceLevel) {

		this->getGameDeta()->SetClearCource(this->CourceLevel + 1);
		this->setNextStg(MenuItemImage::create("next_btn.png", "next_btn_p.png", [this](Ref* ref) {
			this->getAD()->InstCountShow(5);
			this->getGameDeta()->SetSelectCource(this->CourceLevel+1);
//			UserDefault::getInstance()->setIntegerForKey("LEVEL", this->CourceLevel+1);

				//ここで分岐
				if (this->CourceLevel+1 < this->getGameDeta()->MaxCourceLevel) {
					auto scene = MainScene::createScene();
					auto transition = TransitionCrossFade::create(0.5f, scene);
					Director::getInstance()->replaceScene(transition);
				}

			}));

		auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
		auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));

		this->_nextStg->runAction(rep);

		this->setMenuB(Menu::create(_nextStg, _reTry, _modoru, NULL));
		this->getMenuB()->alignItemsVerticallyWithPadding(25);
		this->getMenuB()->setPosition(_resultWaku->getContentSize().width / 2, 180);
	} else {

		auto fadeout = EaseSineIn::create(FadeOut::create(0.5));
		auto rep = RepeatForever::create(Sequence::create(fadeout, fadeout->reverse(), nullptr));

		this->_reTry->runAction(rep);

		this->setMenuB(Menu::create(_reTry, _modoru, NULL));
		this->getMenuB()->alignItemsVerticallyWithPadding(40);
		this->getMenuB()->setPosition(_resultWaku->getContentSize().width / 2, 170);
	}

//menu_e->autorelease();

	this->getMenuB()->setScale(1.0f);
	this->getMenuB()->setAnchorPoint(Vec2(0.5, 0));

	_resultWaku->addChild(this->getMenuB());

	TTFConfig ttfConfig("HGRPP1.TTC", 80, GlyphCollection::DYNAMIC);
	this->setResultLabel(
			Label::createWithTTF(ttfConfig,
					"今の記録\n" + StringUtils::format("%.1f", (float) this->restTime_) + "秒" + "\n獲得ｺｲﾝ:"
							+ StringUtils::toString((int) getCoinA)));
	if (hiFlg) {
		this->getResultLabel()->setColor(Color3B::YELLOW);
	} else {
		this->getResultLabel()->setColor(Color3B::WHITE);
	}
	this->getResultLabel()->setAlignment(TextHAlignment::CENTER);
	this->getResultLabel()->setAnchorPoint(Vec2(0.5, 1));
	_resultLabel->setPosition(_resultWaku->getContentSize().width / 2,
			_resultWaku->getContentSize().height - 80);

	_resultWaku->addChild(this->getResultLabel());

	this->getModal2()->addChild(_resultWaku);

	//ｺｲﾝ獲得アクション

	Vec2 stPt;
	getCoin_ = getCoinA;
//	int coinCnt_ = this->_gameDeta->getStageCoin(this->_gameDeta->GetSelectCource());
	stPt.set(winSize.width - 140, winSize.height - 85);
	stPt -= this->getPosition();
	this->setCoin(SpritePool::create(50, "coin.png"));

	for (int i = 0; i < getCoinA; i++) {
		Sprite* sp = this->_coin->pop();
		sp->setOpacity(0);
		sp->setPosition(ctPt - this->getPosition());

		auto delay_ = DelayTime::create(i * 0.3f + 1);
		auto fadein_ = FadeIn::create(0.3f);
		auto big_ = ScaleTo::create(0.3f, 1.5f);
		auto spn2_ = Spawn::create(fadein_, big_, NULL);
		auto func1_ = CallFuncN::create([this](Node* nd) {
			this->getCoin_--;
			this->_resultLabel->setString(
					"今の記録\n" + StringUtils::format("%.1f", (float) this->restTime_) + "秒" + "\n獲得ｺｲﾝ:"
					+ StringUtils::toString((int) getCoin_));
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin05.mp3");
		});
		auto scale_ = ScaleTo::create(0.3f, 0.45f);
		auto move_ = MoveTo::create(0.3f, stPt);
		auto scale2_ = ScaleTo::create(0.1f, 0.8f);
		auto scale3_ = EaseElasticOut::create(ScaleTo::create(0.1f, 0.45f));
		auto spn_ = Spawn::create(scale_, move_, NULL);
		auto func2_ = CallFuncN::create([this](Node* nd) {
			this->fstCoinCnt_++;
			this->_coinLabel->setString("ｺｲﾝ:  x" + StringUtils::toString((int) (fstCoinCnt_ )));
		});
		auto seq_ = Sequence::create(delay_, spn2_, func1_, spn_, scale2_, scale3_, func2_, NULL);
		sp->runAction(seq_);
//		sp->setScale(0.7f);
//		sp->setPosition(stPt);
		this->addChild(sp, 20);
//		_nomove3->addChild(sp, 4, Vec2::ZERO, sp->getPosition());
	}

//	_resultWaku->setGlobalZOrder(20);
//	_resultLabel->setGlobalZOrder(21);
//	_menuB->setGlobalZOrder(22);

	this->getAD()->AdShow(false, false, true, false, false, false);

}
void MainScene::onPause(float dt) {

//ポーズを実行する

	if (this->fstFlg) {

		this->_ball->fstFlg = true;
		this->_ball->setBikeState(Bike::BikeState::STOP);
		this->_ball->SetPause();

		this->fstFlg = false;
		this->_menuC->setVisible(false);
		//広告を表示する
		this->setModal1(ModalLayer::create());
		this->setPauseWaku(Sprite::create("pausewaku2.png"));

		ccBlendFunc blend;
		blend.src = GL_ZERO;
		blend.dst = GL_SRC_COLOR;
		_pauseWaku->setBlendFunc(blend);

		this->setReTry(MenuItemImage::create("tryagain_btn.png", "tryagain_btn_p.png", [this](Ref* ref) {

			UserDefault::getInstance()->setBoolForKey("SAMECOURCE", true);

			this->getAD()->InstCountShow(5);
			auto scene=MainScene::createScene();
			Director::getInstance()->purgeCachedData();
			auto transition=TransitionCrossFade::create(0.5,scene);
			Director::getInstance()->replaceScene(transition);

		}));

		this->setModoru(MenuItemImage::create("modoru.png", "modoru_p.png", [this](Ref* ref) {

			UserDefault::getInstance()->setBoolForKey("SAMECOURCE", false);

			this->getAD()->InstCountShow(5);

			auto scene=SelectScene::createScene();
			Director::getInstance()->purgeCachedData();
			auto transition=TransitionCrossFade::create(0.5,scene);
			Director::getInstance()->replaceScene(transition);

//			auto scene=TitleScene::createScene();
//			Director::getInstance()->purgeCachedData();
//			auto transition=TransitionCrossFade::create(0.5,scene);
//			Director::getInstance()->replaceScene(transition);

			}));

		this->setSaikai(MenuItemImage::create("saikai_p.png", "saikai.png", [this](Ref* ref) {
//			this->onPause();
				//IMobileCocos2dxModule::show(IMOBILE_TEXTPOPUP_SID);
			}));

		this->setMenuA(Menu::create(_reTry, _modoru, NULL));

		//menu_e->autorelease();
		this->getMenuA()->alignItemsVerticallyWithPadding(40);
		this->getMenuA()->setPosition(_pauseWaku->getContentSize().width / 2,
				_pauseWaku->getContentSize().height / 2);
		_menuA->setScale(1.0f);
		_pauseWaku->addChild(this->getMenuA());

		_nomove3->addChild(this->getModal1(), 5, Vec2::ZERO, this->getModal1()->getPosition());

		_pauseWaku->setScale(0.3f);
		_pauseWaku->setPosition(this->ctPt * 1.9);

		auto scale_ = ScaleTo::create(1.2f, 1);
		auto move_ = MoveTo::create(1.2f, this->ctPt);
		auto spn_ = EaseElasticOut::create(Spawn::create(scale_, move_, NULL));
		_pauseWaku->runAction(spn_);

		this->getModal1()->addChild(_pauseWaku);

//		_pauseWaku->setGlobalZOrder(20);
//		_menuA->setGlobalZOrder(25);
//		_reTry->setGlobalZOrder(30);
//		_modoru->setGlobalZOrder(30);

		this->getAD()->AdShow(false, false, false, false, true, false);
	} else {

	}

}

void MainScene::MadeCource(int Lvl) {

	this->setDot(Dot::create("dot2.png"));
	this->setDot2(Dot::create("dot2.png"));

	this->setItemPool(ItemPool::create(2));
	this->setSFlg(this->_itemPool->pop());
	this->_sFlg->SetState(Item::ItemState::START);
	this->setGFlg(this->_itemPool->pop());
	this->_gFlg->SetState(Item::ItemState::GOAL);

	this->getGameDeta()->MadeCourceFromCourceNo(_dot, this->CourceLevel);		//コースナンバーからコースを作成
	this->courceCnt = this->getGameDeta()->GetSelectCourceLength();

	courceCnt_ = 1;
	this->_gameDeta->ReadDeta2(_dot, this->CourceLevel, courceCnt_);
	courceCnt_++;
	this->_gameDeta->ReadDeta2(_dot2, this->CourceLevel, courceCnt_);
	this->addChild(_dot, 2);
	this->addChild(_dot2, 2);

	//見えない壁を作成
	this->setWaku(Node::create());
	Vec2 kabe[] = { Vec2(0, 0), Vec2(0, 500) };
	this->setWakuBody(PhysicsBody::createEdgeChain(kabe, 2));
	this->_waku->setPhysicsBody(this->_wakuBody);
	this->_waku->setPosition(_dot->_dotG.at(0)->getPosition());
	this->addChild(this->_waku);

	//ゲージを設定
	this->SetGazi(Vec2(160, winSize.height - 143));

	//取得コインを作成

	int coinCnt_ = this->_gameDeta->getStageCoin(this->_gameDeta->GetSelectCource());
	fstCoinCnt_ = this->_gameDeta->getStageCoin(this->_gameDeta->GetSelectCource());

	Vec2 stPt;
	stPt.set(winSize.width - 140, winSize.height - 85);

	Sprite* sp_ = Sprite::create("coin.png");
	sp_->setPosition(stPt);
	sp_->setScale(0.45f);
	_nomove3->addChild(sp_, 4, Vec2::ZERO, sp_->getPosition());

	this->_coinLabel->setString("ｺｲﾝ:  x" + StringUtils::toString((int) fstCoinCnt_));

	this->setBall(Bike::createB());

	this->_ball->SetPositionBike(Vec2::ZERO);
	this->_ball->setBikeState(Bike::BikeState::READY);

	//一時的にフェードアウト
	this->_sFlg->FadeOut(0, 0);
	this->_ball->FadeOutBike(0, 0);
	this->_dot->FadeOut_Dot(0, 0);
	this->_dot2->FadeOut_Dot(0, 0);

	_ball->lifePoint = 1;
	_ball->dushCnt = this->_gameDeta->GetMaxGazeCnt();
	_ball->dushCnt_ = this->_gameDeta->GetMaxGazeCnt();
	this->addChild(_ball, 1);
	this->addChild(_ball->getChaser());
	this->addChild(_ball->getFWheel());
	this->addChild(_ball->getRWheel());
	_ball->SetJointB(this->getScene()->getPhysicsWorld());

	this->addChild(_ball->getFWheelA());
	this->addChild(_ball->getRWheelA());

//	const char *str4 = "MainMadeCource_lvl0_2";
//	log("%s", str4);

//	this->addChild(this->_ball->getPointDbg());
//	this->_ball->getPointDbg()->setGlobalZOrder(50);
//画面フォロー
	if (_ball) {

		this->runAction(Follow::create(_ball->getChaser()));
//		this->_courceMader->setBall(_ball);
	}

//	this->setScale(3.0f);
	_ball->scheduleUpdate();
	_ball->updateFlg = true;

	this->_sFlg->SetPoint(_dot->SetPt2, _dot->mrad2_);
	this->addChild(this->_sFlg, 3);

	this->SetTouchListener();
	this->SetContactListener();
	this->scheduleUpdate();

}

void MainScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm.mp3", true);
	}
//string型

	this->CourceLevel = this->getGameDeta()->GetSelectCource();

	this->MadeCource(this->CourceLevel);

//	const char *str = "onEnterTransitionDidFinish";
//	log("%s", str);
//	this->SetControll0();

}
void MainScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		switch (this->getState()) {

		case GameState::PLAY: {

			this->fstFlg = true;
			this->setState(GameState::PAUSE);

			break;
		}

		case GameState::GAMEOVER: {
			auto scene = TitleScene::createScene();
			auto transition = TransitionCrossFade::create(0.5, scene);
			Director::getInstance()->replaceScene(transition);
			this->getAD()->AdShow(false, false, false, false, true, false);
			break;
		}

		default: {
			auto scene = TitleScene::createScene();
			auto transition = TransitionCrossFade::create(0.5, scene);
			Director::getInstance()->replaceScene(transition);
			this->getAD()->AdShow(false, false, false, true, false, false);
			break;
		}

		}
	}

}
