#include "Kiraru.h"
#include "KiraruPool.h"

USING_NS_CC;

KiraruPool::KiraruPool() :
		_bachNode(NULL) {

}
KiraruPool::~KiraruPool() {
	CC_SAFE_RELEASE_NULL(_bachNode);
}

KiraruPool* KiraruPool::create(int size) {
	auto pool = new KiraruPool();
	if (pool && pool->init(size)) {
		pool->autorelease();
		return pool;
	} else {
		CC_SAFE_DELETE(pool);
		return nullptr;
	}
}

bool KiraruPool::init(int size) {
	//wakka.pngKiraru.png
	this->setBachNode(CCSpriteBatchNode::create("points.png"));

	for (int i = 0; i < size; i++) {

		auto g_ = Kiraru::createWithTexture(_bachNode->getTexture());
		//auto g_ = Kiraru::create();
		// �g���I��������̃R�[���o�b�N��ݒ肷��
		g_->onFinishListener = [this](Kiraru* sender) {
			// �v�[���ɖ߂�

				_member.swap(sender,_member.back());
				_member.popBack();
				this->push(sender);
				sender->release();
			};

		// �\�����I�������e����폜�����悤�ɂ���I

		//g_->setAutoRemoveOnFinish(true);// 表示が終わったら自分を親から削除！
		// ��~��ԂŊi�[����
		//g_->stopSystem();

		push(dynamic_cast<Kiraru*>(g_));
	}
	return true;
}

void KiraruPool::push(Kiraru* ft) {
	_pool.pushBack(ft);
}
void KiraruPool::SetBodyMaterial_NoBound() {
	for (Kiraru* dt : _pool) {
		dt->material_.friction = 1.0f;
		dt->material_.restitution = 0;

	}

}

void KiraruPool::SetBodyMaterial(PhysicsMaterial material0_) {

	for (Kiraru* dt : _pool) {
		dt->material_ = material0_;

	}

}
int KiraruPool::getSize() {

	return _pool.size();

}

Kiraru* KiraruPool::pop() {
	if (_pool.empty()) {
		//CCLOG("�v�[������ł�!");
		return nullptr;
	}
	auto em = _pool.back();
	em->retain();
	_pool.popBack();
	_member.pushBack(em);
	//em->resetSystem();
	return em;
}
