// http://www.instructables.com/id/Hack-your-LED-Strip-with-a-Motion-Sensor-and-Timer/
// http://www.electronicslovers.com/2015/08/how-to-use-pir-sensor-with-arduino.html
// LEDStripMotionTimer.ino
// Controls power to an LED strip controller.
// The controller is turned on when motion is detected, and turned off after a period
// of inactivity.
// 
// 2 Feb 2014 - Brad Kartchner

// ATTINY85 Pinout
//  _____   ________
//  RESET -|   \/   |- VCC
//  PIN 3 -|        |- PIN 2
//  PIN 4 -|        |- PIN 1
// GROUND -|________|- PIN 0

// Configuration items
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;
// Set this to the pn connected to the PIR motion sensor
const byte PIR_PIN_IN = 7;
// Set this to the pin supplying power to the LED control board ICs
const byte CONTROL_PIN_OUT = 8;
// Set this to change the power off delay
const unsigned long POWER_OFF_DELAY_MINUTES = 1;
// Set up the pins connected to the motion sensor and supplying power to the
// LED controller.
void setup()
{
  Serial.begin(9600);
  // Configure the PIR pin as an input
  pinMode (PIR_PIN_IN, INPUT);
  digitalWrite (PIR_PIN_IN, HIGH);
  // Configure the CONTROL pin as an output, initially set to low (LED controller power off)
  pinMode (CONTROL_PIN_OUT, OUTPUT);
  digitalWrite (CONTROL_PIN_OUT, LOW);  
  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){
      Serial.print(".");
      delay(1000);
      }
    Serial.println(" done");
    Serial.println("SENSOR ACTIVE");
    delay(50);
}
// The main loop responsible for turning the LED controller on when motion is detected
// and off again after the specified period of inactivity.
void loop()
{
  // Convert the power off delay from minutes to milliseconds
  static const unsigned long POWER_OFF_DELAY_MS = POWER_OFF_DELAY_MINUTES * 60UL * 1000UL;

  // Keep track of when the LED controller was powered on
  static unsigned long powerOnTime_MS = 0; 

  // Get the current time
  unsigned long currentTime_MS = millis ();

  // If motion has been detected
  if (digitalRead (PIR_PIN_IN) == HIGH)
  {
    Serial.println("---");
    Serial.print("motion detected at ");
    Serial.print(currentTime_MS / 1000); // currentTime_MS is milliseonds (1000) per sec e.i. 5000/1000 is what 5 secs. correct. 
    Serial.println(" sec");
    // Set the power off time
    powerOnTime_MS = currentTime_MS;
    Serial.println("set up for");
    Serial.print( POWER_OFF_DELAY_MS / 1000); // POWER_OFF_DELAY_MS is 60000 so you want / 1000 to be 60 secs
    Serial.print("seconds");
    Serial.println("");
    // Turn on power to the LED control board
    digitalWrite (CONTROL_PIN_OUT, HIGH);
  } // Motion has been detected

  // If it's time to turn the LED controller off
  else if (currentTime_MS - powerOnTime_MS >= POWER_OFF_DELAY_MS)
  {
    // Turn off power to the LED control board
    digitalWrite (CONTROL_PIN_OUT, LOW);
  } // It's time to turn the LED controller off
} 

