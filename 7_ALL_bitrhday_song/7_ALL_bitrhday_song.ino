#include <DHT.h>

// 定義腳位
#define DHT_PIN D1
#define DHT_TYPE DHT11
#define BUZZER_PIN D2
#define RGB_R_PIN D0
#define RGB_G_PIN D3
#define RGB_B_PIN D4
#define SONAR_TRIGGER_PIN D8
#define SONAR_ECHO_PIN D7
#define L9110s_A_PIN D5
#define L9110s_B_PIN D6

// 音符頻率
const int NOTE_DO = 523;
const int NOTE_RE = 587;
const int NOTE_MI = 659;
const int NOTE_FA = 698;
const int NOTE_SO = 784;
const int NOTE_LA = 880;
const int NOTE_SI = 988;
const int NOTE_HIGH_DO = 1046;
int birthcount=0;

DHT dht(DHT_PIN, DHT_TYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RGB_R_PIN, OUTPUT);
  pinMode(RGB_G_PIN, OUTPUT);
  pinMode(RGB_B_PIN, OUTPUT);
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
  pinMode(L9110s_A_PIN, OUTPUT);
  pinMode(L9110s_B_PIN, OUTPUT);
}

// 發送超音波信號並返回距離
float 讀取距離() {
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  
  float duration = pulseIn(SONAR_ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2; // 聲速在空氣中大約是每秒344米，因此1微秒對應0.034公分
  
  return distance;
}

// 讀取濕度的函式
float 讀取濕度() {
  float humidity = dht.readHumidity();
  return humidity;
}

void 設定RGB顏色(int 紅色, int 綠色, int 藍色) {
  analogWrite(RGB_R_PIN, 紅色);
  analogWrite(RGB_G_PIN, 綠色);
  analogWrite(RGB_B_PIN, 藍色);
}
void birth1(){
      tone(BUZZER_PIN, NOTE_DO, 500);
    delay(250);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_RE, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_FA, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_MI, 500);
    delay(500);
}
void birth2(){
      tone(BUZZER_PIN, NOTE_DO, 500);
    delay(250);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_RE, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_SO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_FA, 500);
    delay(500);
}
void birth3(){
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(250);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, NOTE_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_HIGH_DO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_LA, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_FA, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_MI, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_RE, 500);
    delay(500);
}
void birth4(){
    tone(BUZZER_PIN, NOTE_SI, 500);
    delay(250);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, NOTE_SI, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_LA, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_FA, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_SO, 500);
    delay(500);
    tone(BUZZER_PIN, NOTE_FA, 500);
    delay(500);
}

void loop() {
  float 濕度 = 讀取濕度();
  float 距離 = 讀取距離();
  
  Serial.print("濕度: ");
  Serial.print(濕度);
  Serial.print("%  距離: ");
  Serial.print(距離);
  Serial.println(" 公分");

  // 如果濕度高於85%或超音波距離小於20公分
  if (濕度 > 85 || 距離 < 50) {
    
    // 蜂鳴器發出DO RE MI
    
  switch(birthcount){
    case   0:
          birth1() ;
          birthcount++;
          break;
    case   1:
          birth2() ;
          birthcount++;
          break;
    case   2:
          birth3() ;
          birthcount++;
          break;
    default   :
             
          birth4() ;
          birthcount=0;
          break;
          
   }



    // tone(BUZZER_PIN, 523, 500);
    // delay(500);
    // tone(BUZZER_PIN, 587, 500);
    // delay(500);
    // tone(BUZZER_PIN, 659, 500);
    // delay(500);
    noTone(BUZZER_PIN);

    // RGB LED亮紅燈
    設定RGB顏色(255, 0, 0);

    // 馬達全速轉動
    // analogWrite(L9110s_A_PIN, 255);
    // analogWrite(L9110s_B_PIN, 0);
    analogWrite(L9110s_A_PIN, 0);
    analogWrite(L9110s_B_PIN, 255);
  } else {
    // 亮綠燈
    設定RGB顏色(0, 255, 0);

    // 停止蜂鳴器和馬達
    noTone(BUZZER_PIN);
    analogWrite(L9110s_A_PIN, 0);
    analogWrite(L9110s_B_PIN, 0);
  }
  
  delay(1000); // 每秒檢測一次
}
