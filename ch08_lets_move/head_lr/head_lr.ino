//===================================================================
/* head_lr.ino  首を左右に動かす
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-11-10  新規作成
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

const int MOVE_COLOR = M5.Display.color565(53, 240, 196);   // 動いているときの画面の色（#35F0C4）
const int STOP_COLOR = M5.Display.color565(240, 113, 151);  // 止まっているときの画面の色（#F07197）
const unsigned char ROUND_NUM = 3;                          // 往復する回数（3往復で自動で止まる）

bool gIsMoving = true;                                      // 今、動かしているかどうか
unsigned char gCount = ROUND_NUM;                           // 残りの往復回数

// 関数 ===============================================================

// 画面を描く ----------------------------
// 動いているときは「STOP」、止まっているときは「START」を表示する
void drawScreen() {

  if (gIsMoving) {
    M5.Display.fillScreen(MOVE_COLOR);
    M5.Display.drawString("STOP", 160, 120);        // 画面の真ん中(160,120)に書く
  }
  else {
    M5.Display.fillScreen(STOP_COLOR);
    M5.Display.drawString("START", 160, 120);
  }
}

// 画面のどこかを押したら、停止と再開を切り替える --
void checkButton() {

  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？（動いている頭でも押しやすいよう、画面全体で受けつける）
  if (M5.Touch.getDetail().wasPressed()) {
    gIsMoving = !gIsMoving;                         // 停止と再開を入れかえる

    // 再開するときは、いつも3往復から始める
    if (gIsMoving) {
      gCount = ROUND_NUM;
    }
    drawScreen();
  }
}

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯
  M5StackChan.Motion.goHome(500);                   // 正面（左右0°、上下0°）に戻す
  delay(2000);                                      // 戻るまで2秒待つ

  M5.Display.setFont(&fonts::FreeSansBold24pt7b);   // 太字の英字ﾌｫﾝﾄ
  M5.Display.setTextSize(1.8);                      // 1.8倍の大きさ
  M5.Display.setTextColor(WHITE);                   // 白い文字
  M5.Display.setTextDatum(middle_center);           // 文字の真ん中を、指定した座標に合わせる
  drawScreen();
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  checkButton();                              // ﾎﾞﾀﾝを確認する

  // 右へ動かす（StackChanから見て）
  if (gIsMoving) {
    M5StackChan.Motion.moveX(450, 500);       // 右へ45°（角度は10で1°、速さは0〜1000）
    delay(2000);                              // 2秒待つ
    checkButton();                            // ﾎﾞﾀﾝを確認する
  }
  // 左へ動かす
  if (gIsMoving) {
    M5StackChan.Motion.moveX(-450, 500);      // 左へ45°
    delay(2000);                              // 2秒待つ
    gCount--;                                 // 1往復したので、残りを1つ減らす

    // 3往復したら止めて、正面に戻す
    if (gCount == 0) {
      gIsMoving = false;
      M5StackChan.Motion.goHome(500);         // 正面（左右0°、上下0°）に戻す
      drawScreen();                           // 「START」の画面にする
    }
  }
}
