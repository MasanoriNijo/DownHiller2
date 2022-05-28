#include "Item.h"
#include "ItemPool.h"

USING_NS_CC;

ItemPool::ItemPool() :
		_bachNode1(NULL), _bachNode2(NULL), _bachNode3(NULL) , _bachNode4(NULL) , _bachNode5(NULL) , _bachNode6(NULL){

}
ItemPool::~ItemPool() {
	CC_SAFE_RELEASE_NULL(_bachNode1);
	CC_SAFE_RELEASE_NULL(_bachNode2);
	CC_SAFE_RELEASE_NULL(_bachNode3);
	CC_SAFE_RELEASE_NULL(_bachNode4);
	CC_SAFE_RELEASE_NULL(_bachNode5);
	CC_SAFE_RELEASE_NULL(_bachNode6);
}

ItemPool* ItemPool::create(int size) {
	auto pool = new ItemPool();
	if (pool && pool->init(size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		return nullptr;
	}
}

bool ItemPool::init(int size) {

	this->setBachNode1(cocos2d::CCSpriteBatchNode::create("hana.png"));
	this->setBachNode2(cocos2d::CCSpriteBatchNode::create("hana.png"));
	this->setBachNode3(cocos2d::CCSpriteBatchNode::create("hana.png"));
	this->setBachNode4(cocos2d::CCSpriteBatchNode::create("hana.png"));
	this->setBachNode5(cocos2d::CCSpriteBatchNode::create("startflg.png"));
	this->setBachNode6(cocos2d::CCSpriteBatchNode::create("goalflg.png"));


	for (int i = 0; i < size; i++) {
		auto ig = Item::create();
		const char *str = "ItemPool::init";
		log("%s", str);
		ig->setTxter1(this->getBachNode1()->getTexture());
		ig->setTxter2(this->getBachNode2()->getTexture());
		ig->setTxter3(this->getBachNode3()->getTexture());
		ig->setTxter4(this->getBachNode4()->getTexture());
		ig->setTxter5(this->getBachNode5()->getTexture());
		ig->setTxter6(this->getBachNode6()->getTexture());


		ig->onFinishListener = [this](Item* sender) {
			// �v�[���ɖ߂�

				if(sender->getParent()!=NULL) {
					sender->removeFromParent();
				}

				_member.swap(sender,_member.back());
				_member.popBack();

				sender->stopAllActions();
				this->push(sender);
				sender->release();
			};

		// �\�����I�������e����폜�����悤�ɂ���I

		//em->setAutoRemoveOnFinish(true);
		// ��~��ԂŊi�[����
		//em->stopSystem();
		push(ig);
	}
	return true;
}

void ItemPool::push(Item* ig) {
	_pool.pushBack(ig);
}

int ItemPool::getSize() {

	return _pool.size();

}

Item* ItemPool::pop() {
	if (_pool.empty()) {
		//CCLOG("�v�[������ł�!");
		return nullptr;
	}
	auto em = _pool.back();
	_pool.popBack();
	_member.pushBack(em);

	em->retain();

	//em->resetSystem();
	return em;
}
