/* ------------------------------------
   Minimalist humidity and temperature reader

   Only need Arduino, DHT and breadboard
   Read values counting led blinks

   Ex. 2 blinks, 0 blink, 2 sec delay, 5 blinks, 5 blinks, 4 seconds delay
   => 20°C and 55% humidity
   
   https://github.com/helinp
   
   by Pierre Helin
 
 ------------------------------------*/

// DHT 22 setup

#define DHTPIN 2
#define DHTTYPE DHT22

#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  // start DHT
  dht.begin();
  
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  delay(2000);
}

void loop() 
{
  // read data
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  decToLed (13, (int) h);
  delay (2000);
  decToLed (13, (int) t);
  delay (4000);
}

//  Decimal to led blink function
void decToLed (int pin, int n)
{
  
  if (n < 100)
  {
    int first_digit = n / 10;
    int secon_digit = n % 10;
    
    while (first_digit--)
    {
	  
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
      delay(250);  
    }
    
    delay (1000);
    
    while (secon_digit--)
    {
	  
      digitalWrite(pin, HIGH);
      delay(100);
      digitalWrite(pin, LOW);
      delay(250);  
    }
  }
  else
  {
      digitalWrite(pin, HIGH);
      delay(1000);
      digitalWrite(pin, LOW);
      delay(250); 
  }
}
