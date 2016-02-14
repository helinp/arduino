/* -------------------------------------------------------------------------
   Humidity activated fan system
   
   https://github.com/helinp
   
   by Pierre Helin
 
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

---------------------------------------------------------------------------*/

 
// humidity threshold to power on the fan 
const float fan_humidity = 70.00;

// time between probes (ms)
const int milli_wait = 7000;

// number of probes before activating fan
const int n_probes = 2;

// define pins
#define DHTPIN 2 
#define RELPIN 4 

/* No need to modify below this line */

// Setup the Low power functions library (by https://github.com/jcw/jeelib)
#include <JeeLib.h>  
ISR(WDT_vect) { Sleepy::watchdogEvent(); } 

// Initialize DHT22 sensor for normal 16mhz Arduino
#include <DHT.h>
DHT dht(DHTPIN, DHT22);

// declare globals variables
int over_level, below_level = 0;

void setup() {
  
  // debug purpose only
  // Serial.begin(9600); 
  // Serial.println("DHTxx test!");
   
  dht.begin();
  
  pinMode(RELPIN, OUTPUT);
  
  // test relay
  digitalWrite(RELPIN, HIGH);
  Sleepy::loseSomeTime(5000);
  digitalWrite(RELPIN, LOW);
  
  // test DHT, runs fan if OK
  if (dht.readHumidity() != 0.00) 
  {
    digitalWrite(RELPIN, HIGH);
    Sleepy::loseSomeTime(5000);
    digitalWrite(RELPIN, LOW);
  }
}

void loop() {
  
  // delay(5000);
  Sleepy::loseSomeTime(milli_wait);
   
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
