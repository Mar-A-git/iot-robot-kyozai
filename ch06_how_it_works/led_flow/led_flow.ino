//===================================================================
/* led_flow.ino  LEDを1個ずつ順番に流して点灯
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

unsigned long lastTime = 0;                       // 最後にLEDを切り替えた時間を記憶する
int ledNo = 0;                                    // 今光っているLEDの番号を記憶する

// 初期設定 ==========================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);              // 起動時に光っているLEDを全部消灯
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = millis();               // 現在の時間を取得する

  // 最後に切り替えてから0.1秒たったか？
  if (nowTime - lastTime >= 100) {
    lastTime = nowTime;                           // 切り替えた時間を記憶する
    M5StackChan.setRgbColor(ledNo, 0, 0, 0);      // 今のLEDを消灯

    ledNo = ledNo + 1;                            // 次のLEDへ
    if (ledNo >= 12) {
      ledNo = 0;                                  // 最後まで行ったら0番に戻す
    }
    M5StackChan.setRgbColor(ledNo, 0, 0, 168);    // 次のLEDを点灯
    M5StackChan.refreshRgb();                     // LEDに反映する
  }
}
