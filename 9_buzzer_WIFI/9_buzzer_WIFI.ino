#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO_Reno7";
const char* password = "12345678";

ESP8266WebServer server(80);

const int led_pin = 4; // NodeMCU 上的內建 LED 連接到 GPIO 4
const int buzzer_pin = D2;

// 音符頻率
const int NOTE_DO = 523;
const int NOTE_RE = 587;
const int NOTE_MI = 659;
const int NOTE_FA = 698;
const int NOTE_SO = 784;
const int NOTE_LA = 880;
const int NOTE_SI = 988;
const int NOTE_HIGH_DO = 1046;

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  digitalWrite(led_pin, HIGH);

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
  server.on("/do", HTTP_GET, handleDo);
  server.on("/re", HTTP_GET, handleRe);
  server.on("/mi", HTTP_GET, handleMi);
  server.on("/fa", HTTP_GET, handleFa);
  server.on("/so", HTTP_GET, handleSo);
  server.on("/la", HTTP_GET, handleLa);
  server.on("/si", HTTP_GET, handleSi);
  server.on("/high_do", HTTP_GET, handleHighDo);

  server.begin();
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();
}

// 處理根目錄請求，返回控制網頁
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>ESP8266 蜂鳴器控制</title><meta charset=\"UTF-8\"><style>body { font-size: 24px; }</style></head><body><h1>ESP8266 蜂鳴器控制</h1><p>點擊以下按鈕以控制蜂鳴器發出音符：</p><p>";
  html += "<a href=\"/do\"><button style=\"font-size: 24px;\">DO</button></a>&nbsp;";
  html += "<a href=\"/re\"><button style=\"font-size: 24px;\">RE</button></a>&nbsp;";
  html += "<a href=\"/mi\"><button style=\"font-size: 24px;\">MI</button></a>&nbsp;";
  html += "<a href=\"/fa\"><button style=\"font-size: 24px;\">FA</button></a>&nbsp;";
  html += "<a href=\"/so\"><button style=\"font-size: 24px;\">SO</button></a>&nbsp;";
  html += "<a href=\"/la\"><button style=\"font-size: 24px;\">LA</button></a>&nbsp;";
  html += "<a href=\"/si\"><button style=\"font-size: 24px;\">SI</button></a>&nbsp;";
  html += "<a href=\"/high_do\"><button style=\"font-size: 24px;\">高音 DO</button></a>";
  html += "</p></body></html>";
  server.send(200, "text/html", html);
}

// 播放音符並返回到主頁
void playNoteAndReturn(int note) {
  tone(buzzer_pin, note, 500);
  delay(500);
  handleRoot();
}

// 處理蜂鳴器音符的請求
void handleDo() {
  playNoteAndReturn(NOTE_DO);
}

void handleRe() {
  playNoteAndReturn(NOTE_RE);
}

void handleMi() {
  playNoteAndReturn(NOTE_MI);
}

void handleFa() {
  playNoteAndReturn(NOTE_FA);
}

void handleSo() {
  playNoteAndReturn(NOTE_SO);
}

void handleLa() {
  playNoteAndReturn(NOTE_LA);
}

void handleSi() {
  playNoteAndReturn(NOTE_SI);
}

void handleHighDo() {
  playNoteAndReturn(NOTE_HIGH_DO);
}
