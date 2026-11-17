//===================================================================
/* head_nonblock.ino  首を斜めに動かす（非ﾌﾞﾛｯｷﾝｸﾞ）
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-11-17  新規作成
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

const unsigned char ROUND_NUM = 3;                          // 往復する回数（3往復で自動で止まる）
const unsigned char MOVE_NUM = 4;                           // 1往復の動きの数（右上・正面・左上・正面）
const unsigned long MOVE_TIME = 2000;                       // 次の動きに移るまでの時間（2秒）
const int MOVE_COLOR = M5.Display.color565(53, 240, 196);   // 動いているときの画面の色（#35F0C4）
const int STOP_COLOR = M5.Display.color565(240, 113, 151);  // 止まっているときの画面の色（#F07197）

unsigned char gCount = ROUND_NUM;                           // 残りの往復回数
bool gIsMoving = true;                                      // 今、動かしているかどうか
unsigned char gMoveNo = 0;                                  // 次に行う動きの番号（0〜3）
unsigned long gMoveStart = 0;                               // 最後に動きを指示した時間を記憶する
unsigned long gPassTime = 0;                                // 止めたとき、その動きを始めてから何msたっていたか
unsigned long gLoopCount = 0;                               // 1秒間にﾒｲﾝﾙｰﾌﾟが回った回数
unsigned long gCountStart = 0;                              // 回数を数え始めた時間を記憶する

// 関数 ===============================================================

// 画面を描く ----------------------------
// 動いているときは「STOP」、止まっているときは「START」を表示する
void drawScreen() {

  if (gIsMoving) {
    M5.Display.fillScreen(MOVE_COLOR);
    M5.Display.drawString("STOP", 160, 120);  // 画面の真ん中(160,120)に書く
  }
  else {
    M5.Display.fillScreen(STOP_COLOR);
    M5.Display.drawString("START", 160, 120);
  }
}

// 番号に合わせて首を動かす ---------------
void headMove(unsigned char no) {

  if (no == 0) {
    M5StackChan.Motion.move(450, 300, 500);   // 右上へ（右45°、上30°）
  }
  else if (no == 1) {
    M5StackChan.Motion.goHome(500);           // 正面に戻す
  }
  else if (no == 2) {
    M5StackChan.Motion.move(-450, 300, 500);  // 左上へ（左45°、上30°）
  }
  else {
    M5StackChan.Motion.goHome(500);           // 正面に戻す
  }
}

// 画面のどこかを押したら、停止と再開を切り替える --
void checkButton() {

  M5StackChan.update();                       // ﾀｯﾁ状態を読み出す

  // 画面がﾀｯﾁされたか？（動いている頭でも押しやすいよう、画面全体で受けつける）
  if (M5.Touch.getDetail().wasPressed()) {
    gIsMoving = !gIsMoving;                   // 停止と再開を入れかえる

    if (gIsMoving) {
      // 3往復が終わったあとなら、最初からやり直す
      if (gCount == 0) {
        gCount = ROUND_NUM;
        gMoveNo = 0;
        gMoveStart = millis() - MOVE_TIME;    // すぐに最初の動きを始める
      }
      // 途中で止めたときは、止めたときの動きをもう一度指示して、続きから動かす
      else {
        if (gMoveNo > 0) {
          headMove(gMoveNo - 1);              // 止めたときの動き
        }
        gMoveStart = millis() - gPassTime;    // 止めたときの続きの時間から数える
      }
    }
    else {
      M5StackChan.Motion.stop();              // 動いている途中でも、その場で止める
      gPassTime = millis() - gMoveStart;      // その動きを始めてから何msたっていたか記憶する
    }
    drawScreen();
  }
}

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  Serial.begin(9600);                               // ｼﾘｱﾙﾓﾆﾀに文字を送る準備（9600bps）
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯
  M5StackChan.Motion.goHome(500);                   // 正面（左右0°、上下0°）に戻す
  delay(2000);                                      // 戻るまで2秒待つ

  M5.Display.setFont(&fonts::FreeSansBold24pt7b);   // 太字の英字ﾌｫﾝﾄ
  M5.Display.setTextSize(1.8);                      // 1.8倍の大きさ
  M5.Display.setTextColor(WHITE);                   // 白い文字
  M5.Display.setTextDatum(middle_center);           // 文字の真ん中を、指定した座標に合わせる
  drawScreen();
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  unsigned long nowTime = 0;                  // 現在の時間

  checkButton();                              // ﾎﾞﾀﾝを確認する（ﾒｲﾝﾙｰﾌﾟのたびに見る）
  nowTime = millis();                         // 現在の時間を取得する
  gLoopCount++;                               // ﾒｲﾝﾙｰﾌﾟが回った回数を数える

  // 1秒たったら、ﾒｲﾝﾙｰﾌﾟが回った回数をｼﾘｱﾙﾓﾆﾀに出す
  if (nowTime - gCountStart >= 1000) {
    gCountStart = nowTime;                    // 数え始めた時間を記憶する
    Serial.println("1秒間に " + String(gLoopCount) + " 回");
    gLoopCount = 0;                           // 0から数え直す
  }

  // 動かしている間で、最後に動きを指示してから2秒たったか？
  if (gIsMoving && nowTime - gMoveStart >= MOVE_TIME) {
    gMoveStart = nowTime;                     // 指示した時間を記憶する

    // 1往復の動きが全部終わったか？
    if (gMoveNo == MOVE_NUM) {
      gMoveNo = 0;                            // 次の往復は、最初の動きから
      gCount--;                               // 1往復したので、残りを1つ減らす

      // 3往復したら止める
      if (gCount == 0) {
        gIsMoving = false;
        drawScreen();                         // 「START」の画面にする
      }
    }

    // まだ動かしている間なら、次の動きを指示する（終わるのを待たない）
    if (gIsMoving) {
      headMove(gMoveNo);
      gMoveNo++;
    }
  }
}
