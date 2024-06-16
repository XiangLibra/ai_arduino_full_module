#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO_Reno7";        // 請輸入您的WiFi網路名稱
const char* password = "12345678"; // 請輸入您的WiFi網路密碼

ESP8266WebServer server(80);

const int red_PIN = D0;
const int green_PIN = D3;
const int blue_PIN = D4;

void setup() {
  Serial.begin(9600);
  
  // 設定RGB LED的引腳為輸出模式
  pinMode(red_PIN, OUTPUT);
  pinMode(green_PIN, OUTPUT);
  pinMode(blue_PIN, OUTPUT);

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
  server.on("/setRGB", handleSetRGB);
  
  server.begin();
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
  html += "<style>body { font-size: 24px; }</style></head><body>";
  html += "<h1>RGB LED 控制</h1>";
  html += "<p><a href=\"/setRGB?r=255&g=0&b=0\"><button style=\"font-size: 20px;\">紅色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=0&g=255&b=0\"><button style=\"font-size: 20px;\">綠色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=0&g=0&b=255\"><button style=\"font-size: 20px;\">藍色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=255&g=255&b=0\"><button style=\"font-size: 20px;\">紅+綠色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=0&g=255&b=255\"><button style=\"font-size: 20px;\">綠+藍色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=255&g=0&b=255\"><button style=\"font-size: 20px;\">藍+紅色</button></a></p>";
  html += "<p><a href=\"/setRGB?r=255&g=255&b=255\"><button style=\"font-size: 20px;\">白色</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void handleSetRGB() {
  int red = server.arg("r").toInt();
  int green = server.arg("g").toInt();
  int blue = server.arg("b").toInt();

  SetRGBColor(red, green, blue);

  String html = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'></head><body>";
  html += "<h1>RGB LED 控制</h1>";
  html += "<p>已設定顏色為 R:" + String(red) + " G:" + String(green) + " B:" + String(blue) + "</p>";
  html += "<p><a href=\"/\"><button style=\"font-size: 20px;\">返回</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// 控制RGB LED顏色的函式
void SetRGBColor(int red, int green, int blue) {
  analogWrite(red_PIN, red); 
  analogWrite(green_PIN, green);
  analogWrite(blue_PIN, blue);
}
