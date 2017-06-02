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
#define NUM_LEDS 15
#define DATA_PIN 7
CRGB leds[NUM_LEDS];


// Array symbol degree (custom display)
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

byte water[8] = {
 B00000100,
 B00000100,
 B00001110,
 B00011111,
 B00011111,
 B00001110,
 B00000000,
 B00000000,
 };

 byte water2[8] = {
 B00000100,
 B00000100,
 B00001110,
 B00011111,
 B00011111,
 B00011111,
 B00011111,
 B00001110,
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
  lcd.createChar (2, water);
  lcd.createChar (3, water2);
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
 lcd.setCursor (0,0); // where LCD starts at
 lcd.print ("Temp: ");
 lcd.print (f);
 lcd.print(" F");
 lcd.write(1);  // Array symbol degree (draw the degree)
 
 // Show the moisture in the serial monitor and display
 lcd.setCursor (0,1);
 Serial.print ("Humidity: ");
 Serial.print (h);
 Serial.println (" %");
 lcd.print ("Humi: ");
 lcd.print (h);
 lcd.print (" %");
 lcd.setCursor(13,1);
 lcd.write(2);
 delay(1500);
 lcd.setCursor(13,1);
 lcd.write(3);
 delay(500);

 // all temperature numbers are fahrenheit 
 //it's cold here!
  if (f > 0 && f < 30){
    // option 1
    Serial.println("Option 1)");
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x0001FE; //blue
    leds[2] = 0x0001FE; //blue
    leds[3] = 0x0001FE; //blue
    leds[4] = 0x0001FE; //blue
    leds[5] = 0x0001FE; //blue
    leds[6] = 0x0001FE; //blue
    leds[7] = 0x0001FE; //blue
    leds[8] = 0x0001FE; //blue
    leds[9] = 0x0001FE; //blue
    leds[10] = 0x0001FE; //blue
    leds[11] = 0x0001FE; //blue
    leds[12] = 0x0001FE; //blue
    leds[13] = 0x0001FE; //blue
    leds[14] = 0x0001FE; //blue
    FastLED.show();
  }else if (f > 35.1 && f < 40) {
    // option 2
    Serial.println("Option 2");
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x0001FE; //blue
    leds[2] = 0x0001FE; //blue
    leds[3] = 0x0001FE; //blue
    leds[4] = 0x0001FE; //blue
    leds[5] = 0x0001FE; //blue
    leds[6] = 0x0001FE; //blue
    leds[7] = 0x0001FE; //blue
    leds[8] = 0x0001FE; //blue
    leds[9] = 0x0001FE; //blue
    leds[10] = 0x0001FE; //blue
    leds[11] = 0x0001FE; //blue
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  } else if (f > 40.1 && f < 45){
    // option 3
    Serial.println("Option 3");
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x0001FE; //blue
    leds[2] = 0x0001FE; //blue
    leds[3] = 0x0001FE; //blue
    leds[4] = 0x0001FE; //blue
    leds[5] = 0x0001FE; //blue
    leds[6] = 0x0001FE; //blue
    leds[7] = 0x0001FE; //blue
    leds[8] = 0x0001FE; //blue
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  }else if (f > 45.1 && f < 50) {
    // option 4
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x0001FE; //blue
    leds[2] = 0x0001FE; //blue
    leds[3] = 0x0001FE; //blue
    leds[4] = 0x0001FE; //blue
    leds[5] = 0x0001FE; //blue
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  } else if (f > 50.1 && f < 55){
    // option 5
    Serial.println("Option 5");
    leds[0] = 0x0001FE; //blue
    leds[1] = 0x0001FE; //blue
    leds[2] = 0x0001FE; //blue
    leds[3] = CRGB(0,0,0);
    leds[4] = CRGB(0,0,0);
    leds[5] = CRGB(0,0,0);
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  } else if (f > 55.1 && f < 60){
    // option 6
    Serial.println("Option 6");
    leds[0] = 0x01FE00;    //green
    leds[1] = 0x01FE00;    //green
    leds[2] = 0x01FE00;    //green
    leds[3] = CRGB(0,0,0);
    leds[4] = CRGB(0,0,0);
    leds[5] = CRGB(0,0,0);
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);

    FastLED.show();
  } else if (f > 60.1 && f < 65){
    //option 7
    Serial.println("Option 7");
    leds[0] = 0x01FE00;    //green
    leds[1] = 0x01FE00;    //green
    leds[2] = 0x01FE00;    //green
    leds[3] = 0x01FE00;    //green
    leds[4] = 0x01FE00;    //green
    leds[5] = 0x01FE00;    //green
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  } else if (f > 65.1 && f < 70){
    //option 8
    Serial.println("Option 8");
    leds[0] = 0x01FE00;    //green
    leds[1] = 0x01FE00;    //green
    leds[2] = 0x01FE00;    //green
    leds[3] = 0x01FE00;    //green
    leds[4] = 0x01FE00;    //green
    leds[5] = 0x01FE00;    //green
    leds[6] = 0x01FE00;    //green
    leds[7] = 0x01FE00;    //green
    leds[8] = 0x01FE00;    //green
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);  
    FastLED.show();
  } else if (f > 70.1 && f < 75){
    //option 9
    Serial.println("Option 9");
    leds[0] = 0x01FE00;    //green
    leds[1] = 0x01FE00;    //green
    leds[2] = 0x01FE00;    //green
    leds[3] = 0x01FE00;    //green
    leds[4] = 0x01FE00;    //green
    leds[5] = 0x01FE00;    //green
    leds[6] = 0x01FE00;    //green
    leds[7] = 0x01FE00;    //green
    leds[8] = 0x01FE00;    //green
    leds[9] = 0x01FE00;    //green
    leds[10] = 0x01FE00;    //green
    leds[11] = 0x01FE00;    //green
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);
    FastLED.show();
  } else if (f > 75.1 && f < 80){
    //option 10
    Serial.println("Option 10");
    leds[0] = 0x01FE00;    //green
    leds[1] = 0x01FE00;    //green
    leds[2] = 0x01FE00;    //green
    leds[3] = 0x01FE00;    //green
    leds[4] = 0x01FE00;    //green
    leds[5] = 0x01FE00;    //green
    leds[6] = 0x01FE00;    //green
    leds[7] = 0x01FE00;    //green
    leds[8] = 0x01FE00;    //green
    leds[9] = 0x01FE00;    //green
    leds[10] = 0x01FE00;    //green
    leds[11] = 0x01FE00;    //green
    leds[12] = 0x01FE00;    //green
    leds[13] = 0x01FE00;    //green
    leds[14] = 0x01FE00;    //green
    FastLED.show();
  } else if (f > 80.1 && f < 85){
    //option 11
    Serial.println("Option 11");
    leds[0] = 0xFE0001;   //red
    leds[1] = 0xFE0001;   //red
    leds[2] = 0xFE0001;   //red
    leds[3] = CRGB(0,0,0);
    leds[4] = CRGB(0,0,0);
    leds[5] = CRGB(0,0,0);
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);  
    FastLED.show();
  } else if (f > 85.1 && f < 90){
    //option 12
    Serial.println("Option 12");
    leds[0] = 0xFE0001;   //red
    leds[1] = 0xFE0001;   //red
    leds[2] = 0xFE0001;   //red
    leds[3] = 0xFE0001;   //red
    leds[4] = 0xFE0001;   //red
    leds[5] = 0xFE0001;   //red
    leds[6] = CRGB(0,0,0);
    leds[7] = CRGB(0,0,0);
    leds[8] = CRGB(0,0,0);
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);    
    FastLED.show();
  } else if (f > 90.1 && f < 95){
    //option 13
    Serial.println("Option 13");
    leds[0] = 0xFE0001;   //red
    leds[1] = 0xFE0001;   //red
    leds[2] = 0xFE0001;   //red
    leds[3] = 0xFE0001;   //red
    leds[4] = 0xFE0001;   //red
    leds[5] = 0xFE0001;   //red
    leds[6] = 0xFE0001;   //red
    leds[7] = 0xFE0001;   //red
    leds[8] = 0xFE0001;   //red
    leds[9] = CRGB(0,0,0);
    leds[10] = CRGB(0,0,0);
    leds[11] = CRGB(0,0,0);
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);    
    FastLED.show();
  } else if (f > 95.1 && f < 100){
    //option 14
    Serial.println("Option 14");
    leds[0] = 0xFE0001;   //red
    leds[1] = 0xFE0001;   //red
    leds[2] = 0xFE0001;   //red
    leds[3] = 0xFE0001;   //red
    leds[4] = 0xFE0001;   //red
    leds[5] = 0xFE0001;   //red
    leds[6] = 0xFE0001;   //red
    leds[7] = 0xFE0001;   //red
    leds[8] = 0xFE0001;   //red
    leds[9] = 0xFE0001;   //red
    leds[10] = 0xFE0001;   //red
    leds[11] = 0xFE0001;   //red
    leds[12] = CRGB(0,0,0);
    leds[13] = CRGB(0,0,0);
    leds[14] = CRGB(0,0,0);   
    FastLED.show();
  } else if (f > 100){
    //option 15
    Serial.println("Option 15");
    leds[0] = 0xFE0001;   //red
    leds[1] = 0xFE0001;   //red
    leds[2] = 0xFE0001;   //red
    leds[3] = 0xFE0001;   //red
    leds[4] = 0xFE0001;   //red
    leds[5] = 0xFE0001;   //red
    leds[6] = 0xFE0001;   //red
    leds[7] = 0xFE0001;   //red
    leds[8] = 0xFE0001;   //red
    leds[9] = 0xFE0001;   //red
    leds[10] = 0xFE0001;   //red
    leds[11] = 0xFE0001;   //red
    leds[12] = 0xFE0001;   //red
    leds[13] = 0xFE0001;   //red
    leds[14] = 0xFE0001;   //red
    FastLED.show();
  }
}  
  

