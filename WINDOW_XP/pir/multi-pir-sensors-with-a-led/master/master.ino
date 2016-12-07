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
Adafruit_NeoPixel strip = Adafruit_NeoPixel(117, PIN, NEO_GRB + NEO_KHZ800);
// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

int calibrationTime = 10; 

unsigned long timer;
unsigned long interval = 5000;  
unsigned long previousMillis = 0;

//boolean lockLow = true;
//boolean takeLowTime;  

int downUp = 0;

int pirPin = 11;    //the digital pin connected to the PIR sensor's output
int pirPin2 = 12;    //the digital pin connected to the PIR sensor's output
int ledPin = 13;

void setup(){

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
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
    
     if(digitalRead(pirPin) == HIGH && downUp != 2){ // top
       Serial.println("SAW YOU FROM TOP!");
       timer = millis();
       downUp = 2;
       digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
       delay(2000);
       digitalWrite(ledPin,LOW);
       delay(2000);                
         //makes sure we wait for a transition to LOW before any further output is made:
        Serial.println("---");
        Serial.print ("detected TOP ...");                // Helpful debug message         
        Serial.print("motion detected at ");
        Serial.print(millis()/1000);
        Serial.println(" sec"); 
        Serial.println("wait for 10 secs"); 
        delay(10000);
      } 

     if(digitalRead(pirPin2) == HIGH && downUp != 1){ // bottom
      Serial.println("SAW YOU FROM BOTTOM!");
       timer = millis();
       downUp = 1;
       for (int x=0; x < 10; x++) {
         digitalWrite(ledPin, HIGH);   //the led visualizes the sensors output pin state
         delay(100);
         digitalWrite(ledPin,LOW);
         delay(100);
         }                
         //makes sure we wait for a transition to LOW before any further output is made:
        Serial.println("---");
        Serial.print ("detected BOTTOM ...");                // Helpful debug message      
        Serial.print("motion detected at ");
        Serial.print(millis()/1000);
        Serial.println(" sec");
        Serial.println("wait for 10 secs"); 
        delay(10000);
      }
       //if the sensor is low for more than the given interval, 
       //we assume that no more motion is going to happen
       if ( timer - previousMillis > interval){  
           //makes sure this block of code is only executed again after 
           //a new motion sequence has been detected
        if (downUp == 1){
           Serial.println("motion ended at downUp 1 (BOTTOM)");      //output
//           downUp = 1;
        }
        if (downUp == 2){
           Serial.println("motion ended at downUp 2 (TOP)");      //output
//           downUp = 2;
        }
           downUp = 0;
           previousMillis = millis();                      
           Serial.print("motion ended at ");      //output
           Serial.print((millis() - interval)/1000);
           Serial.println(" sec ");
           delay(1000);
           }
       
  } // end loop
