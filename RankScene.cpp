#include "RankScene.h"
#include "SelectScene.h"
#include "AsobiKata.h"
#include "TitleScene.h"

#include "platform/android/jni/JniHelper.h"
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

USING_NS_CC;
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

Scene* RankScene::createScene() {

	auto scene = Scene::createWithPhysics();

	//�����G���W��
	auto world = scene->getPhysicsWorld();
	Vec2 GA;
	GA.set(GRAVITY_ACCERATION);
	//GA.rotate(Vec2::ZERO,M_PI*0.05f);
	world->setGravity(GA);
	//world->setGravity(Vec2::ZERO);
//#if COCOS2D_DEBUG >0

//
//	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

//#endif

	world->setSpeed(2);

	// 'layer' is an autorelease object
	auto layer = RankScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}
RankScene::RankScene() :
		_drawNode(NULL), _resultLabel(NULL), _waku(NULL), _wakuBody(NULL), _wines(NULL), _coins(NULL), _bigWheel(
		NULL), _gameDeta(
		NULL), _dot(
		NULL), _dot2(NULL), _bike(NULL), _nomove1(
		NULL), _nomove2(NULL), _contactlistener(
		NULL) {

}

RankScene::~RankScene() {
	CC_SAFE_RELEASE_NULL(_drawNode);
	CC_SAFE_RELEASE_NULL(_resultLabel);
	CC_SAFE_RELEASE_NULL(_waku);
	CC_SAFE_RELEASE_NULL(_wakuBody);
	CC_SAFE_RELEASE_NULL(_coins);
	CC_SAFE_RELEASE_NULL(_wines);
	CC_SAFE_RELEASE_NULL(_bigWheel);
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_dot2);
	CC_SAFE_RELEASE_NULL(_bike);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_contactlistener);

}
// on "init" you need to initialize your instance
bool RankScene::init() {

	if (!GameScene::init()) {
		return false;
	}

	auto oto = CocosDenshion::SimpleAudioEngine::getInstance();

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1, 1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 4);

//	this->ChgColorRnd(0.9, 1.0);
	this->ChgBeforeColor();
	this->getLayerColor()->removeFromParent();
	_nomove1->addChild(this->getLayerColor(), 1, Vec2::ZERO, this->getLayerColor()->getPosition());

	Sprite* background = Sprite::create("back5.png");
	background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
//	background->setOpacity(150);
	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	background->setBlendFunc(blend);
	_nomove1->addChild(background, 2, Vec2::ZERO, background->getPosition());

	auto title = Sprite::create("kakutokucoin.png");
	title->setPosition(Vec2(winSize.width / 2.0, winSize.height - 180));
	title->setScale(1.0);
	_nomove2->addChild(title, 4, Vec2::ZERO, title->getPosition());

//	Sprite* wheel_ = Sprite::create("titlewheel.png");
//	wheel_->setPosition(Vec2(winSize.width / 2.0, winSize.height - 530));
//
//	auto rot_ = RepeatForever::create(RotateBy::create(3, 360));
//	wheel_->runAction(rot_);
//
//	wheel_->setScale(1.0);
////	this->addChild(wheel_, 4);
//	_nomove1->addChild(wheel_, 2, Vec2::ZERO, wheel_->getPosition());

	this->setGameDeta(GameDeta::create());

	auto modorup = MenuItemImage::create("modoru_btn.png", "modoru_p_btn.png", [this](Ref* ref) {

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
		auto scene=TitleScene::createScene();
		auto transition=TransitionCrossFade::create(0.5,scene);
		Director::getInstance()->replaceScene(transition);

	});

	auto rankingp = MenuItemImage::create("ranking_btn.png", "ranking_btn_p.png", [this](Ref* ref) {

//		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
//		auto scene=RankScene::createScene();
//		auto transition=TransitionCrossFade::create(0.5,scene);
//		Director::getInstance()->replaceScene(transition);

			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("kati.mp3");
			this->sendRankParkScore(this->getGameDeta()->getTotlCoin());
			this->openRankPark();

		});

	Menu* menu_ = Menu::create(rankingp, modorup, NULL);
	menu_->alignItemsHorizontallyWithPadding(35);
	menu_->setPosition(Vec2(winSize.width / 2.0, 200));
	_nomove2->addChild(menu_, 4, Vec2::ZERO, menu_->getPosition());
//	this->addChild(menu5, 4);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(RankScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->getAD()->AdShow(true, true, false, false, false, false);

	this->setState(GameState::READY);

	return true;
}

void RankScene::openRankPark() {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, OPENRNK, "()V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}
void RankScene::sendRankParkScore(int value) {
	JniMethodInfo t;
	// �N���X���ƃ��\�b�h�����w�肵�܂��B
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, SENDSCR, "(I)V")) {
		// void�Ȃ̂ŁACallStaticVoidMethod�ŌĂ�
		t.env->CallStaticVoidMethod(t.classID, t.methodID, value);
		// ���
		t.env->DeleteLocalRef(t.classID);
	}
}

void RankScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
		Director::sharedDirector()->end();
	}
}

bool RankScene::sosaPt(Vec2 pt_, float velo_, float dt) {

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
void RankScene::update(float dt) {

	//各ゲームステートで分岐する。

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

	}

//	this->getBike()->update(dt);

}
void RankScene::onReady(float dt) {

	switch (this->fstFlg) {
	case true: {

		this->fstFlg = false;
		this->sosaCnt_ = 0;
//		this->_setumeiLabel2->setString("画面をスワイプして\n自転車の操作ができるよ！");

		stime_ = 0;
		stime = 0.1f;

		break;
	}
	case false: {

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
			stime_ += dt;
			if (stime_ > stime) {

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
void RankScene::onPlay(float dt) {

	switch (this->fstFlg) {
	case true: {
		this->fstFlg = false;

		this->sFstFlg = false;
		stime_ = 0;
		stime = 0.1f;
		this->sosaCnt_ = 1;
		this->sosaCnt2_ = 1;
		this->sosaCnt2 = this->getCoins()->getMember().size();

		break;
	}
	case false: {

		switch (sosaCnt_) {

		case 0: {
			stime_ += dt;
			if (stime_ > stime) {

				sosaCnt_++;
				stime_ = 0;
				stime = 0.05f;
			}
			break;
		}
		case 1: {

			stime_ += dt;
			if (stime_ > stime) {

				if (sosaCnt2_ < sosaCnt2) {

//					this->getCoins()->getMember().at(sosaCnt2_);
					this->addChild(getCoins()->getMember().at(sosaCnt2_), 5);
					this->_resultLabel->setString("x" + StringUtils::toString((int) sosaCnt2_));
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("coin05.mp3");
					sosaCnt2_++;
					sosaCnt_--;
					stime_ = 0;
				}else{

					auto big_=ScaleTo::create(0.2f,1.5f);
					auto sml_=ScaleTo::create(0.2f,1.0f);
					auto seq_=Sequence::create(big_,sml_,NULL);
					auto rept_=Repeat::create(seq_,2);
					this->_resultLabel->runAction(rept_);

					sosaCnt_++;
				}

			}

			break;
		}

		}
		break;
	}
	}

}
void RankScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("BGM_KEY", true)) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("runk.mp3", false);
	}

	this->setCoins(SpritePool::create(this->getGameDeta()->getTotlCoin() + 1, "coin.png"));
	this->setWines(SpritePool::create(10, "waincup.png"));

	Vec2 wineVec[] = { Vec2(-68, 58), Vec2(-59, 60), Vec2(-54, 42), Vec2(-45, 27), Vec2(-29, 14), Vec2(-9, 6),
			Vec2(10, 7), Vec2(28, 14), Vec2(45, 27), Vec2(53, 41), Vec2(58, 58), Vec2(67, 58) }; //14

	auto material = PHYSICSBODY_MATERIAL_DEFAULT;
	material.restitution = 0;
	material.friction = 0;
	material.density = 0;
	Vec2 cPt = Vec2(ctPt + Vec2(0, 280));
	Vec2 dPtA = Vec2(-90, -120);
	Vec2 dPtB = Vec2(90, -120);
	int Gline = 500;

	this->setDrawNode(DrawNode::create());
	this->addChild(this->_drawNode, 3);
	this->_drawNode->drawSegment(Vec2(-10, Gline - 13), Vec2(winSize.width + 10, Gline - 13), 12,
			Color4F::BLACK);

	this->setWaku(Node::create());
	Vec2 wakuVec[] = { Vec2(246, 1500), Vec2(240, 980), Vec2(0, 632), Vec2(0, Gline), Vec2(winSize.width - 0,
			Gline), Vec2(winSize.width - 0, 632), Vec2(winSize.width - 240, 980), Vec2(winSize.width - 246,
			1500), Vec2(246, 1500) }; //4
	this->setWakuBody(PhysicsBody::createEdgeChain(wakuVec, 9, material));
	this->_waku->setPhysicsBody(_wakuBody);
	this->_waku->setPosition(Vec2::ZERO);
	this->addChild(_waku);

	for (int i = 0; i < 10; i++) {

		Sprite* win_ = this->getWines()->pop();
		PhysicsBody* bdy_ = PhysicsBody::createEdgeChain(wineVec, 12, material);
		win_->setPhysicsBody(bdy_);

		switch (i) {

		case 0: {
			win_->setPosition(cPt);
			break;
		}
		case 1: {
			win_->setPosition(cPt + dPtA);
			break;
		}
		case 2: {
			win_->setPosition(cPt + dPtB);
			break;
		}
		case 3: {
			win_->setPosition(cPt + dPtA + dPtA);
			break;
		}
		case 4: {
			win_->setPosition(cPt + dPtA + dPtB);
			break;
		}
		case 5: {
			win_->setPosition(cPt + dPtB + dPtB);
			break;
		}
		case 6: {
			win_->setPosition(cPt + dPtA + dPtA + dPtA);
			break;
		}
		case 7: {
			win_->setPosition(cPt + dPtA + dPtA + dPtB);
			break;
		}
		case 8: {
			win_->setPosition(cPt + dPtB + dPtB + dPtA);
			break;
		}
		case 9: {
			win_->setPosition(cPt + dPtB + dPtB + dPtB);
			break;
		}

		}

		this->addChild(win_, 3);

	}
	int K = this->getGameDeta()->getTotlCoin() + 1;
	Vec2 dpt = Vec2(1, 0);
	for (int i = 0; i < K; i++) {
		const char *str4 = "int K=this->getGameDeta()->getTotlCoin(100);";
		log("%s", str4);
		Sprite* coin_ = this->getCoins()->pop();
		PhysicsBody* bdy_ = PhysicsBody::createCircle(coin_->getContentSize().width / 2, material);
		bdy_->setLinearDamping(0.05f);
		coin_->setPhysicsBody(bdy_);
		coin_->setScale(0.2f);
		dpt.rotate(Vec2::ZERO, M_PI / 13);
		coin_->setPosition(Vec2(winSize.width / 2, winSize.height - 200) + dpt);

	}
	const char *str4 = "MainMadeCource_lvl0_2";
	log("%s", str4);

	this->getCoins()->getMember().at(0)->setPosition(ctPt.x - 70, Gline - 150);
	this->getCoins()->getMember().at(0)->getPhysicsBody()->setDynamic(false);
	this->getCoins()->getMember().at(0)->setScale(1.0);
	this->addChild(this->getCoins()->getMember().at(0), 2);

	TTFConfig ttfConfig("HGRPP1.TTC", 80, GlyphCollection::DYNAMIC);
	this->setResultLabel(Label::createWithTTF(ttfConfig, "x" + StringUtils::toString((int) 0)));
	this->getResultLabel()->setColor(Color3B::WHITE);
	this->getResultLabel()->setAlignment(TextHAlignment::LEFT);
	this->getResultLabel()->setAnchorPoint(Vec2(0, 0.5));
	_resultLabel->setPosition(ctPt.x - 15, Gline - 150);
	this->addChild(this->getResultLabel(), 3);

	this->SetContactListener();
	this->scheduleUpdate();

}
void RankScene::SetContactListener() {

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

