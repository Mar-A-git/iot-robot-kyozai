//===================================================================
/* led_millis.ino  時間管理を使ったLED点滅
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-09-21  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

unsigned long lastTime = 0;   // 最後にLEDを切り替えた時間を記憶する
bool ledOn = false;           // LEDが点灯しているかどうかを識別する

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
  for (int i = 0; i < 12; i++) {
    M5StackChan.setRgbColor(i, 0, 0, 0);
  }
  M5StackChan.refreshRgb();
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = millis();   // 現在の時間を取得する

  // 最後に切り替えてから1秒たったか？
  if (nowTime - lastTime >= 1000) {
    lastTime = nowTime;               // 切り替えた時間を記憶する
    ledOn = !ledOn;                   // 点灯と消灯を入れかえる
    ledWrite(ledOn);                  // LEDに反映する
  }
}
