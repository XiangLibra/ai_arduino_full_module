#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO_Reno7";        // 請輸入您的WiFi網路名稱
const char* password = "12345678"; // 請輸入您的WiFi網路密碼

ESP8266WebServer server(80);

const int TRIGGER_PIN = D8; // 控制超音波感測器的觸發信號
const int ECHO_PIN = D7;    // 超音波感測器的接收信號

void setup() {
  Serial.begin(9600);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);

  // WiFi連線等待
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi 已連接");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  
  server.begin();
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float distance = getDistance();

  String html = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
  html += "<meta http-equiv='refresh' content='2'>";  // 每2秒自動重新整理
  html += "<style>body { font-size: 24px; }</style></head><body>";
  html += "<h1>超音波距離顯示器</h1>";
  html += "<p>目前距離：" + String(distance) + " 公分</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
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
