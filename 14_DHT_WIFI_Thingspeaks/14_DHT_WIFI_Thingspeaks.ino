#include <ESP8266WiFi.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "OPPO_Reno7";        // 請輸入您的WiFi網路名稱
const char* password = "12345678"; // 請輸入您的WiFi網路密碼

const char* server = "api.thingspeak.com";
const String apiKey = "ITSSIEXG4Z06UN7F";

const int DHTPIN = D1;  // DHT11 传感器连接到 GPIO 5 (D1)
const int DHTTYPE = DHT11;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(10);

  // 连接到 WiFi 网络
  Serial.println();
  Serial.println();
  Serial.print("连接到 ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi 已连接");
  Serial.println("IP 地址: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 等待 30 秒
  delay(10000);

  // 读取传感器数据
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("無法讀取傳感器數據");
    return;
  }

  Serial.print("濕度: ");
  Serial.print(humidity);
  Serial.print(" %\t溫度: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // 发送数据到 ThingSpeak
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
