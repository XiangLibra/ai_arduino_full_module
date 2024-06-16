// 定義超音波感測器的接腳
const int TRIGGER_PIN = D8; // 控制超音波感測器的觸發信號
const int ECHO_PIN = D7;    // 超音波感測器的接收信號

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

// 發送超音波信號並返回距離
float getDistance() {
// 發送一個10微秒的脈衝來觸發超音波感測器
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  
 // 計算超音波感測器返回的脈衝寬度，轉換成距離（單位：公分）
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // 聲速在空氣中大約是每秒344米
  
  return distance;
}

void loop() {
    float distance = getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" 公分");
  
  delay(1000); 
}
