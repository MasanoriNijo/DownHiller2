#ifndef __nekozyaradon__KiraruPool__
#define __nekozyaradon__KiraruPool__

#include "cocos2d.h"

#include "Kiraru.h"
USING_NS_CC;
class KiraruPool: public cocos2d::Ref {

	KiraruPool();
	virtual ~KiraruPool();

public:
	static KiraruPool* create(int size);
	bool init(int size);
	void push(Kiraru* ft);
	int getSize();
	Kiraru* pop();

	void SetBodyMaterial(PhysicsMaterial material0_);
	void SetBodyMaterial_NoBound();CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode,BachNode)
	;CC_SYNTHESIZE(cocos2d::Vector<Kiraru*>,_member,Member)
	;

protected:
	/* �v�[���̎��� */
	cocos2d::Vector<Kiraru*> _pool;
};

#endif /* defined(__androidtest__KiraruPool__) */
