// two pir with WS2812 Master
// try with ws2812
// from top wait till walk down hit second pir do something...
//
#include <Adafruit_NeoPixel.h>
// Thanks to the Neopxel Library by Adafruit
// branch1
#define PIN 6
// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(149, PIN, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int calibrationTime = 10; 
unsigned long timer;
unsigned long interval = 5000;  
unsigned long previousMillis = 0;

int downUp = 0;
int sawPir = 0;

int pirPin = 11;    //the digital pin connected to the PIR sensor's output
int pirPin2 = 12;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;
int ledPin2 = 10;

void setup(){
  // strip.begin();
  // strip.show(); // Initialize all pixels to 'off'
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(pirPin, INPUT);
  digitalWrite(pirPin, LOW);
  pinMode(pirPin2, INPUT);
  digitalWrite(pirPin2, LOW);

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor please wait for 10 secs ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
  }

//////////////////////////////LOOP

void loop(){
    previousMillis = millis(); 

      if(digitalRead(pirPin) == LOW){
        Serial.println("top pir is LOW");
      }

      if(digitalRead(pirPin) == HIGH && downUp != 2){ // top
       Serial.println("SAW YOU FROM TOP!");
      // timer = millis();
       sawPir = 1;
     //colourWipeDown(strip.Color(50, 50, 30), 40); 
       topdown();
       for (int x=0; x < 10; x++) {
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       delay(100);
       digitalWrite(ledPin,LOW);
       delay(100);
       }                
         //makes sure we wait for a transition to LOW before any further output is made:
        // Serial.println("---");
        // Serial.print ("detected TOP ...");                // Helpful debug message         
        // Serial.print("motion detected at ");
        // Serial.print(millis()/1000);
        // Serial.println(" sec"); 
        // Serial.println("wait for 10 secs"); 
//        delay(10000);
      } 

    if(digitalRead(pirPin2) == HIGH && sawPir == 1){
      Serial.println("GETTING LOWER");
      timer = millis();
      downUp = 2;
//      colourWipeDown(strip.Color(0, 0, 0), 30); 
      analogWrite(ledPin2, HIGH);
      delay(2000);
      for (int x=255; x >= 0; x--) {
       analogWrite(ledPin2,x);
       delay(50);
      }
    }

    if(digitalRead(pirPin2) == HIGH && downUp != 1){ // bottom
        Serial.println("SAW YOU FROM BOTTOM!");
        timer = millis();
        downUp = 1;
        sawPir = 2;
        digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
        delay(2000);
        digitalWrite(ledPin,LOW);
        delay(100);             
        //makes sure we wait for a transition to LOW before any further output is made:
        // Serial.println("---");
        // Serial.print ("detected BOTTOM ...");     
        // Serial.print("motion detected at ");
        // Serial.print(millis()/1000);
        // Serial.println(" sec");
        // Serial.println("wait for 10 secs"); 
        // delay(10000);
      } 
      
       //if the sensor is low or more than the given interval, 
       //we assume that no more motion is going to happen
      if ( timer - previousMillis > interval){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
        if (downUp == 1){
           Serial.println("motion ended at downUp 1 (BOTTOM)");      //output
        }
        if (downUp == 2){
           Serial.println("motion ended at downUp 2 (TOP)");      //output
           // colourWipeDown(strip.Color(0, 0, 0), 30);   // Warm White 
        }
        downUp = 0; // reset
        sawPir = 0; // reset                    
        Serial.print("motion ended at ");      //output
        Serial.print((millis() - interval)/1000);
        Serial.println(" sec ");
        delay(1000);
      }
  } // end loop

 void topdown() {
    Serial.println("SAW YOU FROM TOP!");            // Helpful debug message
    colourWipeDown(strip.Color(50, 50, 30), 40);    // Warm White
    for(int i=0; i<3; i++) {                        // Helpful debug indication flashes led on Arduino board twice
      digitalWrite(ledPin,HIGH);
      delay(200);
      digitalWrite(ledPin,LOW);
      delay(200);
    }
 }

// Fill the dots one after the other with a color
void colourWipeDown(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}




