//===================================================================
/* face_four.ino  4つの表情を順番に表示する
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

unsigned long lastTime = 0;                         // 最後に表情を切り替えた時間を記憶する
int faceNo = 0;                                     // 今の表情の番号（0～3）

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

  unsigned long nowTime = millis();                 // 現在の時間を取得する

  // 最後に切り替えてから2秒たったか？
  if (nowTime - lastTime >= 2000) {
    lastTime = nowTime;                             // 切り替えた時間を記憶する
    faceNo = faceNo + 1;                            // 次の表情へ
    if (faceNo >= 4) {
      faceNo = 0;                                   // 最後まで行ったら最初に戻す
    }
    // 表情を順に選択する(switch文でもよい)
    if (faceNo == 0) {
      faceNormal();
    }
    else if (faceNo == 1) {
      faceHappy();
    }
    else if (faceNo == 2) {
      faceSurprise();
    }
    else if (faceNo == 3) {
      faceSleep();
    }
  }
}
