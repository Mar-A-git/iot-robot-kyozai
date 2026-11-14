//===================================================================
/* head_move.ino  0°の位置を合わせて、首を斜めに動かす（右上、正面、左上、正面）
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

const unsigned char ROUND_NUM = 3;                          // 往復する回数（3往復で自動で止まる）
const int MOVE_COLOR = M5.Display.color565(53, 240, 196);   // 動いているときの画面の色（#35F0C4）
const int STOP_COLOR = M5.Display.color565(240, 113, 151);  // 止まっているときの画面の色（#F07197）
const int SET_COLOR  = M5.Display.color565(166, 137, 245);  // 0°を合わせるときの画面の色（#A689F5）

unsigned char gCount = ROUND_NUM;                           // 残りの往復回数

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                        // 起動時に光っているLEDを全部消灯
  M5.Display.setFont(&fonts::FreeSansBold24pt7b);           // 太字の英字ﾌｫﾝﾄ
  M5.Display.setTextSize(1.8);                              // 1.8倍の大きさ
  M5.Display.setTextColor(WHITE);                           // 白い文字
  M5.Display.setTextDatum(middle_center);                   // 文字の真ん中を、指定した座標に合わせる

  // 0°の位置を合わせる（起動した直後は力が抜けているので、首を手で動かせる）
  M5.Display.fillScreen(SET_COLOR);
  M5.Display.drawString("SET", 160, 120);                   // 首を手で正面に合わせてから、画面を押す

  // 画面が押されるまで待つ
  while (!M5.Touch.getDetail().wasPressed()) {
    M5StackChan.update();                                   // ﾀｯﾁ状態を読み出す
  }
  M5StackChan.Motion.setCurrentPostionAsHome();             // 今の首の位置を0°として本体に記録する
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  // まだ往復する回数が残っているか？
  if (gCount > 0) {
    M5.Display.fillScreen(MOVE_COLOR);
    M5.Display.drawString(String(gCount), 160, 120);  // 残りの往復回数を表示する

    M5StackChan.Motion.move(450, 300, 500);           // 右上へ（右45°、上30°）（左右, 上下, 速さ）
    delay(2000);                                      // 2秒待つ

    M5StackChan.Motion.goHome(500);                   // 正面（左右0°、上下0°）に戻す
    delay(2000);

    M5StackChan.Motion.move(-450, 300, 500);          // 左上へ（左45°、上30°）
    delay(2000);

    M5StackChan.Motion.goHome(500);                   // 正面に戻す
    delay(2000);

    gCount--;                                         // 1往復したので、残りを1つ減らす

    // 3往復したら、「START」を表示する
    if (gCount == 0) {
      M5.Display.fillScreen(STOP_COLOR);
      M5.Display.drawString("START", 160, 120);       // 画面の真ん中(160,120)に書く
    }
  }
  // 止まっているときは、画面が押されるのを待つ
  else {
    M5StackChan.update();                             // ﾀｯﾁ状態を読み出す
    if (M5.Touch.getDetail().wasPressed()) {
      gCount = ROUND_NUM;                             // もう一度、3往復する
    }
  }
}
