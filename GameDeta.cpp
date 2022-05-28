#include "GameDeta.h"

USING_NS_CC;

#include <string>
#include <fstream>
#include <vector>
// ヘッダファイルインクルード
//#include "cocos-ext.h"
#include "platform/android/jni/JniHelper.h"
// 呼び出すメソッドが書かれているパッケージ名とjavaクラス名
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"
#define TWEET "tweet"
#define OPENRNK "openRankPark"
#define SENDSCR "sendRankParkScore"
#define WRITEDETA "writeDeta"
#define READDETA "readDeta"

GameDeta::GameDeta() {
}
GameDeta::~GameDeta() {

}

GameDeta* GameDeta::create() {
	auto mdr = new GameDeta();
	if (mdr && mdr->init()) {
		mdr->autorelease();
		return mdr;
	} else {
		CC_SAFE_DELETE(mdr);
		return nullptr;
	}
}

bool GameDeta::init() {

	return true;
}

void GameDeta::SetDebug(bool flg_) {
	auto udf = UserDefault::getInstance();
	udf->setBoolForKey("DEBUG_", flg_);

}
bool GameDeta::GetDebug() {
	auto udf = UserDefault::getInstance();
	return udf->getBoolForKey("DEBUG_", false);
}

float GameDeta::getClearTime(int x) {
//基準タイムを算出
	switch (x) {

	case 1: {
		return 30.0f;
		break;
	}
	case 2: {
		return 30.0f;
		break;
	}
	case 3: {
		return 30.0f;
		break;
	}
	case 4: {
		return 30.0f;
		break;
	}
	case 5: {
		return 35.0f;
		break;
	}
	case 6: {
		return 35.0f;
		break;
	}
	case 7: {
		return 35.0f;
		break;
	}
	case 8: {
		return 35.0f;
		break;
	}
	case 9: {
		return 35.0f;
		break;
	}
	case 10: {
		return 38.0f;
		break;
	}
	case 11: {
		return 38.0f;
		break;
	}
	case 12: {
		return 38.0f;
		break;
	}
	case 13: {
		return 38.0f;
		break;
	}
	case 14: {
		return 40.0f;
		break;
	}
	case 15: {
		return 40.0f;
		break;
	}
	case 16: {
		return 40.0f;
		break;
	}
	case 17: {
		return 40.0f;
		break;
	}
	case 18: {
		return 40.0f;
		break;
	}
	case 19: {
		return 40.0f;
		break;
	}
	case 20: {
		return 40.0f;
		break;
	}
	case 21: {
		return 40.0f;
		break;
	}
	case 22: {
		return 40.0f;
		break;
	}
	case 23: {
		return 42.0f;
		break;
	}
	case 24: {
		return 43.0f;
		break;
	}
	case 25: {
		return 45.0f;
		break;
	}
	case 26: {
		return 45.0f;
		break;
	}
	case 27: {
		return 47.0f;
		break;
	}
	case 28: {
		return 47.0f;
		break;
	}
	case 29: {
		return 47.0f;
		break;
	}
	case 30: {
		return 40.0f;
		break;
	}
	case 31: {
		return 30.0f;
		break;
	}
	case 32: {
		return 30.0f;
		break;
	}
	case 33: {
		return 30.0f;
		break;
	}
	case 34: {
		return 30.0f;
		break;
	}
	case 35: {
		return 30.0f;
		break;
	}
	case 36: {
		return 30.0f;
		break;
	}
	case 37: {
		return 30.0f;
		break;
	}
	case 38: {
		return 30.0f;
		break;
	}
	case 39: {
		return 30.0f;
		break;
	}
	case 40: {
		return 30.0f;
		break;
	}
	case 41: {
		return 30.0f;
		break;
	}
	case 42: {
		return 30.0f;
		break;
	}
	case 43: {
		return 30.0f;
		break;
	}
	case 44: {
		return 30.0f;
		break;
	}
	case 45: {
		return 30.0f;
		break;
	}
	case 46: {
		return 30.0f;
		break;
	}
	case 47: {
		return 30.0f;
		break;
	}
	case 48: {
		return 30.0f;
		break;
	}
	case 49: {
		return 30.0f;
		break;
	}
	case 50: {
		return 30.0f;
		break;
	}
	case 51: {
		return 30.0f;
		break;
	}
	case 52: {
		return 30.0f;
		break;
	}
	case 53: {
		return 30.0f;
		break;
	}
	case 54: {
		return 30.0f;
		break;
	}
	case 55: {
		return 30.0f;
		break;
	}
	case 56: {
		return 30.0f;
		break;
	}
	case 57: {
		return 30.0f;
		break;
	}
	case 58: {
		return 30.0f;
		break;
	}
	case 59: {
		return 30.0f;
		break;
	}
	case 60: {
		return 30.0f;
		break;
	}
	case 61: {
		return 30.0f;
		break;
	}
	case 62: {
		return 30.0f;
		break;
	}
	case 63: {
		return 30.0f;
		break;
	}
	case 64: {
		return 30.0f;
		break;
	}
	case 65: {
		return 30.0f;
		break;
	}
	case 66: {
		return 30.0f;
		break;
	}
	case 67: {
		return 30.0f;
		break;
	}
	case 68: {
		return 30.0f;
		break;
	}
	case 69: {
		return 30.0f;
		break;
	}
	case 70: {
		return 30.0f;
		break;
	}
	case 71: {
		return 30.0f;
		break;
	}
	case 72: {
		return 30.0f;
		break;
	}
	case 73: {
		return 30.0f;
		break;
	}
	case 74: {
		return 30.0f;
		break;
	}
	case 75: {
		return 30.0f;
		break;
	}
	case 76: {
		return 30.0f;
		break;
	}
	case 77: {
		return 30.0f;
		break;
	}
	case 78: {
		return 30.0f;
		break;
	}
	case 79: {
		return 30.0f;
		break;
	}
	case 80: {
		return 30.0f;
		break;
	}
	case 81: {
		return 30.0f;
		break;
	}
	case 82: {
		return 30.0f;
		break;
	}
	case 83: {
		return 30.0f;
		break;
	}
	case 84: {
		return 30.0f;
		break;
	}
	case 85: {
		return 30.0f;
		break;
	}
	case 86: {
		return 30.0f;
		break;
	}
	case 87: {
		return 30.0f;
		break;
	}
	case 88: {
		return 30.0f;
		break;
	}
	case 89: {
		return 30.0f;
		break;
	}
	case 90: {
		return 30.0f;
		break;
	}
	case 91: {
		return 30.0f;
		break;
	}
	case 92: {
		return 30.0f;
		break;
	}
	case 93: {
		return 30.0f;
		break;
	}
	case 94: {
		return 30.0f;
		break;
	}
	case 95: {
		return 30.0f;
		break;
	}
	case 96: {
		return 30.0f;
		break;
	}
	case 97: {
		return 30.0f;
		break;
	}
	case 98: {
		return 30.0f;
		break;
	}
	case 99: {
		return 30.0f;
		break;
	}
	case 100: {
		return 30.0f;
		break;
	}

	}
	return 0;
}

int GameDeta::GetMaxGazeCnt() {
	//コインの取得数に応じて最大のゲージ数を変化させる。
	//最大50目盛り
	//初期：10目盛

	int x = this->getTotlCoin(100) * 0.2f;
	x += 10;

	if (x > 50) {
		x = 50;
	}
	return x;
}

int GameDeta::getTotlCoin(int x) {
	//コース番号ｘまでのトータルコイン数を取得

	int ttl = 0;

	for (int i = 1; i <= x; i++) {

		ttl += this->getStageCoin(i);

	}

	return ttl;

}

int GameDeta::getTotlCoin() {

	int ttl = 0;
	int x = MaxCourceLevel;
	for (int i = 1; i <= x; i++) {

		ttl += this->getStageCoin(i);

	}

	return ttl;

}

int GameDeta::JudgeCoinGet(int cNo, float time_) {
	//cNoをtime_でクリヤした時に、前回よりいくらコインをゲットしたか登録及び出力

	//基準タイムより、1秒短縮で、プラス1個コインゲット。

	if ((this->getClearTime(cNo) - time_) < 0) {
		return 0;
	}

	int cCnt_ = (int) (((float) this->getClearTime(cNo) - (float) time_) / 1);
	cCnt_++;
	int ans_ = 0;
	if (cCnt_ > this->getStageCoin(cNo)) {

		ans_ = cCnt_ - this->getStageCoin(cNo);
		this->setStageCoin(cNo, cCnt_);
	}
	return ans_;
}
bool GameDeta::JudgeClearTime(int cNo, float time_) {
	//記録更新の登録および判定
	if (time_ < this->getStageTime(cNo)) {
		this->setStageTime(cNo, time_);
		return true;
	} else {
		return false;
	}
}

void GameDeta::setStageTime(int x, float y) {

	auto udf = UserDefault::getInstance();
	switch (x) {

	case 1: {
		udf->setFloatForKey("CLEARTIME1", y);
		break;
	}
	case 2: {
		udf->setFloatForKey("CLEARTIME2", y);
		break;
	}
	case 3: {
		udf->setFloatForKey("CLEARTIME3", y);
		break;
	}
	case 4: {
		udf->setFloatForKey("CLEARTIME4", y);
		break;
	}
	case 5: {
		udf->setFloatForKey("CLEARTIME5", y);
		break;
	}
	case 6: {
		udf->setFloatForKey("CLEARTIME6", y);
		break;
	}
	case 7: {
		udf->setFloatForKey("CLEARTIME7", y);
		break;
	}
	case 8: {
		udf->setFloatForKey("CLEARTIME8", y);
		break;
	}
	case 9: {
		udf->setFloatForKey("CLEARTIME9", y);
		break;
	}
	case 10: {
		udf->setFloatForKey("CLEARTIME10", y);
		break;
	}
	case 11: {
		udf->setFloatForKey("CLEARTIME11", y);
		break;
	}
	case 12: {
		udf->setFloatForKey("CLEARTIME12", y);
		break;
	}
	case 13: {
		udf->setFloatForKey("CLEARTIME13", y);
		break;
	}
	case 14: {
		udf->setFloatForKey("CLEARTIME14", y);
		break;
	}
	case 15: {
		udf->setFloatForKey("CLEARTIME15", y);
		break;
	}
	case 16: {
		udf->setFloatForKey("CLEARTIME16", y);
		break;
	}
	case 17: {
		udf->setFloatForKey("CLEARTIME17", y);
		break;
	}
	case 18: {
		udf->setFloatForKey("CLEARTIME18", y);
		break;
	}
	case 19: {
		udf->setFloatForKey("CLEARTIME19", y);
		break;
	}
	case 20: {
		udf->setFloatForKey("CLEARTIME20", y);
		break;
	}
	case 21: {
		udf->setFloatForKey("CLEARTIME21", y);
		break;
	}
	case 22: {
		udf->setFloatForKey("CLEARTIME22", y);
		break;
	}
	case 23: {
		udf->setFloatForKey("CLEARTIME23", y);
		break;
	}
	case 24: {
		udf->setFloatForKey("CLEARTIME24", y);
		break;
	}
	case 25: {
		udf->setFloatForKey("CLEARTIME25", y);
		break;
	}
	case 26: {
		udf->setFloatForKey("CLEARTIME26", y);
		break;
	}
	case 27: {
		udf->setFloatForKey("CLEARTIME27", y);
		break;
	}
	case 28: {
		udf->setFloatForKey("CLEARTIME28", y);
		break;
	}
	case 29: {
		udf->setFloatForKey("CLEARTIME29", y);
		break;
	}
	case 30: {
		udf->setFloatForKey("CLEARTIME30", y);
		break;
	}
	case 31: {
		udf->setFloatForKey("CLEARTIME31", y);
		break;
	}
	case 32: {
		udf->setFloatForKey("CLEARTIME32", y);
		break;
	}
	case 33: {
		udf->setFloatForKey("CLEARTIME33", y);
		break;
	}
	case 34: {
		udf->setFloatForKey("CLEARTIME34", y);
		break;
	}
	case 35: {
		udf->setFloatForKey("CLEARTIME35", y);
		break;
	}
	case 36: {
		udf->setFloatForKey("CLEARTIME36", y);
		break;
	}
	case 37: {
		udf->setFloatForKey("CLEARTIME37", y);
		break;
	}
	case 38: {
		udf->setFloatForKey("CLEARTIME38", y);
		break;
	}
	case 39: {
		udf->setFloatForKey("CLEARTIME39", y);
		break;
	}
	case 40: {
		udf->setFloatForKey("CLEARTIME40", y);
		break;
	}
	case 41: {
		udf->setFloatForKey("CLEARTIME41", y);
		break;
	}
	case 42: {
		udf->setFloatForKey("CLEARTIME42", y);
		break;
	}
	case 43: {
		udf->setFloatForKey("CLEARTIME43", y);
		break;
	}
	case 44: {
		udf->setFloatForKey("CLEARTIME44", y);
		break;
	}
	case 45: {
		udf->setFloatForKey("CLEARTIME45", y);
		break;
	}
	case 46: {
		udf->setFloatForKey("CLEARTIME46", y);
		break;
	}
	case 47: {
		udf->setFloatForKey("CLEARTIME47", y);
		break;
	}
	case 48: {
		udf->setFloatForKey("CLEARTIME48", y);
		break;
	}
	case 49: {
		udf->setFloatForKey("CLEARTIME49", y);
		break;
	}
	case 50: {
		udf->setFloatForKey("CLEARTIME50", y);
		break;
	}
	case 51: {
		udf->setFloatForKey("CLEARTIME51", y);
		break;
	}
	case 52: {
		udf->setFloatForKey("CLEARTIME52", y);
		break;
	}
	case 53: {
		udf->setFloatForKey("CLEARTIME53", y);
		break;
	}
	case 54: {
		udf->setFloatForKey("CLEARTIME54", y);
		break;
	}
	case 55: {
		udf->setFloatForKey("CLEARTIME55", y);
		break;
	}
	case 56: {
		udf->setFloatForKey("CLEARTIME56", y);
		break;
	}
	case 57: {
		udf->setFloatForKey("CLEARTIME57", y);
		break;
	}
	case 58: {
		udf->setFloatForKey("CLEARTIME58", y);
		break;
	}
	case 59: {
		udf->setFloatForKey("CLEARTIME59", y);
		break;
	}
	case 60: {
		udf->setFloatForKey("CLEARTIME60", y);
		break;
	}
	case 61: {
		udf->setFloatForKey("CLEARTIME61", y);
		break;
	}
	case 62: {
		udf->setFloatForKey("CLEARTIME62", y);
		break;
	}
	case 63: {
		udf->setFloatForKey("CLEARTIME63", y);
		break;
	}
	case 64: {
		udf->setFloatForKey("CLEARTIME64", y);
		break;
	}
	case 65: {
		udf->setFloatForKey("CLEARTIME65", y);
		break;
	}
	case 66: {
		udf->setFloatForKey("CLEARTIME66", y);
		break;
	}
	case 67: {
		udf->setFloatForKey("CLEARTIME67", y);
		break;
	}
	case 68: {
		udf->setFloatForKey("CLEARTIME68", y);
		break;
	}
	case 69: {
		udf->setFloatForKey("CLEARTIME69", y);
		break;
	}
	case 70: {
		udf->setFloatForKey("CLEARTIME70", y);
		break;
	}
	case 71: {
		udf->setFloatForKey("CLEARTIME71", y);
		break;
	}
	case 72: {
		udf->setFloatForKey("CLEARTIME72", y);
		break;
	}
	case 73: {
		udf->setFloatForKey("CLEARTIME73", y);
		break;
	}
	case 74: {
		udf->setFloatForKey("CLEARTIME74", y);
		break;
	}
	case 75: {
		udf->setFloatForKey("CLEARTIME75", y);
		break;
	}
	case 76: {
		udf->setFloatForKey("CLEARTIME76", y);
		break;
	}
	case 77: {
		udf->setFloatForKey("CLEARTIME77", y);
		break;
	}
	case 78: {
		udf->setFloatForKey("CLEARTIME78", y);
		break;
	}
	case 79: {
		udf->setFloatForKey("CLEARTIME79", y);
		break;
	}
	case 80: {
		udf->setFloatForKey("CLEARTIME80", y);
		break;
	}
	case 81: {
		udf->setFloatForKey("CLEARTIME81", y);
		break;
	}
	case 82: {
		udf->setFloatForKey("CLEARTIME82", y);
		break;
	}
	case 83: {
		udf->setFloatForKey("CLEARTIME83", y);
		break;
	}
	case 84: {
		udf->setFloatForKey("CLEARTIME84", y);
		break;
	}
	case 85: {
		udf->setFloatForKey("CLEARTIME85", y);
		break;
	}
	case 86: {
		udf->setFloatForKey("CLEARTIME86", y);
		break;
	}
	case 87: {
		udf->setFloatForKey("CLEARTIME87", y);
		break;
	}
	case 88: {
		udf->setFloatForKey("CLEARTIME88", y);
		break;
	}
	case 89: {
		udf->setFloatForKey("CLEARTIME89", y);
		break;
	}
	case 90: {
		udf->setFloatForKey("CLEARTIME90", y);
		break;
	}
	case 91: {
		udf->setFloatForKey("CLEARTIME91", y);
		break;
	}
	case 92: {
		udf->setFloatForKey("CLEARTIME92", y);
		break;
	}
	case 93: {
		udf->setFloatForKey("CLEARTIME93", y);
		break;
	}
	case 94: {
		udf->setFloatForKey("CLEARTIME94", y);
		break;
	}
	case 95: {
		udf->setFloatForKey("CLEARTIME95", y);
		break;
	}
	case 96: {
		udf->setFloatForKey("CLEARTIME96", y);
		break;
	}
	case 97: {
		udf->setFloatForKey("CLEARTIME97", y);
		break;
	}
	case 98: {
		udf->setFloatForKey("CLEARTIME98", y);
		break;
	}
	case 99: {
		udf->setFloatForKey("CLEARTIME99", y);
		break;
	}
	case 100: {
		udf->setFloatForKey("CLEARTIME100", y);
		break;
	}

	}
}

float GameDeta::getStageTime(int x) {
	auto udf = UserDefault::getInstance();
	switch (x) {

	case 1: {
		return udf->getFloatForKey("CLEARTIME1", 1000);
		break;
	}
	case 2: {
		return udf->getFloatForKey("CLEARTIME2", 1000);
		break;
	}
	case 3: {
		return udf->getFloatForKey("CLEARTIME3", 1000);
		break;
	}
	case 4: {
		return udf->getFloatForKey("CLEARTIME4", 1000);
		break;
	}
	case 5: {
		return udf->getFloatForKey("CLEARTIME5", 1000);
		break;
	}
	case 6: {
		return udf->getFloatForKey("CLEARTIME6", 1000);
		break;
	}
	case 7: {
		return udf->getFloatForKey("CLEARTIME7", 1000);
		break;
	}
	case 8: {
		return udf->getFloatForKey("CLEARTIME8", 1000);
		break;
	}
	case 9: {
		return udf->getFloatForKey("CLEARTIME9", 1000);
		break;
	}
	case 10: {
		return udf->getFloatForKey("CLEARTIME10", 1000);
		break;
	}
	case 11: {
		return udf->getFloatForKey("CLEARTIME11", 1000);
		break;
	}
	case 12: {
		return udf->getFloatForKey("CLEARTIME12", 1000);
		break;
	}
	case 13: {
		return udf->getFloatForKey("CLEARTIME13", 1000);
		break;
	}
	case 14: {
		return udf->getFloatForKey("CLEARTIME14", 1000);
		break;
	}
	case 15: {
		return udf->getFloatForKey("CLEARTIME15", 1000);
		break;
	}
	case 16: {
		return udf->getFloatForKey("CLEARTIME16", 1000);
		break;
	}
	case 17: {
		return udf->getFloatForKey("CLEARTIME17", 1000);
		break;
	}
	case 18: {
		return udf->getFloatForKey("CLEARTIME18", 1000);
		break;
	}
	case 19: {
		return udf->getFloatForKey("CLEARTIME19", 1000);
		break;
	}
	case 20: {
		return udf->getFloatForKey("CLEARTIME20", 1000);
		break;
	}
	case 21: {
		return udf->getFloatForKey("CLEARTIME21", 1000);
		break;
	}
	case 22: {
		return udf->getFloatForKey("CLEARTIME22", 1000);
		break;
	}
	case 23: {
		return udf->getFloatForKey("CLEARTIME23", 1000);
		break;
	}
	case 24: {
		return udf->getFloatForKey("CLEARTIME24", 1000);
		break;
	}
	case 25: {
		return udf->getFloatForKey("CLEARTIME25", 1000);
		break;
	}
	case 26: {
		return udf->getFloatForKey("CLEARTIME26", 1000);
		break;
	}
	case 27: {
		return udf->getFloatForKey("CLEARTIME27", 1000);
		break;
	}
	case 28: {
		return udf->getFloatForKey("CLEARTIME28", 1000);
		break;
	}
	case 29: {
		return udf->getFloatForKey("CLEARTIME29", 1000);
		break;
	}
	case 30: {
		return udf->getFloatForKey("CLEARTIME30", 1000);
		break;
	}
	case 31: {
		return udf->getFloatForKey("CLEARTIME31", 1000);
		break;
	}
	case 32: {
		return udf->getFloatForKey("CLEARTIME32", 1000);
		break;
	}
	case 33: {
		return udf->getFloatForKey("CLEARTIME33", 1000);
		break;
	}
	case 34: {
		return udf->getFloatForKey("CLEARTIME34", 1000);
		break;
	}
	case 35: {
		return udf->getFloatForKey("CLEARTIME35", 1000);
		break;
	}
	case 36: {
		return udf->getFloatForKey("CLEARTIME36", 1000);
		break;
	}
	case 37: {
		return udf->getFloatForKey("CLEARTIME37", 1000);
		break;
	}
	case 38: {
		return udf->getFloatForKey("CLEARTIME38", 1000);
		break;
	}
	case 39: {
		return udf->getFloatForKey("CLEARTIME39", 1000);
		break;
	}
	case 40: {
		return udf->getFloatForKey("CLEARTIME40", 1000);
		break;
	}
	case 41: {
		return udf->getFloatForKey("CLEARTIME41", 1000);
		break;
	}
	case 42: {
		return udf->getFloatForKey("CLEARTIME42", 1000);
		break;
	}
	case 43: {
		return udf->getFloatForKey("CLEARTIME43", 1000);
		break;
	}
	case 44: {
		return udf->getFloatForKey("CLEARTIME44", 1000);
		break;
	}
	case 45: {
		return udf->getFloatForKey("CLEARTIME45", 1000);
		break;
	}
	case 46: {
		return udf->getFloatForKey("CLEARTIME46", 1000);
		break;
	}
	case 47: {
		return udf->getFloatForKey("CLEARTIME47", 1000);
		break;
	}
	case 48: {
		return udf->getFloatForKey("CLEARTIME48", 1000);
		break;
	}
	case 49: {
		return udf->getFloatForKey("CLEARTIME49", 1000);
		break;
	}
	case 50: {
		return udf->getFloatForKey("CLEARTIME50", 1000);
		break;
	}
	case 51: {
		return udf->getFloatForKey("CLEARTIME51", 1000);
		break;
	}
	case 52: {
		return udf->getFloatForKey("CLEARTIME52", 1000);
		break;
	}
	case 53: {
		return udf->getFloatForKey("CLEARTIME53", 1000);
		break;
	}
	case 54: {
		return udf->getFloatForKey("CLEARTIME54", 1000);
		break;
	}
	case 55: {
		return udf->getFloatForKey("CLEARTIME55", 1000);
		break;
	}
	case 56: {
		return udf->getFloatForKey("CLEARTIME56", 1000);
		break;
	}
	case 57: {
		return udf->getFloatForKey("CLEARTIME57", 1000);
		break;
	}
	case 58: {
		return udf->getFloatForKey("CLEARTIME58", 1000);
		break;
	}
	case 59: {
		return udf->getFloatForKey("CLEARTIME59", 1000);
		break;
	}
	case 60: {
		return udf->getFloatForKey("CLEARTIME60", 1000);
		break;
	}
	case 61: {
		return udf->getFloatForKey("CLEARTIME61", 1000);
		break;
	}
	case 62: {
		return udf->getFloatForKey("CLEARTIME62", 1000);
		break;
	}
	case 63: {
		return udf->getFloatForKey("CLEARTIME63", 1000);
		break;
	}
	case 64: {
		return udf->getFloatForKey("CLEARTIME64", 1000);
		break;
	}
	case 65: {
		return udf->getFloatForKey("CLEARTIME65", 1000);
		break;
	}
	case 66: {
		return udf->getFloatForKey("CLEARTIME66", 1000);
		break;
	}
	case 67: {
		return udf->getFloatForKey("CLEARTIME67", 1000);
		break;
	}
	case 68: {
		return udf->getFloatForKey("CLEARTIME68", 1000);
		break;
	}
	case 69: {
		return udf->getFloatForKey("CLEARTIME69", 1000);
		break;
	}
	case 70: {
		return udf->getFloatForKey("CLEARTIME70", 1000);
		break;
	}
	case 71: {
		return udf->getFloatForKey("CLEARTIME71", 1000);
		break;
	}
	case 72: {
		return udf->getFloatForKey("CLEARTIME72", 1000);
		break;
	}
	case 73: {
		return udf->getFloatForKey("CLEARTIME73", 1000);
		break;
	}
	case 74: {
		return udf->getFloatForKey("CLEARTIME74", 1000);
		break;
	}
	case 75: {
		return udf->getFloatForKey("CLEARTIME75", 1000);
		break;
	}
	case 76: {
		return udf->getFloatForKey("CLEARTIME76", 1000);
		break;
	}
	case 77: {
		return udf->getFloatForKey("CLEARTIME77", 1000);
		break;
	}
	case 78: {
		return udf->getFloatForKey("CLEARTIME78", 1000);
		break;
	}
	case 79: {
		return udf->getFloatForKey("CLEARTIME79", 1000);
		break;
	}
	case 80: {
		return udf->getFloatForKey("CLEARTIME80", 1000);
		break;
	}
	case 81: {
		return udf->getFloatForKey("CLEARTIME81", 1000);
		break;
	}
	case 82: {
		return udf->getFloatForKey("CLEARTIME82", 1000);
		break;
	}
	case 83: {
		return udf->getFloatForKey("CLEARTIME83", 1000);
		break;
	}
	case 84: {
		return udf->getFloatForKey("CLEARTIME84", 1000);
		break;
	}
	case 85: {
		return udf->getFloatForKey("CLEARTIME85", 1000);
		break;
	}
	case 86: {
		return udf->getFloatForKey("CLEARTIME86", 1000);
		break;
	}
	case 87: {
		return udf->getFloatForKey("CLEARTIME87", 1000);
		break;
	}
	case 88: {
		return udf->getFloatForKey("CLEARTIME88", 1000);
		break;
	}
	case 89: {
		return udf->getFloatForKey("CLEARTIME89", 1000);
		break;
	}
	case 90: {
		return udf->getFloatForKey("CLEARTIME90", 1000);
		break;
	}
	case 91: {
		return udf->getFloatForKey("CLEARTIME91", 1000);
		break;
	}
	case 92: {
		return udf->getFloatForKey("CLEARTIME92", 1000);
		break;
	}
	case 93: {
		return udf->getFloatForKey("CLEARTIME93", 1000);
		break;
	}
	case 94: {
		return udf->getFloatForKey("CLEARTIME94", 1000);
		break;
	}
	case 95: {
		return udf->getFloatForKey("CLEARTIME95", 1000);
		break;
	}
	case 96: {
		return udf->getFloatForKey("CLEARTIME96", 1000);
		break;
	}
	case 97: {
		return udf->getFloatForKey("CLEARTIME97", 1000);
		break;
	}
	case 98: {
		return udf->getFloatForKey("CLEARTIME98", 1000);
		break;
	}
	case 99: {
		return udf->getFloatForKey("CLEARTIME99", 1000);
		break;
	}
	case 100: {
		return udf->getFloatForKey("CLEARTIME100", 1000);
		break;
	}
	default: {

		return 100;
		break;
	}
	}

}

void GameDeta::WriteDeta(Dot* dot_, int cx_, int cy_) {

	std::string mMapDetaSt;
//
//	int dspCnt = 0;//ドットスプライトの描写数
//	Vec2 dotPoints[200];//シェープ作成用のドット。
//	int dpCnt = 0;
//	Vec2 dShape[200];//シェープのドット。
//	int dsCnt = 0;
//	const char *str0 = "GameDeta::WriteDeta_1";
//	log("%s", str0);
	//ポイントを追加する

//	Vec2 SetPt2; //前回セットしたポイント2
//	float mrad2_ = 0;
	mMapDetaSt.append(StringUtils::toString((float) dot_->SetPt2.x) + "/");
	mMapDetaSt.append(StringUtils::toString((float) dot_->SetPt2.y) + "/");
	mMapDetaSt.append(StringUtils::toString((float) dot_->mrad2_) + "/");
	mMapDetaSt.append(StringUtils::toString((int) dot_->dsCnt) + "/");
	mMapDetaSt.append(StringUtils::toString((int) dot_->cNo) + "/");
	mMapDetaSt.append(StringUtils::toString("@"));

	for (int i = 0; i < dot_->dspCnt; i++) {
		mMapDetaSt.append(
				StringUtils::toString((float) (dot_->_dotG.at(i)->getPosition().x - dot_->cPt_.x)) + "/");
		if (i == (dot_->dspCnt - 1)) {
			mMapDetaSt.append(
					StringUtils::toString((float) (dot_->_dotG.at(i)->getPosition().y - dot_->cPt_.y)));
		} else {
			mMapDetaSt.append(
					StringUtils::toString((float) (dot_->_dotG.at(i)->getPosition().y - dot_->cPt_.y)) + "/");
		}

//		const char *str2 = "GameDeta::WriteDeta_2";
//		log("%s", str2);
	}

	mMapDetaSt.append(StringUtils::toString("@"));

	for (int i = 0; i < dot_->dsCnt; i++) {
		mMapDetaSt.append(StringUtils::toString((float) (dot_->dShape[i].x)) + "/");
		mMapDetaSt.append(StringUtils::toString((float) (dot_->dShape[i].y)) + "/");
	}

	this->SetCourceDeta(cx_, cy_, mMapDetaSt.c_str());
//	UserDefault::getInstance()->setStringForKey("CDETA", mMapDetaSt.c_str());

//	const char *str3 = "GameDeta::WriteDeta_3";
//	log("%s", str3);

}

String GameDeta::GetCourceDeta(int x, int y) {
	auto udf = UserDefault::getInstance();
	switch (y) {

	case 0: {
		return udf->getStringForKey("CDETA_0", "N");
		break;
	}
	case 1: {
		return udf->getStringForKey("CDETA_1", "N");
		break;
	}
	case 2: {
		return udf->getStringForKey("CDETA_2", "N");
		break;
	}
	case 3: {
		return udf->getStringForKey("CDETA_3", "N");
		break;
	}
	case 4: {
		return udf->getStringForKey("CDETA_4", "N");
		break;
	}
	case 5: {
		return udf->getStringForKey("CDETA_5", "N");
		break;
	}
	case 6: {
		return udf->getStringForKey("CDETA_6", "N");
		break;
	}
	case 7: {
		return udf->getStringForKey("CDETA_7", "N");
		break;
	}
	case 8: {
		return udf->getStringForKey("CDETA_8", "N");
		break;
	}
	case 9: {
		return udf->getStringForKey("CDETA_9", "N");
		break;
	}
	case 10: {
		return udf->getStringForKey("CDETA_10", "N");
		break;
	}
	case 11: {
		return udf->getStringForKey("CDETA_11", "N");
		break;
	}
	case 12: {
		return udf->getStringForKey("CDETA_12", "N");
		break;
	}
	case 13: {
		return udf->getStringForKey("CDETA_13", "N");
		break;
	}
	case 14: {
		return udf->getStringForKey("CDETA_14", "N");
		break;
	}
	case 15: {
		return udf->getStringForKey("CDETA_15", "N");
		break;
	}
	case 16: {
		return udf->getStringForKey("CDETA_16", "N");
		break;
	}
	case 17: {
		return udf->getStringForKey("CDETA_17", "N");
		break;
	}
	case 18: {
		return udf->getStringForKey("CDETA_18", "N");
		break;
	}
	case 19: {
		return udf->getStringForKey("CDETA_19", "N");
		break;
	}
	case 20: {
		return udf->getStringForKey("CDETA_20", "N");
		break;
	}
	case 21: {
		return udf->getStringForKey("CDETA_21", "N");
		break;
	}
	case 22: {
		return udf->getStringForKey("CDETA_22", "N");
		break;
	}
	case 23: {
		return udf->getStringForKey("CDETA_23", "N");
		break;
	}
	case 24: {
		return udf->getStringForKey("CDETA_24", "N");
		break;
	}
	case 25: {
		return udf->getStringForKey("CDETA_25", "N");
		break;
	}
	case 26: {
		return udf->getStringForKey("CDETA_26", "N");
		break;
	}
	case 27: {
		return udf->getStringForKey("CDETA_27", "N");
		break;
	}
	case 28: {
		return udf->getStringForKey("CDETA_28", "N");
		break;
	}
	case 29: {
		return udf->getStringForKey("CDETA_29", "N");
		break;
	}
	case 30: {
		return udf->getStringForKey("CDETA_30", "N");
		break;
	}
	case 31: {
		return udf->getStringForKey("CDETA_31", "N");
		break;
	}
	case 32: {
		return udf->getStringForKey("CDETA_32", "N");
		break;
	}
	case 33: {
		return udf->getStringForKey("CDETA_33", "N");
		break;
	}
	case 34: {
		return udf->getStringForKey("CDETA_34", "N");
		break;
	}
	case 35: {
		return udf->getStringForKey("CDETA_35", "N");
		break;
	}
	case 36: {
		return udf->getStringForKey("CDETA_36", "N");
		break;
	}
	case 37: {
		return udf->getStringForKey("CDETA_37", "N");
		break;
	}
	case 38: {
		return udf->getStringForKey("CDETA_38", "N");
		break;
	}
	case 39: {
		return udf->getStringForKey("CDETA_39", "N");
		break;
	}
	case 40: {
		return udf->getStringForKey("CDETA_40", "N");
		break;
	}
	case 41: {
		return udf->getStringForKey("CDETA_41", "N");
		break;
	}
	case 42: {
		return udf->getStringForKey("CDETA_42", "N");
		break;
	}
	case 43: {
		return udf->getStringForKey("CDETA_43", "N");
		break;
	}
	case 44: {
		return udf->getStringForKey("CDETA_44", "N");
		break;
	}
	case 45: {
		return udf->getStringForKey("CDETA_45", "N");
		break;
	}
	case 46: {
		return udf->getStringForKey("CDETA_46", "N");
		break;
	}
	case 47: {
		return udf->getStringForKey("CDETA_47", "N");
		break;
	}
	case 48: {
		return udf->getStringForKey("CDETA_48", "N");
		break;
	}
	case 49: {
		return udf->getStringForKey("CDETA_49", "N");
		break;
	}
	case 50: {
		return udf->getStringForKey("CDETA_50", "N");
		break;
	}

	default: {
		return udf->getStringForKey("CDETA_0", "N");
		break;
	}

	}
}
void GameDeta::SetCourceDeta(int x, int y, std::string st) {
	auto udf = UserDefault::getInstance();
	switch (y) {

	case 0: {
		return udf->setStringForKey("CDETA_0", st);
		break;
	}
	case 1: {
		return udf->setStringForKey("CDETA_1", st);
		break;
	}
	case 2: {
		return udf->setStringForKey("CDETA_2", st);
		break;
	}
	case 3: {
		return udf->setStringForKey("CDETA_3", st);
		break;
	}
	case 4: {
		return udf->setStringForKey("CDETA_4", st);
		break;
	}
	case 5: {
		return udf->setStringForKey("CDETA_5", st);
		break;
	}
	case 6: {
		return udf->setStringForKey("CDETA_6", st);
		break;
	}
	case 7: {
		return udf->setStringForKey("CDETA_7", st);
		break;
	}
	case 8: {
		return udf->setStringForKey("CDETA_8", st);
		break;
	}
	case 9: {
		return udf->setStringForKey("CDETA_9", st);
		break;
	}
	case 10: {
		return udf->setStringForKey("CDETA_10", st);
		break;
	}
	case 11: {
		return udf->setStringForKey("CDETA_11", st);
		break;
	}
	case 12: {
		return udf->setStringForKey("CDETA_12", st);
		break;
	}
	case 13: {
		return udf->setStringForKey("CDETA_13", st);
		break;
	}
	case 14: {
		return udf->setStringForKey("CDETA_14", st);
		break;
	}
	case 15: {
		return udf->setStringForKey("CDETA_15", st);
		break;
	}
	case 16: {
		return udf->setStringForKey("CDETA_16", st);
		break;
	}
	case 17: {
		return udf->setStringForKey("CDETA_17", st);
		break;
	}
	case 18: {
		return udf->setStringForKey("CDETA_18", st);
		break;
	}
	case 19: {
		return udf->setStringForKey("CDETA_19", st);
		break;
	}
	case 20: {
		return udf->setStringForKey("CDETA_20", st);
		break;
	}
	case 21: {
		return udf->setStringForKey("CDETA_21", st);
		break;
	}
	case 22: {
		return udf->setStringForKey("CDETA_22", st);
		break;
	}
	case 23: {
		return udf->setStringForKey("CDETA_23", st);
		break;
	}
	case 24: {
		return udf->setStringForKey("CDETA_24", st);
		break;
	}
	case 25: {
		return udf->setStringForKey("CDETA_25", st);
		break;
	}
	case 26: {
		return udf->setStringForKey("CDETA_26", st);
		break;
	}
	case 27: {
		return udf->setStringForKey("CDETA_27", st);
		break;
	}
	case 28: {
		return udf->setStringForKey("CDETA_28", st);
		break;
	}
	case 29: {
		return udf->setStringForKey("CDETA_29", st);
		break;
	}
	case 30: {
		return udf->setStringForKey("CDETA_30", st);
		break;
	}
	case 31: {
		return udf->setStringForKey("CDETA_31", st);
		break;
	}
	case 32: {
		return udf->setStringForKey("CDETA_32", st);
		break;
	}
	case 33: {
		return udf->setStringForKey("CDETA_33", st);
		break;
	}
	case 34: {
		return udf->setStringForKey("CDETA_34", st);
		break;
	}
	case 35: {
		return udf->setStringForKey("CDETA_35", st);
		break;
	}
	case 36: {
		return udf->setStringForKey("CDETA_36", st);
		break;
	}
	case 37: {
		return udf->setStringForKey("CDETA_37", st);
		break;
	}
	case 38: {
		return udf->setStringForKey("CDETA_38", st);
		break;
	}
	case 39: {
		return udf->setStringForKey("CDETA_39", st);
		break;
	}
	case 40: {
		return udf->setStringForKey("CDETA_40", st);
		break;
	}
	case 41: {
		return udf->setStringForKey("CDETA_41", st);
		break;
	}
	case 42: {
		return udf->setStringForKey("CDETA_42", st);
		break;
	}
	case 43: {
		return udf->setStringForKey("CDETA_43", st);
		break;
	}
	case 44: {
		return udf->setStringForKey("CDETA_44", st);
		break;
	}
	case 45: {
		return udf->setStringForKey("CDETA_45", st);
		break;
	}
	case 46: {
		return udf->setStringForKey("CDETA_46", st);
		break;
	}
	case 47: {
		return udf->setStringForKey("CDETA_47", st);
		break;
	}
	case 48: {
		return udf->setStringForKey("CDETA_48", st);
		break;
	}
	case 49: {
		return udf->setStringForKey("CDETA_49", st);
		break;
	}
	case 50: {
		return udf->setStringForKey("CDETA_50", st);
		break;
	}
	default: {
		return udf->setStringForKey("CDETA_0", st);
		break;
	}
	}
}

void GameDeta::SetClearCource(int No_) {
	//現在クリヤしているコースNo
	auto udf = UserDefault::getInstance();

	if (this->GetClearCource() < No_) {

		udf->setIntegerForKey("CLEAR_COURCE_LEVEL", No_);

	}
}
int GameDeta::GetClearCource() {
	auto udf = UserDefault::getInstance();

//	udf->setIntegerForKey("CLEAR_COURCE_LEVEL", 31);

	return udf->getIntegerForKey("CLEAR_COURCE_LEVEL", 1);
}

int GameDeta::GetSelectCourceNo() {
	//現在セットされているコースNo
	auto udf = UserDefault::getInstance();
	return udf->getIntegerForKey("SELECT_COURCE_LEVEL", 1);

}
int GameDeta::GetSelectCourceLength() {
	//現在セットされているコースNoの長さ
	auto udf = UserDefault::getInstance();
	return udf->getIntegerForKey("SELECT_COURCE_LENGTH", 0);
}

void GameDeta::SetDrawPosition() {
	//現在の全コースのポイント情報を取得する。
	dotDrawCnt = 0;
	int x = 0;

	String Bffer_;
	int fsturn = 0;
	int turn = 0;
	float x_;
	float y_;
	float s_;
	float xx_;
	float yy_;

//	Vec2 dotDrawPt[5000]; //シェープ作成用のドット。

	for (int i = 1; i <= this->GetSelectCourceLength(); i++) {

		String Str = this->GetCourceDeta(1, i);
		CCString* pStr = CCString::create(Str._string);

		fsturn = 0;
		turn = 0;

		if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
			break;
		}

		int sCnt = 0;

		for (int i = 0; i < pStr->length(); i++) {

			String str_ = pStr->_string.substr(i, 1);
			switch (fsturn) {
			case 0: {
				if (str_._string == "/") {
					switch (turn) {
					case 0: {
						x_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
						break;
					}
					case 1: {
						y_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
						break;
					}
					case 2: {
						Bffer_ = "";
						turn++;
						break;
					}
					case 3: {
						Bffer_ = "";
						turn++;
						break;
					}
					}
				} else if (str_._string == "@") {
					fsturn++;
					Bffer_ = "";
					turn = 0;
					x_ = 0;
					y_ = 0;
				} else {
					Bffer_.append(str_._string);
				}
				break;
			}
			case 1: {
				if (str_._string == "/") {
					switch (turn) {
					case 0: {
						x_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
						break;
					}
					case 1: {
						y_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
						dotDrawPt[dotDrawCnt].set(x_, y_);
						dotDrawCnt++;
						turn = 0;
						break;
					}
					}
				} else if (str_._string == "@") {
					fsturn++;
					turn = 0;
					Bffer_ = "";
					x_ = 0;
					y_ = 0;
				} else {
					Bffer_.append(str_._string);
				}
				break;
			}
			case 2: {
				if (str_._string == "/") {
					switch (turn) {
					case 0: {
						x_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
						break;
					}
					case 1: {
						y_ = Bffer_.floatValue();
						Bffer_ = "";
						turn++;
//						dot_->dShape[sCnt].set(Vec2(x_, y_));
						sCnt++;
						turn = 0;
						break;
					}
					}
				} else {
					Bffer_.append(str_._string);
				}
				break;
			}
			}
		}

	}
}
void GameDeta::SetSelectCource(int No_) {
	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("SELECT_COURCE_LEVEL", No_);
}

int GameDeta::GetSelectCource() {
	auto udf = UserDefault::getInstance();
	return udf->getIntegerForKey("SELECT_COURCE_LEVEL", 1);
}

void GameDeta::MadeCourceTitle(Dot* dot_, int courceNo) {
	MadeCourceFromTxt(dot_, courceNo, "0_3_4_6_7_8_9_10_13_14_15_16_100_"); //タイトル時

	//ここで高速化処理作成
	this->ReadDeta2_Prepare(dot_);
}
void GameDeta::MadeCourceAsobikata(Dot* dot_, int courceNo) {
	MadeCourceFromTxt(dot_, courceNo, "0_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_1_100_"); //遊び方時

	//ここで高速化処理作成
	this->ReadDeta2_Prepare(dot_);
}
void GameDeta::MadeCourceFromCourceNo(Dot* dot_, int courceNo) {
	//コースナンバーからコースを作成

	if (this->GetDebug()) {

		this->MadeCourceFromCourceNo_debug(dot_, courceNo);
		return;
	}

	//現在保存されているコースデータと違う場合は、コースを新規に作成する。
//	if (this->GetSelectCourceNo() == courceNo) {
//		return;
//	}

	this->SetSelectCource(courceNo);

	switch (courceNo) {

	case 1: {
		MadeCourceFromTxt(dot_, courceNo, "0_22_17_18_9_10_24_3_23_25_22_100_");
		break;
	}
	case 2: {
		MadeCourceFromTxt(dot_, courceNo, "0_1_13_26_24_12_29_27_4_29_11_100_");
		break;
	}
	case 3: {
		MadeCourceFromTxt(dot_, courceNo, "0_16_24_3_18_15_5_19_20_8_9_100_");
		break;
	}
	case 4: {
		MadeCourceFromTxt(dot_, courceNo, "0_25_25_18_30_28_7_21_30_8_17_100_");
		break;
	}
	case 5: {
		MadeCourceFromTxt(dot_, courceNo, "0_4_30_21_6_18_4_4_24_9_7_100_");
		break;
	}
	case 6: {
		MadeCourceFromTxt(dot_, courceNo, "0_29_31_29_49_50_32_28_24_25_40_100_");
		break;
	}
	case 7: {
		MadeCourceFromTxt(dot_, courceNo, "0_32_32_42_30_39_26_25_38_22_34_100_");
		break;
	}
	case 8: {
		MadeCourceFromTxt(dot_, courceNo, "0_48_28_44_31_28_48_39_39_33_23_100_");
		break;
	}
	case 9: {
		MadeCourceFromTxt(dot_, courceNo, "0_37_41_48_45_20_36_48_33_41_35_100_");
		break;
	}
	case 10: {
		MadeCourceFromTxt(dot_, courceNo, "0_51_48_44_46_41_32_39_70_32_46_100_");
		break;
	}
	case 11: {
		MadeCourceFromTxt(dot_, courceNo, "0_44_50_36_49_40_55_52_36_68_56_100_");
		break;
	}
	case 12: {
		MadeCourceFromTxt(dot_, courceNo, "0_50_46_34_62_48_60_54_64_30_38_100_");
		break;
	}
	case 13: {
		MadeCourceFromTxt(dot_, courceNo, "0_33_34_43_35_30_52_56_52_63_33_100_");
		break;
	}
	case 14: {
		MadeCourceFromTxt(dot_, courceNo, "0_37_57_48_44_36_58_68_51_33_61_100_");
		break;
	}
	case 15: {
		MadeCourceFromTxt(dot_, courceNo, "0_56_58_60_48_53_43_64_46_78_44_100_");
		break;
	}
	case 16: {
		MadeCourceFromTxt(dot_, courceNo, "0_58_51_75_70_51_67_50_43_41_53_100_");
		break;
	}
	case 17: {
		MadeCourceFromTxt(dot_, courceNo, "0_72_52_49_59_50_53_41_59_48_75_100_");
		break;
	}
	case 18: {
		MadeCourceFromTxt(dot_, courceNo, "0_64_70_78_53_62_43_66_56_79_44_100_");
		break;
	}
	case 19: {
		MadeCourceFromTxt(dot_, courceNo, "0_77_65_54_46_59_48_80_45_41_54_100_");
		break;
	}
	case 20: {
		MadeCourceFromTxt(dot_, courceNo, "0_72_87_72_66_84_83_77_79_90_63_100_");
		break;
	}
	case 21: {
		MadeCourceFromTxt(dot_, courceNo, "0_77_69_57_55_81_62_68_58_53_89_100_");
		break;
	}
	case 22: {
		MadeCourceFromTxt(dot_, courceNo, "0_88_75_71_52_86_68_60_61_60_75_100_");
		break;
	}
	case 23: {
		MadeCourceFromTxt(dot_, courceNo, "0_70_60_94_78_76_73_87_86_70_61_100_");
		break;
	}
	case 24: {
		MadeCourceFromTxt(dot_, courceNo, "0_76_85_81_92_72_87_74_99_72_64_100_");
		break;
	}
	case 25: {
		MadeCourceFromTxt(dot_, courceNo, "0_75_84_82_77_89_83_93_80_98_84_100_");
		break;
	}
	case 26: {
		MadeCourceFromTxt(dot_, courceNo, "0_80_95_88_93_80_78_94_84_77_83_100_");
		break;
	}
	case 27: {
		MadeCourceFromTxt(dot_, courceNo, "0_76_80_78_90_79_97_75_94_88_76_100_");
		break;
	}
	case 28: {
		MadeCourceFromTxt(dot_, courceNo, "0_80_77_88_99_80_75_89_95_90_88_100_");
		break;
	}
	case 29: {
		MadeCourceFromTxt(dot_, courceNo, "0_78_82_76_88_84_97_80_94_92_99_100_");
		break;
	}
	case 30: {
		MadeCourceFromTxt(dot_, courceNo, "0_80_93_81_84_78_98_75_87_98_85_100_");
		break;
	}
	case 31: {
		MadeCourceFromRnd(dot_, courceNo, 12);
		break;
	}
	case 32: {
		MadeCourceFromTxt(dot_, courceNo, "0_22_49_66_14_90_40_17_9_88_25_100_");
		break;
	}
	case 33: {
		MadeCourceFromTxt(dot_, courceNo, "0_53_53_17_79_99_6_9_83_77_34_100_");
		break;
	}
	case 34: {
		MadeCourceFromTxt(dot_, courceNo, "0_64_17_98_33_8_90_86_61_69_96_100_");
		break;
	}
	case 35: {
		MadeCourceFromTxt(dot_, courceNo, "0_24_6_91_84_19_71_67_62_3_96_100_");
		break;
	}
	case 36: {
		MadeCourceFromTxt(dot_, courceNo, "0_90_24_49_87_45_99_23_87_11_35_100_");
		break;
	}
	case 37: {
		MadeCourceFromTxt(dot_, courceNo, "0_44_62_93_90_89_16_87_68_9_31_100_");
		break;
	}
	case 38: {
		MadeCourceFromTxt(dot_, courceNo, "0_53_63_70_29_30_41_35_64_66_40_100_");
		break;
	}
	case 39: {
		MadeCourceFromTxt(dot_, courceNo, "0_47_32_76_93_57_13_26_88_65_35_100_");
		break;
	}
	case 40: {
		MadeCourceFromTxt(dot_, courceNo, "0_39_34_95_62_29_71_85_10_58_93_100_");
		break;
	}
	case 41: {
		MadeCourceFromTxt(dot_, courceNo, "0_12_80_22_99_32_33_52_71_56_68_100_");
		break;
	}
	case 42: {
		MadeCourceFromTxt(dot_, courceNo, "0_54_75_42_41_62_87_17_7_25_48_100_");
		break;
	}
	case 43: {
		MadeCourceFromTxt(dot_, courceNo, "0_19_77_9_34_71_15_36_63_77_43_100_");
		break;
	}
	case 44: {
		MadeCourceFromTxt(dot_, courceNo, "0_38_20_38_88_42_9_98_46_73_28_100_");
		break;
	}
	case 45: {
		MadeCourceFromTxt(dot_, courceNo, "0_22_62_96_72_77_54_64_59_68_48_100_");
		break;
	}
	case 46: {
		MadeCourceFromTxt(dot_, courceNo, "0_7_82_72_42_36_86_13_95_80_66_100_");
		break;
	}
	case 47: {
		MadeCourceFromTxt(dot_, courceNo, "0_55_43_41_1_27_33_77_94_62_95_100_");
		break;
	}
	case 48: {
		MadeCourceFromTxt(dot_, courceNo, "0_10_64_73_25_59_34_44_98_97_62_100_");
		break;
	}
	case 49: {
		MadeCourceFromTxt(dot_, courceNo, "0_54_16_37_95_17_58_36_45_59_84_100_");
		break;
	}
	case 50: {
		MadeCourceFromTxt(dot_, courceNo, "0_28_86_9_38_83_88_19_92_94_60_100_");
		break;
	}
	case 51: {
		MadeCourceFromTxt(dot_, courceNo, "0_12_10_77_34_51_34_7_63_33_2_100_");
		break;
	}
	case 52: {
		MadeCourceFromTxt(dot_, courceNo, "0_78_48_13_85_83_89_44_53_24_63_100_");
		break;
	}
	case 53: {
		MadeCourceFromTxt(dot_, courceNo, "0_52_58_43_26_30_56_81_36_55_43_100_");
		break;
	}
	case 54: {
		MadeCourceFromTxt(dot_, courceNo, "0_60_8_39_17_90_89_94_67_7_63_100_");
		break;
	}
	case 55: {
		MadeCourceFromTxt(dot_, courceNo, "0_35_92_21_71_86_37_9_67_44_54_100_");
		break;
	}
	case 56: {
		MadeCourceFromTxt(dot_, courceNo, "0_17_94_33_95_93_87_9_27_49_97_100_");
		break;
	}
	case 57: {
		MadeCourceFromTxt(dot_, courceNo, "0_76_65_38_41_34_44_66_84_47_4_100_");
		break;
	}
	case 58: {
		MadeCourceFromTxt(dot_, courceNo, "0_24_38_39_99_43_83_16_49_81_32_100_");
		break;
	}
	case 59: {
		MadeCourceFromTxt(dot_, courceNo, "0_8_90_29_91_41_74_43_75_36_76_100_");
		break;
	}
	case 60: {
		MadeCourceFromTxt(dot_, courceNo, "0_4_25_23_36_95_63_87_22_20_71_100_");
		break;
	}
	case 61: {
		MadeCourceFromTxt(dot_, courceNo, "0_47_20_23_88_37_49_58_40_40_98_100_");
		break;
	}
	case 62: {
		MadeCourceFromTxt(dot_, courceNo, "0_64_87_25_90_76_7_18_74_58_91_100_");
		break;
	}
	case 63: {
		MadeCourceFromTxt(dot_, courceNo, "0_3_34_59_72_35_33_96_77_90_76_100_");
		break;
	}
	case 64: {
		MadeCourceFromTxt(dot_, courceNo, "0_65_5_35_95_70_20_20_71_83_91_100_");
		break;
	}
	case 65: {
		MadeCourceFromTxt(dot_, courceNo, "0_1_63_25_36_86_81_75_94_4_71_100_");
		break;
	}
	case 66: {
		MadeCourceFromTxt(dot_, courceNo, "0_5_39_99_27_33_92_54_36_8_87_100_");
		break;
	}
	case 67: {
		MadeCourceFromTxt(dot_, courceNo, "0_34_36_21_35_53_9_32_35_77_93_100_");
		break;
	}
	case 68: {
		MadeCourceFromTxt(dot_, courceNo, "0_34_93_39_23_29_81_82_92_41_8_100_");
		break;
	}
	case 69: {
		MadeCourceFromTxt(dot_, courceNo, "0_39_44_48_21_16_84_39_39_21_22_100_");
		break;
	}
	case 70: {
		MadeCourceFromTxt(dot_, courceNo, "0_94_94_7_29_1_18_41_37_73_36_100_");
		break;
	}
	case 71: {
		MadeCourceFromTxt(dot_, courceNo, "0_1_43_25_97_94_54_40_27_6_50_100_");
		break;
	}
	case 72: {
		MadeCourceFromTxt(dot_, courceNo, "0_88_98_64_71_54_42_43_34_93_64_100_");
		break;
	}
	case 73: {
		MadeCourceFromTxt(dot_, courceNo, "0_75_68_23_3_2_84_20_6_40_58_100_");
		break;
	}
	case 74: {
		MadeCourceFromTxt(dot_, courceNo, "0_59_27_80_49_72_57_8_36_26_74_100_");
		break;
	}
	case 75: {
		MadeCourceFromTxt(dot_, courceNo, "0_44_84_34_21_21_31_87_4_72_4_100_");
		break;
	}
	case 76: {
		MadeCourceFromTxt(dot_, courceNo, "0_13_21_58_55_58_16_8_29_95_51_100_");
		break;
	}
	case 77: {
		MadeCourceFromTxt(dot_, courceNo, "0_89_51_56_10_7_39_92_25_21_47_100_");
		break;
	}
	case 78: {
		MadeCourceFromTxt(dot_, courceNo, "0_52_29_90_22_92_28_49_2_14_10_100_");
		break;
	}
	case 79: {
		MadeCourceFromTxt(dot_, courceNo, "0_93_22_12_63_11_58_65_37_17_91_100_");
		break;
	}
	case 80: {
		MadeCourceFromTxt(dot_, courceNo, "0_42_8_31_93_30_89_70_42_99_55_100_");
		break;
	}
	case 81: {
		MadeCourceFromTxt(dot_, courceNo, "0_72_63_82_91_34_91_81_72_89_60_100_");
		break;
	}
	case 82: {
		MadeCourceFromTxt(dot_, courceNo, "0_1_63_98_17_7_45_72_58_11_68_100_");
		break;
	}
	case 83: {
		MadeCourceFromTxt(dot_, courceNo, "0_18_1_75_29_5_63_45_67_63_85_100_");
		break;
	}
	case 84: {
		MadeCourceFromTxt(dot_, courceNo, "0_11_1_5_65_84_67_66_22_14_8_100_");
		break;
	}
	case 85: {
		MadeCourceFromTxt(dot_, courceNo, "0_81_86_12_66_76_16_13_17_85_31_100_");
		break;
	}
	case 86: {
		MadeCourceFromTxt(dot_, courceNo, "0_60_13_4_83_12_66_51_39_68_48_100_");
		break;
	}
	case 87: {
		MadeCourceFromTxt(dot_, courceNo, "0_73_97_40_14_57_29_23_57_77_39_100_");
		break;
	}
	case 88: {
		MadeCourceFromTxt(dot_, courceNo, "0_7_86_68_56_13_24_18_47_45_34_100_");
		break;
	}
	case 89: {
		MadeCourceFromTxt(dot_, courceNo, "0_88_56_79_75_62_68_65_75_12_98_100_");
		break;
	}
	case 90: {
		MadeCourceFromTxt(dot_, courceNo, "0_65_33_94_7_5_48_71_35_63_66_100_");
		break;
	}
	case 91: {
		MadeCourceFromTxt(dot_, courceNo, "0_58_73_76_63_88_50_70_38_14_40_100_");
		break;
	}
	case 92: {
		MadeCourceFromTxt(dot_, courceNo, "0_21_49_24_12_33_57_87_83_54_7_100_");
		break;
	}
	case 93: {
		MadeCourceFromTxt(dot_, courceNo, "0_27_20_99_27_15_40_20_57_87_59_100_");
		break;
	}
	case 94: {
		MadeCourceFromTxt(dot_, courceNo, "0_71_97_98_52_37_89_83_44_49_13_100_");
		break;
	}
	case 95: {
		MadeCourceFromTxt(dot_, courceNo, "0_56_22_53_15_31_74_87_62_67_58_100_");
		break;
	}
	case 96: {
		MadeCourceFromTxt(dot_, courceNo, "0_91_16_37_82_40_32_26_27_99_92_100_");
		break;
	}
	case 97: {
		MadeCourceFromTxt(dot_, courceNo, "0_46_80_14_53_90_4_6_19_93_18_100_");
		break;
	}
	case 98: {
		MadeCourceFromTxt(dot_, courceNo, "0_16_50_34_21_60_84_51_24_8_93_100_");
		break;
	}
	case 99: {
		MadeCourceFromTxt(dot_, courceNo, "0_92_19_93_54_82_62_49_52_18_94_100_");
		break;
	}

	case 100: {
		MadeCourceFromRnd(dot_, courceNo, 12);
		break;
	}
	}
	//ここで高速化処理作成
	this->ReadDeta2_Prepare(dot_);

}

void GameDeta::MadeCourceFromCourceNo_debug(Dot* dot_, int courceNo) {
	//コースナンバーからコースを作成

	//現在保存されているコースデータと違う場合は、コースを新規に作成する。
//	if (this->GetSelectCourceNo() == courceNo) {
//		return;
//	}

	this->SetSelectCource(courceNo);

	switch (courceNo) {

	case 1: {
		MadeCourceFromTxt(dot_, courceNo, "0_1_100_");
		break;
	}
	case 2: {
		MadeCourceFromTxt(dot_, courceNo, "0_2_100_");
		break;
	}
	case 3: {
		MadeCourceFromTxt(dot_, courceNo, "0_3_100_");
		break;
	}
	case 4: {
		MadeCourceFromTxt(dot_, courceNo, "0_4_100_");
		break;
	}
	case 5: {
		MadeCourceFromTxt(dot_, courceNo, "0_5_100_");
		break;
	}
	case 6: {
		MadeCourceFromTxt(dot_, courceNo, "0_6_100_");
		break;
	}
	case 7: {
		MadeCourceFromTxt(dot_, courceNo, "0_7_100_");
		break;
	}
	case 8: {
		MadeCourceFromTxt(dot_, courceNo, "0_8_100_");
		break;
	}
	case 9: {
		MadeCourceFromTxt(dot_, courceNo, "0_9_100_");
		break;
	}
	case 10: {
		MadeCourceFromTxt(dot_, courceNo, "0_10_100_");
		break;
	}
	case 11: {
		MadeCourceFromTxt(dot_, courceNo, "0_11_100_");
		break;
	}
	case 12: {
		MadeCourceFromTxt(dot_, courceNo, "0_12_100_");
		break;
	}
	case 13: {
		MadeCourceFromTxt(dot_, courceNo, "0_13_100_");
		break;
	}
	case 14: {
		MadeCourceFromTxt(dot_, courceNo, "0_14_100_");
		break;
	}
	case 15: {
		MadeCourceFromTxt(dot_, courceNo, "0_15_100_");
		break;
	}
	case 16: {
		MadeCourceFromTxt(dot_, courceNo, "0_16_100_");
		break;
	}
	case 17: {
		MadeCourceFromTxt(dot_, courceNo, "0_17_100_");
		break;
	}
	case 18: {
		MadeCourceFromTxt(dot_, courceNo, "0_18_100_");
		break;
	}
	case 19: {
		MadeCourceFromTxt(dot_, courceNo, "0_19_100_");
		break;
	}
	case 20: {
		MadeCourceFromTxt(dot_, courceNo, "0_20_100_");
		break;
	}
	case 21: {
		MadeCourceFromTxt(dot_, courceNo, "0_21_100_");
		break;
	}
	case 22: {
		MadeCourceFromTxt(dot_, courceNo, "0_22_100_");
		break;
	}
	case 23: {
		MadeCourceFromTxt(dot_, courceNo, "0_23_100_");
		break;
	}
	case 24: {
		MadeCourceFromTxt(dot_, courceNo, "0_24_100_");
		break;
	}
	case 25: {
		MadeCourceFromTxt(dot_, courceNo, "0_25_100_");
		break;
	}
	case 26: {
		MadeCourceFromTxt(dot_, courceNo, "0_26_100_");
		break;
	}
	case 27: {
		MadeCourceFromTxt(dot_, courceNo, "0_27_100_");
		break;
	}
	case 28: {
		MadeCourceFromTxt(dot_, courceNo, "0_28_100_");
		break;
	}
	case 29: {
		MadeCourceFromTxt(dot_, courceNo, "0_29_100_");
		break;
	}
	case 30: {
		MadeCourceFromTxt(dot_, courceNo, "0_30_100_");
		break;
	}
	case 31: {
		MadeCourceFromTxt(dot_, courceNo, "0_31_100_");
		break;
	}
	case 32: {
		MadeCourceFromTxt(dot_, courceNo, "0_32_100_");
		break;
	}
	case 33: {
		MadeCourceFromTxt(dot_, courceNo, "0_33_100_");
		break;
	}
	case 34: {
		MadeCourceFromTxt(dot_, courceNo, "0_34_100_");
		break;
	}
	case 35: {
		MadeCourceFromTxt(dot_, courceNo, "0_35_100_");
		break;
	}
	case 36: {
		MadeCourceFromTxt(dot_, courceNo, "0_36_100_");
		break;
	}
	case 37: {
		MadeCourceFromTxt(dot_, courceNo, "0_37_100_");
		break;
	}
	case 38: {
		MadeCourceFromTxt(dot_, courceNo, "0_38_100_");
		break;
	}
	case 39: {
		MadeCourceFromTxt(dot_, courceNo, "0_39_100_");
		break;
	}
	case 40: {
		MadeCourceFromTxt(dot_, courceNo, "0_40_100_");
		break;
	}
	case 41: {
		MadeCourceFromTxt(dot_, courceNo, "0_41_100_");
		break;
	}
	case 42: {
		MadeCourceFromTxt(dot_, courceNo, "0_42_100_");
		break;
	}
	case 43: {
		MadeCourceFromTxt(dot_, courceNo, "0_43_100_");
		break;
	}
	case 44: {
		MadeCourceFromTxt(dot_, courceNo, "0_44_100_");
		break;
	}
	case 45: {
		MadeCourceFromTxt(dot_, courceNo, "0_45_100_");
		break;
	}
	case 46: {
		MadeCourceFromTxt(dot_, courceNo, "0_46_100_");
		break;
	}
	case 47: {
		MadeCourceFromTxt(dot_, courceNo, "0_47_100_");
		break;
	}
	case 48: {
		MadeCourceFromTxt(dot_, courceNo, "0_48_100_");
		break;
	}
	case 49: {
		MadeCourceFromTxt(dot_, courceNo, "0_49_100_");
		break;
	}
	case 50: {
		MadeCourceFromTxt(dot_, courceNo, "0_50_100_");
		break;
	}
	case 51: {
		MadeCourceFromTxt(dot_, courceNo, "0_51_100_");
		break;
	}
	case 52: {
		MadeCourceFromTxt(dot_, courceNo, "0_52_100_");
		break;
	}
	case 53: {
		MadeCourceFromTxt(dot_, courceNo, "0_53_100_");
		break;
	}
	case 54: {
		MadeCourceFromTxt(dot_, courceNo, "0_54_100_");
		break;
	}
	case 55: {
		MadeCourceFromTxt(dot_, courceNo, "0_55_100_");
		break;
	}
	case 56: {
		MadeCourceFromTxt(dot_, courceNo, "0_56_100_");
		break;
	}
	case 57: {
		MadeCourceFromTxt(dot_, courceNo, "0_57_100_");
		break;
	}
	case 58: {
		MadeCourceFromTxt(dot_, courceNo, "0_58_100_");
		break;
	}
	case 59: {
		MadeCourceFromTxt(dot_, courceNo, "0_59_100_");
		break;
	}
	case 60: {
		MadeCourceFromTxt(dot_, courceNo, "0_60_100_");
		break;
	}
	case 61: {
		MadeCourceFromTxt(dot_, courceNo, "0_61_100_");
		break;
	}
	case 62: {
		MadeCourceFromTxt(dot_, courceNo, "0_62_100_");
		break;
	}
	case 63: {
		MadeCourceFromTxt(dot_, courceNo, "0_63_100_");
		break;
	}
	case 64: {
		MadeCourceFromTxt(dot_, courceNo, "0_64_100_");
		break;
	}
	case 65: {
		MadeCourceFromTxt(dot_, courceNo, "0_65_100_");
		break;
	}
	case 66: {
		MadeCourceFromTxt(dot_, courceNo, "0_66_100_");
		break;
	}
	case 67: {
		MadeCourceFromTxt(dot_, courceNo, "0_67_100_");
		break;
	}
	case 68: {
		MadeCourceFromTxt(dot_, courceNo, "0_68_100_");
		break;
	}
	case 69: {
		MadeCourceFromTxt(dot_, courceNo, "0_69_100_");
		break;
	}
	case 70: {
		MadeCourceFromTxt(dot_, courceNo, "0_70_100_");
		break;
	}
	case 71: {
		MadeCourceFromTxt(dot_, courceNo, "0_71_100_");
		break;
	}
	case 72: {
		MadeCourceFromTxt(dot_, courceNo, "0_72_100_");
		break;
	}
	case 73: {
		MadeCourceFromTxt(dot_, courceNo, "0_73_100_");
		break;
	}
	case 74: {
		MadeCourceFromTxt(dot_, courceNo, "0_74_100_");
		break;
	}
	case 75: {
		MadeCourceFromTxt(dot_, courceNo, "0_75_100_");
		break;
	}
	case 76: {
		MadeCourceFromTxt(dot_, courceNo, "0_76_100_");
		break;
	}
	case 77: {
		MadeCourceFromTxt(dot_, courceNo, "0_77_100_");
		break;
	}
	case 78: {
		MadeCourceFromTxt(dot_, courceNo, "0_78_100_");
		break;
	}
	case 79: {
		MadeCourceFromTxt(dot_, courceNo, "0_79_100_");
		break;
	}
	case 80: {
		MadeCourceFromTxt(dot_, courceNo, "0_80_100_");
		break;
	}
	case 81: {
		MadeCourceFromTxt(dot_, courceNo, "0_81_100_");
		break;
	}
	case 82: {
		MadeCourceFromTxt(dot_, courceNo, "0_82_100_");
		break;
	}
	case 83: {
		MadeCourceFromTxt(dot_, courceNo, "0_83_100_");
		break;
	}
	case 84: {
		MadeCourceFromTxt(dot_, courceNo, "0_84_100_");
		break;
	}
	case 85: {
		MadeCourceFromTxt(dot_, courceNo, "0_85_100_");
		break;
	}
	case 86: {
		MadeCourceFromTxt(dot_, courceNo, "0_86_100_");
		break;
	}
	case 87: {
		MadeCourceFromTxt(dot_, courceNo, "0_87_100_");
		break;
	}
	case 88: {
		MadeCourceFromTxt(dot_, courceNo, "0_88_100_");
		break;
	}
	case 89: {
		MadeCourceFromTxt(dot_, courceNo, "0_89_100_");
		break;
	}
	case 90: {
		MadeCourceFromTxt(dot_, courceNo, "0_90_100_");
		break;
	}
	case 91: {
		MadeCourceFromTxt(dot_, courceNo, "0_91_100_");
		break;
	}
	case 92: {
		MadeCourceFromTxt(dot_, courceNo, "0_92_100_");
		break;
	}
	case 93: {
		MadeCourceFromTxt(dot_, courceNo, "0_93_100_");
		break;
	}
	case 94: {
		MadeCourceFromTxt(dot_, courceNo, "0_94_100_");
		break;
	}
	case 95: {
		MadeCourceFromTxt(dot_, courceNo, "0_95_100_");
		break;
	}
	case 96: {
		MadeCourceFromTxt(dot_, courceNo, "0_96_100_");
		break;
	}
	case 97: {
		MadeCourceFromTxt(dot_, courceNo, "0_97_100_");
		break;
	}
	case 98: {
		MadeCourceFromTxt(dot_, courceNo, "0_98_100_");
		break;
	}
	case 99: {
		MadeCourceFromTxt(dot_, courceNo, "0_99_100_");
		break;
	}
	case 100: {
		MadeCourceFromTxt(dot_, courceNo, "0_100_100_");
		break;
	}
	}

	//ここで高速化処理作成
	this->ReadDeta2_Prepare(dot_);

}

void GameDeta::MadeCourceFromRnd(Dot* dot_, int lvl_, int cCnt) {
	auto udf = UserDefault::getInstance();
	udf->setIntegerForKey("SELECT_COURCE_LENGTH", cCnt);
	int cNo;
	int cCnt_ = 0;
	for (int i = 0; i < cCnt; i++) {

		int lvl;
		if (i == 0) {
			cNo = 0;
		} else if (i == cCnt - 1) {
			cNo = 100;
		} else {
			cNo = arc4random() % static_cast<int>(99) + 1;
		}
		cCnt_++;
		this->MadeCource(dot_, cNo, lvl, cCnt_); //
	}
}

void GameDeta::MadeCourceFromTxt(Dot* dot_, int lvl, std::string st_) {
	//ctxt exp 0_01_08_at_100 //0:スタート、100:ゴール

	CCString* pStr = CCString::create(st_);
	dot_->ResetDot();
//	const char *str1 = "GameDeta::MadeCourceFromTxt";
//	log("%s", str1);

	String Bffer_;
	Bffer_ = "";
	const String hk = "_";

	int cnt = 0;
	int cNo;

	this->cLvl = 0;

	for (int i = 0; i < pStr->length(); i++) {

		String str_ = pStr->_string.substr(i, 1);

		if (str_._string == "_") {
//			const char *str3 = "GameDeta::MadeCourceFromTxt:cNo = Bffer_.intValue();";
//			log("%s", str3);
			cNo = Bffer_.intValue();
			cnt++;
			this->MadeCource(dot_, cNo, lvl, cnt); //
			auto udf = UserDefault::getInstance();
			udf->setIntegerForKey("SELECT_COURCE_LENGTH", cnt);
//			this->WriteDeta(dot_, lvl, cnt);

			Bffer_ = "";
		} else {
			Bffer_.append(str_._string);
		}

	}

}
void GameDeta::MadeCource(Dot* dot_, int cNo, int lvl, int cnt) {
	dot_->ResetDot();
	dot_->cNo = cNo;
	switch (cNo) {
	case 0: {
		dot_->SetPt.set(-380, -200); //スタート地点となる。
		dot_->StartLine();
		break;
	}

	case 1: {
		dot_->CPtn1();
		break;
	}
	case 2: {
		dot_->CPtn2();
		break;
	}
	case 3: {
		dot_->CPtn3();
		break;
	}
	case 4: {
		dot_->CPtn4();
		break;
	}
	case 5: {
		dot_->CPtn5();
		break;
	}
	case 6: {
		dot_->CPtn6();
		break;
	}
	case 7: {
		dot_->CPtn7();
		break;
	}
	case 8: {
		dot_->CPtn8();
		break;
	}
	case 9: {
		dot_->CPtn9();
		break;
	}
	case 10: {
		dot_->CPtn10();
		break;
	}
	case 11: {
		dot_->CPtn11();
		break;
	}
	case 12: {
		dot_->CPtn12();
		break;
	}
	case 13: {
		dot_->CPtn13();
		break;
	}
	case 14: {
		dot_->CPtn14();
		break;
	}
	case 15: {
		dot_->CPtn15();
		break;
	}
	case 16: {
		dot_->CPtn16();
		break;
	}
	case 17: {
		dot_->CPtn17();
		break;
	}
	case 18: {
		dot_->CPtn18();
		break;
	}
	case 19: {
		dot_->CPtn19();
		break;
	}
	case 20: {
		dot_->CPtn20();
		break;
	}
	case 21: {
		dot_->CPtn21();
		break;
	}
	case 22: {
		dot_->CPtn22();
		break;
	}
	case 23: {
		dot_->CPtn23();
		break;
	}
	case 24: {
		dot_->CPtn24();
		break;
	}
	case 25: {
		dot_->CPtn25();
		break;
	}
	case 26: {
		dot_->CPtn26();
		break;
	}
	case 27: {
		dot_->CPtn27();
		break;
	}
	case 28: {
		dot_->CPtn28();
		break;
	}
	case 29: {
		dot_->CPtn29();
		break;
	}
	case 30: {
		dot_->CPtn30();
		break;
	}
	case 31: {
		dot_->CPtn31();
		break;
	}
	case 32: {
		dot_->CPtn32();
		break;
	}
	case 33: {
		dot_->CPtn33();
		break;
	}
	case 34: {
		dot_->CPtn34();
		break;
	}
	case 35: {
		dot_->CPtn35();
		break;
	}
	case 36: {
		dot_->CPtn36();
		break;
	}
	case 37: {
		dot_->CPtn37();
		break;
	}
	case 38: {
		dot_->CPtn38();
		break;
	}
	case 39: {
		dot_->CPtn39();
		break;
	}
	case 40: {
		dot_->CPtn40();
		break;
	}
	case 41: {
		dot_->CPtn41();
		break;
	}
	case 42: {
		dot_->CPtn42();
		break;
	}
	case 43: {
		dot_->CPtn43();
		break;
	}
	case 44: {
		dot_->CPtn44();
		break;
	}
	case 45: {
		dot_->CPtn45();
		break;
	}
	case 46: {
		dot_->CPtn46();
		break;
	}
	case 47: {
		dot_->CPtn47();
		break;
	}
	case 48: {
		dot_->CPtn48();
		break;
	}
	case 49: {
		dot_->CPtn49();
		break;
	}
	case 50: {
		dot_->CPtn50();
		break;
	}
	case 51: {
		dot_->CPtn51();
		break;
	}
	case 52: {
		dot_->CPtn52();
		break;
	}
	case 53: {
		dot_->CPtn53();
		break;
	}
	case 54: {
		dot_->CPtn54();
		break;
	}
	case 55: {
		dot_->CPtn55();
		break;
	}
	case 56: {
		dot_->CPtn56();
		break;
	}
	case 57: {
		dot_->CPtn57();
		break;
	}
	case 58: {
		dot_->CPtn58();
		break;
	}
	case 59: {
		dot_->CPtn59();
		break;
	}
	case 60: {
		dot_->CPtn60();
		break;
	}
	case 61: {
		dot_->CPtn61();
		break;
	}
	case 62: {
		dot_->CPtn62();
		break;
	}
	case 63: {
		dot_->CPtn63();
		break;
	}
	case 64: {
		dot_->CPtn64();
		break;
	}
	case 65: {
		dot_->CPtn65();
		break;
	}
	case 66: {
		dot_->CPtn66();
		break;
	}
	case 67: {
		dot_->CPtn67();
		break;
	}
	case 68: {
		dot_->CPtn68();
		break;
	}
	case 69: {
		dot_->CPtn69();
		break;
	}
	case 70: {
		dot_->CPtn70();
		break;
	}
	case 71: {
		dot_->CPtn71();
		break;
	}
	case 72: {
		dot_->CPtn72();
		break;
	}
	case 73: {
		dot_->CPtn73();
		break;
	}
	case 74: {
		dot_->CPtn74();
		break;
	}
	case 75: {
		dot_->CPtn75();
		break;
	}
	case 76: {
		dot_->CPtn76();
		break;
	}
	case 77: {
		dot_->CPtn77();
		break;
	}
	case 78: {
		dot_->CPtn78();
		break;
	}
	case 79: {
		dot_->CPtn79();
		break;
	}
	case 80: {
		dot_->CPtn80();
		break;
	}
	case 81: {
		dot_->CPtn81();
		break;
	}
	case 82: {
		dot_->CPtn82();
		break;
	}
	case 83: {
		dot_->CPtn83();
		break;
	}
	case 84: {
		dot_->CPtn84();
		break;
	}
	case 85: {
		dot_->CPtn85();
		break;
	}
	case 86: {
		dot_->CPtn86();
		break;
	}
	case 87: {
		dot_->CPtn87();
		break;
	}
	case 88: {
		dot_->CPtn88();
		break;
	}
	case 89: {
		dot_->CPtn89();
		break;
	}
	case 90: {
		dot_->CPtn90();
		break;
	}
	case 91: {
		dot_->CPtn91();
		break;
	}
	case 92: {
		dot_->CPtn92();
		break;
	}
	case 93: {
		dot_->CPtn93();
		break;
	}
	case 94: {
		dot_->CPtn94();
		break;
	}
	case 95: {
		dot_->CPtn95();
		break;
	}
	case 96: {
		dot_->CPtn96();
		break;
	}
	case 97: {
		dot_->CPtn97();
		break;
	}
	case 98: {
		dot_->CPtn98();
		break;
	}
	case 99: {
		dot_->CPtn99();
		break;
	}
	case 100: {
//		const char *str3 = "GameDeta::MadeCourceFromTxt:dot_->GoalLine();";
//		log("%s", str3);
		dot_->GoalLine();
		break;
	}
	}

	this->cLvl += dot_->cLvl;

	this->WriteDeta(dot_, lvl, cnt);

}
void GameDeta::RndMadeCource(Dot* dot_, int lvl, const int cnt) {

	int cnt_ = 1;
	int x = 0;
	while (cnt_ <= cnt) {

		if (cnt_ == 1) {
			dot_->SetPt.set(-200, -500);
			dot_->ResetDot();
			dot_->StartLine();
//			const char *str0 = "GameDeta::RndMadeCource_dot_->StartLine();";
//			log("%s", str0);
		} else if (cnt_ == cnt) {
			dot_->ResetDot();
			dot_->GoalLine();
//			const char *str1 = "GameDeta::RndMadeCource_dot_->GoalLine();";
//			log("%s", str1);
		} else {
			dot_->ResetDot();
			x = arc4random() % static_cast<int>(20);
			x++;
//			x = 20;
			switch (x) {

			case 0: {

//				dot_->CPtn1();
				int rndA = arc4random() % static_cast<int>(5) + 1;
				int rndB = arc4random() % static_cast<int>(300) + 100;
				int rndC = arc4random() % static_cast<int>(400) + 50;
				dot_->rndMade(rndA, rndB, rndC, 10);
				break;
			}
			case 1: {
				dot_->CPtn1();
				break;
			}
			case 2: {
				dot_->CPtn2();
				break;
			}
			case 3: {
				dot_->CPtn3();
				break;
			}
			case 4: {
				dot_->CPtn4();
				break;
			}
			case 5: {
				dot_->CPtn5();
				break;
			}
			case 6: {
				dot_->CPtn6();
				break;
			}
			case 7: {
				dot_->CPtn7();
				break;
			}
			case 8: {
				dot_->CPtn8();
				break;
			}
			case 9: {
				dot_->CPtn9();
				break;
			}
			case 10: {
				dot_->CPtn10();
				break;
			}
			case 11: {
				dot_->CPtn11();
				break;
			}
			case 12: {
				dot_->CPtn12();
				break;
			}
			case 13: {
				dot_->CPtn13();
				break;
			}
			case 14: {
				dot_->CPtn14();
				break;
			}
			case 15: {
				dot_->CPtn15();
				break;
			}
			case 16: {
				dot_->CPtn16();
				break;
			}
			case 17: {
				dot_->CPtn17();
				break;
			}
			case 18: {
				dot_->CPtn18();
				break;
			}
			case 19: {
				dot_->CPtn19();
				break;
			}
			case 20: {
				dot_->CPtn20();
				break;
			}

			}

//			const char *str2 = "GameDeta::RndMadeCource_dot_->rndMade(rndA, rndB, rndC, 10);";
//			log("%s", str2);

		}

		this->WriteDeta(dot_, lvl, cnt_);
		//外部ファイルに書き込む時
//		this->WriteDetaToFile(dot_, lvl, cnt_);
		cnt_++;

	}

}

void GameDeta::WriteDetaToFile(Dot* dot_, int cx_, int cy_) {

	JniMethodInfo t;
	std::string mMapDetaSt;

	int x = 1;

//	const char *str0 = "GameDeta::WriteDetaToFile";
//	log("%s", str0);
	for (int i = 0; i < dot_->dspCnt; i++) {
		mMapDetaSt.append(StringUtils::toString((int) dot_->_dotG.at(i)->getPosition().x) + "/");
		mMapDetaSt.append(StringUtils::toString((int) dot_->_dotG.at(i)->getPosition().y) + "/");
//		const char *str2 = "GameDeta::WriteDeta_2";
//		log("%s", str2);
	}
	mMapDetaSt.append(StringUtils::toString("@"));

	for (int i = 0; i < dot_->dsCnt; i++) {
		mMapDetaSt.append(StringUtils::toString((int) dot_->dShape[i].x) + "/");
		mMapDetaSt.append(StringUtils::toString((int) dot_->dShape[i].y) + "/");
	}

// クラス名とメソッド名を指定します。
//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(IILjava/lang/String;)V")) {
		jstring jstr = t.env->NewStringUTF(mMapDetaSt.c_str());
		t.env->CallStaticVoidMethod(t.classID, t.methodID, cx_, cy_, jstr);
// 解放
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);

	}

}
void GameDeta::ReadDetaFromAssetFile(Dot* dot_, int cx_, int cy_) {

	CCDictionary* meirodata_;
	meirodata_ = CCDictionary::createWithContentsOfFile("courcedeta.plist");
//	int index_ = 1;

	CCString* map = (CCString*) meirodata_->objectForKey(
			"cource_" + StringUtils::toString((int) cx_) + "_" + StringUtils::toString((int) cy_));

	String Str = map->getCString();
//	CCString* pStr = CCString::create(Str._string);
	this->ReadDetaFromString(dot_, Str._string);

}
void GameDeta::ReadDetaFromFile(Dot* dot_, int cx_, int cy_) {

	JniMethodInfo t;
	std::string mMapDetaSt;

//	int x = 1;

//if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, WRITEDETA, "(I[I)V")) {
	if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, READDETA, "(II)Ljava/lang/String;")) {
		jstring jstr = (jstring) t.env->CallStaticObjectMethod(t.classID, t.methodID, cx_, cy_);
		const char* str = t.env->GetStringUTFChars(jstr, NULL);
		mMapDetaSt = str;
// 解放
		t.env->ReleaseStringUTFChars(jstr, str);
		t.env->DeleteLocalRef(t.classID);
		t.env->DeleteLocalRef(jstr);
	}

	this->ReadDetaFromString(dot_, mMapDetaSt);

}
void GameDeta::ReadDetaFromString(Dot* dot_, std::string st_) {

	CCString* pStr = CCString::create(st_);
	dot_->ResetDot();
//	const char *str1 = "GameDeta::ReadDetaFromString";
//	log("%s", str1);

	String Bffer_;
	String hk = "@";

	int fsturn = 0;
	int turn = 0;
	float x_;
	float y_;
	float s_;
	float xx_;
	float yy_;

	for (int i = 0; i < pStr->length(); i++) {

		String str_ = pStr->_string.substr(i, 1);

		if (fsturn == 0) {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {
//					const char *str3 = "GameDeta::ReadDeta_x_=Bffer_.floatValue();";
//					log("%s", str3);
					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {
//					const char *str3 =
//							"GameDeta::ReadDeta__dot->SetDotType((Dot::DotType) Bffer_.intValue());";
//					log("%s", str3);
					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dot_->AddDot(Vec2(x_, y_), false);
					turn = 0;

					break;
				}
				}
			} else if (str_._string == "@") {
				fsturn++;
				turn = 0;
				x_ = 0;
				y_ = 0;
			} else {
				Bffer_.append(str_._string);
			}

		} else if (fsturn == 1) {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {
//					const char *str3 = "GameDeta::ReadDeta_x_=Bffer_.floatValue();";
//					log("%s", str3);
					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {
//					const char *str3 =
//							"GameDeta::ReadDeta__dot->SetDotType((Dot::DotType) Bffer_.intValue());";
//					log("%s", str3);
					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dot_->dotPoints[dot_->dpCnt].set(Vec2(x_, y_));
					dot_->dpCnt++;
					turn = 0;

					break;
				}
				}
			} else {
				Bffer_.append(str_._string);
			}

		}
	}

	dot_->SetShape();

}
void GameDeta::ReadDeta(Dot* dot_, int cx_, int cy_) {

	dot_->ResetDot();

//	const char *stra = "GameDeta::ReadDeta(Dot* dot_)";
//	log("%s", stra);

//	String Str = UserDefault::getInstance()->getStringForKey("GDETA", "N");
	String Str = this->GetCourceDeta(cx_, cy_);

	CCString* pStr = CCString::create(Str._string);

	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
//		const char *str0 = "MeiroMeder::MeiroMadeFromFile_debug_N";
//		log("%s", str0);
		dot_->rndMade(1000, 10);
		return;
	}

//	const char *str1 = "GameDeta::ReadDeta(Dot* dot_)";
//	log("%s", str1);

	String Bffer_;
	String hk = "@";

	int fsturn = 0;
	int turn = 0;
	float x_;
	float y_;
	float s_;
	float xx_;
	float yy_;

	int sCnt = 0;

//	const char *str3 = "GameDeta::ReadDeta_ShowWrite";
//	log("%s", str3);

	for (int i = 0; i < pStr->length(); i++) {

		String str_ = pStr->_string.substr(i, 1);
		switch (fsturn) {

		case 0: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {

					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {

					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dot_->SetPt2.set(x_, y_);

					break;
				}

				case 2: {

					dot_->mrad2_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					break;
				}

				case 3: {

					dot_->dsCnt = Bffer_.intValue();
					Bffer_ = "";
					turn++;

					break;
				}
				case 4: {

					dot_->cNo = Bffer_.intValue();
					Bffer_ = "";
					turn++;

					break;
				}
				}
			} else if (str_._string == "@") {
				fsturn++;
				Bffer_ = "";
				turn = 0;

				x_ = 0;
				y_ = 0;

			} else {
				Bffer_.append(str_._string);

			}

			break;
		}

		case 1: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {
//					const char *str3 = "GameDeta::ReadDeta_x_=Bffer_.floatValue();";
//					log("%s", str3);
					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {
//					const char *str3 =
//							"GameDeta::ReadDeta__dot->SetDotType((Dot::DotType) Bffer_.intValue());";
//					log("%s", str3);
					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dot_->AddDot(Vec2(x_, y_), false);
					turn = 0;

					break;
				}
				}
			} else if (str_._string == "@") {
				fsturn++;
				turn = 0;
				Bffer_ = "";
				x_ = 0;
				y_ = 0;

			} else {
				Bffer_.append(str_._string);

			}
			break;
		}
		case 2: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {
//					const char *str3 = "GameDeta::ReadDeta_x_=Bffer_.floatValue();";
//					log("%s", str3);
					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {
//					const char *str3 =
//							"GameDeta::ReadDeta__dot->SetDotType((Dot::DotType) Bffer_.intValue());";
//					log("%s", str3);
					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					dot_->dShape[sCnt].set(Vec2(x_, y_));
					sCnt++;
//					dot_->dotPoints[dot_->dpCnt].set(Vec2(x_, y_));
//					dot_->dpCnt++;
					turn = 0;

					break;
				}
				}
			} else {
				Bffer_.append(str_._string);

			}
			break;
		}
		}
	}
//	dot_->dsCnt = sCnt;
	dot_->SetShape2();

	dot_->ShowCourceName(dot_->cNo); //コースナンバーを表示

}
void GameDeta::ReadDeta2(Dot* dot_, int cx_, int cy_, bool cFlg, bool nFlg) {
	//あらかじめ作成済みのコースデータから作成。高速化

//	int CNos[50];//コースナンバー
//	int dotPointNo_ = 0;
//	int dotPointNo[50];
//	Vec2 dotPoints[10000]; //シェープ作成用のドット。
//	int dotShapeNo_=0;
//	int dotShapeNo[50];
//	Vec2 Shapes[10000]; //シェープのドット。

	const char *str = "GameDeta::ReadDeta2);";
	log("%s", str);

	dot_->ResetDot();
	dot_->SetPt2.set(dotPoints[dotPointNo[cy_ - 1]]);
	dot_->mrad2_ = 0;

	dot_->cNo = CNos[cy_];
	int k = 0;
	if (cy_ == 0) {

		dot_->fstPt.set(dotPoints[0]); //最初のポイント
		dot_->lstPt.set(dotPoints[dotPointNo[cy_] - 1]); //最後のポイント

		for (int i = 0; i < dotPointNo[cy_]; i++) {
			dot_->AddDot(dotPoints[i], false);
		}
		for (int i = 0; i < dotShapeNo[cy_]; i++) {
			dot_->dShape[k].set(dotShapes[i]);
			k++;
		}
	} else {

		dot_->fstPt.set(dotPoints[dotPointNo[cy_ - 1] + 1]); //最初のポイント
		dot_->lstPt.set(dotPoints[dotPointNo[cy_] - 1]); //最後のポイント

		for (int i = dotPointNo[cy_ - 1] + 1; i < dotPointNo[cy_]; i++) {
			dot_->AddDot(dotPoints[i], false);
//			const char *str2 = "GameDeta::ReadDeta2);";
//			log("%s", str2);

		}
		for (int i = dotShapeNo[cy_ - 1]; i < dotShapeNo[cy_]; i++) {
			dot_->dShape[k].set(dotShapes[i]);
			k++;
		}
	}

	dot_->dsCnt = k;
	dot_->SetShape2();
	if (cFlg) {
		dot_->ShowCourceName(dot_->cNo); //コースナンバーを表示
	}
	if (nFlg) {
		dot_->ShowCourceOrder(this->GetSelectCourceLength() - cy_ + 1, this->GetSelectCourceLength() - 1); //コースナンバーを表示
	}
}
void GameDeta::ReadDeta2(Dot* dot_, int cx_, int cy_) {
	//あらかじめ作成済みのコースデータから作成。高速化

//	int CNos[50];//コースナンバー
//	int dotPointNo_ = 0;
//	int dotPointNo[50];
//	Vec2 dotPoints[10000]; //シェープ作成用のドット。
//	int dotShapeNo_=0;
//	int dotShapeNo[50];
//	Vec2 Shapes[10000]; //シェープのドット。

//	const char *str = "GameDeta::ReadDeta2);";
//	log("%s", str);

	dot_->ResetDot();
	dot_->SetPt2.set(dotPoints[dotPointNo[cy_ - 1]]);
	dot_->mrad2_ = 0;

	dot_->cNo = CNos[cy_];
	int k = 0;
	if (cy_ == 0) {

		dot_->fstPt.set(dotPoints[0]); //最初のポイント
		dot_->lstPt.set(dotPoints[dotPointNo[cy_] - 1]); //最後のポイント

		for (int i = 0; i < dotPointNo[cy_]; i++) {
			dot_->AddDot(dotPoints[i], false);
		}
		for (int i = 0; i < dotShapeNo[cy_]; i++) {
			dot_->dShape[k].set(dotShapes[i]);
			k++;
		}
	} else {

		dot_->fstPt.set(dotPoints[dotPointNo[cy_ - 1] + 1]); //最初のポイント
		dot_->lstPt.set(dotPoints[dotPointNo[cy_] - 1]); //最後のポイント

		for (int i = dotPointNo[cy_ - 1] + 1; i < dotPointNo[cy_]; i++) {
			dot_->AddDot(dotPoints[i], false);
//			const char *str2 = "GameDeta::ReadDeta2);";
//			log("%s", str2);

		}
		for (int i = dotShapeNo[cy_ - 1]; i < dotShapeNo[cy_]; i++) {
			dot_->dShape[k].set(dotShapes[i]);
			k++;
		}
	}

	dot_->dsCnt = k;
	dot_->SetShape2();
//	dot_->ShowCourceName(dot_->cNo); //コースナンバーを表示
	dot_->ShowCourceOrder(this->GetSelectCourceLength() - cy_ + 1, this->GetSelectCourceLength() - 1); //コースナンバーを表示

}
void GameDeta::ReadDeta2_Prepare(Dot* dot_) {

	for (int i = 0; i <= GetSelectCourceLength(); i++) {
		ReadDeta2_Prepare(dot_, 0, i);
	}

}
void GameDeta::ReadDeta2_Prepare(Dot* dot_, int cx_, int cy_) {

	if (cy_ == 0) {
		dotPointNo_ = 0;
		dotShapeNo_ = 0;
	} else {
		dotPointNo_ = dotPointNo[cy_ - 1];
		dotShapeNo_ = dotShapeNo[cy_ - 1];
//		const char *str2 = "GameDeta::ReadDeta2_Prepare(Dot* dot_, int cx_, int cy_) ";
//		log("%s", str2);
	}

	//あらかじめコースデータを配列に作成。
	dot_->ResetDot();

	String Str = this->GetCourceDeta(cx_, cy_);

	CCString* pStr = CCString::create(Str._string);

	if (pStr->_string.substr(0, 1) == "N" || pStr->_string == "") {
		return;
	}

	String Bffer_;
	String hk = "@";

	int fsturn = 0;
	int turn = 0;
	float x_;
	float y_;
	float s_;
	float xx_;
	float yy_;

	int sCnt = 0;

	for (int i = 0; i < pStr->length(); i++) {

		String str_ = pStr->_string.substr(i, 1);
		switch (fsturn) {

		case 0: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {

					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {

					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dot_->SetPt2.set(x_, y_);
					dotPoints[dotPointNo_].set(Vec2(x_, y_));
					dotPointNo_++;
					break;
				}

				case 2: {

					dot_->mrad2_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					break;
				}

				case 3: {

					dot_->dsCnt = Bffer_.intValue();
					Bffer_ = "";
					turn++;

					break;
				}
				case 4: {

					CNos[cy_] = Bffer_.intValue();
					dot_->cNo = Bffer_.intValue();
					Bffer_ = "";
					turn++;

					break;
				}
				}
			} else if (str_._string == "@") {
				fsturn++;
				Bffer_ = "";
				turn = 0;

				x_ = 0;
				y_ = 0;

			} else {
				Bffer_.append(str_._string);

			}

			break;
		}

		case 1: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {

					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {

					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dotPoints[dotPointNo_].set(Vec2(x_, y_));
					dotPointNo_++;

					dot_->AddDot(Vec2(x_, y_), false);
					turn = 0;

					break;
				}
				}
			} else if (str_._string == "@") {
				fsturn++;
				turn = 0;
				Bffer_ = "";
				x_ = 0;
				y_ = 0;

			} else {
				Bffer_.append(str_._string);

			}
			break;
		}
		case 2: {

			if (str_._string == "/") {

				switch (turn) {
				case 0: {
//					const char *str3 = "GameDeta::ReadDeta_x_=Bffer_.floatValue();";
//					log("%s", str3);
					x_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;
					break;
				}
				case 1: {
//					const char *str3 =
//							"GameDeta::ReadDeta__dot->SetDotType((Dot::DotType) Bffer_.intValue());";
//					log("%s", str3);
					y_ = Bffer_.floatValue();
					Bffer_ = "";
					turn++;

					dotShapes[dotShapeNo_].set(Vec2(x_, y_));
					dotShapeNo_++;

					sCnt++;

					turn = 0;

					break;
				}
				}
			} else {
				Bffer_.append(str_._string);

			}
			break;
		}
		}
	}

	dotShapeNo[cy_] = dotShapeNo_;
	dotPointNo[cy_] = dotPointNo_;

}

void GameDeta::setStageCoin(int x, int y) {

	auto udf = UserDefault::getInstance();

	switch (x) {

	case 1: {
		return udf->setIntegerForKey("COIN1", y);
		break;
	}
	case 2: {
		return udf->setIntegerForKey("COIN2", y);
		break;
	}
	case 3: {
		return udf->setIntegerForKey("COIN3", y);
		break;
	}
	case 4: {
		return udf->setIntegerForKey("COIN4", y);
		break;
	}
	case 5: {
		return udf->setIntegerForKey("COIN5", y);
		break;
	}
	case 6: {
		return udf->setIntegerForKey("COIN6", y);
		break;
	}
	case 7: {
		return udf->setIntegerForKey("COIN7", y);
		break;
	}
	case 8: {
		return udf->setIntegerForKey("COIN8", y);
		break;
	}
	case 9: {
		return udf->setIntegerForKey("COIN9", y);
		break;
	}
	case 10: {
		return udf->setIntegerForKey("COIN10", y);
		break;
	}
	case 11: {
		return udf->setIntegerForKey("COIN11", y);
		break;
	}
	case 12: {
		return udf->setIntegerForKey("COIN12", y);
		break;
	}
	case 13: {
		return udf->setIntegerForKey("COIN13", y);
		break;
	}
	case 14: {
		return udf->setIntegerForKey("COIN14", y);
		break;
	}
	case 15: {
		return udf->setIntegerForKey("COIN15", y);
		break;
	}
	case 16: {
		return udf->setIntegerForKey("COIN16", y);
		break;
	}
	case 17: {
		return udf->setIntegerForKey("COIN17", y);
		break;
	}
	case 18: {
		return udf->setIntegerForKey("COIN18", y);
		break;
	}
	case 19: {
		return udf->setIntegerForKey("COIN19", y);
		break;
	}
	case 20: {
		return udf->setIntegerForKey("COIN20", y);
		break;
	}
	case 21: {
		return udf->setIntegerForKey("COIN21", y);
		break;
	}
	case 22: {
		return udf->setIntegerForKey("COIN22", y);
		break;
	}
	case 23: {
		return udf->setIntegerForKey("COIN23", y);
		break;
	}
	case 24: {
		return udf->setIntegerForKey("COIN24", y);
		break;
	}
	case 25: {
		return udf->setIntegerForKey("COIN25", y);
		break;
	}
	case 26: {
		return udf->setIntegerForKey("COIN26", y);
		break;
	}
	case 27: {
		return udf->setIntegerForKey("COIN27", y);
		break;
	}
	case 28: {
		return udf->setIntegerForKey("COIN28", y);
		break;
	}
	case 29: {
		return udf->setIntegerForKey("COIN29", y);
		break;
	}
	case 30: {
		return udf->setIntegerForKey("COIN30", y);
		break;
	}
	case 31: {
		return udf->setIntegerForKey("COIN31", y);
		break;
	}
	case 32: {
		return udf->setIntegerForKey("COIN32", y);
		break;
	}
	case 33: {
		return udf->setIntegerForKey("COIN33", y);
		break;
	}
	case 34: {
		return udf->setIntegerForKey("COIN34", y);
		break;
	}
	case 35: {
		return udf->setIntegerForKey("COIN35", y);
		break;
	}
	case 36: {
		return udf->setIntegerForKey("COIN36", y);
		break;
	}
	case 37: {
		return udf->setIntegerForKey("COIN37", y);
		break;
	}
	case 38: {
		return udf->setIntegerForKey("COIN38", y);
		break;
	}
	case 39: {
		return udf->setIntegerForKey("COIN39", y);
		break;
	}
	case 40: {
		return udf->setIntegerForKey("COIN40", y);
		break;
	}
	case 41: {
		return udf->setIntegerForKey("COIN41", y);
		break;
	}
	case 42: {
		return udf->setIntegerForKey("COIN42", y);
		break;
	}
	case 43: {
		return udf->setIntegerForKey("COIN43", y);
		break;
	}
	case 44: {
		return udf->setIntegerForKey("COIN44", y);
		break;
	}
	case 45: {
		return udf->setIntegerForKey("COIN45", y);
		break;
	}
	case 46: {
		return udf->setIntegerForKey("COIN46", y);
		break;
	}
	case 47: {
		return udf->setIntegerForKey("COIN47", y);
		break;
	}
	case 48: {
		return udf->setIntegerForKey("COIN48", y);
		break;
	}
	case 49: {
		return udf->setIntegerForKey("COIN49", y);
		break;
	}
	case 50: {
		return udf->setIntegerForKey("COIN50", y);
		break;
	}
	case 51: {
		return udf->setIntegerForKey("COIN51", y);
		break;
	}
	case 52: {
		return udf->setIntegerForKey("COIN52", y);
		break;
	}
	case 53: {
		return udf->setIntegerForKey("COIN53", y);
		break;
	}
	case 54: {
		return udf->setIntegerForKey("COIN54", y);
		break;
	}
	case 55: {
		return udf->setIntegerForKey("COIN55", y);
		break;
	}
	case 56: {
		return udf->setIntegerForKey("COIN56", y);
		break;
	}
	case 57: {
		return udf->setIntegerForKey("COIN57", y);
		break;
	}
	case 58: {
		return udf->setIntegerForKey("COIN58", y);
		break;
	}
	case 59: {
		return udf->setIntegerForKey("COIN59", y);
		break;
	}
	case 60: {
		return udf->setIntegerForKey("COIN60", y);
		break;
	}
	case 61: {
		return udf->setIntegerForKey("COIN61", y);
		break;
	}
	case 62: {
		return udf->setIntegerForKey("COIN62", y);
		break;
	}
	case 63: {
		return udf->setIntegerForKey("COIN63", y);
		break;
	}
	case 64: {
		return udf->setIntegerForKey("COIN64", y);
		break;
	}
	case 65: {
		return udf->setIntegerForKey("COIN65", y);
		break;
	}
	case 66: {
		return udf->setIntegerForKey("COIN66", y);
		break;
	}
	case 67: {
		return udf->setIntegerForKey("COIN67", y);
		break;
	}
	case 68: {
		return udf->setIntegerForKey("COIN68", y);
		break;
	}
	case 69: {
		return udf->setIntegerForKey("COIN69", y);
		break;
	}
	case 70: {
		return udf->setIntegerForKey("COIN70", y);
		break;
	}
	case 71: {
		return udf->setIntegerForKey("COIN71", y);
		break;
	}
	case 72: {
		return udf->setIntegerForKey("COIN72", y);
		break;
	}
	case 73: {
		return udf->setIntegerForKey("COIN73", y);
		break;
	}
	case 74: {
		return udf->setIntegerForKey("COIN74", y);
		break;
	}
	case 75: {
		return udf->setIntegerForKey("COIN75", y);
		break;
	}
	case 76: {
		return udf->setIntegerForKey("COIN76", y);
		break;
	}
	case 77: {
		return udf->setIntegerForKey("COIN77", y);
		break;
	}
	case 78: {
		return udf->setIntegerForKey("COIN78", y);
		break;
	}
	case 79: {
		return udf->setIntegerForKey("COIN79", y);
		break;
	}
	case 80: {
		return udf->setIntegerForKey("COIN80", y);
		break;
	}
	case 81: {
		return udf->setIntegerForKey("COIN81", y);
		break;
	}
	case 82: {
		return udf->setIntegerForKey("COIN82", y);
		break;
	}
	case 83: {
		return udf->setIntegerForKey("COIN83", y);
		break;
	}
	case 84: {
		return udf->setIntegerForKey("COIN84", y);
		break;
	}
	case 85: {
		return udf->setIntegerForKey("COIN85", y);
		break;
	}
	case 86: {
		return udf->setIntegerForKey("COIN86", y);
		break;
	}
	case 87: {
		return udf->setIntegerForKey("COIN87", y);
		break;
	}
	case 88: {
		return udf->setIntegerForKey("COIN88", y);
		break;
	}
	case 89: {
		return udf->setIntegerForKey("COIN89", y);
		break;
	}
	case 90: {
		return udf->setIntegerForKey("COIN90", y);
		break;
	}
	case 91: {
		return udf->setIntegerForKey("COIN91", y);
		break;
	}
	case 92: {
		return udf->setIntegerForKey("COIN92", y);
		break;
	}
	case 93: {
		return udf->setIntegerForKey("COIN93", y);
		break;
	}
	case 94: {
		return udf->setIntegerForKey("COIN94", y);
		break;
	}
	case 95: {
		return udf->setIntegerForKey("COIN95", y);
		break;
	}
	case 96: {
		return udf->setIntegerForKey("COIN96", y);
		break;
	}
	case 97: {
		return udf->setIntegerForKey("COIN97", y);
		break;
	}
	case 98: {
		return udf->setIntegerForKey("COIN98", y);
		break;
	}
	case 99: {
		return udf->setIntegerForKey("COIN99", y);
		break;
	}
	case 100: {
		return udf->setIntegerForKey("COIN100", y);
		break;
	}

	}
}
int GameDeta::getStageCoin(int x) {

	auto udf = UserDefault::getInstance();

	switch (x) {

	case 1: {
		return udf->getIntegerForKey("COIN1", 0);
		break;
	}
	case 2: {
		return udf->getIntegerForKey("COIN2", 0);
		break;
	}
	case 3: {
		return udf->getIntegerForKey("COIN3", 0);
		break;
	}
	case 4: {
		return udf->getIntegerForKey("COIN4", 0);
		break;
	}
	case 5: {
		return udf->getIntegerForKey("COIN5", 0);
		break;
	}
	case 6: {
		return udf->getIntegerForKey("COIN6", 0);
		break;
	}
	case 7: {
		return udf->getIntegerForKey("COIN7", 0);
		break;
	}
	case 8: {
		return udf->getIntegerForKey("COIN8", 0);
		break;
	}
	case 9: {
		return udf->getIntegerForKey("COIN9", 0);
		break;
	}
	case 10: {
		return udf->getIntegerForKey("COIN10", 0);
		break;
	}
	case 11: {
		return udf->getIntegerForKey("COIN11", 0);
		break;
	}
	case 12: {
		return udf->getIntegerForKey("COIN12", 0);
		break;
	}
	case 13: {
		return udf->getIntegerForKey("COIN13", 0);
		break;
	}
	case 14: {
		return udf->getIntegerForKey("COIN14", 0);
		break;
	}
	case 15: {
		return udf->getIntegerForKey("COIN15", 0);
		break;
	}
	case 16: {
		return udf->getIntegerForKey("COIN16", 0);
		break;
	}
	case 17: {
		return udf->getIntegerForKey("COIN17", 0);
		break;
	}
	case 18: {
		return udf->getIntegerForKey("COIN18", 0);
		break;
	}
	case 19: {
		return udf->getIntegerForKey("COIN19", 0);
		break;
	}
	case 20: {
		return udf->getIntegerForKey("COIN20", 0);
		break;
	}
	case 21: {
		return udf->getIntegerForKey("COIN21", 0);
		break;
	}
	case 22: {
		return udf->getIntegerForKey("COIN22", 0);
		break;
	}
	case 23: {
		return udf->getIntegerForKey("COIN23", 0);
		break;
	}
	case 24: {
		return udf->getIntegerForKey("COIN24", 0);
		break;
	}
	case 25: {
		return udf->getIntegerForKey("COIN25", 0);
		break;
	}
	case 26: {
		return udf->getIntegerForKey("COIN26", 0);
		break;
	}
	case 27: {
		return udf->getIntegerForKey("COIN27", 0);
		break;
	}
	case 28: {
		return udf->getIntegerForKey("COIN28", 0);
		break;
	}
	case 29: {
		return udf->getIntegerForKey("COIN29", 0);
		break;
	}
	case 30: {
		return udf->getIntegerForKey("COIN30", 0);
		break;
	}
	case 31: {
		return udf->getIntegerForKey("COIN31", 0);
		break;
	}
	case 32: {
		return udf->getIntegerForKey("COIN32", 0);
		break;
	}
	case 33: {
		return udf->getIntegerForKey("COIN33", 0);
		break;
	}
	case 34: {
		return udf->getIntegerForKey("COIN34", 0);
		break;
	}
	case 35: {
		return udf->getIntegerForKey("COIN35", 0);
		break;
	}
	case 36: {
		return udf->getIntegerForKey("COIN36", 0);
		break;
	}
	case 37: {
		return udf->getIntegerForKey("COIN37", 0);
		break;
	}
	case 38: {
		return udf->getIntegerForKey("COIN38", 0);
		break;
	}
	case 39: {
		return udf->getIntegerForKey("COIN39", 0);
		break;
	}
	case 40: {
		return udf->getIntegerForKey("COIN40", 0);
		break;
	}
	case 41: {
		return udf->getIntegerForKey("COIN41", 0);
		break;
	}
	case 42: {
		return udf->getIntegerForKey("COIN42", 0);
		break;
	}
	case 43: {
		return udf->getIntegerForKey("COIN43", 0);
		break;
	}
	case 44: {
		return udf->getIntegerForKey("COIN44", 0);
		break;
	}
	case 45: {
		return udf->getIntegerForKey("COIN45", 0);
		break;
	}
	case 46: {
		return udf->getIntegerForKey("COIN46", 0);
		break;
	}
	case 47: {
		return udf->getIntegerForKey("COIN47", 0);
		break;
	}
	case 48: {
		return udf->getIntegerForKey("COIN48", 0);
		break;
	}
	case 49: {
		return udf->getIntegerForKey("COIN49", 0);
		break;
	}
	case 50: {
		return udf->getIntegerForKey("COIN50", 0);
		break;
	}
	case 51: {
		return udf->getIntegerForKey("COIN51", 0);
		break;
	}
	case 52: {
		return udf->getIntegerForKey("COIN52", 0);
		break;
	}
	case 53: {
		return udf->getIntegerForKey("COIN53", 0);
		break;
	}
	case 54: {
		return udf->getIntegerForKey("COIN54", 0);
		break;
	}
	case 55: {
		return udf->getIntegerForKey("COIN55", 0);
		break;
	}
	case 56: {
		return udf->getIntegerForKey("COIN56", 0);
		break;
	}
	case 57: {
		return udf->getIntegerForKey("COIN57", 0);
		break;
	}
	case 58: {
		return udf->getIntegerForKey("COIN58", 0);
		break;
	}
	case 59: {
		return udf->getIntegerForKey("COIN59", 0);
		break;
	}
	case 60: {
		return udf->getIntegerForKey("COIN60", 0);
		break;
	}
	case 61: {
		return udf->getIntegerForKey("COIN61", 0);
		break;
	}
	case 62: {
		return udf->getIntegerForKey("COIN62", 0);
		break;
	}
	case 63: {
		return udf->getIntegerForKey("COIN63", 0);
		break;
	}
	case 64: {
		return udf->getIntegerForKey("COIN64", 0);
		break;
	}
	case 65: {
		return udf->getIntegerForKey("COIN65", 0);
		break;
	}
	case 66: {
		return udf->getIntegerForKey("COIN66", 0);
		break;
	}
	case 67: {
		return udf->getIntegerForKey("COIN67", 0);
		break;
	}
	case 68: {
		return udf->getIntegerForKey("COIN68", 0);
		break;
	}
	case 69: {
		return udf->getIntegerForKey("COIN69", 0);
		break;
	}
	case 70: {
		return udf->getIntegerForKey("COIN70", 0);
		break;
	}
	case 71: {
		return udf->getIntegerForKey("COIN71", 0);
		break;
	}
	case 72: {
		return udf->getIntegerForKey("COIN72", 0);
		break;
	}
	case 73: {
		return udf->getIntegerForKey("COIN73", 0);
		break;
	}
	case 74: {
		return udf->getIntegerForKey("COIN74", 0);
		break;
	}
	case 75: {
		return udf->getIntegerForKey("COIN75", 0);
		break;
	}
	case 76: {
		return udf->getIntegerForKey("COIN76", 0);
		break;
	}
	case 77: {
		return udf->getIntegerForKey("COIN77", 0);
		break;
	}
	case 78: {
		return udf->getIntegerForKey("COIN78", 0);
		break;
	}
	case 79: {
		return udf->getIntegerForKey("COIN79", 0);
		break;
	}
	case 80: {
		return udf->getIntegerForKey("COIN80", 0);
		break;
	}
	case 81: {
		return udf->getIntegerForKey("COIN81", 0);
		break;
	}
	case 82: {
		return udf->getIntegerForKey("COIN82", 0);
		break;
	}
	case 83: {
		return udf->getIntegerForKey("COIN83", 0);
		break;
	}
	case 84: {
		return udf->getIntegerForKey("COIN84", 0);
		break;
	}
	case 85: {
		return udf->getIntegerForKey("COIN85", 0);
		break;
	}
	case 86: {
		return udf->getIntegerForKey("COIN86", 0);
		break;
	}
	case 87: {
		return udf->getIntegerForKey("COIN87", 0);
		break;
	}
	case 88: {
		return udf->getIntegerForKey("COIN88", 0);
		break;
	}
	case 89: {
		return udf->getIntegerForKey("COIN89", 0);
		break;
	}
	case 90: {
		return udf->getIntegerForKey("COIN90", 0);
		break;
	}
	case 91: {
		return udf->getIntegerForKey("COIN91", 0);
		break;
	}
	case 92: {
		return udf->getIntegerForKey("COIN92", 0);
		break;
	}
	case 93: {
		return udf->getIntegerForKey("COIN93", 0);
		break;
	}
	case 94: {
		return udf->getIntegerForKey("COIN94", 0);
		break;
	}
	case 95: {
		return udf->getIntegerForKey("COIN95", 0);
		break;
	}
	case 96: {
		return udf->getIntegerForKey("COIN96", 0);
		break;
	}
	case 97: {
		return udf->getIntegerForKey("COIN97", 0);
		break;
	}
	case 98: {
		return udf->getIntegerForKey("COIN98", 0);
		break;
	}
	case 99: {
		return udf->getIntegerForKey("COIN99", 0);
		break;
	}
	case 100: {
		return udf->getIntegerForKey("COIN100", 0);
		break;
	}
	default: {

		return -1;
		break;
	}

	}
}

