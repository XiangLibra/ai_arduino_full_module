#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

#define DHTPIN D1          // DHT11溫濕度感應器接在D1腳位
#define DHTTYPE DHT11      // DHT11型號

const char* ssid = "OPPO_Reno7";        // 請輸入您的WiFi網路名稱
const char* password = "12345678"; // 請輸入您的WiFi網路密碼

ESP8266WebServer server(80);        // 設定Web伺服器埠號為80

DHT dht(DHTPIN, DHTTYPE);           // 宣告DHT物件

void handleRoot() {
  float h = dht.readHumidity();     // 讀取濕度
  float t = dht.readTemperature();  // 讀取溫度（攝氏）

  String message = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
  message += "<meta http-equiv='refresh' content='2'>"; // 每2秒重新整理
  message += "</head><body>"; // 網頁開始標籤
  message += "<h1 style='font-size:40px;'>溫濕度顯示器</h1>";   // 標題
  message += "<h2 style='font-size:30px;'>現在溫度：" + String(t) + "℃</h2>";   // 顯示溫度
  message += "<h2 style='font-size:30px;'>現在濕度：" + String(h) + "%</h2>";   // 顯示濕度
  message += "</body></html>";      // 網頁結束標籤

  server.send(200, "text/html", message); // 回傳網頁
}

void setup() {
  Serial.begin(9600);               // 設定序列埠速度
  delay(10);

  dht.begin();                      // 初始化DHT感應器

  Serial.println();
  Serial.println();
  Serial.print("連接到 ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);       // 連接WiFi網路

  // WiFi連線等待
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi 已連接");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());   // 顯示IP位置

  server.on("/", handleRoot);       // 設定網頁伺服器回應函式
  server.begin();                   // 啟動Web伺服器
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();            // 處理網頁請求
}
