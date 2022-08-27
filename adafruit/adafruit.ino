
#define AIO_USERNAME  "NITIAN_kriti"
#define AIO_KEY       "aio_fgwP20toAJE3szPOKKaDkDTVjdCJ"

#define WLAN_SSID       "ICO"
#define WLAN_PASS       "9876543210"


#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

/*#define WLAN_SSID       "...your SSID..."
#define WLAN_PASS       "...your password..."

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'potValue' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Publish potValue = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/potValue");

// Setup a feed called 'ledBrightness' for subscribing to changes.
Adafruit_MQTT_Subscribe LEDbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/LEDbutton");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

uint8_t ledPin = D6;
int LED1 = 2;      // Assign LED1 to pin GPIO2

int LED2 = 16;     // Assign LED1 to pin GPIO16
uint16_t potAdcValue = 0;
uint16_t ledBrightValue = 0;

void setup() {
  pinMode(LED1, OUTPUT);

  pinMode(LED2, OUTPUT);
  Serial.begin(9600);
  delay(10);

  Serial.println(F("Adafruit MQTT demo"));

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
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for ledBrightness feed.
  mqtt.subscribe(&LEDbutton);
}

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(200))) {
    if (subscription == &LEDbutton) {
      Serial.print(F("Got LED command : "));
//      Serial.println(LEDbutton.lastread);
      ledBrightValue = atoi((char *)LEDbutton.lastread);
      if(ledBrightValue==1)
      {
          digitalWrite(LED1, LOW);     // turn the LED off

  digitalWrite(LED2, HIGH);
      }
      else if(ledBrightValue==0)
      {
        digitalWrite(LED1, HIGH);  // turn the LED on

  digitalWrite(LED2, LOW);
      }
      Serial.println(ledBrightValue);
      analogWrite(ledPin, ledBrightValue);
    }
  }

  // Now we can publish stuff!
  uint16_t AdcValue = analogRead(A0);
  if((AdcValue > (potAdcValue + 7)) || (AdcValue < (potAdcValue - 7))){
    potAdcValue = AdcValue;
    Serial.print(F("Sending pot val "));
    Serial.print(potAdcValue);
    Serial.print("...");
    if (! potValue.publish(potAdcValue)) {
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("OK!"));
    }
  }
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
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
