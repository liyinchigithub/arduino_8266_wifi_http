#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

const char* ssid = "WIFI账号名";
const char* password = "WIFI密码";

void setup() {
  // 
  pinMode(D0, OUTPUT); // 设置D0为输出模
  pinMode(D1, OUTPUT); // 设置D0为输出模
  pinMode(D2, OUTPUT); // 设置D0为输出模
  pinMode(D3, OUTPUT); // 设置D0为输出模
  // 
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("连接WiFi...");
  }

  Serial.println("WiFi 连接成功");
  Serial.println("WiFi IPAddress:");
  Serial.println(WiFi.localIP().toString());
  
}

void loop() {
  // 
  lightInit();
  
  if (WiFi.status() == WL_CONNECTED) {
   httpRequestPost();
   delay(2000); 
   httpRequestGet();
  }

  delay(1000); //等待10秒再次发送请求
}

void httpRequestPost(){
    WiFiClientSecure client;
    HTTPClient http;

    client.setInsecure(); // 关闭 SSL 验证

    http.begin(client, "https://u357b53148.yicp.fun/v1/users/addUser"); //指定HTTP请求的URL
    http.addHeader("Content-Type", "application/json"); //指定HTTP请求的头部

    //发送POST请求，数据为JSON格式
    int httpCode = http.POST("{\"password\": \"1111111\", \"userName\": \"liyinchi\"}");

    if(httpCode > 0) {
      String payload = http.getString(); //获取服务器响应
      Serial.println("httpCode:"); 
      Serial.println(httpCode); //打印HTTP响应码
      Serial.println("payload:"); 
      Serial.println(payload); //打印服务器响应
      isLight(httpCode);
    } else {
      Serial.println("HTTP request failed.");
      Serial.println(http.errorToString(httpCode).c_str());
      isLight(httpCode);
    }

    http.end(); //关闭连接
}

void httpRequestGet(){
    WiFiClientSecure client;
    HTTPClient http;

    client.setInsecure(); // 关闭 SSL 验证

    http.begin(client, "https://u357b53148.yicp.fun/v1/getLatestImage?fileName=test.png"); //指定HTTP请求的URL

    int httpCode = http.GET(); //发送GET请求

    if(httpCode > 0) {
      String payload = http.getString(); //获取服务器响应
      Serial.println("httpCode:"); 
      Serial.println(httpCode); //打印HTTP响应码
      Serial.println("payload:"); 
      Serial.println(payload); //打印服务器响应
      isLight(httpCode);
    } else {
      Serial.println("HTTP request failed.");
      Serial.println(http.errorToString(httpCode).c_str());
      isLight(httpCode);
    }

    http.end(); //关闭连接
}

void isLight(int httpCode){
    if(httpCode > 0) {
      digitalWrite(D0, HIGH); // 当HTTP请求成功时，将D0引脚设置为高电平
    } else {
      digitalWrite(D0, LOW); // 当HTTP请求失败时，将D0引脚设置为低电平
    }
    // 生成随机数
    lightRYG(random(1,4));
}


void lightRYG(int pinNum){
  switch (pinNum)
  {
  case 1:
    /* code */
    digitalWrite(D1, HIGH); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, LOW); 
    Serial.println("亮D1"); 
    break;
  case 2:
    digitalWrite(D1, LOW); 
    digitalWrite(D2, HIGH); 
    digitalWrite(D3, LOW); 
    Serial.println("亮D2"); 
    break;
  default:
    digitalWrite(D1, LOW); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, HIGH); 
    Serial.println("亮D3"); 
    break;
  }
}


void lightInit(){
    digitalWrite(D0, LOW); 
    digitalWrite(D1, LOW); 
    digitalWrite(D2, LOW); 
    digitalWrite(D3, LOW); 
}