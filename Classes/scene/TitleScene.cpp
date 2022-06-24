#include "TitleScene.h"
#include "scene/TestScene.h"
#include "scene/TestPhysicsScene.h"
#include "scene/GameStage.h"

TitleScene::TitleScene():
_gameTitle(NULL), _startBtn(NULL), _howtoBtn(NULL), _resultBtn(NULL), _menu(NULL),_btn1(NULL)
{}

TitleScene::~TitleScene() {
    CC_SAFE_RELEASE_NULL(_gameTitle);
    CC_SAFE_RELEASE_NULL(_startBtn);
    CC_SAFE_RELEASE_NULL(_howtoBtn);
    CC_SAFE_RELEASE_NULL(_resultBtn);
    CC_SAFE_RELEASE_NULL(_btn1);
    
}

Scene* TitleScene::createScene() {
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init() {
    if (!GameScene::init()) {
        return false;
    }
    this->setBackGroundColor();
    this->setGameTitle(Sprite::create("title5.png"));
    this->mountNode(this->getGameTitle(), this->ctPt + Vec2(0,20), OBJ_LAYER_TOP);
    this->setStartBtn(MenuItemImage::create("start_btn.png", "start_btn_p.png",[this](Ref* ref) {
        this->transitonScene(GameStage::createScene());
    }));
    this->setHowToBtn(MenuItemImage::create("howto_btn.png", "howto_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestPhysicsScene::createScene());
    }));
    this->setResultBtn(MenuItemImage::create("ranking_btn.png", "ranking_btn_p.png",[this](Ref* ref) {
        this->transitonScene(TestScene::createScene());
    }));
    this->setMenu(Menu::create(this->getStartBtn(),this->getHowToBtn(),this->getResultBtn(), NULL));
    getMenu()->alignItemsHorizontallyWithPadding(20);
    this->mountNode(this->getMenu(), this->ctPt + Vec2(0,-20), OBJ_LAYER_TOP);
    
    
    setBtn1(Button::create());
    
    getBtn1()->setButton(Size(40,20),"？");
    mountNode(getBtn1(), ctPt+Vec2(0,100), OBJ_LAYER_TOP);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish() {
    GameScene::onEnterTransitionDidFinish();
//    getAD()->AdShow(false, true, false, false, false, false);
    // todo
}

void TitleScene::update(float dt) {
    // todo
}

/** パラメータサンプル
this->setGameTitle(Sprite::create());
this->getGameTitle();
this->setStartBtn(MenuItemImage::create());
this->getStartBtn();
this->setHowToBtn(MenuItemImage::create());
this->getHowToBtn();
this->setResultBtn(MenuItemImage::create());
this->getResultBtn();
this->setSMenu(Menu::create());
this->getSMenu();
*/
