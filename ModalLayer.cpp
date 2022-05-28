#include "ModalLayer.h"
#define kModalLayerPriority -1


ModalLayer::~ModalLayer() {

	auto dip = Director::getInstance()->getEventDispatcher();
	dip->removeEventListenersForTarget(this,false);
}


bool ModalLayer::init(){

	if(!Layer::init()){
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [](Touch *touch,Event*event)->bool{


	   return true;

	};
	auto dip = Director::getInstance()->getEventDispatcher();
	dip->addEventListenerWithSceneGraphPriority(listener, this);
	dip->setPriority(listener, kModalLayerPriority);

	return true;

}
