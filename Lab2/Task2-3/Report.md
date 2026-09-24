# 課題報告：Advanced Task 2-3 External Interrupt 與 Polling 比較

- **學生姓名**：范芷祺
- **學生學號**：113511013
- **完成日期**：2026-9-24

---

### 1. 實驗目標(可參考課程投影片寫法)
- 延續 Basic Task 2-3，建立兩組按鍵與 LED 電路。
- Button A + LED A 使用 External Interrupt 控制 LED 狀態。
- Button B + LED B 使用 Polling 持續讀取按鍵狀態，並利用 edge detection 偵測按下事件。
- 在 `loop()` 結尾加入 `delay(2000)` 模擬 busy/blocking system，比較 External Interrupt 與 Polling 在阻塞狀態下的反應差異。

### 2. 設備與元件
- Arduino Uno 開發板 x 1
- Push button x 2
- LED x 2
- LED 限流電阻 x 2
- 麵包板 x 1
- 杜邦線若干
- USB Type-B 傳輸線 x 1
- 個人電腦（已安裝 Arduino IDE）x 1

### 3. 操作說明與成果
1. **建立 Button A + LED A 電路**：將 Button A 接至 Arduino Uno 支援 external interrupt 的腳位，並將 LED A 接至數位輸出腳位。
2. **設定 External Interrupt**：使用 `attachInterrupt()` 設定 Button A 的中斷條件；當按鍵產生指定的訊號變化時執行 ISR，並在 ISR 中切換 LED A 的狀態。
3. **建立 Button B + LED B 電路**：將 Button B 接至一般數位輸入腳位，並在 `loop()` 中使用 `digitalRead()` 持續讀取按鍵狀態。
4. **使用 Edge Detection**：比較 Button B 目前狀態與前一次狀態，只在偵測到按鍵由未按下變為按下時切換 LED B，避免按住按鍵時重複觸發。
5. **加入 Blocking Delay**：在 `loop()` 結尾加入 `delay(2000)`，使主程式每次執行後暫停 2 秒，以模擬忙碌或阻塞中的系統。
6. **實驗成果**：Button A 使用 external interrupt，因此即使主程式正在執行 `delay(2000)`，按鍵事件仍能觸發 ISR 並更新 LED A。Button B 使用 polling，只能在 `loop()` 執行到讀取按鍵的程式碼時偵測輸入，因此反應較慢，短暫按鍵事件也可能在延遲期間被漏掉。實驗結果清楚顯示 external interrupt 較適合需要即時反應的非同步事件，而 polling 較適合不需要立即處理的輸入。
7. **操作影片**：請參閱同目錄下 `video/Task2-3.mp4` 之實際操作畫面。