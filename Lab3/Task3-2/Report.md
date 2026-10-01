# 課題報告：Task 3-2 LED Control with Serial Communication

- **學生姓名**：范芷祺

- **學生學號**：113511013

- **完成日期**：2026-10-1

---

### 1. 實驗目標(可參考課程投影片寫法)

- 使用 C# 建立 Host PC GUI 應用程式，並透過按鈕控制 Arduino 外接 LED。

- 學習利用 Windows Serial Port 與 Arduino 進行序列通訊。

- 掌握 Arduino `Serial.begin()`、`Serial.available()`、`Serial.readStringUntil()` 等序列埠函式之使用方式。

- 學習由 C# 程式透過 COM Port 傳送 `ON` 與 `OFF` 指令至 Arduino。

- 完成 Host PC 與 Arduino 之間的雙向序列通訊架構，並驗證外接 LED 能依照收到的指令正確亮滅。

### 2. 設備與元件

- Arduino Uno 開發板 x 1

- USB Type-B 傳輸線 x 1

- LED x 1

- 220 Ω 或 330 Ω 電阻 x 1

- 麵包板 x 1

- 杜邦線數條

- 個人電腦（已安裝 Arduino IDE 與 Visual Studio）x 1

### 3. 操作說明與成果

1. **硬體接線**：將 Arduino Digital Pin 11 連接至限流電阻，再將電阻連接至 LED 長腳（Anode），LED 短腳（Cathode）接至 Arduino GND。

2. **Arduino 程式設定**：在 Arduino 程式中使用 `Serial.begin(9600)` 初始化序列通訊，並使用 `Serial.available()` 持續檢查是否收到來自電腦的資料。

3. **指令接收與 LED 控制**：Arduino 使用 `Serial.readStringUntil('\n')` 接收 C# 程式傳送的字串，當收到 `ON` 時，使用 `digitalWrite(11, HIGH)` 將外接 LED 點亮；當收到 `OFF` 時，使用 `digitalWrite(11, LOW)` 將 LED 關閉。

4. **C# GUI 設計**：使用 Windows Forms 建立 Host PC 應用程式，介面包含 `ON` 與 `OFF` 兩個按鈕。

5. **序列埠通訊**：C# 程式透過 `SerialPort` 類別開啟 Arduino 所使用的 COM Port，並將鮑率（Baud rate）設定為 **9600 baud**。

6. **ON 按鈕功能**：按下 `ON` 按鈕後，C# 程式透過序列埠傳送 `ON` 指令至 Arduino，使外接 LED 點亮。

7. **OFF 按鈕功能**：按下 `OFF` 按鈕後，C# 程式透過序列埠傳送 `OFF` 指令至 Arduino，使外接 LED 熄滅。

8. **實驗成果**：成功由 C# Host PC 應用程式透過 USB Serial Communication 控制 Arduino 外接 LED。按下 `ON` 時 LED 正常亮起，按下 `OFF` 時 LED 正常熄滅，驗證 PC 與 Arduino 之間的序列通訊功能正常。

9. **操作影片**：請參閱同目錄下 `video/Task3-2.mp4` 之實際操作畫面。