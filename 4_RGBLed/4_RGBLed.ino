const int red_PIN = D0;
const int green_PIN = D3;
const int blue_PIN = D4;

void setup() {
  Serial.begin(9600);
  
  // 設定RGB LED的引腳為輸出模式
  pinMode(red_PIN, OUTPUT);
  pinMode(green_PIN, OUTPUT);
  pinMode(blue_PIN, OUTPUT);
}

// 控制RGB LED顏色的函式
void SetRGBColor(int red, int green, int blue) {
  analogWrite(red_PIN, red); 
  analogWrite(green_PIN, green);
  analogWrite(blue_PIN, blue);
}

void loop() {
  // 設定不同顏色的RGB值
  SetRGBColor(255, 0, 0); // 紅色
  delay(1000);
  
  SetRGBColor(0, 255, 0); // 綠色
  delay(1000);
  
  SetRGBColor(0, 0, 255); // 藍色
  delay(1000);

  SetRGBColor(255, 255, 0); // 紅+綠色
  delay(1000);
  SetRGBColor(0, 255, 255); // 綠+藍色
  delay(1000);
  SetRGBColor(255, 0, 255); // 藍+紅色
  delay(1000);
  SetRGBColor(30, 30, 30); // 白色
  delay(1000);
  SetRGBColor(100, 100, 100); // 白色
  delay(1000);
  SetRGBColor(255, 255, 255); // 白色
  delay(1000);
}
