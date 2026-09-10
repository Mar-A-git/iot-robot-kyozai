#include <M5Unified.h>

void setup() {
  M5.begin();
  M5.Display.fillScreen(BLACK);
  M5.Display.fillCircle(100, 90, 25, WHITE);    // 左目
  M5.Display.fillCircle(220, 90, 25, WHITE);    // 右目
  M5.Display.fillRect(130, 170, 60, 8, WHITE);  // 口
}

void loop() {

}
