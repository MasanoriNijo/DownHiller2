#include "TitleScene.h"
#include "scene/TestScene.h"

#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

USING_NS_CC;

using namespace cocos2d;

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
 _waku(NULL), _wakuBody(NULL), _touchlistener(NULL), _contactlistener(NULL), _state(GameState::READY) {

}

TitleScene::~TitleScene() {
	CC_SAFE_RELEASE_NULL(_waku);
	CC_SAFE_RELEASE_NULL(_wakuBody);
	CC_SAFE_RELEASE_NULL(_touchlistener);
	CC_SAFE_RELEASE_NULL(_contactlistener);

}

// on "init" you need to initialize your instance
bool TitleScene::init() {

	if (!GameScene::init()) {
		return false;
	}

	this->setState(GameState::READY);

	return true;
}

void TitleScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
//		Director::sharedDirector()->end();
	}
}

void TitleScene::openRankPark() {

}

void TitleScene::sendRankParkScore(int value) {

}

void TitleScene::tweet() {

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
        case GameState::AUTOSOSA: {
        
            break;
        }
    }

//	this->getBike()->update(dt);

}

void TitleScene::onReady(float dt) {


}

void TitleScene::onPlay(float dt) {

}

void TitleScene::onStop(float dt) {

}

void TitleScene::SetCource() {

	this->scheduleUpdate();
}

void TitleScene::onEnterTransitionDidFinish() {

}

void TitleScene::SetContactListener() {

//接触感知
	this->setContactListenner(EventListenerPhysicsContact::create());
	_contactlistener->onContactBegin = [this](PhysicsContact& contact) {

		switch(contact.getShapeA()->getBody()->getTag()) {
			//ゲートをくぐったとき
			case 20: {

				break;
			}
			//後輪
			case 12: {

				break;
			}
			//前輪
			case 11: {

				break;
			}
			//ライダー本体
			case 10: {

				break;
			}

		}

		switch(contact.getShapeB()->getBody()->getTag()) {

			//ゴールした時
			case 20: {
				break;
			}
			//後輪
			case 12: {
                break;
			}
			//前輪
			case 11: {
                break;
			}
			//ライダー本体
			case 10: {
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
    _contactlistener->onContactSeparate = [this](PhysicsContact& contact) {
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
//				_bike->RtchPt.set(Vec2::ZERO);
//				_bike->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
//				_bike->FtchPt.set(Vec2::ZERO);
//				_bike->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
//				if(contact.getShapeB()->getBody()->getNode()==_bike->getTchNode()) {
//					_bike->setTchNode(NULL);
//				}

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
//				_bike->RtchPt.set(Vec2::ZERO);
//				_bike->RtchFlg=false;
				break;
			}
			//前輪
			case 11: {
				//Ball* sp=dynamic_cast<Ball *>(contact.getShapeA()->getBody()->getNode());
				//sp->setPosition(ctPt);
//				_bike->FtchPt.set(Vec2::ZERO);
//				_bike->FtchFlg=false;
				break;
			}
			//ボール本体
			case 10: {
//				if (contact.getShapeA()->getBody()->getNode() == _bike->getTchNode()) {
//					_bike->setTchNode(NULL);
//				}
				break;
			}

		}

	};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_contactlistener,
			this);

}

