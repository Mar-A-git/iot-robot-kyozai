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
```

## ライセンス

- **ソースコード**（`ch*/` 以下）… MIT License
- **教材資料**（`docs/` 以下）… CC BY 4.0

## 作成者

@MarA_Elec
