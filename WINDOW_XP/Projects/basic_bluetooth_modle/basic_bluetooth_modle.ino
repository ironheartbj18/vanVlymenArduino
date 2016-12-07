char inbyte;
int led = 13;
int ledPin2 = 5;
int ledPin3 = 11;

void setup(){
 Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  allpinslow(); 
}

void allpinslow(){
   digitalWrite(led,LOW);
   digitalWrite(ledPin2,LOW);
   analogWrite(ledPin3,LOW);
 }

void loop(){
 Serial.println("press");
while(!Serial.available());
inbyte = Serial.read();
if (inbyte == '0') 
  allpinslow();
if (inbyte == '1')
  digitalWrite(led, HIGH);
//if (inbyte == '2') digitalWrite(le, HIGH);
int r;
for (r = 0; r < 256; r++) { 
    analogWrite(ledPin2, r);
    delay(FADESPEED);
  } 

delay(50);
}
