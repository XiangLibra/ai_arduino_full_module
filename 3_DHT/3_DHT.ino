#include <DHT.h>

#define DHTPIN D1     // 將DHT11的數據輸出引腳接到D1腳位
#define DHTTYPE DHT11   // 設置DHT11傳感器類型

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);  // 初始化串口，設置波特率為9600
  dht.begin();         // 初始化DHT11
}

void loop() {
  delay(2000);          // 每隔2秒讀取一次數據

  float humidity = dht.readHumidity();      // 讀取濕度數據
  float temperature = dht.readTemperature();  // 讀取溫度數據

  Serial.print("濕度: ");
  Serial.print(humidity);
  Serial.print("%\t");      // 以製表符分隔濕度和溫度數據
  Serial.print("溫度: ");
  Serial.print(temperature);
  Serial.println("C");     // 溫度數據以Celsius度為單位輸出

}
