//===================================================================
/* touch_xy.ino  ﾀｯﾁした場所の座標を表示する
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-22  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯
  M5.Display.fillScreen(BLACK);                     // 画面を黒で塗りつぶす

  M5.Display.setTextSize(2);                        // 文字の大きさ
  M5.Display.setTextColor(WHITE);                   // 文字の色
  M5.Display.drawString("Touch me!", 0, 0);         // 左上に表示
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？
  if (M5.Touch.getDetail().wasPressed()) {
    int x = M5.Touch.getDetail().x;                 // ﾀｯﾁした場所のX座標
    int y = M5.Touch.getDetail().y;                 // ﾀｯﾁした場所のY座標

    M5.Display.fillScreen(BLACK);                   // 前の表示を消す
    M5.Display.fillCircle(x, y, 8, RED);            // ﾀｯﾁした場所に赤い丸を描く

    M5.Display.drawString("X=" + String(x) + " Y=" + String(y), 0, 0);   // 座標を左上に表示
  }
}
