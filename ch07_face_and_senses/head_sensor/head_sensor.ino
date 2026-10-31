//===================================================================
/* head_sensor.ino  頭のﾀｯﾁｾﾝｻの強さを表示して、触れたらLEDを前から順に光らせる
*
*   IoTﾛﾎﾞｯﾄ開発教材
*   @MarA_Elec
*
*   ▼改版履歴
*     2026-10-30  新規作成
*/
//===================================================================
#include <M5StackChan.h>
//===================================================================

const unsigned long WAIT_TIME  = 300;               // 外側のLEDから内側のLEDを光らせるまでの時間（0.3秒）
const unsigned long LIGHT_TIME = 2000;              // 光ってから消すまでの時間（2秒）

unsigned long gFrontTime  = 0;                      // 前のｾﾝｻに触れた時間を記憶する
unsigned long gMiddleTime = 0;                      // 中のｾﾝｻに触れた時間を記憶する
unsigned long gBackTime   = 0;                      // 後ろのｾﾝｻに触れた時間を記憶する
int gLastFront  = 0;                                // 1つ前のﾙｰﾌﾟのときの、前のｾﾝｻの強さ
int gLastMiddle = 0;                                // 1つ前のﾙｰﾌﾟのときの、中のｾﾝｻの強さ
int gLastBack   = 0;                                // 1つ前のﾙｰﾌﾟのときの、後ろのｾﾝｻの強さ
int gShowFront  = 0;                                // 画面に表示している、前のｾﾝｻの強さ
int gShowMiddle = 0;                                // 画面に表示している、中のｾﾝｻの強さ
int gShowBack   = 0;                                // 画面に表示している、後ろのｾﾝｻの強さ

// 関数 ===============================================================

// 画面に表示する強さを決める -------------------------------------------
//   上がるときはすぐ上げて、下げるのはLEDが消えるときまで待つ
//   strength  : 今のｾﾝｻの強さ
//   showValue : 今、画面に表示している強さ
//   startTime : ｾﾝｻに触れた時間
int holdStrength(int strength, int showValue, unsigned long startTime, unsigned long nowTime) {

  int result = showValue;                           // 基本は、今の表示のまま

  // 今の強さの方が大きいか？
  if (strength > showValue) {
    result = strength;                              // すぐに上げる
  }
  // 指が離れていて、LEDが全部消える時間（0.3秒 + 2秒）をすぎたか？
  else if (strength == 0 && nowTime - startTime >= WAIT_TIME + LIGHT_TIME) {
    result = 0;                                     // 0に戻す
  }
  return result;
}

// 左右1組のLEDを光らせる・消す ----------------------------------------
//   pair      : 左側のLEDの番号（0～5）。右側のLEDは 11 - pair 番
//   startTime : ｾﾝｻに触れた時間
//   waitTime  : 触れてから光らせるまでの時間
void lightPair(int pair, unsigned long startTime, unsigned long waitTime,
               int red, int green, int blue, unsigned long nowTime) {

  unsigned long passTime = 0;                       // ｾﾝｻに触れてからの時間

  passTime = nowTime - startTime;

  // 一度でも触れていて、光らせる時間の範囲に入っているか？
  if (startTime > 0 && passTime >= waitTime && passTime < waitTime + LIGHT_TIME) {
    M5StackChan.setRgbColor(pair, red, green, blue);        // 左側
    M5StackChan.setRgbColor(11 - pair, red, green, blue);   // 右側
  }
  else {
    M5StackChan.setRgbColor(pair, 0, 0, 0);
    M5StackChan.setRgbColor(11 - pair, 0, 0, 0);
  }
}

// 初期設定 ============================================================
// 起動時、1回だけ実行する
void setup() {

  M5StackChan.begin();
  M5StackChan.showRgbColor(0, 0, 0);                // 起動時に光っているLEDを全部消灯

  M5.Display.fillScreen(BLACK);
  M5.Display.setFont(&fonts::lgfxJapanGothic_24);   // 日本語のｺﾞｼｯｸ体（24ﾄﾞｯﾄ）
  M5.Display.setTextColor(WHITE, BLACK);            // 文字は白、文字の背景は黒
  M5.Display.drawString("頭のセンサの強さ（0〜3）", 20, 30);
  M5.Display.drawString("前　：", 100, 90);
  M5.Display.drawString("中　：", 100, 130);
  M5.Display.drawString("後ろ：", 100, 170);
}

// ﾒｲﾝﾙｰﾌﾟ ============================================================
void loop() {

  int front  = 0;                                   // 前のｾﾝｻの強さ
  int middle = 0;                                   // 中のｾﾝｻの強さ
  int back   = 0;                                   // 後ろのｾﾝｻの強さ
  unsigned long nowTime = 0;                        // 現在の時間

  M5StackChan.update();                             // ﾀｯﾁ状態を読み出す（頭のｾﾝｻも）
  nowTime = millis();                               // 現在の時間を取得する

  // 3か所の強さを読み出す（0：触れていない、1～3：強さ）
  front  = M5StackChan.TouchSensor.getIntensities()[0];
  middle = M5StackChan.TouchSensor.getIntensities()[1];
  back   = M5StackChan.TouchSensor.getIntensities()[2];

  // 触れた瞬間（0 から 1以上 に変わったとき）の時間を記憶する
  if (front > 0 && gLastFront == 0) {
    gFrontTime = nowTime;
  }
  if (middle > 0 && gLastMiddle == 0) {
    gMiddleTime = nowTime;
  }
  if (back > 0 && gLastBack == 0) {
    gBackTime = nowTime;
  }
  gLastFront  = front;                              // 次のﾙｰﾌﾟのために記憶する
  gLastMiddle = middle;
  gLastBack   = back;

  // 数字を表示する（LEDが光っている間は、いちばん強かった値を残す）
  gShowFront  = holdStrength(front, gShowFront, gFrontTime, nowTime);
  gShowMiddle = holdStrength(middle, gShowMiddle, gMiddleTime, nowTime);
  gShowBack   = holdStrength(back, gShowBack, gBackTime, nowTime);
  M5.Display.drawString(String(gShowFront), 180, 90);       // 文字の背景を黒にしているので、
  M5.Display.drawString(String(gShowMiddle), 180, 130);     // 前の数字は上書きで消える
  M5.Display.drawString(String(gShowBack), 180, 170);

  // 前のｾﾝｻ → LED 0・11 → 0.3秒後に LED 1・10
  lightPair(0, gFrontTime, 0, 83, 150, 120, nowTime);
  lightPair(1, gFrontTime, WAIT_TIME, 83, 150, 120, nowTime);
  // 中のｾﾝｻ → LED 2・9 → 0.3秒後に LED 3・8
  lightPair(2, gMiddleTime, 0, 110, 190, 160, nowTime);
  lightPair(3, gMiddleTime, WAIT_TIME, 110, 190, 160, nowTime);
  // 後ろのｾﾝｻ → LED 4・7 → 0.3秒後に LED 5・6
  lightPair(4, gBackTime, 0, 140, 240, 190, nowTime);
  lightPair(5, gBackTime, WAIT_TIME, 140, 240, 190, nowTime);

  M5StackChan.refreshRgb();                         // LEDに反映する
}
