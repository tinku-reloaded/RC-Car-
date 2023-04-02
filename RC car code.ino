#include <Servo.h>

#include <IRremote.h>

const int headlight = 8;
const int right_indicator = 6;
const int left_indicator = 7;
const int move_forward = 9;
//const int move_backward = 10;
const int horn =5;
const int IR_recv_butt = 1;
const int servo_button = 2;
const int echo_butt = 3;
const int trig_butt = 4;

int distance;
int duration;

Servo servo;
IRrecv irrecv(IR_recv_butt);
decode_results results;

void setup()
{
  pinMode(headlight, OUTPUT);
  pinMode(right_indicator, OUTPUT);
  pinMode(left_indicator, OUTPUT);
  pinMode(move_forward, OUTPUT);
  pinMode(horn, OUTPUT);
  pinMode(IR_recv_butt, OUTPUT);
  pinMode(echo_butt,INPUT);
  pinMode(trig_butt,OUTPUT);
  servo.attach(servo_button);
  
  irrecv.enableIRIn();
  
  //initial connditions
  digitalWrite(headlight,LOW);
  digitalWrite(right_indicator,LOW);
  digitalWrite(left_indicator,LOW);
  digitalWrite(horn,LOW);
  digitalWrite(move_forward,LOW);
  servo.write(0);
}

void loop()
{ 
  if (irrecv.decode(&results)){
    switch(results.value){
      case 0xFD00FF:
        digitalWrite(headlight,HIGH);
        break;
      case 0xFD20DF:
      	digitalWrite(left_indicator,HIGH);
      	delay(500);
      	digitalWrite(left_indicator,LOW);
      	delay(500);
      	break;
  	  case 0xFD609F:
      	digitalWrite(right_indicator,HIGH);
      	delay(500);
      	digitalWrite(right_indicator,LOW);
      	delay(500);
      	break;
      case 0xFDA05F:
      	digitalWrite(horn,HIGH);
      	delay(100);
      	digitalWrite(horn,LOW);
      	delay(100);
      	digitalWrite(horn,HIGH);
      	delay(100);
      	digitalWrite(horn,LOW);
      	break;
    }
    irrecv.resume();
  
  }
  digitalWrite(trig_butt, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_butt, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_butt, LOW);
  duration = pulseIn(echo_butt,HIGH);
  distance = (duration * 0.034/2);
  
  if(distance >100)
  {
    Serial.println('Move Forward');
    digitalWrite(servo_button,HIGH);
    digitalWrite(headlight,LOW);
  }
  
  else
  {
    Serial.println('Warning! Cant move furthur because of obstacle');
    digitalWrite(headlight,HIGH);
    digitalWrite(left_indicator,HIGH);
    digitalWrite(right_indicator,HIGH);
    servo.write(90);
    delay(500);
    digitalWrite(left_indicator,LOW);
    digitalWrite(right_indicator,LOW);
    servo.write(0);
    delay(500);
  }
  
  
}