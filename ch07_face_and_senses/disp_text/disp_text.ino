//===================================================================
/* disp_text.ino  画面に英数字を表示する
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-12  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

// 初期設定 ==========================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                  // 起動時に光っているLEDを全部消灯

  M5.Display.fillScreen(BLACK);                       // 画面を黒で塗りつぶす

  M5.Display.setTextSize(2);                          // 文字の大きさ
  M5.Display.setTextColor(WHITE);                     // 文字の色
  M5.Display.drawString("Hello StackChan!", 0, 0);    // 左上に表示

  M5.Display.setTextSize(3);                          // 文字の大きさ
  M5.Display.setTextColor(YELLOW);                    // 文字の色
  M5.Display.drawString("X=100 Y=120", 100, 120);     // 横100、縦120の位置に表示
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

}
