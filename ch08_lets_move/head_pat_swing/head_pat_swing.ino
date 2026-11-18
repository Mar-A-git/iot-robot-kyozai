//===================================================================
/* head_pat_swing.ino  頭をなでると笑顔になってﾊｰﾄを出し、ﾋﾟﾝｸのLEDを流して首を振る
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-11-17  新規作成（07章 head_pat に首振りを追加）
*
*   表情の形は、ｽﾀｯｸﾁｬﾝの顔のﾗｲﾌﾞﾗﾘ「M5Stack-Avatar」
*   （Shinya Ishikawa, MIT License）の描き方を参考にしています。
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

// 顔のﾊﾟｰﾂの位置と大きさ（M5Stack-Avatarと同じ値）
const int EYE_R  = 8;                               // 目の半径
const int EYE_IN = 5;                               // 笑う目の、内側の黒い円の半径
const int EYE_LX = 90;                              // 画面左側の目の中心X
const int EYE_LY = 93;                              // 画面左側の目の中心Y
const int EYE_RX = 230;                             // 画面右側の目の中心X
const int EYE_RY = 96;                              // 画面右側の目の中心Y

// ﾊｰﾄの位置と色、笑顔を続ける時間
const int HEART_X = 275;                                    // ﾊｰﾄの中心X
const int HEART_Y = 40;                                     // ﾊｰﾄの中心Y
const int HEART_COLOR = M5.Display.color565(255, 60, 150);  // ﾊｰﾄの色（赤, 緑, 青）
const unsigned long HAPPY_TIME = 3000;                      // 笑顔を続ける時間（3000ms = 3秒）
const unsigned long FLOW_TIME  = 300;                       // 次のLEDを光らせるまでの時間（0.3秒）

// 首振りの間隔と、進める量
const unsigned long SWING_TIME = 20;                        // 首を少し進める間隔（20ms）
const int SWING_STEP = 10;                                  // 1回に進める角度（10 = 1°）
const int SWING_MAX  = 300;                                 // 左右に振る角度（300 = 30°）

unsigned long gHappyStart = 0;                              // 笑顔になった時間を記憶する
bool gIsHappy = false;                                      // 今、笑顔かどうか

unsigned long gSwingStart = 0;                              // 最後に合図を立てた時間を記憶する
bool gSwingFlag = false;                                    // 首を動かす合図（ﾌﾗｸﾞ）
int gAngle = 0;                                             // 今の左右の角度
int gStep = SWING_STEP;                                     // 進める向きと量（＋は右、－は左）

// 関数 ===============================================================

// 口（横長の四角） ------------------------
void drawMouth() {

  M5.Display.fillRect(118, 146, 90, 4, WHITE);              // 中心(163,148)、横90×縦4
}

// ふつう --------------------------------
void faceNormal() {

  M5.Display.fillScreen(BLACK);
  M5.Display.fillCircle(EYE_LX, EYE_LY, EYE_R, WHITE);
  M5.Display.fillCircle(EYE_RX, EYE_RY, EYE_R, WHITE);
  drawMouth();
}

// 笑う：目の内側と下半分を黒で隠して「∩」 --
void happyEye(int x, int y) {

  M5.Display.fillCircle(x, y, EYE_R, WHITE);
  M5.Display.fillCircle(x, y, EYE_IN, BLACK);
  M5.Display.fillRect(x - EYE_R, y, EYE_R * 2 + 4, EYE_R + 2, BLACK);
}

// 笑う表情 ------------------------------
void faceHappy() {

  M5.Display.fillScreen(BLACK);
  happyEye(EYE_LX, EYE_LY);
  happyEye(EYE_RX, EYE_RY);
  drawMouth();
}

// ﾊｰﾄ：円2つと三角形1つで描く ------------
void drawHeart(int x, int y) {

  M5.Display.fillCircle(x - 10, y, 12, HEART_COLOR);                              // 左の丸
  M5.Display.fillCircle(x + 10, y, 12, HEART_COLOR);                              // 右の丸
  M5.Display.fillTriangle(x - 21, y + 5, x + 21, y + 5, x, y + 30, HEART_COLOR);  // 下の三角
}

// 首を少しだけ進める ---------------------
// 横へ行くほど上を向き、正面に戻ると下を向く
void swingHead() {

  gAngle = gAngle + gStep;                              // 左右の角度を少し進める
  if (gAngle >= SWING_MAX || gAngle <= -SWING_MAX) {
    gStep = -gStep;                                     // 端まで来たら向きを変える
  }
  M5StackChan.Motion.move(gAngle, abs(gAngle), 1000);   // 上下の角度は、左右の角度の大きさと同じ
}

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                    // 起動時に光っているLEDを全部消灯
  M5StackChan.Motion.setAutoAngleSyncEnabled(false);    // 細かく指示しても、なめらかに動くようにする
  M5StackChan.Motion.goHome(500);                       // 正面に戻す
  faceNormal();                                         // 最初はふつうの顔
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = 0;                            // 現在の時間

  M5StackChan.update();                                 // ﾀｯﾁ状態を読み出す（頭のｾﾝｻも）
  nowTime = millis();                                   // 現在の時間を取得する

  // 20msたったら、首を動かす合図（ﾌﾗｸﾞ）を立てる
  if (nowTime - gSwingStart >= SWING_TIME) {
    gSwingStart = nowTime;                              // 合図を立てた時間を記憶する
    gSwingFlag = true;
  }
  // 頭を前から後ろへなでたか？
  if (M5StackChan.TouchSensor.wasSwipedForward()) {
    faceHappy();                                        // 笑顔にして
    drawHeart(HEART_X, HEART_Y);                        // ﾊｰﾄを出す
    M5StackChan.showRgbColor(0, 0, 0);                  // LEDを一度消して、前から流し直す
    gHappyStart = nowTime;                              // 笑顔になった時間を記憶する
    gIsHappy = true;
  }
  // 笑顔になってから3秒たったか？
  else if (gIsHappy && nowTime - gHappyStart >= HAPPY_TIME) {
    faceNormal();                                       // ふつうの顔に戻す
    M5StackChan.showRgbColor(0, 0, 0);                  // LEDを消す
    M5StackChan.Motion.goHome(500);                     // 首を正面に戻す
    gAngle = 0;                                         // 首振りを最初からにする
    gStep = SWING_STEP;
    gIsHappy = false;
  }
  // 笑顔の間は、ﾋﾟﾝｸのLEDを前から順に0.3秒ずつ光らせる
  if (gIsHappy) {
    for (int i = 0; i < 6; i++) {
      // 笑顔になってから i × 0.3秒 たったか？
      if (nowTime - gHappyStart >= i * FLOW_TIME) {
        M5StackChan.setRgbColor(i, 168, 40, 100);       // 左側（i番）
        M5StackChan.setRgbColor(11 - i, 168, 40, 100);  // 右側（11 - i番）
      }
    }
    M5StackChan.refreshRgb();                           // LEDに反映する
  }
  // 合図が立っているときだけ、首を動かす
  if (gSwingFlag) {
    gSwingFlag = false;                                 // 合図を下ろす
    if (gIsHappy) {
      swingHead();                                      // 笑顔の間は、首を少し進める
    }
  }
}
