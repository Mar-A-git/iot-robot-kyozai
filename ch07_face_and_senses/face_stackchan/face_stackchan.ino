//===================================================================
/* face_stackchan.ino  本物のｽﾀｯｸﾁｬﾝの表情を再現する（課題の見本）
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-28  新規作成  
*
*   表情の形は、ｽﾀｯｸﾁｬﾝの顔のﾗｲﾌﾞﾗﾘ「M5Stack-Avatar」
*   （Shinya Ishikawa, MIT License）の描き方を参考にしています。
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

// 顔のﾊﾟｰﾂの位置と大きさ（M5Stack-Avatarと同じ値）
const int EYE_R  = 8;                               // 目の半径
const int EYE_IN = 5;                               // 笑う目の、内側の黒い円の半径
const int EYE_LX = 90;                              // 画面左側の目の中心X
const int EYE_LY = 93;                              // 画面左側の目の中心Y
const int EYE_RX = 230;                             // 画面右側の目の中心X
const int EYE_RY = 96;                              // 画面右側の目の中心Y

// 関数 ===============================================================

// 口（横長の四角） ------------------------
void drawMouth() {

  M5.Display.fillRect(118, 146, 90, 4, WHITE);      // 中心(163,148)、横90×縦4
}

// ふつう --------------------------------
void faceNormal() {

  M5.Display.fillScreen(BLACK);
  M5.Display.fillCircle(EYE_LX, EYE_LY, EYE_R, WHITE);
  M5.Display.fillCircle(EYE_RX, EYE_RY, EYE_R, WHITE);
  drawMouth();
}

// 笑う：目の内側と下半分を黒で隠して「∩」 --
void happyEye(int x, int y) {

  M5.Display.fillCircle(x, y, EYE_R, WHITE);
  M5.Display.fillCircle(x, y, EYE_IN, BLACK);
  M5.Display.fillRect(x - EYE_R, y, EYE_R * 2 + 4, EYE_R + 2, BLACK);
}

// 笑う表情 ------------------------------
void faceHappy() {

  M5.Display.fillScreen(BLACK);
  happyEye(EYE_LX, EYE_LY);
  happyEye(EYE_RX, EYE_RY);
  drawMouth();
}

// 眠い：目の上半分を黒で隠す --------------
void sleepyEye(int x, int y) {

  M5.Display.fillCircle(x, y, EYE_R, WHITE);
  M5.Display.fillRect(x - EYE_R, y - EYE_R, EYE_R * 2 + 4, EYE_R + 2, BLACK);
}

// 眠い表情 ------------------------------
void faceSleepy() {

  M5.Display.fillScreen(BLACK);
  sleepyEye(EYE_LX, EYE_LY);
  sleepyEye(EYE_RX, EYE_RY);
  drawMouth();
}

// 怒る：目の上を三角形で斜めに隠す --------
void angryEye(int x, int y, bool isLeftSide) {

  int x0 = x - EYE_R;                               // 左上
  int y0 = y - EYE_R;
  int x1 = x + EYE_R;                               // 右上
  int x2;

  M5.Display.fillCircle(x, y, EYE_R, WHITE);
  if (isLeftSide) {
    x2 = x1;                                        // 画面左側の目：三角形の下の角を右（内側）に
  }
  else {
    x2 = x0;                                        // 画面右側の目：三角形の下の角を左（内側）に
  }
  M5.Display.fillTriangle(x0, y0, x1, y0, x2, y, BLACK);  // 3つの角の座標と色
}

// 怒る表情 ------------------------------
void faceAngry() {

  M5.Display.fillScreen(BLACK);
  angryEye(EYE_LX, EYE_LY, true);
  angryEye(EYE_RX, EYE_RY, false);
  drawMouth();
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

  int x = 0;                                        // ﾀｯﾁした場所のX座標
  int y = 0;                                        // ﾀｯﾁした場所のY座標
  
  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？
  if (M5.Touch.getDetail().wasPressed()) {
    x = M5.Touch.getDetail().x;                     // ﾀｯﾁした場所のX座標
    y = M5.Touch.getDetail().y;                     // ﾀｯﾁした場所のY座標
    
    // どこを押したか判定して、表情を変える
    if (x < 160 && y < 120) {
      faceNormal();                                 // 左上：ふつう
    }
    else if (x >= 160 && y < 120) {
      faceHappy();                                  // 右上：笑う
    }
    else if (x < 160 && y >= 120) {
      faceAngry();                                  // 左下：怒る
    }
    else if (x >= 160 && y >= 120) {
      faceSleepy();                                 // 右下：眠い
    }
  }
}
