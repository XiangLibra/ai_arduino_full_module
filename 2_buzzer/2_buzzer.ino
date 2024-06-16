// Do(523Hz), Re(587Hz), Mi(659Hz), Fa(698Hz)
// So(784Hz), La(880Hz), Si(988Hz) 高音 Do (1047Hz)

#define BUZZER_PIN D2  // 定義蜂鳴器腳位

void setup() {
  pinMode(BUZZER_PIN, OUTPUT); // 設定蜂鳴器腳位為輸出

  
  tone(BUZZER_PIN, 523,500);  // 發出Do音
  delay(500);             
  tone(BUZZER_PIN, 587,500);  // 發出Re音
  delay(500);             
  tone(BUZZER_PIN, 659,500);  // 發出Mi音
  delay(500);             
  noTone(BUZZER_PIN);     // 停止發聲
  delay(500);  
  
}

void loop() {
           
}
