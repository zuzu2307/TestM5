/*#include <Arduino.h>      //? Main Arduino Lib Framework
#include <WiFi.h>         //? Connect WiFi
#include <PubSubClient.h> //? Client MQTT
#include <ArduinoJson.h>

//* Prototype Function
void callback(char *topic, byte *payload, unsigned int length);
void mqttReconnect();
void mqttSetup();
void mqttTestPub();
void pubJSON();
void wifiSetup();

//* WIFI STA Details
#define WiFi_STA_USERNAME "Pipek_PC"       //? WiFi UserName
#define WiFi_STA_PASSWORD "12345678" //? WiFi Password

//* MQTT Server Details
#define MQTT_SERVER "soldier.cloudmqtt.com" //?Server URLS
#define MQTT_PORT 16880                     //? Server Port
#define MQTT_USERNAME "zuzu2307"               //? MQTT UserName
#define MQTT_PASSWORD "police1234"            //? MQTT Password
#define MQTT_NAME "ESP32_1"                 //?Topic Name

//* Params
#define Intervals 500 //? Global Interval Time
unsigned long long previousMillis_WiFi = 0,
                   previousMillis_MQTT = 0,
                   previousMillis_PUB = 0;
const char *title, *status;
int duration;
//* SUB Topic
#define MQTT_SUB_TEST "/NODE_RED/Test" //? Test MQTT Only
#define MQTT_SUB_JSON "/NODE_RED/JSON" //? JSON Format
#define MQTT_PUB_JSON "/ESP32_1/JSON_PUB"
WiFiClient client;         //? Create TCP Connection
PubSubClient mqtt(client); //? Create Mqtt over WiFiClient

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  wifiSetup();
  mqttSetup();
}

void loop()
{
  // put your main code here, to run repeatedly:
  if (mqtt.connected() == false)
  {
    mqttReconnect();
  }
  else
  {
    mqtt.loop();
   // pubJSON();
  }
}

void wifiSetup()
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WiFi_STA_USERNAME);

  //* WiFi Connection
  WiFi.mode(WIFI_STA);
  WiFi.begin(WiFi_STA_USERNAME, WiFi_STA_PASSWORD);

  Serial.print("Status: [");
  while (WiFi.status() != WL_CONNECTED)
  {
    //* Time Loop Uss Millis
    unsigned long currentMillis = millis(); //? Store Current time
    if (currentMillis - previousMillis_WiFi > Intervals)
    {
      previousMillis_WiFi = currentMillis; //? Save Current time
      Serial.print("=");
    }
  }
  Serial.println("] 100%");

  Serial.println("--- WiFi Connected ---");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

void mqttSetup()
{
  mqtt.setServer(MQTT_SERVER, MQTT_PORT); //? Set Destination Server
  mqtt.setCallback(callback);             //? Set Callback Function
  Serial.println("--- MQTT Connected ---");
}

void callback(char *topic, byte *payload, unsigned int length)
{
  payload[length] = '\0';
  String topic_str = topic, payload_str = (char *)payload;
  Serial.println("[" + topic_str + "]: " + payload_str);
  if (topic_str == MQTT_SUB_JSON)
  {
    Serial.println("--- Start JSON Process ---");
    const size_t capacity = JSON_OBJECT_SIZE(3); //? Object Size
    DynamicJsonDocument doc(capacity);           //? Declare variable for store json

    deserializeJson(doc, payload, length); //? deserialize JSON

    title = doc["title"];       //? Store key title to tittle
    duration = doc["duration"]; //? Store key duration to duration
    status = doc["status"];     //? Store key status to status

    Serial.println("title : " + String(title) + " | " +
                   "durations : " + String(duration) + " | " +
                   "status : " + String(status)); //?Print Output

    Serial.println("--- END JSON Process ---");
  }
}
void mqttReconnect()
{
  Serial.println("MQTT Connecting ");
  Serial.print("Status: [");
  while (mqtt.connected() == false)
  {
    mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD); //? Reconnect To Server

    //* Time Loop
    unsigned long currentMillis = millis(); //? Store Current time
    if (currentMillis - previousMillis_MQTT > Intervals)
    {
      previousMillis_MQTT = currentMillis; //? Save Current time
      Serial.print("=");
    }
  }
  Serial.println("] 100%");
  Serial.println("--- MQTT Reconnected ---");

  if (mqtt.connect(MQTT_NAME, MQTT_USERNAME, MQTT_PASSWORD))
  {
    Serial.println("connected : " + String(MQTT_SUB_TEST));
    mqtt.subscribe(MQTT_SUB_TEST);
    Serial.println("connected : " + String(MQTT_SUB_JSON));
    mqtt.subscribe(MQTT_SUB_JSON);
  }
  else
  {
    Serial.println("--- failed ---");
  }
}

void mqttTestPub()
{
  unsigned long currentMillis = millis(); //? Store Current time
  if (currentMillis - previousMillis_PUB > Intervals)
  {
    previousMillis_PUB = currentMillis; //? Save Current time

    mqtt.publish(MQTT_SUB_TEST, "Hello From M5GO");
  }
}

void pubJSON()
{
  unsigned long currentMillis = millis(); //? Store Current time
  if (currentMillis - previousMillis_PUB > 500)
  {
    previousMillis_PUB = currentMillis; //? Save Current time
    const size_t capacity = JSON_OBJECT_SIZE(3);
    DynamicJsonDocument doc(capacity);
    char buffer[512];

    doc["title"] = "test1";
    doc["duration"] = 10;
    doc["status"] = "Todo";

    serializeJson(doc, buffer);

    mqtt.publish(MQTT_PUB_JSON, buffer);
  }
}*/

///////////////////////////////////////////////////////////////////////////////////

#include <M5Stack.h>

// the setup routine runs once when M5Stack starts up
void setup() {
  
  // initialize the M5Stack object
  M5.begin();

  // Lcd display
  //M5.Lcd.fillScreen(WHITE);
  

  // text print
  M5.Lcd.fillScreen(BLUE);
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3.9);
  M5.Lcd.printf("Display Test!");

  
  // draw graphic
  /*delay(1000);
  M5.Lcd.drawRect(100, 100, 50, 50, BLUE);
  delay(1000);
  M5.Lcd.fillRect(100, 100, 50, 50, BLUE);
  delay(1000);
  M5.Lcd.drawCircle(100, 100, 50, RED);
  delay(1000);
  M5.Lcd.fillCircle(100, 100, 50, RED);
  delay(1000);
  M5.Lcd.drawTriangle(30, 30, 180, 100, 80, 150, YELLOW);
  delay(1000);
  M5.Lcd.fillTriangle(30, 30, 180, 100, 80, 150, YELLOW);*/

}

// the loop routine runs over and over again forever
int scstate = 0;
void loop(){

  //rand draw 
 // M5.Lcd.fillTriangle(random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(M5.Lcd.width()-1), random(M5.Lcd.height()-1), random(0xfffe));
if(M5.BtnA.wasPressed())
  {
    if(scstate == 0)
    {
      scstate++;
      M5.Lcd.fillScreen(BLACK);
    }
    else
    {
      scstate = 0;
      M5.Lcd.fillScreen(BLUE);
      M5.Lcd.setCursor(10, 10);
      M5.Lcd.setTextColor(WHITE);
      M5.Lcd.setTextSize(3.9);
      M5.Lcd.printf("Display Test!");
    }
    
  }

  M5.update();
}

