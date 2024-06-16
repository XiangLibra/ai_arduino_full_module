#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "OPPO_Reno7";        // 請輸入您的WiFi網路名稱
const char* password = "12345678"; // 請輸入您的WiFi網路密碼

ESP8266WebServer server(80);

const int motorPin1 = D5; // 馬達控制引腳
const int motorPin2 = D6; // 馬達控制引腳

void setup() {
  Serial.begin(9600);

  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

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
  server.on("/half-speed", handleHalfSpeed);
  server.on("/full-speed", handleFullSpeed);
  server.on("/stop", handleStop);
  server.on("/reverse-half-speed", handleReverseHalfSpeed);
  server.on("/reverse-full-speed", handleReverseFullSpeed);
  
  server.begin();
  Serial.println("HTTP 伺服器已啟動");
}

void loop() {
  server.handleClient();
}

// 處理根目錄請求，返回控制網頁
void handleRoot() {
  String html = "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'>";
  html += "<style>body { font-size: 24px; }</style></head><body>";
  html += "<h1>馬達控制器</h1>";
  html += "<p><a href=\"/half-speed\"><button>半速正轉</button></a></p>";
  html += "<p><a href=\"/full-speed\"><button>全速正轉</button></a></p>";
  html += "<p><a href=\"/stop\"><button>停止</button></a></p>";
  html += "<p><a href=\"/reverse-half-speed\"><button>半速反轉</button></a></p>";
  html += "<p><a href=\"/reverse-full-speed\"><button>全速反轉</button></a></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

// 處理半速正轉請求
void handleHalfSpeed() {
  analogWrite(motorPin1, 128);
  analogWrite(motorPin2, 0);
  server.send(200, "text/html", "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='refresh' content='2;url=/'></head><body><p>馬達半速正轉中...</p><a href=\"/\">返回</a></body></html>");
}

// 處理全速正轉請求
void handleFullSpeed() {
  analogWrite(motorPin1, 255);
  analogWrite(motorPin2, 0);
  server.send(200, "text/html", "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='refresh' content='2;url=/'></head><body><p>馬達全速正轉中...</p><a href=\"/\">返回</a></body></html>");
}

// 處理停止請求
void handleStop() {
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 0);
  server.send(200, "text/html", "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='refresh' content='2;url=/'></head><body><p>馬達已停止...</p><a href=\"/\">返回</a></body></html>");
}

// 處理半速反轉請求
void handleReverseHalfSpeed() {
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 128);
  server.send(200, "text/html", "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='refresh' content='2;url=/'></head><body><p>馬達半速反轉中...</p><a href=\"/\">返回</a></body></html>");
}

// 處理全速反轉請求
void handleReverseFullSpeed() {
  analogWrite(motorPin1, 0);
  analogWrite(motorPin2, 255);
  server.send(200, "text/html", "<html><head><meta http-equiv='Content-Type' content='text/html; charset=utf-8'><meta http-equiv='refresh' content='2;url=/'></head><body><p>馬達全速反轉中...</p><a href=\"/\">返回</a></body></html>");
}
