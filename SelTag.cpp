#include "cocos2d.h"
#include "SelTag.h"

#include "cmath"

USING_NS_CC;

//const int FRAME_COUNT = 1;
/*
 const int ballCatg = 1 << 0;
 const int SelTagCatg = 1 << 1;
 const int courceCatg = 1 << 2;
 const int startCatg = 1 << 3;
 const int goalCatg = 1 << 4;
 */
// on "init" you need to initialize your instance
SelTag::SelTag() :
		_lvlLabel(NULL), _kagi(NULL), _selMemo(NULL), _lokMemo(NULL), _selBtn(NULL), _menu(NULL), _selWaku(
		NULL), _dot(NULL), _gameDeta(NULL), _bachNode(NULL), _drawNode(NULL), _rdTx(NULL), _coin(NULL) {
}
SelTag::~SelTag() {
	CC_SAFE_RELEASE_NULL(_lvlLabel);
	CC_SAFE_RELEASE_NULL(_kagi);
	CC_SAFE_RELEASE_NULL(_selMemo);
	CC_SAFE_RELEASE_NULL(_lokMemo);
	CC_SAFE_RELEASE_NULL(_selBtn);
	CC_SAFE_RELEASE_NULL(_menu);
	CC_SAFE_RELEASE_NULL(_selWaku);
	CC_SAFE_RELEASE_NULL(_dot);
	CC_SAFE_RELEASE_NULL(_gameDeta);
	CC_SAFE_RELEASE_NULL(_bachNode);
	CC_SAFE_RELEASE_NULL(_drawNode);
	CC_SAFE_RELEASE_NULL(_rdTx);
	CC_SAFE_RELEASE_NULL(_coin);
}
bool SelTag::init() {

	if (!Sprite::initWithFile("levelwaku3.png")) {
		return false;
	}
//	this->setOpacity(0);

	ccBlendFunc blend;
	blend.src = GL_ZERO;
	blend.dst = GL_SRC_COLOR;
	this->setBlendFunc(blend);


	wakuSize.setSize(this->getContentSize().width, this->getContentSize().height);
	ctPt.set(wakuSize.width / 2, wakuSize.height / 2);
	TTFConfig ttfConfig2("HGRPP1.TTC", 80, GlyphCollection::DYNAMIC);

	this->setLvlLabel(Label::createWithTTF(ttfConfig2, "LEVELSELECT"));
	this->_lvlLabel->setAnchorPoint(Vec2(0, 1));
	this->_lvlLabel->setAlignment(TextHAlignment::LEFT);
	this->_lvlLabel->setColor(Color3B::WHITE);
//	this->_lvlLabel->enableOutline(Color4B::RED, 2);
//	this->_lvlLabel->enableGlow(Color4B::WHITE);
	this->_lvlLabel->setPosition(50, 770);

	this->addChild(_lvlLabel, 1);

	TTFConfig ttfConfig3("HGRPP1.TTC", 40, GlyphCollection::DYNAMIC);

	this->setSelMemo(Label::createWithTTF(ttfConfig3, "SELMEMO"));
	_selMemo->setColor(Color3B::WHITE);
	_selMemo->setAnchorPoint(Vec2(0, 0));
	//_atai->setAnchorPoint(Vec2::ZERO);
	_selMemo->setAlignment(TextHAlignment::LEFT);
	_selMemo->setPosition(Vec2(120, 25));
	this->addChild(_selMemo, 2);
	TTFConfig ttfConfig4("HGRPP1.TTC", 80, GlyphCollection::DYNAMIC);
	this->setLokMemo(Label::createWithTTF(ttfConfig3, "ロックメモ\nミッションを\nクリヤしてね！"));
	_lokMemo->setColor(Color3B::RED);
	_lokMemo->setAnchorPoint(Vec2(0.5, 0.5));
	//_atai->setAnchorPoint(Vec2::ZERO);
	_lokMemo->setAlignment(TextHAlignment::LEFT);
	_lokMemo->setPosition(ctPt);
	this->addChild(_lokMemo, 2);

	//ｺｲﾝを作成
	this->setCoin(SpritePool::create(coinCnt_, "coin.png"));
	for (int i = 0; i < coinCnt_; i++) {

		auto sp = this->_coin->pop();
		sp->setVisible(false);
		this->addChild(sp, 2);

	}

//	this->setSelBtn(MenuItemImage::create("levelwaku.png", "levelwaku2.png", [this](Ref* ref) {
//
//		UserDefault::getInstance()->setIntegerForKey("LEVEL", this->Level_);
//		UserDefault::getInstance()->setIntegerForKey("SELECT_Y", (int) this->getParent()->getPosition().y);
//		const char *str0 = "SelTag_Push";
//		log("%s", str0);
//		auto scene=MainScene::createScene();
//		auto transition=TransitionCrossFade::create(0.8f,scene);
//		Director::getInstance()->replaceScene(transition);
//	}));
//	this->setMenu(Menu::create(_selBtn, NULL));
//	this->_menu->setPosition(ctPt);
//	this->addChild(_menu, 1);

	this->setSelWaku(Sprite::create("levelwaku2.png"));
	this->_selWaku->setPosition(ctPt);
	this->_selWaku->setVisible(false);
	this->addChild(this->_selWaku, 1);

	this->setKagi(Sprite::create("lock.png"));
	this->_kagi->setRotation(-45);
	this->_kagi->setPosition(30, wakuSize.height - 30);
	this->addChild(this->_kagi, 1);

	this->setBachNode(CCSpriteBatchNode::create("dot3.png"));
//	 Size size = Director::getInstance()->getVisibleSize();
//	this->setRdTx(RenderTexture::create(size.width,size.height));
//	this->addChild(_rdTx, 4);

	this->setDrawNode(DrawNode::create());
	this->addChild(_drawNode, 4);

	this->SetLock(false);
	this->SetLevel(1);
	return true;
}

void SelTag::ClearCoin() {
	//ｺｲﾝを非表示する。
	for (int i = 0; i < coinCnt_; i++) {

		Sprite* sp = this->_coin->getMember().at(i);
		sp->setVisible(false);
		sp->setPosition(Vec2(-50, wakuSize.height + 10));
	}

}
void SelTag::ShowCoin2() {
	//ｺｲﾝを表示する。

	this->ClearCoin();

	int coinCnt_ = 1;

	if (coinCnt_ > 0) {

		Vec2 stPt;
		float w = (wakuSize.width - 80) / (coinCnt_);

		stPt.set(298, 44);
		for (int i = 0; i < coinCnt_; i++) {

			auto fade_ = FadeIn::create(0.5f);
			auto delay_ = DelayTime::create((float) i / (float) 20);
			auto move_ = MoveTo::create(0.1f, stPt);
			auto seq_ = Sequence::create(delay_, Spawn::create(fade_, move_, NULL), NULL);
			Sprite* sp = this->_coin->getMember().at(i);
			sp->setVisible(true);
			sp->setOpacity(0);
			sp->setPosition(stPt);
			sp->runAction(fade_);
			sp->setScale(0.45f);
			stPt += Vec2(-w, 0);

		}
	}
//	const char *str3 = "SelTag::ShowCoin()_3";
//	log("%s", str3);

}
void SelTag::ShowCoin() {
	//ｺｲﾝを表示する。

	this->ClearCoin();

	int coinCnt_ = this->_gameDeta->getStageCoin(this->Level_);

	if (coinCnt_ > 0) {

		Vec2 stPt;
		float w = (wakuSize.width - 80) / (coinCnt_);

		stPt.set(wakuSize.width / 2 + w / 2 * coinCnt_, 200);
		for (int i = 0; i < coinCnt_; i++) {

			auto fade_ = FadeIn::create(0.5f);
			auto delay_ = DelayTime::create((float) i / (float) 20);
			auto move_ = MoveTo::create(0.1f, stPt);
			auto seq_ = Sequence::create(delay_, Spawn::create(fade_, move_, NULL), NULL);
			Sprite* sp = this->_coin->getMember().at(i);
			sp->setVisible(true);
			sp->setOpacity(0);
			sp->setPosition(stPt);
			sp->runAction(fade_);
			stPt += Vec2(-w, 0);

		}
	}
	const char *str3 = "SelTag::ShowCoin()_3";
	log("%s", str3);

}
void SelTag::SetLevel(int i) {

	this->getLvlLabel()->setString("コース:" + StringUtils::toString((int) i));
	Level_ = i;

	if (this->_gameDeta) {
		if (this->_gameDeta->GetClearCource() >= Level_) {
			this->SetLock(false);
		} else {
			this->SetLock(false); //デバック時はfalseにする
		}
	}

//	if (this->getGameDeta() && this->getDot()) {
//		this->DrawCource2(i);
//	}

}
void SelTag::DrawCource(int level) {

	//コースを描く。
	const char *str0 = "SelTag::DrawCource_1";
	log("%s", str0);
	this->getGameDeta()->MadeCourceFromCourceNo(this->_dot, level);
	const char *str1 = "SelTag::DrawCource_2";
	log("%s", str1);
	this->getGameDeta()->SetDrawPosition();
	const char *str2 = "SelTag::DrawCource_3";
	log("%s", str2);

	float dw_ = 20;
	float scale = (wakuSize.width - 2 * dw_)
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
		const char *str3 = "this->_cMember.at(i)->setVisible(false);";
		log("%s", str3);
	}

}
void SelTag::DrawCource2(int level) {

	//コースを描く。
	const char *str0 = "SelTag::DrawCource_1";
	log("%s", str0);
	this->getGameDeta()->MadeCourceFromCourceNo(this->_dot, level);
	const char *str1 = "SelTag::DrawCource_2";
	log("%s", str1);
	this->getGameDeta()->SetDrawPosition();
	const char *str2 = "SelTag::DrawCource_3";
	log("%s", str2);

	float dw_ = 20;
	float scale = (wakuSize.width - 2 * dw_)
			/ (this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1].x
					- this->getGameDeta()->dotDrawPt[0].x);
	Vec2 centerPt;
	centerPt.set(
			(this->getGameDeta()->dotDrawPt[this->getGameDeta()->dotDrawCnt - 1]
					+ this->getGameDeta()->dotDrawPt[0]) / 2);
	centerPt *= scale;
	centerPt -= ctPt;
	centerPt *= -1;
	this->_drawNode->clear();
//	this->_rdTx->begin();

//	int cnt_ = this->_cMember.size();

	for (int i = 0; i < this->getGameDeta()->dotDrawCnt - 20; i++) {

		if (i % 20 == 0) {
			this->_drawNode->drawSegment((this->getGameDeta()->dotDrawPt[i]) * scale + centerPt,
					(this->getGameDeta()->dotDrawPt[i + 20]) * scale + centerPt, 36 * scale, Color4F::BLACK);
		}
	}

//	this->_drawNode->visit(); // RenderTextureにレンダリング
//	this->_rdTx->end();
}

void SelTag::SetLock(bool lok_) {
//ロックするしない。
	if (lok_) {
//		this->_menu->setVisible(false);
		this->getKagi()->setVisible(true);
		this->setSelState(SelState::LOCK);
		this->getSelMemo()->setVisible(true);
		this->getLokMemo()->setVisible(false);
	} else {
//		this->_menu->setVisible(true);
		this->getKagi()->setVisible(false);
		this->setSelState(SelState::UNLOCK);
		this->getSelMemo()->setVisible(true);
		this->getLokMemo()->setVisible(false);
	}

}

void SelTag::SetMemoText(std::string txt_) {
	this->getSelMemo()->setString("" + txt_);
}
void SelTag::SetLockText(std::string txt_) {
	this->getLokMemo()->setString("" + txt_);
}

bool SelTag::SelectTag(Vec2 pt_) {

	Vec2 ptp;
	ptp.set(pt_);
	Rect rect = this->getBoundingBox();
//touch->getworldPosition();
	if (rect.containsPoint(ptp)) {
		this->touchFlg_ = true;
	} else {
		this->touchFlg_ = false;
	}

	return touchFlg_;

}
void SelTag::TouchOn(Vec2 pt) {

	this->_point1.set(pt);
	this->_point2.set(pt);
	this->SelectTag(pt);

	const char *str0 = "SelTag::TouchOn";
	log("%s", str0);

	switch (this->getSelState()) {

	case SelState::LOCK: {
		if (this->touchFlg_) {
			this->getLokMemo()->setVisible(true);
			this->getSelMemo()->setVisible(false);
		}
		break;

	}
	case SelState::UNLOCK: {

		if (this->touchFlg_) {
			this->_selWaku->setVisible(true);
		}

		break;

	}
	}

}
void SelTag::Swaip(Vec2 pt1, Vec2 pt2) {

//	const char *str = "Pen::Swaip";
//	log("%s", str);

	this->_point1.set(pt1);
	this->_point2.set(pt2);
	this->SelectTag(pt2);
	switch (this->getSelState()) {

	case SelState::LOCK: {
		if (!this->touchFlg_) {
			this->getLokMemo()->setVisible(false);
			this->getSelMemo()->setVisible(true);
		}
		break;

	}
	case SelState::UNLOCK: {
		if (!this->touchFlg_ || (this->_point1 - this->_point2).length() > 50) {
			this->touchFlg_ = false;
			this->_selWaku->setVisible(false);
		}
		break;

	}

	}

}
void SelTag::TouchOff() {

	this->_point1.set(Vec2::ZERO);
	this->_point2.set(Vec2::ZERO);
	switch (this->getSelState()) {

	case SelState::LOCK: {
		this->getLokMemo()->setVisible(false);
		this->getSelMemo()->setVisible(true);
		break;

	}
	case SelState::UNLOCK: {

		if (this->touchFlg_) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("btnon.mp3");
			UserDefault::getInstance()->setBoolForKey("SAMECOURCE", false);
			UserDefault::getInstance()->setIntegerForKey("LEVEL", this->Level_);
			this->getGameDeta()->SetSelectCource(this->Level_);

			UserDefault::getInstance()->setIntegerForKey("SELECT_Y",
					(int) this->getParent()->getPosition().y);
			const char *str0 = "SelTag_Push";
			log("%s", str0);

			//ここで分岐
			if (this->Level_ <= 100) {
				auto scene = MainScene::createScene();
				auto transition = TransitionCrossFade::create(0.5f, scene);
				Director::getInstance()->replaceScene(transition);
			}

		}

		break;

	}

	}
	touchFlg_ = false;
}
void SelTag::update(float dt) {

}

