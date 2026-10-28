# IoTロボット開発教材 サンプルプログラム

「IoTロボット開発教材」で使用するサンプルプログラムを公開しています。
教材はnoteで順次公開しています。

- 教材（note）: https://note.com/mar_69/m/m94231fca754c

教材の進行に合わせて、動作確認が済んだものから順次追加していきます。

## 対象ハードウェア

M5Stack社の StackChan を使用します。

| 品名 | SKU |
|---|---|
| StackChan Core | C156 |
| StackChan Body | A180 |

## 開発環境

| 項目 | バージョン・設定 |
|---|---|
| Arduino IDE | 2.3.2 |
| ボードマネージャURL | `https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json` |
| M5Stack ボードパッケージ | 3.3.9 |
| ボードの選択 | M5CoreS3 |
| M5StackChan | 1.1.0 |

### 注意点

- **ボードパッケージは3.x系が必要です。** 2.1.4以前は C++11 でコンパイルされるため、M5StackChanがビルドできません。
- **M5StackChan 1.1.0 は、ライブラリマネージャでは入手できません**（2026年9月10日時点で1.0.1までしか公開されていません）。1.0.1は最新のM5Unifiedと組み合わせるとコンパイルエラーになります。
  [StackChan-BSP](https://github.com/m5stack/StackChan-BSP) から ZIP をダウンロードし、「スケッチ → ライブラリをインクルード → .ZIP形式のライブラリをインストール」で導入してください。

## 構成

```
ch05_setup/          05章 開発環境の構築と簡単な操作
  hello_face/        (2) StackChanの顔を表示する
  led_delay/         1⃣ Delayを使ったLED点滅
  led_counter/       2⃣ カウンタを使ったLED点滅
  led_millis/        3⃣ 時間管理を使ったLED点滅
  led_touch/         (5) ボタン入力（画面タッチでLEDをON/OFF）
ch06_how_it_works/   06章 プログラムと動作の仕組み
  led_color/         (4) 1⃣ 全部のLEDを青く光らせる
  led_mycolor/       (4) 2⃣ 全部のLEDを好きな色で光らせる
  led_side/          (4) 3⃣ 片側6個のLEDだけ光らせる
  led_alternate/     (4) 4⃣ 左右6個ずつ交互に点滅
  led_flow/          (4) 5⃣ LEDを1個ずつ順番に流して点灯
ch07_face_and_senses/ 07章 表情と感覚を作る
  disp_text/         (2) 1⃣ 英数字を表示する
  disp_japanese/     (2) 2⃣ 日本語を表示する
  disp_name/         (2) 3⃣ 名前を画面の真ん中に表示する（参考例）
  disp_scroll/       (2) 4⃣ 文字を横に流す（テロップ）
  disp_scroll_v/     (2) 5⃣ 文字を縦に流す（縦テロップ・課題の解答例）
  disp_photo/        (3) 1⃣ microSDカードの写真（JPG）を表示する
  disp_png/          (3) 2⃣ microSDカードの画像（PNG）を表示する（画像サンプル image.png 付き）
  touch_xy/          (4) 1⃣ タッチした場所の座標を表示する
  touch_area/        (4) 2⃣ 画面を4つに分けてボタンにする
  face_four/         (5) 1⃣ 4つの表情を順番に表示する
  face_touch/        (5) 2⃣ タッチした場所で表情を切り替える
  face_stackchan/    (5) 3⃣ 本物のStackChanの表情を再現する（課題の見本）
```

## ライセンス

- **ソースコード**（`ch*/` 以下）… MIT License
- **教材資料**（`docs/` 以下）… CC BY-NC-ND 4.0
  - ただし、授業料を受け取る教育・研修（学校、職業訓練、企業研修など）の中で、本教材をそのまま使うことは許可します。
  - 本教材そのものを販売すること、改変したものを配布することは禁止します。

## 作成者

@MarA_Elec
