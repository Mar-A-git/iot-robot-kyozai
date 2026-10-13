//===================================================================
/* disp_scroll.ino  文字を横に流す（ﾃﾛｯﾌﾟ）
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
int textX = 320;                                    // 文字の横の位置（画面の右端から始める）

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

    textX = textX - 2;                              // 左へ2ﾄﾞｯﾄ動かす
    if (textX < -192) {                             // 文字（8文字×24ﾄﾞｯﾄ）が左に出きったら
      textX = 320;                                  // 右端に戻す
    }

    M5.Display.drawString("いらっしゃいませ", textX, 108);
    M5.Display.fillRect(textX + 192, 108, 2, 24, BLACK);  // 文字の右に残った2ﾄﾞｯﾄ分を消す
  }
}
