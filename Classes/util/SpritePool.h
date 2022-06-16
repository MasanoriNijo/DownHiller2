#ifndef __SPRITEPOOL_H__
#define __SPRITEPOOL_H__

#include "util/Const.h"
#include "cocos2d.h"
USING_NS_CC;

class SpritePool:Ref {

	SpritePool();
	virtual ~SpritePool();

public:

	static SpritePool* create(int size, const std::string& filename);
	bool init(int size, const std::string& filename);
	void push(Sprite* ig);
	int getSize();
	Sprite* pop();
	void ClearAll();
    CC_SYNTHESIZE_RETAIN(SpriteBatchNode*, _bachNode1,BachNode1);
    CC_SYNTHESIZE(Vector<Sprite*>,_member,Member);

protected:
	Vector<Sprite*> _pool;
};

#endif
