#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "Weber"; // 替换为您的WiFi SSID
const char* password = "88888888"; // 替换为您的WiFi密码
const String backendURL = "http://172.20.10.5:3000/receive-data"; // 后端API URL

const String deviceId = "1";

void setup() {
  Serial.begin(115200);

  // 连接到WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  while (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // 假设数据以换行符结束
    Serial.println(data);
    // 解析数据并发送到后端
    DynamicJsonDocument jsonDoc(1024);
    jsonDoc["deviceId"] = deviceId;

    // 解析从Arduino Mega 2560接收到的数据
    String delimiter = ",";
    int sensorIndex = 0;
    size_t pos = 0;

    while ((pos = data.indexOf(delimiter)) != -1 && sensorIndex < 9) {
      String sensorValue = data.substring(0, pos);
      String sensorKey = "fsr" + String(sensorIndex);
      int sensorReading = sensorValue.toFloat(); // 将字符串转换为浮点数
      jsonDoc["data"][sensorKey] = sensorReading;
      data = data.substring(pos + 1);
      sensorIndex++;
    }

    // 将数据发送到后端
    WiFiClient client;
    HTTPClient http;

    http.begin(client, backendURL);
    http.addHeader("Content-Type", "application/json");

    String jsonString;
    serializeJson(jsonDoc, jsonString);

    int httpCode = http.POST(jsonString);

    if (httpCode > 0) {
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        const String &payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
    } else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }
}
