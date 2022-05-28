#include "SelectScene.h"
#include "TitleScene.h"
#include "IMobileCocos2dxModule.h"
#include "ParticleSystemPool.h"
#include "MainScene.h"
#include "TestScene.h"
#include "cmath"

USING_NS_CC;

//重力ベクトル
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

SelectScene::SelectScene() :
		_backGround(NULL), _backGround2(NULL), _stageLabel(NULL), _level(1), _nomove1(
		NULL), _nomove2(NULL), _nomove3(
		NULL), _touchListener(NULL), _selectStage(NULL), _stg(NULL), _ad(NULL), _prmBtn(NULL), _menuPrm(NULL), _baseNode(
		NULL), _sel1(NULL), _sel2(NULL), _sel3(
		NULL), _sel4(NULL), _sel5(NULL), _sel6(NULL), _sel7(NULL), _selYaziTop(NULL), _selYaziDown(NULL), _fstTch(
		NULL), _dot(NULL), _gameDeta(NULL), _bachNode(NULL), _drawNode(NULL), _coin(NULL) {
}

SelectScene::~SelectScene() {
	CC_SAFE_RELEASE_NULL(_menuPrm);
	CC_SAFE_RELEASE_NULL(_prmBtn);
	CC_SAFE_RELEASE_NULL(_backGround);
	CC_SAFE_RELEASE_NULL(_backGround2);
	CC_SAFE_RELEASE_NULL(_stageLabel);
	//CC_SAFE_RELEASE_NULL(_world);
	CC_SAFE_RELEASE_NULL(_nomove1);
	CC_SAFE_RELEASE_NULL(_nomove2);
	CC_SAFE_RELEASE_NULL(_nomove3);
	CC_SAFE_RELEASE_NULL(_touchListener);
	CC_SAFE_RELEASE_NULL(_selectStage);
	CC_SAFE_RELEASE_NULL(_stg);
	CC_SAFE_RELEASE_NULL(_ad);
	CC_SAFE_RELEASE_NULL(_baseNode);
	CC_SAFE_RELEASE_NULL(_sel1);
	CC_SAFE_RELEASE_NULL(_sel2);
	CC_SAFE_RELEASE_NULL(_sel3);
	CC_SAFE_RELEASE_NULL(_sel4);
	CC_SAFE_RELEASE_NULL(_sel5);
	CC_SAFE_RELEASE_NULL(_sel6);
	CC_SAFE_RELEASE_NULL(_sel7);
	CC_SAFE_RELEASE_NULL(_selYaziTop);
	CC_SAFE_RELEASE_NULL(_selYaziDown);
	CC_SAFE_RELEASE_NULL(_fstTch);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_bachNode);
	CC_SAFE_RELEASE_NULL(_drawNode);
	CC_SAFE_RELEASE_NULL(_coin);

}

Scene* SelectScene::createScene() {
	/*
	 auto scene = Scene::createWithPhysics();

	 //物理エンジン
	 auto world = scene->getPhysicsWorld();

	 //world->setGravity(GRAVITY_ACCERATION);
	 world->setGravity(Vec2::ZERO);
	 //#if COCOS2D_DEBUG >0

	 //world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	 //#endif

	 world->setSpeed(6.0);

	 // 'layer' is an autorelease object
	 auto layer = SelectScene::create();

	 // add layer as a child to scene
	 scene->addChild(layer);

	 // return the scene
	 return scene;

	 */

	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);

	// return the scene
	return scene;

}

// on "init" you need to initialize your instance
bool SelectScene::init() {

	if (!Layer::init()) {
		return false;
	}
	//this->setScale(0.5f);
//毎回のアップデート

	auto director = Director::getInstance();
	winSize.setSize(director->getWinSize().width, director->getWinSize().height);

	this->ctPt.set(winSize.width / 2, winSize.height / 2);

	this->setnoMove1(ParallaxNode::create());
	this->addChild(_nomove1);
	this->setnoMove2(ParallaxNode::create());
	this->addChild(_nomove2, 6);
	this->setnoMove3(ParallaxNode::create());
	this->addChild(_nomove3, 6);

	//矢印をセット
	this->setSelYaziTop(Sprite::create("selyazi.png"));
	this->_selYaziTop->setPosition(50, ctPt.y);
	this->_selYaziTop->setRotation(-90);
	this->setSelYaziDown(Sprite::create("selyazi.png"));
	this->_selYaziDown->setRotation(90);
	this->_selYaziDown->setPosition(winSize.width - 50, ctPt.y);
	this->getnoMove3()->addChild(_selYaziTop, 1, Vec2::ZERO, _selYaziTop->getPosition());
	this->getnoMove3()->addChild(_selYaziDown, 1, Vec2::ZERO, _selYaziDown->getPosition());

//	this->ChgColorRnd(0.9,1.0);
	this->ChgBeforeColor();
	this->setBackGround(Sprite::create("back5.png"));
	_backGround->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));

//	_backGround->setOpacity(150);
	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	_backGround->setBlendFunc(blend);

	this->addChild(_backGround, 2);

	this->setSelectStage(Sprite::create("selectlevel.png"));
	this->_selectStage->setPosition(ctPt.x, winSize.height - 150);
	this->addChild(_selectStage, 6);

//	this->setBackGround2(Sprite::create("levelwaku.png"));
//	_backGround2->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2));
//	this->addChild(_backGround2, 2);

	this->setBaseNode(Sprite2::create());
	this->_baseNode->setPosition(0, UserDefault::getInstance()->getIntegerForKey("SELECT_Y", 0));
	this->addChild(this->_baseNode, 5);

//	auto udf = UserDefault::getInstance();
//	this->setLevel(udf->getIntegerForKey("LEVEL", 1));

//degugselectデバックモードにする場合はtRUE
//	udf->setBoolForKey("DEBUG", false);

	this->setGameDeta(GameDeta::create());

	this->setLevel(this->getGameDeta()->GetSelectCource());

	this->setDot(Dot::create("dot2.png"));

//ｺｲﾝを作成
//	this->setCoin(SpritePool::create(30, "coin.png"));

	this->MaxLevl = this->getGameDeta()->GetClearCource();
	//ラベルを表示

//	this->setBachNode(CCSpriteBatchNode::create("dot3.png"));
	this->setDrawNode(DrawNode::create());
//	this->addChild(_drawNode, 10);
	this->_baseNode->addChild(_drawNode, 10);
	//ステージを表示

	this->setSel1(SelTag::create());
//	this->getSel1()->setDot(this->_dot);
	this->getSel1()->setGameDeta(this->_gameDeta);
	this->_sel1->setPosition(ctPt.x, ctPt.y);
	this->_sel1->SetLevel(1);
//	this->_sel1->DrawCource(1);
//	this->_sel1->SetMemoText("超簡単!\nまずはここから！");

	this->_selTags.pushBack(this->_sel1);
	this->_baseNode->addChild(_sel1, 2);

	this->setSel2(SelTag::create());
//	this->getSel2()->setDot(this->_dot);
	this->getSel2()->setGameDeta(this->_gameDeta);
	this->_sel2->setPosition(ctPt.x + SetPitch * 1, ctPt.y);
	this->_sel2->SetLevel(2);
//	this->_sel2->DrawCource(2);

//	this->_sel2->SetMemoText("普通な感じ\nクリヤすると\nちょっぴり\nうれしい");

	this->_selTags.pushBack(this->_sel2);
	this->_baseNode->addChild(_sel2, 2);

	this->setSel3(SelTag::create());
//	this->getSel3()->setDot(this->_dot);
	this->getSel3()->setGameDeta(this->_gameDeta);
	this->_sel3->setPosition(ctPt.x + SetPitch * 2, ctPt.y);
	this->_sel3->SetLevel(3);
//	this->_sel3->DrawCource(3);
//	this->_sel3->SetMemoText("まあまあムズい\nクリヤすると\nそれなりに\nうれしい");

	this->_selTags.pushBack(this->_sel3);
	this->_baseNode->addChild(_sel3, 2);

//	this->setSel4(SelTag::create());
////	this->getSel4()->setDot(this->_dot);
////	this->getSel4()->setGameDeta(this->_gameDeta);
//	this->_sel4->setPosition(ctPt.x, ctPt.y - SetPitch * 3);
//	this->_sel4->SetLevel(4);
////	this->_sel4->DrawCource(4);
//
//	this->_sel4->SetMemoText("少し骨がある\n空き時間に\nどうぞ!");
//
//	this->_selTags.pushBack(this->_sel4);
//	this->_baseNode->addChild(_sel4, 2);
//
//	this->setSel5(SelTag::create());
////	this->getSel5()->setDot(this->_dot);
////	this->getSel5()->setGameDeta(this->_gameDeta);
//	this->_sel5->setPosition(ctPt.x, ctPt.y - SetPitch * 4);
//	this->_sel5->SetLevel(5);
////	this->_sel5->DrawCource(5);
//
//	this->_sel5->SetMemoText("チョイムズ\nじっくり迷路\nを楽しむ時に\nどうぞ!");
//
//	this->_selTags.pushBack(this->_sel5);
//	this->_baseNode->addChild(_sel5, 2);
//
//	this->setSel6(SelTag::create());
//	this->_sel6->setPosition(ctPt.x, ctPt.y - SetPitch * 5);
//	this->_sel6->SetLevel(6);
//	this->_sel6->SetMemoText("超ムズレベル\n地図を見ずに\nクリヤで来たら\n天才!?");
//	this->_selTags.pushBack(this->_sel6);
//	this->_baseNode->addChild(_sel6, 2);
//
//	this->setSel7(SelTag::create());
//	this->_sel7->setPosition(ctPt.x, ctPt.y - SetPitch * 6);
//	this->_sel7->SetLevel(7);
//
//	this->_sel7->SetMemoText("迷路を自由に\n作れるぞ！");
//	this->_selTags.pushBack(this->_sel7);
//	this->_baseNode->addChild(_sel7, 2);

//	this->_baseNode->addChild(_sel2->getMenu(),1);
	//広告表示

	this->setAD(ImovileAd::create());
	_ad->AdShow(false, true, false, false, false, false);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyReleased = CC_CALLBACK_2(SelectScene::onKeyReleased, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->SetBeforeCource(this->_level);
//	this->DrawCource2(1);
//	this->DrawCource2(this->getGameDeta()->GetSelectCource());
//	moveLeftX = 0;//(this->getGameDeta()->GetSelectCource() - 1) * SetPitch;
	return true;

}

void SelectScene::SetBeforeCource(int no_) {
	//前回選択したコースにする。
	this->_baseNode->setPosition(SetPitch * (1 - no_), 0);
	this->_sel1->setPosition(ctPt.x + SetPitch * (no_ - 2), ctPt.y);
	this->_sel1->SetLevel(no_ - 1);
	this->_sel2->setPosition(ctPt.x + SetPitch * (no_ - 1), ctPt.y);
	this->_sel2->SetLevel(no_);
	this->_sel3->setPosition(ctPt.x + SetPitch * (no_), ctPt.y);
	this->_sel3->SetLevel(no_ + 1);
	this->setSel4(this->_sel2);
	this->DrawCource2(no_);
}

void SelectScene::DrawCource(int level) {
	//コースを描く。使ってない
//	const char *str0 = "SelTag::DrawCource_1";
//	log("%s", str0);
	this->getGameDeta()->MadeCourceFromCourceNo(this->_dot, level);	//本番用

//	const char *str1 = "SelTag::DrawCource_2";
//	log("%s", str1);
	this->getGameDeta()->SetDrawPosition();
//	const char *str2 = "SelTag::DrawCource_3";
//	log("%s", str2);

	float dw_ = 20;
	float scale = (winSize.width - 2 * dw_)
			/ (this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1].x
					- this->getGameDeta()->dotDrawPt[0].x);
	Vec2 centerPt;
	centerPt.set(
			(this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
					+ this->getGameDeta()->dotDrawPt[0]) / 2);
	centerPt *= scale;
	centerPt -= ctPt;
	centerPt *= -1;

	int cnt_ = this->_cMember.size();

	for (int i = 0; i < this->getGameDeta()->dotDrawCnt; i++) {

		if (i < cnt_) {
			this->_cMember.at(i)->setVisible(true);
			this->_cMember.at(i)->setScale(scale);
			this->_cMember.at(i)->setPosition((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt);
//			this->_cMember.at(i)->stopAllActions();
//			auto fade_=FadeIn::create(0.5f);
//			auto move_=MoveTo::create(0.5,(this->getGameDeta()->dotDrawPt[i]) * scale + centerPt);
//			auto scale_=ScaleTo::create(0.5f,scale);
//			auto spm_=Spawn::create(fade_,move_,scale_,NULL);
//			this->_cMember.at(i)->runAction(spm_);

		} else {
			auto g_ = Sprite::createWithTexture(_bachNode->getTexture());
			g_->setVisible(true);
			g_->setScale(scale);
			g_->setPosition((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt);

//			g_->setOpacity(0);
//			g_->setScale(scale);
//			auto fade_=FadeIn::create(0.5f);
//			auto move_=MoveTo::create(0.5,(this->getGameDeta()->dotDrawPt[i]) * scale + centerPt);
//			auto scale_=ScaleTo::create(0.5f,scale);
//			auto spm_=Spawn::create(fade_,move_,scale_,NULL);
//			g_->runAction(spm_);

//			g_->setPosition((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt);
			this->_cMember.pushBack(g_);
			this->addChild(g_, 5);
		}

	}

	for (int i = this->getGameDeta()->dotDrawCnt; i < this->_cMember.size(); i++) {
		this->_cMember.at(i)->setVisible(false);

//		this->_cMember.at(i)->stopAllActions();
//		auto fade_=FadeOut::create(0.5f);
//		this->_cMember.at(i)->runAction(fade_);

//		this->_cMember.at(i)->setVisible(false);
//		const char *str3 = "this->_cMember.at(i)->setVisible(false);";
//		log("%s", str3);
	}

}
void SelectScene::DrawCource3(int level, bool rstFlg) {

	//コースを描く。使ってない

	if (level == 1) {

		this->_selYaziDown->setVisible(false);
		this->_selYaziTop->setVisible(true);

	} else if (level == MaxLevl) {
		this->_selYaziDown->setVisible(true);
		this->_selYaziTop->setVisible(false);

	}

//	const char *str0 = "SelTag::DrawCource_1";
//	log("%s", str0);

//	const char *str1 = "SelTag::DrawCource_2";
//	log("%s", str1);
	this->getGameDeta()->SetDrawPosition();
//	const char *str2 = "SelTag::DrawCource_3";
//	log("%s", str2);

	float dw_ = 60;
	float scale = (winSize.width - 2 * dw_)
			/ (this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1].x
					- this->getGameDeta()->dotDrawPt[0].x);
	Vec2 centerPt;
	centerPt.set(
			(this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
					+ this->getGameDeta()->dotDrawPt[0]) / 2);
	centerPt *= scale;
	centerPt -= ctPt;
	centerPt *= -1;
	centerPt += Vec2(SetPitch * (level - 1), 0);
//	const char *str3 = "SelTag::DrawCource_4";
//	log("%s", str3);

	this->_drawNode->clear();

	for (int i = 0; i < this->getGameDeta()->dotDrawCnt - 2; i++) {

		if (i % 2 == 0) {
			this->_drawNode->drawSegment((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt,
					(this->getGameDeta()->dotDrawPt[i + 2]) * scale + centerPt, 36 * scale, Color4F::BLACK);
		}
	}
	this->_drawNode->setOpacity(0);
	auto fade_ = FadeIn::create(10);
	this->_drawNode->runAction(fade_);

	if (this->getSel4()) {
		this->getSel4()->SetMemoText(
				"高低差:"
						+ StringUtils::toString(
								(int) ((this->getGameDeta()->dotDrawPt[0].y
										- this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1].y))
										/ 100) + "m\n" + "距離:"
						+ StringUtils::toString(
								(int) ((this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
										- this->getGameDeta()->dotDrawPt[0]).length()) / 100) + "m\n"
						+ "ベストタイム:"
						+ StringUtils::format("%.1f", (float) this->getGameDeta()->getStageTime(level))
						+ "秒");
//						+ StringUtils::toString((int) level));

	}
//	this->_drawNode->visit(); // RenderTextureにレンダリング
//	this->_rdTx->end();
}

void SelectScene::DrawCource2(int level) {

	//まず背景色を確定する
	float h = -(float) (level - 1) / (float) 100;
	h *= 8.0f;
	h += 0.5;
	while (h < 0) {
		h++;
	}
	this->ChgColor(h, 0.6, 1.0);

	//コースを描く。

	if (level == 1) {

		this->_selYaziDown->setVisible(false);
		this->_selYaziTop->setVisible(true);

	} else if (level == MaxLevl) {
		this->_selYaziDown->setVisible(true);
		this->_selYaziTop->setVisible(false);

	}

//	const char *str0 = "SelTag::DrawCource_1";
//	log("%s", str0);

	this->getGameDeta()->SetSelectCource(level);
	this->getGameDeta()->MadeCourceFromCourceNo(this->_dot, level);
	this->getGameDeta()->SetDrawPosition();

	float dw_ = 60;
	float scale = (winSize.width - 2 * dw_)
			/ (this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1].x
					- this->getGameDeta()->dotDrawPt[0].x);
	Vec2 centerPt;
	centerPt.set(
			(this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
					+ this->getGameDeta()->dotDrawPt[0]) / 2);
	centerPt *= scale;
	centerPt -= ctPt;
	centerPt *= -1;
	centerPt += Vec2(SetPitch * (level - 1), 0);

	const char *str2 = "SelTag::DrawCource2_1";
	log("%s", str2);

	this->_drawNode->clear();
	this->_drawNode->setVisible(true);

	int haba = 36 * scale;
	if (haba < 3) {
		haba = 3;
	}

	for (int i = 0; i < this->getGameDeta()->dotDrawCnt - 2; i++) {

		if (i % 2 == 0) {
			this->_drawNode->drawSegment((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt,
					(this->getGameDeta()->dotDrawPt[i + 2]) * scale + centerPt, haba, Color4F::BLACK);
		}
	}

//	this->_drawNode->drawSegment(Vec2(0, 0) - this->_baseNode->getPosition(),
//			ctPt - this->_baseNode->getPosition(), 36* scale, Color4F::BLACK);

//	this->_drawNode->setOpacity(0);
//	auto fade_ = FadeIn::create(10);
//	this->_drawNode->runAction(fade_);

	if (this->getSel4()) {

//		this->getSel4()->ShowCoin();
		this->getSel4()->ShowCoin2();

		if (this->getGameDeta()->MaxCourceLevel != level) {
			this->getSel4()->SetMemoText(
					"高低差:"
							+ StringUtils::toString(
									(int) ((this->getGameDeta()->dotDrawPt[0].y
											- this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt
													- 1].y)) / 100) + "m\n" + "距離:"
							+ StringUtils::toString(
									(int) ((this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
											- this->getGameDeta()->dotDrawPt[0]).length()) / 100) + "m\n"
							+ "難易度：" + StringUtils::toString((int) this->getGameDeta()->cLvl) + "\n"
							+ "基準ﾀｲﾑ："
							+ StringUtils::toString(
									(int) this->getGameDeta()->getClearTime(
											this->getGameDeta()->GetSelectCource())) + "秒\n" + "ﾍﾞｽﾄﾀｲﾑ:"
							+ StringUtils::format("%.1f",
									(float) this->getGameDeta()->getStageTime(
											this->getGameDeta()->GetSelectCource())) + "秒\n獲得ｺｲﾝ:  x"
							+ StringUtils::toString(
									(int) this->_gameDeta->getStageCoin(this->getSel4()->Level_)));	//+ "\n"

			if (this->_gameDeta->GetDebug()) {

				this->getSel4()->SetMemoText(
						"高低差:"
								+ StringUtils::toString(
										(int) (this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[1]].y
												- this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[2]].y)
												/ 100) + "m\n" + "距離:"
								+ StringUtils::toString(
										(int) (this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[2]]
												- this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[1]]).length()
												/ 100) + "m\n" + "難易度："
								+ StringUtils::toString((int) this->getGameDeta()->cLvl) + "\n" + "ﾍﾞｽﾄﾀｲﾑ:"
								+ StringUtils::format("%.1f",
										(float) this->getGameDeta()->getStageTime(
												this->getGameDeta()->GetSelectCource())) + "秒\n獲得ｺｲﾝ:  x"
								+ StringUtils::toString(
										(int) this->_gameDeta->getStageCoin(this->getSel4()->Level_)));

			}

//											+ StringUtils::toString((int) this->r) + "_"
//											+ StringUtils::toString((int) this->g) + "_"
//											+ StringUtils::toString((int) this->b)));
//			this->getSel4()->SetMemoText(
//					StringUtils::toString((int) this->r) + "_" + StringUtils::toString((int) this->g) + "_"
//							+ StringUtils::toString((int) this->b) + "\n"
//							+ StringUtils::format("%.3f", (float) this->h_) + "_"
//							+ StringUtils::format("%.3f", (float) this->s_) + "_"
//							+ StringUtils::format("%.3f", (float) this->v_) + "\n\n");

		} else {
			this->getSel4()->SetMemoText("選択し直すと\nコースが変わるよ\n" + this->getSel4()->getSelMemo()->getString());
		}
	}

	const char *str3 = "SelectScene::DrawCource2_2";
	log("%s", str3);

//	int coinCnt_ = this->_gameDeta->getStageCoin(this->_gameDeta->GetSelectCource());
//
//	Vec2 stPt;
//	stPt.set(winSize.width - 30, winSize.height - 85);
//	for (int i = 0; i < coinCnt_; i++) {
//
//		Sprite* sp = this->_coin->pop();
//		sp->setPosition(stPt);
//		_nomove3->addChild(sp, 4, Vec2::ZERO, sp->getPosition());
////		stPt += Vec2(-sp->getContentSize().width + 2, 0);
//		stPt += Vec2(-25, 0);
//	}

}

void SelectScene::SetTouchListener() {

//	const char *str = "SetTouchListener() ";
//	log("%s", str);
//タッチイベントをセットする。
	this->setTouchListenner(EventListenerTouchOneByOne::create());
	_touchListener->onTouchBegan = [this](Touch* touch,Event* event) {

		if(_fstTch==NULL ) {

			this->setSelState(SelState::TAP);
			this->fstFlg=true;
			this->setFstTch(touch);
			_point1.set(touch->getLocation());
			_point2.set(touch->getLocation());
//			const char *str = "TouchBegan";
//			log("%s", str);

			for(SelTag* tg:this->_selTags) {

//				const char *str = "for(SelTag* tg:this->_selTags)";
//				log("%s", str);
				tg->TouchOn(-this->_baseNode->getPosition()+_point1);
				fstSet_=false;
			}

			tch_=true;
			moveVelo =0;
			return true;
		} else {
			return false;
		}

	};

	_touchListener->onTouchMoved = [this](Touch* touch,Event* event) {

		if(_fstTch==touch) {
			_point2_before.set(_point2);
			_point2.set(touch->getLocation());
//					const char *str = "TouchMove1";
//					log("%s", str);

			if((_point2-_point1).length()>20 && this->getSelState()==SelState::TAP) {
				this->setSelState(SelState::SWAIP);
				this->fstFlg=true;
			}
			if(_point1.y>200 && _point1.y<winSize.height-200) {

				if((this->_baseNode->getPosition().x+touch->getDelta().x)>moveLeftX) {
					this->_baseNode->setPosition(moveLeftX,0);
					this->_selYaziDown->setVisible(false);
					this->_selYaziTop->setVisible(true);
				} else if((this->_baseNode->getPosition().x+touch->getDelta().x)<-SetPitch * (MaxLevl-1)+moveLeftX) {
					this->_baseNode->setPosition(-SetPitch * (MaxLevl-1)+moveLeftX,0);
					this->_selYaziDown->setVisible(true);
					this->_selYaziTop->setVisible(false);
				} else {
					this->_baseNode->setPosition(this->_baseNode->getPosition().x+touch->getDelta().x,0);
					this->_selYaziDown->setVisible(true);
					this->_selYaziTop->setVisible(true);
				}

			}
			for(SelTag* tg:this->_selTags) {

				tg->Swaip(-this->_baseNode->getPosition()+_point1,-this->_baseNode->getPosition()+_point2);

			}

		}
	};

	_touchListener->onTouchEnded = [this](Touch* touch,Event* event) {
		if(_fstTch==touch) {
			_fstTch=NULL;
			tch_=false;

			this->setSelState(SelState::SCROLL);
			this->fstFlg=true;

			for(SelTag* tg:this->_selTags) {
//				const char *str = "tg->TouchOff();";
//				log("%s", str);
			tg->TouchOff();
		}
	}
};

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener,
			this);

}
void SelectScene::update(float dt) {

	for (SelTag* tg : this->_selTags) {

		if ((tg->getPosition().x + this->_baseNode->getPosition().x) < (-SetPitch * 1.1 + ctPt.x / 2)) {
			tg->SetLevel(tg->Level_ + 3);
			tg->setPosition(tg->getPosition() + Vec2(SetPitch * 3, 0));
		} else if ((tg->getPosition().x + this->_baseNode->getPosition().x) > (SetPitch * 1.1 + ctPt.x / 2)) {
			tg->SetLevel(tg->Level_ - 3);
			tg->setPosition(tg->getPosition() - Vec2(SetPitch * 3, 0));
		}

		if (tg->Level_ == this->getGameDeta()->MaxCourceLevel) {
			tg->getLvlLabel()->setString("おまけコース");
		}

	}

////	枠の慣性の動き
//	if (tch_) {
//		moveVelo = moveVelo * 0.5 + 0.5 * (_baseNode->getPosition().x - beforePt) / dt;
//		beforePt = _baseNode->getPosition().x;
//	} else {
//		if ((this->_baseNode->getPosition().x) > moveLeftX) {
//			this->_baseNode->setPosition(moveLeftX, 0);
//			this->_selYaziDown->setVisible(false);
//			this->_selYaziTop->setVisible(true);
//			moveVelo = 0;
//			moveVelo = 0;
//			int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
//			int b = SetPitch;
//			Y = a / b;
//			this->setSelState(SelState::STOP);
//			this->fstFlg = true;
//		} else if ((this->_baseNode->getPosition().x) < -SetPitch * (MaxLevl - 1) + moveLeftX) {
//			this->_baseNode->setPosition(-SetPitch * (MaxLevl - 1) + moveLeftX, 0);
//			this->_selYaziDown->setVisible(true);
//			this->_selYaziTop->setVisible(false);
//			moveVelo = 0;
//			int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
//			int b = SetPitch;
//			Y = a / b;
//			Y--;
//			this->setSelState(SelState::STOP);
//			this->fstFlg = true;
//			moveVelo = 0;
//		} else {
//			this->_selYaziDown->setVisible(true);
//			this->_selYaziTop->setVisible(true);
//
//			if (moveVelo > 1000) {
//				moveVelo -= (1500 * dt);
//				this->_baseNode->setPosition(this->_baseNode->getPosition().x + moveVelo * dt, 0);
//				this->setSelState(SelState::SCROLL);
//				this->fstFlg = true;
//			} else if (moveVelo < -1000) {
//				moveVelo += (1500 * dt);
//				this->_baseNode->setPosition(this->_baseNode->getPosition().x + moveVelo * dt, 0);
//				this->setSelState(SelState::SCROLL);
//				this->fstFlg = true;
//			} else {
//				if (!fstSet_) {
//					fstSet_ = true;
//					moveVelo = 400;
//					int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
//					int b = SetPitch;
//					Y = a / b;
//					this->_baseNode->setPosition(
//							this->_baseNode->ChaseA(Vec2(Y * SetPitch, 0), this->_baseNode->getPosition(),
//									moveVelo, dt));
//				} else {
//					this->_baseNode->ChaseA(dt);
//				}
//			}
//		}
//	}

//各ゲームステートで分岐する。

	switch (this->getSelState()) {

	case SelState::TAP: {
		this->onTap(dt);
		break;
	}
	case SelState::SWAIP: {
		this->onSwaip(dt);
		break;
	}

	case SelState::SCROLL: {
		this->onScroll(dt);
		break;
	}

	case SelState::STOP: {
		this->onStop(dt);
		break;
	}

	}

	if (this->onUpDateListener) {
		onUpDateListener(this, dt);
	}

}

void SelectScene::onTap(float dt) {
	if (fstFlg) {

		//this->setScale(0.1f);
		fstFlg = false;
	} else {

	}
}
void SelectScene::onSwaip(float dt) {

	if (fstFlg) {
//		this->_drawNode->clear();
		fstFlg = false;
		//this->setScale(0.1f);
		moveVelo = 0;
		beforePt = _baseNode->getPosition().x;
	} else {

		//	枠の慣性の動き
//		const char *str = "SelectScene::onSwaip(float dt)";
//		log("%s", str);
		moveVelo = moveVelo * 0.1 + 0.9 * (_baseNode->getPosition().x - beforePt) / dt;
		beforePt = _baseNode->getPosition().x;

//		if (-MaxmoveVelo > moveVelo) {
//			moveVelo = -MaxmoveVelo;
//		} else if (MaxmoveVelo < moveVelo) {
//			moveVelo = MaxmoveVelo;
//		}

	}
}
void SelectScene::onScroll(float dt) {

	switch (fstFlg) {

	case true: {
//	if (fstFlg) {
//		this->_coin->ClearAll();
		//this->setScale(0.1f);
		fstFlg = false;
		this->_baseNode->chsFlg = false;
		this->_drawNode->clear();

		for (SelTag* tg : this->_selTags) {
			tg->getSelMemo()->setVisible(false);
			tg->ClearCoin();
		}
//	} else {
		break;
	}
	case false: {

		if ((this->_baseNode->getPosition().x) > moveLeftX) {
			this->_baseNode->setPosition(moveLeftX, 0);
			this->_selYaziDown->setVisible(false);
			this->_selYaziTop->setVisible(true);
			int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
			int b = SetPitch;
			Y = a / b;
			this->setSelState(SelState::STOP);
			this->fstFlg = true;
			moveVelo = 0;
		} else if ((this->_baseNode->getPosition().x) < -SetPitch * (MaxLevl - 1) + moveLeftX) {
			this->_baseNode->setPosition(-SetPitch * (MaxLevl - 1) + moveLeftX, 0);
			this->_selYaziDown->setVisible(true);
			this->_selYaziTop->setVisible(false);
			int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
			int b = SetPitch;
			Y = a / b;
			Y--;
			this->setSelState(SelState::STOP);
			this->fstFlg = true;
			moveVelo = 0;
		} else {

			this->_selYaziDown->setVisible(true);
			this->_selYaziTop->setVisible(true);

			if (moveVelo > 1000) {
				moveVelo -= (1500 * dt);

				if (moveVelo < 400) {
					moveVelo = 400;
				}

				this->_baseNode->setPosition(this->_baseNode->getPosition().x + moveVelo * dt, 0);

			} else if (moveVelo < -1000) {
				moveVelo += (1500 * dt);

				if (moveVelo > -400) {
					moveVelo = -400;
				}

				this->_baseNode->setPosition(this->_baseNode->getPosition().x + moveVelo * dt, 0);

			} else {

				switch (fstSet_) {

				case false: {
					fstSet_ = true;
					moveVelo = 400;
					int a = (int) (this->_baseNode->getPosition().x - SetPitch / 2);
					int b = SetPitch;
					Y = a / b;
					this->_baseNode->setPosition(
							this->_baseNode->ChaseA(Vec2(Y * SetPitch, 0), this->_baseNode->getPosition(),
									moveVelo, dt));
					break;
				}
				case true: {
					this->_baseNode->ChaseA(dt);
					if (this->_baseNode->chsFlg) {
						this->setSelState(SelState::STOP);
						this->fstFlg = true;
					}

					break;
				}

				}

			}
		}

		break;
	}

	}

}
void SelectScene::onStop(float dt) {
	if (fstFlg) {

		//this->setScale(0.1f);
		fstFlg = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btnon.mp3");
		for (SelTag* tg : this->_selTags) {

			tg->getSelMemo()->setVisible(false);
			if ((tg->getPosition() - ctPt + this->_baseNode->getPosition()).length() < 50) {

				//一瞬光る
				tg->getSelWaku()->setVisible(true);
				auto delay_ = DelayTime::create(0.3f);
				auto func_ = CallFuncN::create([this](Node * nd) {
					SelTag* tg=dynamic_cast<SelTag*>(nd);
					tg->getSelWaku()->setVisible(false);
				});
				auto seq_ = Sequence::create(delay_, func_, NULL);
				tg->runAction(seq_);

				this->setSel4(tg);
				this->getGameDeta()->SetSelectCource(tg->Level_);
				this->DrawCource2(this->getSel4()->Level_);
			}
		}

	} else {

		if (this->getSel4()) {

//			const char *str = "this->getSel4()->SetMemoText(xxx";
//			log("%s", str);
//色確認用
//			this->getSel4()->SetMemoText(
//					StringUtils::toString((int) this->r) + "_" + StringUtils::toString((int) this->g) + "_"
//							+ StringUtils::toString((int) this->b)+"\n\n\n");
			if (this->getGameDeta()->MaxCourceLevel != this->getSel4()->Level_) {
				this->getSel4()->SetMemoText(
						"高低差:"
								+ StringUtils::toString(
										(int) ((this->getGameDeta()->dotDrawPt[0].y
												- this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt
														- 1].y)) / 100) + "m\n" + "距離:"
								+ StringUtils::toString(
										(int) ((this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt
												- 1] - this->getGameDeta()->dotDrawPt[0]).length()) / 100)
								+ "m\n" + "難易度：" + StringUtils::toString((int) this->getGameDeta()->cLvl)
								+ "\n" + "基準ﾀｲﾑ："
								+ StringUtils::toString(
										(int) this->getGameDeta()->getClearTime(
												this->getGameDeta()->GetSelectCource())) + "秒\n" + "ﾍﾞｽﾄﾀｲﾑ:"
								+ StringUtils::format("%.1f",
										(float) this->getGameDeta()->getStageTime(
												this->getGameDeta()->GetSelectCource())) + "秒\n獲得ｺｲﾝ:  x"
								+ StringUtils::toString(
										(int) this->_gameDeta->getStageCoin(this->getSel4()->Level_)));	//+ "\n"

				if (this->_gameDeta->GetDebug()) {

					this->getSel4()->SetMemoText(
							"高低差:"
									+ StringUtils::toString(
											(int) (this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[1]].y
													- this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[2]].y)
													/ 100) + "m\n" + "距離:"
									+ StringUtils::toString(
											(int) (this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[2]]
													- this->getGameDeta()->dotDrawPt[this->_gameDeta->dotPointNo[1]]).length()
													/ 100) + "m\n" + "難易度："
									+ StringUtils::toString((int) this->getGameDeta()->cLvl) + "\n"
									+ "ﾍﾞｽﾄﾀｲﾑ:"
									+ StringUtils::format("%.1f",
											(float) this->getGameDeta()->getStageTime(
													this->getGameDeta()->GetSelectCource())) + "秒\n獲得ｺｲﾝ:  x"
									+ StringUtils::toString(
											(int) this->_gameDeta->getStageCoin(this->getSel4()->Level_)));

				}

//			this->getSel4()->SetMemoText(
//					StringUtils::toString((int) this->r) + "_" + StringUtils::toString((int) this->g) + "_"
//							+ StringUtils::toString((int) this->b) + "\n"
//							+ StringUtils::format("%.3f", (float) this->h_) + "_"
//							+ StringUtils::format("%.3f", (float) this->s_) + "_"
//							+ StringUtils::format("%.3f", (float) this->v_) + "\n\n");

			} else {
				this->getSel4()->SetMemoText(
						"ﾗﾝﾀﾞﾑ生成ｺｰｽ\n高低差:"
								+ StringUtils::toString(
										(int) ((this->getGameDeta()->dotDrawPt[0].y
												- this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt
														- 1].y)) / 100) + "m\n" + "距離:"
								+ StringUtils::toString(
										(int) ((this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt
												- 1] - this->getGameDeta()->dotDrawPt[0]).length()) / 100)
								+ "m\n" + "難易度：" + StringUtils::toString((int) this->getGameDeta()->cLvl)
								+ "\n" + "基準ﾀｲﾑ："
								+ StringUtils::toString(
										(int) this->getGameDeta()->getClearTime(
												this->getGameDeta()->GetSelectCource())) + "秒\n" + "ﾍﾞｽﾄﾀｲﾑ:"
								+ StringUtils::format("%.1f",
										(float) this->getGameDeta()->getStageTime(
												this->getGameDeta()->GetSelectCource())) + "秒\n獲得ｺｲﾝ:  x"
								+ StringUtils::toString(
										(int) this->_gameDeta->getStageCoin(this->getSel4()->Level_)));	//+ "\n"
			}

			this->getSel4()->getSelMemo()->setVisible(true);
		}

	}
}

void SelectScene::setUpdateAction(std::function<void(SelectScene*, float)> action) {

	this->unscheduleUpdate();
	this->onUpDateListener = action;
	this->scheduleUpdate();

}

void SelectScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {

		UserDefault::getInstance()->setIntegerForKey("SELECT_Y", (int) this->getBaseNode()->getPosition().y);

		auto scene = TitleScene::createScene();
		auto transition = TransitionCrossFade::create(0.5, scene);
		Director::getInstance()->replaceScene(transition);
	}
}

void SelectScene::onEnterTransitionDidFinish() {

	if (UserDefault::getInstance()->getBoolForKey("bgmkey", true)) {
		//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
		//			"bgm.mp3", true);
	}

	this->SetTouchListener();
	this->scheduleUpdate();

}

