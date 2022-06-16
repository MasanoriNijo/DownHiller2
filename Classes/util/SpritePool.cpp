#include "SpritePool.h"
USING_NS_CC;

SpritePool::SpritePool() :
		_bachNode1(NULL) {

}
SpritePool::~SpritePool() {
	CC_SAFE_RELEASE_NULL(_bachNode1);
}

SpritePool* SpritePool::create(int size, const std::string& filename) {
	auto pool = new SpritePool();
	if (pool && pool->init(size, filename)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		return nullptr;
	}
}

bool SpritePool::init(int size, const std::string& filename) {

    this->setBachNode1(cocos2d::SpriteBatchNode::create(filename));

	for (int i = 0; i < size; i++) {
		auto sp_ = Sprite::createWithTexture(this->_bachNode1->getTexture());
		push(sp_);
	}
	return true;
}
void SpritePool::ClearAll() {

	while(_member.size()>0) {
		Sprite* sp_ = _member.at(_member.size() - 1);
		if(sp_->getParent()){
			sp_->removeFromParent();
		}
		sp_->stopAllActions();
		this->push(sp_);
		_member.popBack();
	}

}
void SpritePool::push(Sprite* ig) {
	_pool.pushBack(ig);
}

int SpritePool::getSize() {
	return (int)_pool.size();
}

Sprite* SpritePool::pop() {
	if (_pool.empty()) {
		return nullptr;
	}
	auto em = _pool.back();
	_pool.popBack();
	_member.pushBack(em);
	em->retain();
	return em;
}
