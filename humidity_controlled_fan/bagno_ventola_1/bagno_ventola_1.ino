/* ------------------------------------
   Humidity activated fan system
   
   https://github.com/helinp
   
   by Pierre Helin
 
 ------------------------------------*/
 
// min humidity to power on the fan 
const float fan_humidity = 70.00;

// time between probes (ms)
const int seconds_wait = 5000;

// number of successful probes before activating fan
int n_probes = 3;

// define pins
#define DHTPIN 2 
#define RELPIN 4 

// Setup the Low power functions library (by https://github.com/jcw/jeelib)
#include <JeeLib.h>  
ISR(WDT_vect) { Sleepy::watchdogEvent(); } 

// Initialize DHT22 sensor for normal 16mhz Arduino
#include <DHT.h>
DHT dht(DHTPIN, DHT22);

// declare globals variables
int over_level, below_level = 0;

void blinkLed() {

  int led = 13;
  int n_blinks = 3;
  
  pinMode(led, OUTPUT);
   
  while(n_blinks--) {
    digitalWrite(led, HIGH);   
    delay(100);               
    digitalWrite(led, LOW);   
    delay(100);               
  }
}

void setup() {
  
  // debug purpose only
  // Serial.begin(9600); 
  // Serial.println("DHTxx test!");
   
  dht.begin();
  
  pinMode(RELPIN, OUTPUT);
  digitalWrite(RELPIN, HIGH);
  
  // test DHT
  if (dht.readHumidity() != 0.00) blinkLed();
}

void loop() {
  
  // delay(5000);
  Sleepy::loseSomeTime(seconds_wait);
   
  // read humidity
  float humidity = dht.readHumidity();
  
  // debug purpose only
  // Serial.println(humidity);
  // Serial.println(over_level);
  
  if (humidity > fan_humidity) over_level++;
  else below_level++;
    
  if (over_level > n_probes) {
    digitalWrite(RELPIN, LOW);
    over_level = n_probes;
    below_level = 0;
  }
  else if (below_level > n_probes) {
    digitalWrite(RELPIN, HIGH);
    below_level = n_probes;
    over_level = 0;
  }
}
