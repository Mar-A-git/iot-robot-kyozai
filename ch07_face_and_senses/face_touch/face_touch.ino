//===================================================================
/* face_touch.ino  ﾀｯﾁした場所で表情を切り替える
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-27  新規作成  
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

// 関数 ===============================================================

// ふつう --------------------------------
void faceNormal() {
  M5.Display.fillScreen(BLACK);                     // 前の顔を消す
  M5.Display.fillCircle(100, 90, 25, WHITE);        // 左目
  M5.Display.fillCircle(220, 90, 25, WHITE);        // 右目
  M5.Display.fillRect(130, 170, 60, 8, WHITE);      // 口
}

// 笑う ----------------------------------
void faceHappy() {
  M5.Display.fillScreen(BLACK);
  // 目：白い円の内側と下半分を黒で隠して「∩」にする
  M5.Display.fillCircle(100, 90, 25, WHITE);
  M5.Display.fillCircle(100, 90, 16, BLACK);
  M5.Display.fillRect(75, 90, 51, 26, BLACK);
  M5.Display.fillCircle(220, 90, 25, WHITE);
  M5.Display.fillCircle(220, 90, 16, BLACK);
  M5.Display.fillRect(195, 90, 51, 26, BLACK);
  // 口：白い円の上半分を黒で隠して「∪」にする
  M5.Display.fillCircle(160, 160, 30, WHITE);
  M5.Display.fillRect(130, 130, 61, 30, BLACK);
}

// 驚く ----------------------------------
void faceSurprise() {
  M5.Display.fillScreen(BLACK);
  M5.Display.fillCircle(100, 90, 32, WHITE);        // 目を大きく
  M5.Display.fillCircle(220, 90, 32, WHITE);
  M5.Display.fillCircle(160, 180, 18, WHITE);       // 口を丸く
}

// 眠る ----------------------------------
void faceSleep() {
  M5.Display.fillScreen(BLACK);
  M5.Display.fillRect(75, 87, 50, 6, WHITE);        // 目を横線に
  M5.Display.fillRect(195, 87, 50, 6, WHITE);
  M5.Display.fillRect(145, 172, 30, 6, WHITE);      // 口を小さく
}

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯
  faceNormal();                                     // 最初はふつうの顔
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？
  if (M5.Touch.getDetail().wasPressed()) {
    int x = M5.Touch.getDetail().x;                 // ﾀｯﾁした場所のX座標
    int y = M5.Touch.getDetail().y;                 // ﾀｯﾁした場所のY座標

    // どこを押したか判定して、表情を変える
    if (x < 160 && y < 120) {
      faceNormal();                                 // 左上：ふつう
    }
    else if (x >= 160 && y < 120) {
      faceHappy();                                  // 右上：笑う
    }
    else if (x < 160 && y >= 120) {
      faceSurprise();                               // 左下：驚く
    }
    else if (x >= 160 && y >= 120) {
      faceSleep();                                  // 右下：眠る
    }
  }
}
