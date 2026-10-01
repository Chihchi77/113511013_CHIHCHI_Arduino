# 課題報告：Task 3-1 Timer Interrupt vs Blocking Delay

- **學生姓名**：范芷祺

- **學生學號**：113511013

- **完成日期**：2026-10-1

---

### 1. 實驗目標(可參考課程投影片寫法)

- 建立兩組 Button + LED 電路，分別使用 Timer Interrupt 與 Blocking Delay 方式讀取按鈕狀態並控制 LED。

- 學習使用 `TimerOne` library 建立週期性 Timer Interrupt，並設定每 50 ms 觸發一次中斷。

- 學習在 Interrupt Service Routine（ISR）中讀取 Button A 的狀態並更新 LED A。

- 比較 Timer Interrupt 與一般 `loop()` 搭配 Blocking Delay 在按鈕反應速度與程式執行方式上的差異。

- 理解 Blocking Delay 對 Arduino 主程式執行流程的影響，並思考不同控制方式在機器人系統中的適用情況。

### 2. 設備與元件

- Arduino Uno 開發板 x 1

- USB Type-B 傳輸線 x 1

- Push Button x 2

- LED x 2

- LED 限流電阻 x 2

- 麵包板 x 1

- 杜邦線數條

- 個人電腦（已安裝 Arduino IDE 與 TimerOne Library）x 1

### 3. 操作說明與成果

1. **硬體接線**：建立兩組 Button + LED 電路，分別作為 Button A + LED A 與 Button B + LED B，並將按鈕與 LED 連接至 Arduino 的 Digital I/O Pin。

2. **Timer Interrupt 設定**：在 Arduino 程式中引入 `TimerOne` library，設定 Timer Interrupt 每 **50 ms** 觸發一次，並指定 Interrupt Service Routine（ISR）作為中斷處理函式。

3. **Button A + LED A 控制**：在 Timer Interrupt 的 ISR 中讀取 Button A 的狀態，並依照按鈕狀態即時更新 LED A。由於 Timer Interrupt 會週期性執行，因此不需要等待主程式 `loop()` 執行到特定位置即可檢查 Button A。

4. **Button B + LED B 控制**：在 Arduino 的 `loop()` 中讀取 Button B 的狀態，並依照按鈕狀態更新 LED B。

5. **Blocking Delay 設定**：在 `loop()` 函式最後加入 `delay(1000)`，使主程式每次執行後暫停 **1 秒**，藉此觀察 Blocking Delay 對 Button B 與 LED B 反應速度的影響。

6. **Timer Interrupt 實驗結果**：Button A 的狀態每 50 ms 由 Timer Interrupt 檢查一次，因此按下或放開 Button A 時，LED A 能快速反映按鈕狀態，即使主程式存在較長的 Blocking Delay，Timer Interrupt 仍可週期性執行。

7. **Blocking Delay 實驗結果**：Button B 僅在 `loop()` 執行時被讀取，而每次 `loop()` 後會執行 `delay(1000)`，因此 Button B 的狀態可能需要等待最多約 1 秒才會被讀取，使 LED B 的反應明顯較慢。

8. **兩種方法比較**：Timer Interrupt 能在固定時間間隔執行指定工作，不需要等待主程式完成其他工作，因此較適合需要快速且固定週期反應的控制任務；Blocking Delay 的程式較簡單，但執行 `delay()` 時主程式會暫停，其他需要由 `loop()` 處理的工作也必須等待。

9. **機器人系統應用**：在機器人系統中，通常需要同時處理感測器讀取、馬達控制、通訊與安全監控等多項工作，因此相較於長時間的 Blocking Delay，Timer Interrupt 較適合用於具有固定週期或即時性需求的控制工作。

10. **實驗成果**：成功使用兩組 Button + LED 電路比較 Timer Interrupt 與 Blocking Delay。實驗中 LED A 能快速回應 Button A 的狀態，而 LED B 因受到 1 秒 Blocking Delay 影響，反應速度明顯較慢，成功觀察兩種程式執行方式的差異。

11. **操作影片**：請參閱同目錄下 `video/Task3-1.mp4` 之實際操作畫面。