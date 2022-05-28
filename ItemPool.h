
#ifndef __piyopiyo__ItemPool__
#define __piyopiyo__ItemPool__

#include "cocos2d.h"
#include "Item.h"

class ItemPool: public cocos2d::Ref {

	ItemPool();
	virtual ~ItemPool();

public:
	static ItemPool* create(int size);
	bool init(int size);
	void push(Item* ig);
	int getSize();
	Item* pop();

CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode1,BachNode1)
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode2,BachNode2)
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode3,BachNode3)
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode4,BachNode4)
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode5,BachNode5)
	;CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _bachNode6,BachNode6)

	;CC_SYNTHESIZE(cocos2d::Vector<Item*>,_member,Member)
	;

protected:
	/* �v�[���̎��� */
	cocos2d::Vector<Item*> _pool;
};

#endif /* defined(__androidtest__EnemyPool__) */
