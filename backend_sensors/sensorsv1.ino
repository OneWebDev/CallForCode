// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <math.h>
#include "DHT.h"
#ifdef __AVR__
  #include <avr/power.h>
#endif

int bright;

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            7
#define COPIN    A0

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      16



#define DHTPIN 8     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGBW + NEO_KHZ800);

int neodelayval = 500; // delay for half a second
int neodelayval2 = 20; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
//#if defined (__AVR_ATtiny85__)
//  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
//#endif
//  // End of trinket special code

  pixels.begin(); // This initializes the NeoPixel library.
  Serial.begin(115200);
  Serial.println("sensor demo!");
  bright = 0;
  dht.begin();
  
}


void showWhite(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0, 100)); // Moderately bright white color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}


void showBlue(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}

void showGreen(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,0,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}

void allWhite() {   //white out
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0, 20)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(10); // Delay for a period of time (in milliseconds).

  }
   for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(10); // Delay for a period of time (in milliseconds).

  }
}

void allGreen() {   //green out
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  delay(10); // Delay for a period of time (in milliseconds).
}


void allRed() {   //blue out
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  delay(10); // Delay for a period of time (in milliseconds).
}

void allBlue() {   //green out
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,150,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

  }
  delay(10); // Delay for a period of time (in milliseconds).
}


void blank() {   //blank out
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0, 0)); // Moderately bright green color.

    delay(5); // Delay for a period of time (in milliseconds).

  }
   pixels.show(); // This sends the updated pixel color to the hardware.
}


void showRed(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}

void showOrange(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(50,210,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}


void showYellow(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,200,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}

void showPurple(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}


void showTeal(int x) {   //x between 0 and 20
    for(int i=0;i<x;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(150,0,150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval2); // Delay for a period of time (in milliseconds).

  }
}

void testPixels() {
    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(200,0,0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval); // Delay for a period of time (in milliseconds).

  }

    for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,150, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(neodelayval); // Delay for a period of time (in milliseconds).

  }
}


void loop() {

//  allWhite();
//  showGreen(14);
//  blank();
//  showRed(10);
//  blank();
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
  delay(500);
  blank();
  //testPixels();
  bright = 1024 - analogRead(COPIN);
  float reading = floor(16.0 * (bright/1023.0)); 
//  Serial.print("light: ");
//  Serial.println(bright);
//  Serial.println(reading);
//  

  //show CO as orange
  showOrange(int(reading));
  delay(500);
  delay(2000);
  allWhite();

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

//  // Compute heat index in Fahrenheit (the default)
//  float hif = dht.computeHeatIndex(f, h);
//  // Compute heat index in Celsius (isFahreheit = false)
//  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print(F("Humidity: "));
//  Serial.println(h);

    // humidity
  reading = floor(16.0 * ((h)/100.0)); 
//  Serial.println(reading);
//  
  showBlue(int(reading));
  
  delay(500);
  delay(2000);
 
  allWhite();
  
//  Serial.print(F("%  Temperature: "));
//  Serial.println(f);
  // temperature
  reading = floor(16.0 * ((f+20.0)/240.0)); 
//  Serial.println(reading);
//  
  showRed(int(reading));
  
  delay(500);
  delay(2000);
 
  allWhite();

//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
  Serial.print("##:");
  Serial.print(bright);
  Serial.print(":");
  Serial.print(f);
  Serial.print(":");
  Serial.print(h);
  Serial.print(":");
  Serial.print(h*0.86);
  Serial.println(":##");

}









