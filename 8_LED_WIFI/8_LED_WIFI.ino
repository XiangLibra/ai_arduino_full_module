#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO_Reno7";
const char* password = "12345678";

ESP8266WebServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(9600);
  delay(10);

  // 連接到 WiFi 網路
  Serial.println();
  Serial.println();
  Serial.print("連接到 ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi 已連接");
  Serial.println("IP 地址: ");
  Serial.println(WiFi.localIP());

  // 定義 HTTP 請求處理程序
  server.on("/", HTTP_GET, handleRoot);
  server.on("/on", HTTP_GET, handleOn);
  server.on("/off", HTTP_GET, handleOff);

  server.begin();
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();
}

// 處理根目錄請求，返回控制網頁
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP8266 LED 控制</title><meta charset=\"UTF-8\"><style>body { font-size: 24px; }</style></head><body><h1>ESP8266 LED 控制</h1><p>點擊以下按鈕以控制 LED：</p><p><a href=\"/on\"><button style=\"font-size: 24px;\">打開 LED</button></a>&nbsp;<a href=\"/off\"><button style=\"font-size: 24px;\">關閉 LED</button></a></p></body></html>";
  server.send(200, "text/html", html);
}

// 處理打開 LED 的請求
void handleOn() {
  digitalWrite(LED_BUILTIN, LOW);
  server.send(200, "text/html", "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><style>body { font-size: 24px; }</style></head><body><p>LED 已打開</p><p><a href=\"/\">返回</a></p></body></html>");
}

// 處理關閉 LED 的請求
void handleOff() {
  digitalWrite(LED_BUILTIN, HIGH);
  server.send(200, "text/html", "<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><style>body { font-size: 24px; }</style></head><body><p>LED 已關閉</p><p><a href=\"/\">返回</a></p></body></html>");
}
