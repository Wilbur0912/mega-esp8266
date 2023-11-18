#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "HELLREVENGER"; // 替换为您的WiFi SSID
const char* password = "1029384756"; // 替换为您的WiFi密码
const String backendURL = "https://spineinspectorbackend-production.up.railway.app/api/ap/recieve/"; // 后端API URL
const String backendHost = "spineinspectorbackend-production.up.railway.app";
const String api = "/api/ap/receive/";

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
  //testRequest();
}



void testRequest() {
  WiFiClientSecure client;
  client.setInsecure();
  if(client.connect(backendHost, 443)){
    Serial.println("trying to send something");
      //client.print(String("GET ") + "/" + "HTTP/1.1\r\nHost: "+"www.google.com"+"\r\n"+"Content-Type: plain/text\r\nContent-Length: 0\r\nbody:\r\n\r\n");

      client.print(String("POST ") + api + "HTTP/1.1\r\nHost: "+backendHost+"\r\n"+"Content-Type: application/json\r\nContent-Length: 2\r\nbody:{}\r\n\r\n");
    while(client.available()) {
      String line = client.readStringUntil('\n');
      Serial.println(line);
    }
      Serial.println("end");
  } else {
    Serial.println("cannot connect");
  }
}

void splitData(DynamicJsonDocument &doc, String data) {
  String result[9] = {};
  int index = data.indexOf(',');
  doc["fsr0"] = data.substring(0, index++).toFloat();

  for(int i = 1; i < 9; i++) {
    int newIndex = data.indexOf(',', index);
    String key = "fsr";
    key.concat(i);
    doc[key] = data.substring(index, newIndex).toFloat();
    index = newIndex+1;
  }
  
}

void loop() {
  if(WiFi.status() != WL_CONNECTED) {
    //Serial.print(".");
    delay(500);
    return;
  }
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n'); // 假设数据以换行符结束
    //Serial.println(data);
    // 解析数据并发送到后端
    DynamicJsonDocument jsonDoc(1024);
    jsonDoc["deviceId"] = deviceId;
    splitData(jsonDoc, data);

    String jsonString;
    
    serializeJson(jsonDoc, jsonString);
    //jsonDoc["data"] = data;

    // 将数据发送到后端
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    http.begin(client,backendURL);
    http.addHeader("Content-Type", "application/json");

    Serial.println(jsonString);

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
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
  }
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
  }
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
  }
}
