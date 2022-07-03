#ifndef Lang_hpp
#define Lang_hpp
#include <stdio.h>

// 各文言を記述
static const std::string L_TITLE = "自転車";
static const std::string L_TITLE2 = "ゲーム";
static const std::string L_TITLE_SELECT = "ステージを選択";
static const std::string L_STAGE = "ステージ";
static const std::string L_BTN_START = "はじめる";
static const std::string L_BTN_HOWTO = "操作方法";
static const std::string L_BTN_QUIT = "やめる";
static const std::string L_BTN_NEXT = "次のステージ";
static const std::string L_BTN_RETRY = "もう一度";
static const std::string L_BTN_BACK = "もどる";
static const std::string L_GAME_READY = "よーい!";
static const std::string L_GAME_START = "どん!";
static const std::string L_GAME_GOAL = "ゴール!";
static const std::string L_GAME_CLEAR = "成功!";
static const std::string L_GAME_MISS = "失敗!";

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
"下から上に素早くスワイプすると\n"
"両輪ジャンプします。\n";

static const std::string DEMO_R_JUMP = "<<後輪ジャンプ>>\n"
"前輪ウイリー時に\n"
"下から上に素早くスワイプすると\n"
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
