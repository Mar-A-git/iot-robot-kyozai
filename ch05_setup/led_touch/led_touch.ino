//===================================================================
/* led_touch.ino  画面ﾀｯﾁでLEDをON/OFF
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-09-24  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

bool ledOn = false;    // LEDが点灯しているかどうかを識別する

// 関数 =============================================================

// LED点灯/消灯 --------------------------
void ledWrite(bool on) {

  if (on) {
    M5StackChan.setRgbColor(0, 168, 0, 0);   // 1個目を赤点灯
  } 
  else {
    M5StackChan.setRgbColor(0, 0, 0, 0);     // 1個目を消灯
  }
  M5StackChan.refreshRgb();
}

// 初期設定 ==========================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();

  // 起動時に光っているLEDを全部消灯
  M5StackChan.showRgbColor(0, 0, 0);

  // 画面に案内を表示
  M5.Display.setTextSize(3);
  M5.Display.drawString("Touch me!", 80, 105);
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  M5StackChan.update();           // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？
  if (M5.Touch.getDetail().wasPressed()) {
    ledOn = !ledOn;               // 点灯と消灯を入れかえる
    ledWrite(ledOn);              // LEDに反映する
  }
}
