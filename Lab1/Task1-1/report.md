# 課題報告：Advanced Task 1-1 使用可變電阻調整 LED 亮度

**學生姓名**：范芷祺

**學生學號**：113511013

**完成日期**：2026-9-24

----
### 1. 實驗目標

使用可變電阻作為類比輸入，利用 analogRead(pin) 讀取輸入值。

依照可變電阻的類比輸入值調整 LED 亮度；輸入值越大，LED 越亮。

將 analogRead() 的讀值由 0～1023 對應到 PWM 輸出的 0～255，再使用 analogWrite() 控制 LED 亮度。

使用 Serial.begin()、Serial.print() / Serial.println()，每 1 秒在 Serial Monitor 顯示一次目前的類比輸入值。

### 2. 設備與元件

Arduino Uno 開發板 x 1

USB Type-B 傳輸線 x 1

麵包板 x 1

LED x 1

LED 限流電阻 x 1

可變電阻（Variable Resistor / Potentiometer）x 1

杜邦線若干

個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果

建立可變電阻輸入電路：將可變電阻兩側端點分別接至 Arduino 的 5V 與 GND，中間端點接至類比輸入腳位，讓 Arduino 能以 analogRead() 讀取旋鈕位置所對應的電壓值。

建立 LED 輸出電路：將 LED 串接限流電阻後接至支援 PWM 的數位腳位，並使用 analogWrite() 控制 LED 亮度。

類比值轉換：analogRead() 的讀值範圍為 0～1023，而 analogWrite() 的 PWM 輸出值範圍為 0～255，因此將讀到的類比值縮放至 PWM 可使用的範圍後輸出到 LED。

Serial Monitor 顯示：在 setup() 中設定序列通訊，並在程式執行期間每 1 秒輸出一次目前的 analog value，方便觀察可變電阻的位置與讀值變化。

實驗成果：旋轉可變電阻時，Serial Monitor 中的數值會隨旋鈕位置改變；數值增加時 LED 亮度提高，數值減少時 LED 亮度降低，成功以類比輸入控制 PWM 輸出。

原理解釋：Arduino Uno 的類比輸入使用 10-bit ADC，因此共有 (2^{10}=1024) 個量化階級，analogRead() 的輸出範圍為 0～1023，最大值為 1023。

操作影片：請參閱同目錄下 video/Task1-1.mp4 之實際操作畫面。
