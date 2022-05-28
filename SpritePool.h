#ifndef __piyopiyo__SpritePool__
#define __piyopiyo__SpritePool__

#include "cocos2d.h"
USING_NS_CC;

class SpritePool: public cocos2d::Ref {

	SpritePool();
	virtual ~SpritePool();

public:

	static SpritePool* create(int size, const std::string& filename);
	bool init(int size, const std::string& filename);

	void push(Sprite* ig);
	int getSize();
	Sprite* pop();

	void ClearAll();

CC_SYNTHESIZE_RETAIN(SpriteBatchNode*, _bachNode1,BachNode1)

	;CC_SYNTHESIZE(cocos2d::Vector<Sprite*>,_member,Member)
	;

protected:
	/* �v�[���̎��� */
	cocos2d::Vector<Sprite*> _pool;
};

#endif /* defined(__androidtest__EnemyPool__) */
