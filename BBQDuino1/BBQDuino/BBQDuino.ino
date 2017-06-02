// https://forum.arduino.cc/index.php?topic=110221.0
// http://hruska.us/tempmon/
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor
unsigned int food_temp = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Start bbq mon");
  delay(2000);  
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  food_temp = thermister_temp(sensorValue);
  Serial.println(food_temp);  
  delay(2000);
}

int thermister_temp(int aval) {
  double R, T;

  // These were calculated from the thermister data sheet
  //  A = 2.3067434E-4;
  //  B = 2.3696596E-4;
  //  C = 1.2636414E-7;
  //
  // This is the value of the other half of the voltage divider
    int Rknown = 22000;
       // int Rknown = 21630;
  // Do the log once so as not to do it 4 times in the equation
  //  R = log(((1024/(double)aval)-1)*(double)22200);
  R = log((1 / ((1024 / (double) aval) - 1)) * (double) Rknown);
  //lcd.print("A="); lcd.print(aval); lcd.print(" R="); lcd.print(R);
  // Compute degrees C
  T = (1 / ((2.3067434E-4) + (2.3696596E-4) * R + (1.2636414E-7) * R * R * R)) - 273.25;
        
  // return degrees F
  return ((int) ((T * 9.0) / 5.0 + 32.0));
}
