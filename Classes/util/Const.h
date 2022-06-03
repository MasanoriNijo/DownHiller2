
// 各変数を記入する

// debug用ログを表示する
#define DEBUG_LOG 1

// display statusを表示する
#define DISPLAY_STATUS 1

// NJLOGを表示する。
#define ENABLE_NJLOG 1

#if !defined(ENABLE_NJLOG) || ENABLE_NJLOG == 0
#define NJLOG(...)
#else
#define NJLOG(format, ...)     cocos2d::log(format, ##__VA_ARGS__)
#endif

// デフォルトのバックグラウンドカラーをセット 色相H:0-360,彩度S:0-100,明度V:0-100
#define DEFAULT_COLOR_H 165
#define DEFAULT_COLOR_S 20
#define DEFAULT_COLOR_V 30

// 物理関連の定数
const Vec2 GRAVITY_ACCERATION = Vec2(0, -10);
const Vec2 NONGRAVITY = Vec2(0, 0);

// 物理ラインを表示する
#define DEBUG_PHYSICS_MASK 1

// 物理世界の処理スピード
#define PHYSICS_WOELD_SPEED 3
