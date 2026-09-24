# 課題報告：Advanced Task 1-2 RGB LED — Layering Three Inputs

**學生姓名**：范芷祺

**學生學號**：113511013

**完成日期**：2026-9-24

### 1. 實驗目標

將數位輸入、序列埠輸入與類比輸入整合，用三種不同輸入共同控制一顆 RGB LED。

使用 Button（digital input） 控制紅色通道 R。

使用 Serial Monitor 的序列輸入控制綠色通道 G。

使用 Variable Resistor（analog input） 控制藍色通道 B。

觀察三個顏色通道疊加後的顏色變化：藍色 → 加入紅色形成紫色 → 再加入綠色形成白色。

### 2. 設備與元件

Arduino Uno 開發板 x 1

USB Type-B 傳輸線 x 1

麵包板 x 1

Common-cathode RGB LED x 1

LED 限流電阻 x 3（R、G、B 各一個）

Push button x 1

可變電阻（Variable Resistor / Potentiometer）x 1

杜邦線若干

個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果

RGB LED 接線：使用 common-cathode RGB LED，將最長腳接至 Arduino GND；R、G、B 三個 color pin 分別串接一個限流電阻後再接至 Arduino 輸出腳位。

藍色通道 B — 類比輸入：使用可變電阻作為 analog input，讀取旋鈕位置後控制藍色通道的輸出。當可變電阻被旋轉並使藍色通道點亮時，RGB LED 顯示藍色。

紅色通道 R — 數位輸入：讀取 push button 的 digital input。當按下按鈕時加入紅色通道，使原本的藍色與紅色疊加，RGB LED 顯示紫色。

綠色通道 G — Serial input：利用 Serial Monitor 輸入資料；當接收到字元 1 時開啟綠色通道。此時紅、綠、藍三個通道同時點亮，RGB LED 顯示接近白色。

分階段測試：先確認藍色通道能正常由可變電阻控制，再加入按鈕控制紅色，最後加入 Serial Monitor 控制綠色，以便逐步確認每一個輸入與顏色通道都能正常工作。

實驗成果：三種不同輸入成功整合於同一個 RGB LED 控制程式中。旋轉可變電阻可產生藍色；再按下按鈕後加入紅色形成紫色；最後由 Serial Monitor 輸入 1 開啟綠色，使三色疊加成白色，符合課程要求的 layering 效果。

操作影片：請參閱同目錄下 video/Task1-2.mp4 之實際操作畫面。