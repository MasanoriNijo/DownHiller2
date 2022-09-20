#ifndef Lang_hpp
#define Lang_hpp
#include <stdio.h>

// 各文言を記述
static const std::string L_TITLE = "自転車\nゲーム";
static const std::string L_TITLE2 = "ゲーム";
static const std::string L_TITLE_SELECT_STAGE = "コースを選択";
static const std::string L_TITLE_SELECT_COURCE = "コースを選択";
static const std::string L_STAGE = "ステージ";
static const std::string L_BTN_START = "はじめる";
static const std::string L_BTN_TRAINING = "  練  習  ";
static const std::string L_BTN_HOWTO = "操作方法";
static const std::string L_BTN_QUIT = "やめる";
static const std::string L_BTN_NEXT = "つぎ";
static const std::string L_BTN_RETRY = "もう一回";
static const std::string L_BTN_BACK = "もどる";
static const std::string L_GAME_READY = "READY!";
static const std::string L_GAME_START = "GO!";
static const std::string L_GAME_GOAL = "GOAL!";
static const std::string L_GAME_CLEAR = "GOAL!";
static const std::string L_GAME_MISS = "MISS!";

static const std::string DEMO_SOSA = "<<操作方法>>\n"
"画面をタップして、\n"
"上下左右にスワイプすると\n"
"ライダーも上下左右に\n"
"重心移動します。\n";

static const std::string DEMO_WERRY = "<<ウイリー>>\n"
"左右に素早くスワイプすると\n"
"ライダーが左右に\n"
"ウイリーします。\n";

static const std::string DEMO_FR_JUMP = "<<両輪ジャンプ>>\n"
"両輪が地面接地時に\n"
"下から上に素早く\n"
"スワイプすると\n"
"両輪ジャンプします。\n";

static const std::string DEMO_R_JUMP = "<<後輪ジャンプ>>\n"
"前輪ウイリー時に\n"
"下から上に素早く\n"
"スワイプすると\n"
"両輪ジャンプより\n"
"より高くジャンプします。\n";

static const std::string DEMO_DUSH ="<<加速>>\n"
"しゃがんだ状態で\n"
"右に素早くスワイプすると\n"
"加速します。\n";

static const std::string DEMO_BREAK ="<<減速>>\n"
"左下に重心を\n"
"置き続けると\n"
"ブレーキが働きます。\n";

#endif /* Lang_hpp */
