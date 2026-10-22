//===================================================================
/* touch_area.ino  画面を4つに分けてﾎﾞﾀﾝにする
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

  // 画面を4つに塗り分ける（1つの大きさは 横160 × 縦120）
  M5.Display.fillRect(  0,   0, 160, 120, RED);     // 左上：赤
  M5.Display.fillRect(160,   0, 160, 120, GREEN);   // 右上：緑
  M5.Display.fillRect(  0, 120, 160, 120, BLUE);    // 左下：青
  M5.Display.fillRect(160, 120, 160, 120, YELLOW);  // 右下：黄
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？
  if (M5.Touch.getDetail().wasPressed()) {
    int x = M5.Touch.getDetail().x;                 // ﾀｯﾁした場所のX座標
    int y = M5.Touch.getDetail().y;                 // ﾀｯﾁした場所のY座標

    // どこを押したか判定して、LEDの色を変える
    if (x < 160 && y < 120) {
      M5StackChan.showRgbColor(168, 0, 0);          // 左上：赤
    }
    if (x >= 160 && y < 120) {
      M5StackChan.showRgbColor(0, 168, 0);          // 右上：緑
    }
    if (x < 160 && y >= 120) {
      M5StackChan.showRgbColor(0, 0, 168);          // 左下：青
    }
    if (x >= 160 && y >= 120) {
      M5StackChan.showRgbColor(168, 168, 0);        // 右下：黄
    }
  }
}
