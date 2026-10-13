//===================================================================
/* disp_scroll_v.ino  文字を縦に流す（縦ﾃﾛｯﾌﾟ）
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-13  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

unsigned long lastTime = 0;                         // 最後に文字を動かした時間を記憶する
int textY = 240;                                    // 文字の縦の位置（画面の下端から始める）

// 初期設定 ==========================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯

  M5.Display.fillScreen(BLACK);                     // 画面を黒で塗りつぶす
  M5.Display.setFont(&fonts::lgfxJapanGothic_24);   // 日本語のｺﾞｼｯｸ体（24ﾄﾞｯﾄ）
  M5.Display.setTextColor(WHITE, BLACK);            // 文字は白、文字の背景は黒
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = millis();                 // 現在の時間を取得する

  // 最後に動かしてから0.02秒たったか？
  if (nowTime - lastTime >= 20) {
    lastTime = nowTime;                             // 動かした時間を記憶する

    textY = textY - 2;                              // 上へ2ﾄﾞｯﾄ動かす
    if (textY < -24) {                              // 文字が上に出きったら
      textY = 240;                                  // 下端に戻す
    }

    M5.Display.drawString("いらっしゃいませ", 64, textY);
    M5.Display.fillRect(64, textY + 24, 192, 2, BLACK);   // 文字の下に残った2ﾄﾞｯﾄ分を消す
  }
}
