//const char* serverName = "http://maker.ifttt.com/trigger/test_event/with/key/nAZjOphL3d-ZO4N3k64-1A7gTlNSrxMJdmqy3tC";
 
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define Relay1            D1

#define WLAN_SSID       "Legend"             // Your SSID
#define WLAN_PASS       "123456789"        // Your password

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "prikshit_anthal"            // Replace it with your username
#define AIO_KEY         "aio_ikNJ80P2A1c6lhj1kBxh5DVZFu6H"   // Replace with your Project Auth Key

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/


// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe Light1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME"/feeds/Ledtoggle"); // FeedName

void MQTT_connect();

  int LED1 = 2;      // Assign LED1 to pin GPIO2

int LED2 = 16;     // Assign LED1 to pin GPIO16

void setup() {
  Serial.begin(115200);



  pinMode(LED1, OUTPUT);

  pinMode(LED2, OUTPUT);
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&Light1);
}

void loop() {
 
  MQTT_connect();
  
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &Light1) {
      Serial.print(F("Got: "));
      Serial.println((char *)Light1.lastread);
      int ledBrightValue = atoi((char *)Light1.lastread);
       if(ledBrightValue==1)
      {
          digitalWrite(LED1, LOW);     // turn the LED off

  digitalWrite(LED2, HIGH);
      }
      else if(ledBrightValue==0)
      {f
        digitalWrite(LED1, HIGH);  // turn the LED on

  digitalWrite(LED2, LOW);
      }
      Serial.println(ledBrightValue);
//      digitalWrite(Relay1, !(Light1_State));
      
    }
  }
}

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);  // wait 5 seconds
    retries--;
    if (retries == 0) {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
  
}
