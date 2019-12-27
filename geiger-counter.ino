#include <SPI.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#include <Ethernet2.h>
#include <EthernetClient.h>
//#include <Dns.h>
#include <Dhcp.h>

/************************* Ethernet Client Setup *****************************/
byte mac[] = {0xDE, 0xAD, 0xDE, 0xAD, 0xDE, 0xAD};

//Uncomment the following, and set to a valid ip if you don't have dhcp available.
//IPAddress iotIP (192, 168, 5, 225);
//Uncomment the following, and set to your preference if you don't have automatic dns.
//IPAddress dnsIP (8, 8, 8, 8);
//If you uncommented either of the above lines, make sure to change "Ethernet.begin(mac)" to "Ethernet.begin(mac, iotIP)" or "Ethernet.begin(mac, iotIP, dnsIP)"


/************************* Geiger Setup *********************************/
#define LOG_PERIOD 15000  //Logging period in milliseconds, recommended value 15000-60000.
#define MAX_PERIOD 60000  //Maximum logging period without modifying this sketch

unsigned long counts;     //variable for GM Tube events
unsigned long cpm;        //variable for CPM
unsigned int multiplier;  //variable for calculation CPM in this sketch
unsigned long previousMillis;  //variable for time measurement
int cold=1;               //variable for indicating cold start/reboot



/************************* MQTT Setup *********************************/

#define MQTT_SERVER      "MQTT SERVER IP"
#define MQTT_SERVERPORT  1883
#define MQTT_USERNAME    "user"
#define MQTT_KEY         "pass"


/************ Global State (you don't need to change this!) ******************/

//Set up the ethernet client
EthernetClient client;

Adafruit_MQTT_Client mqtt(&client, MQTT_SERVER, MQTT_SERVERPORT, MQTT_USERNAME, MQTT_KEY);

#define halt(s) { Serial.println(F( s )); while(1);  }


/****************************** Topics ***************************************/


Adafruit_MQTT_Publish cpmtopic = Adafruit_MQTT_Publish(&mqtt, "nuclear/count");
Adafruit_MQTT_Publish nuclearstatus = Adafruit_MQTT_Publish(&mqtt, "nuclear/message");



const byte interruptPin = 3;
/*************************** Sketch Code ************************************/
void tube_impulse(){       //subprocedure for capturing events from Geiger Kit
  counts++;
}

void setup() {
  Serial.begin(115200);
  
  counts = 0;
  cpm = 0;
  multiplier = MAX_PERIOD / LOG_PERIOD;      //calculating multiplier, depend on your log period

  
 
// Initialise the Client
//  Serial.print(F("\nInit the Client..."));
  Ethernet.begin(mac);
//    Ethernet.begin(mac, iotIP);
  delay(1000); //give the ethernet a second to initialize
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), tube_impulse, FALLING); //define external interrupts 


//  mqtt.subscribe(&onoffbutton);
}

uint32_t x=0;

void loop() {

  MQTT_connect();
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > LOG_PERIOD)
  {
    previousMillis = currentMillis;
    cpm = counts * multiplier;
    counts = 0;
    if (cold<1)
    {
       
       if (cpm>0)
       {
          Serial.println(cpm);
          if (! cpmtopic.publish(cpm)) {Serial.println(F("..Failed"));} 
       }
       else
       {
          Serial.print(F("\nNone "));
          nuclearstatus.publish("zero");
          cold=1;
       }

    }
    else
    {

      if (cpm>0)
      {
          nuclearstatus.publish("start");
          cold =0;
      }
      
      
   }
  }


  


  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
    cold =1;
  }


}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

//  Serial.print("Connecting to MQTT... ");

  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
//       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
  }
  counts = 0;
  cold=1;
  Serial.println("Connected");
  nuclearstatus.publish("connected");
}