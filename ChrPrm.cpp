#include "cocos2d.h"
#include "ChrPrm.h"
#include "cmath"

//#define ARRAY_LENGTH(array) (sizeof(array) / sizeof(array[0]))
USING_NS_CC;

// on "init" you need to initialize your instance
ChrPrm::ChrPrm() {
}
ChrPrm::~ChrPrm() {
}

ChrPrm * ChrPrm::create(){

	ChrPrm * chr=new ChrPrm();

	if(chr){

		chr->autorelease();
		return chr;

	}else{
		CC_SAFE_DELETE(chr); return NULL;
}

}

bool ChrPrm::init() {
 //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ChrPrms.plist");


/*
 frameSize = Size(this->getContentSize().width,
 this->getContentSize().height);

 auto director = Director::getInstance();
 auto winSize = director->getWinSize();

 this->setTextureRect(Rect(0, 0, frameSize.width, frameSize.height));

 //this->SetChrPrmA(ChrPrmType::C01);
 */
//	this->setVisible(false);
//this->SetChrPrm(ChrPrmType::C00);
return true;
}

