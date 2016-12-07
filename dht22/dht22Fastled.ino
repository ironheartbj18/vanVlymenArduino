#include <LiquidCrystal.h>
#include "DHT.h"
#include <FastLED.h>

#define DHTPIN 8     // what digital pin we're connected to

int num;
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Display pins
LiquidCrystal lcd (12, 11, 5, 4, 3, 2);

// we need to define how many LEDs (pixels)
#define NUM_LEDS 7
#define DATA_PIN 7
CRGB leds[NUM_LEDS];

// Array symbol degree
byte level[8] = {
 B00001100,
 B00010010,
 B00010010,
 B00001100,
 B00000000,
 B00000000,
 B00000000,
 B00000000,
 };
 
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

void setup() {
   // Initialize the display
  lcd.begin (16, 2);
 // Create the custom character with the symbol of the degree
  lcd.createChar (1, level);
  Serial.begin(9600);
  Serial.println("Waiting for data...");
  // Starts DHT sensor
  dht.begin();
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(64);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

 // Display the temperature in the serial monitor and display
 Serial.print ("Temperature: ");
 Serial.print(f);
 Serial.println(" *F\t");
 lcd.setCursor (0,0);
 lcd.print ("Temp: ");
 lcd.print (f);
 lcd.print(" F");
 
 // Show the moisture in the serial monitor and display
 Serial.print ("Humidity: ");
 Serial.print (h);
 Serial.println (" %");
 // Array symbol degree
 lcd.write(1);
 lcd.setCursor (0,1);
 lcd.print ("Humi.:");
 lcd.print (h);
 lcd.print (" %");

 //it's cold here!
  if (f > 50 && f < 55){
    Serial.println("Option 1");
    //Set LED colors, black is off
//    fill_solid( &(leds[0]), NUM_LEDS, CRGB::Blue);
      leds[0] = 0x0001FE; //blue
      leds[1] = CRGB(0,0,0);
      leds[2] = CRGB(0,0,0);
      leds[3] = CRGB(0,0,0);
      leds[4] = CRGB(0,0,0);
      leds[5] = CRGB(0,0,0);
      leds[6] = CRGB(0,0,0);
      FastLED.show();
  }else if (f > 55 && f < 60.8) {
    Serial.println("Option 2");
    //Set LED colors, black is off
//    fill_solid( &(leds[0]), NUM_LEDS, CRGB::Red);
      leds[0] = 0x0001FE; //blue
      leds[1] = 0x00cc33;
      leds[2] = CRGB(0,0,0);
      leds[3] = CRGB(0,0,0);
      leds[4] = CRGB(0,0,0);
      leds[5] = CRGB(0,0,0);
      leds[6] = CRGB(0,0,0);
      FastLED.show();
  } else if (f > 60.8 && f < 62.6){
    // option 3
    Serial.println("Option 3");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = CRGB(0,0,0);
    leds[4] = CRGB(0,0,0);
    leds[5] = CRGB(0,0,0);
    leds[6] = CRGB(0,0,0);
    FastLED.show();
  }else if (f > 62.6 && f < 65.2) {
    // option 4
    Serial.println("Option 4");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = CRGB::Black;
    leds[5] = CRGB(0,0,0);
    leds[6] = CRGB(0,0,0);
    FastLED.show();
  }else if (f > 65.2 && f < 68){
    // option 5
    Serial.println("Option 5");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = 0x66ff00;
    leds[5] = 0x000000;
    leds[6] = 0x000000;
    FastLED.show();
  } else if (f > 68 && f < 70.4){
    // option 6
    Serial.println("Option 6");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = 0x66ff00;
    leds[5] = 0xffff00;
    leds[6] = 0x000000;
    FastLED.show();
  } else if (f > 70.4 && f < 72.8) {
    // option 7
    Serial.println("Option 7");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = 0x66ff00;
    leds[5] = 0xffff00;
    leds[6] = 0xffcc00;
    FastLED.show();
  } else if(f > 72.8 && f < 79.6){ // 75.2
    // option 8
    Serial.println("Option 8");
    #define NUM_LEDS 3
     RGBLoopFadeIN(); 
   
  } else if ( f > 79.6 && f < 79.8){ // 75.2 && 77.6
    // option 9
    Serial.println("Option 9");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = 0xffff00;
    leds[5] = 0xffcc00;
    leds[6] = 0xff9900;
    FastLED.show();
  } else if (f > 79.8 && f < 80){ // 77.6
    // option 10
    Serial.println("Option 10");
    //Set LED colors, black is off
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x00cc33;
    leds[2] = 0x00ff00;
    leds[3] = 0x33ff00;
    leds[4] = 0x66ff00;
    leds[5] = 0xffff00;
    leds[6] = 0xffcc00;
    FastLED.show();
  }

  if(f > 80){
    turnOnAllRed();
  }
}

 void turnOnAllRed() {
  leds[0] = CRGB::Red;
  leds[1] = CRGB::Red;
  leds[2] = CRGB::Red;
  leds[3] = CRGB::Red;
  leds[4] = CRGB::Red;
  leds[5] = CRGB::Red;
  leds[6] = CRGB::Red;
  FastLED.show(); //turn on the LEDs 
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue); 
  }
  showStrip();
}

void RGBLoopFadeIN(){
    // Fade IN
//  int num;
  Serial.print(num);
  if(num == 0){
    for(int k = num; k < 256; k++) { 
          setAll(k,0,0);
        }
        showStrip();
        delay(50);
        num = 255;
    }
  if(num == 255){
    Serial.print(num);
    setAll(255,0,0);
    num = 255;
  }
    
}

void RGBLoopFadeOUT(){
    // Fade OUT
  for(int j = 3; j > 0; j--){
    for(int k = 255; k >= 0; k--) { 
      switch(j) { 
        case 0: setAll(k,0,0); break;
        case 1: setAll(0,k,0); break;
        case 2: setAll(0,0,k); break;
      }
      showStrip();
      delay(3);
    }
  }
}

