//===================================================================
/* led_alternate.ino  左右6個ずつ交互に点滅
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-09-29  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

unsigned long lastTime = 0;   // 最後にLEDを切り替えた時間を記憶する
bool leftOn = false;          // 左側が点灯しているかどうかを識別する

// 関数 =============================================================

// 左右の点灯/消灯 -----------------------
void sideWrite(bool left) {

  for (int i = 0; i < 6; i++) {
    if (left) {
      M5StackChan.setRgbColor(i, 0, 0, 168);      // 左を点灯
      M5StackChan.setRgbColor(i + 6, 0, 0, 0);    // 右を消灯
    }
    else {
      M5StackChan.setRgbColor(i, 0, 0, 0);        // 左を消灯
      M5StackChan.setRgbColor(i + 6, 0, 0, 168);  // 右を点灯
    }
  }
  M5StackChan.refreshRgb();                       // LEDに反映する
}

// 初期設定 ==========================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();

  // 起動時に光っているLEDを全部消灯
  M5StackChan.showRgbColor(0, 0, 0);
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = millis();   // 現在の時間を取得する

  // 最後に切り替えてから1秒たったか？
  if (nowTime - lastTime >= 1000) {
    lastTime = nowTime;               // 切り替えた時間を記憶する
    leftOn = !leftOn;                 // 左と右を入れ替える
    sideWrite(leftOn);                // LEDに反映する
  }
}
