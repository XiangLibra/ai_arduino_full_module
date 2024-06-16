#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "fcxxmi";
const char* password = "1234567890";

const char* server = "api.thingspeak.com";
const String apiKey = "DVC1V30A5BORQ7EC";

void setup() {
  Serial.begin(115200);
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
}

void loop() {
  // 等待 30 秒
  delay(15000);

  // 生成隨機溫度和濕度數據
  float temperature = random(200, 401) / 10.0; // 20~40之間的溫度
  float humidity = random(500, 901) / 10.0;    // 50~90之間的濕度

  Serial.print("溫度: ");
  Serial.print(temperature);
  Serial.print(" °C\t濕度: ");
  Serial.print(humidity);
  Serial.println(" %");

  // 發送數據到 ThingSpeak
  sendToThingSpeak(temperature, humidity);
}

// 將數據發送到 ThingSpeak
void sendToThingSpeak(float temperature, float humidity) {
  WiFiClient client;
  if (!client.connect(server, 80)) {
    Serial.println("連接到 ThingSpeak 失敗");
    return;
  }

  String url = "/update?api_key=";
  url += apiKey;
  url += "&field1=";
  url += String(temperature);
  url += "&field2=";
  url += String(humidity);

  Serial.print("發送數據到 ThingSpeak: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(500);

  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
}
