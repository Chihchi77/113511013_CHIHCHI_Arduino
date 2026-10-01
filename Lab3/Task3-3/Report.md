# 課題報告：Task 3-3 HC-05 Wireless LED Control

- **學生姓名**：范芷祺

- **學生學號**：113511013

- **完成日期**：2026-10-1
---

### 1. 實驗目標(可參考課程投影片寫法)

- 使用 HC-05 Bluetooth 模組實現 Arduino 與 Host PC 之間的無線通訊。

- 將 Task 3-2 的有線序列通訊控制方式改為 Bluetooth 無線通訊。

- 學習 HC-05 Bluetooth 模組與 Arduino UART 通訊之接線與設定方式。

- 學習使用 Arduino `SoftwareSerial` 建立額外的序列通訊介面。

- 使用 C# Host PC 應用程式透過 Bluetooth Virtual COM Port 傳送 `ON` 與 `OFF` 指令。

- 驗證 Arduino 能透過 HC-05 接收電腦端指令，並正確控制外接 LED 亮滅。

### 2. 設備與元件

- Arduino Uno 開發板 x 1

- HC-05 Bluetooth 模組 x 1

- USB Type-B 傳輸線 x 1

- LED x 1

- 220 Ω 或 330 Ω 電阻 x 1

- 麵包板 x 1

- 杜邦線數條

- 個人電腦（已安裝 Arduino IDE 與 Visual Studio，並支援 Bluetooth）x 1

### 3. 操作說明與成果

1. **LED 接線**：將 Arduino Digital Pin 11 連接至限流電阻，再將電阻連接至 LED 長腳（Anode），LED 短腳（Cathode）接至 Arduino GND。

2. **HC-05 接線**：將 HC-05 的 `VCC` 連接至 Arduino 5V、`GND` 連接至 Arduino GND、`TXD` 連接至 Arduino D10，並將 Arduino D9 作為 TX 連接至 HC-05 的 `RXD`。

3. **SoftwareSerial 設定**：Arduino 程式使用 `SoftwareSerial bluetooth(10, 9)` 建立與 HC-05 之間的 UART 通訊，其中 D10 為 RX，D9 為 TX。

4. **Bluetooth 通訊初始化**：在 Arduino 程式中使用 `bluetooth.begin(9600)` 將 HC-05 通訊鮑率設定為 **9600 baud**。

5. **Bluetooth 配對**：在 Windows Bluetooth 設定中搜尋並配對 `HC-05`，完成配對後確認 Windows 所建立的 Bluetooth Virtual COM Port。

6. **C# GUI 設定**：沿用 Task 3-2 的 Windows Forms Host PC 應用程式，保留 `ON` 與 `OFF` 兩個控制按鈕。

7. **Bluetooth COM Port 設定**：將 C# `SerialPort` 所使用的 COM Port 改為 HC-05 在 Windows 中所建立的 Bluetooth COM Port，並將鮑率設為 **9600 baud**。

8. **ON 指令傳送**：按下 C# GUI 中的 `ON` 按鈕後，程式透過 Bluetooth COM Port 傳送 `ON` 指令，HC-05 接收後再透過 UART 傳送至 Arduino。

9. **LED 點亮**：Arduino 接收到 `ON` 指令後，使用 `digitalWrite(11, HIGH)` 將外接 LED 點亮。

10. **OFF 指令傳送**：按下 C# GUI 中的 `OFF` 按鈕後，程式透過 Bluetooth 傳送 `OFF` 指令至 Arduino。

11. **LED 熄滅**：Arduino 接收到 `OFF` 指令後，使用 `digitalWrite(11, LOW)` 將外接 LED 關閉。

12. **實驗成果**：成功使用 HC-05 Bluetooth 模組取代 Task 3-2 的 USB Serial Communication，實現由 C# Host PC 應用程式無線控制 Arduino 外接 LED。按下 `ON` 時 LED 正常亮起，按下 `OFF` 時 LED 正常熄滅，驗證 Bluetooth 無線序列通訊功能正常。

13. **操作影片**：請參閱同目錄下 `video/Task3-3.mp4` 之實際操作畫面。