#include <Servo.h>

// Arduino pin assignment
#define PIN_LED 9

#define PIN_POTENTIOMETER 0 // Potentiometer at Pin A3
// Add IR Sensor Definition Here !!!
#define PIN_SERVO 10

#define _DIST_MIN 100.0
#define _DIST_MAX 250.0

#define _DUTY_MIN 535  // servo full clock-wise position (0 degree)
#define _DUTY_NEU 1480 // servo neutral position (90 degree)
#define _DUTY_MAX 2425 // servo full counter-clockwise position (180 degree)

#define LOOP_INTERVAL 50   // Loop Interval (unit: msec)

#define _EMA_ALPHA 0.2

#define _TARGET_LOW 100.0
#define _TARGET_HIGH 250.0

float dist_ema;
float dist_prev = _DIST_MAX;

Servo myservo;
unsigned long last_loop_time;   // unit: msec

void setup()
{
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(_DUTY_NEU);

  dist_prev = _DIST_MIN;
  
  Serial.begin(2000000);
}

void loop()
{
  unsigned long time_curr = millis();
  int a_value, duty;
  float dist;

  // wait until next event time
  if (time_curr < (last_loop_time + LOOP_INTERVAL))
    return;
  last_loop_time += LOOP_INTERVAL;

  // Remove Next line !!!
  a_value = analogRead(PIN_POTENTIOMETER);
  // Read IR Sensor value !!!
  // Convert IR sensor value into distance !!!
  

  duty = map(a_value, 0, 1023, 0, 180);

  dist = (6762.0/(a_value-9)-4.0)*10.0 - 60.0;

  // we need distance range filter here !!!
  if (dist < _DIST_MIN) {
    digitalWrite(PIN_LED, 1);
    myservo.writeMicroseconds(_DUTY_MIN);
  } else if (dist > _DIST_MAX) {
    digitalWrite(PIN_LED, 1);
    myservo.writeMicroseconds(_DUTY_MAX);
  } else {
    digitalWrite(PIN_LED, 0);
    myservo.writeMicroseconds(duty);
  }

  // we need EMA filter here !!!
  dist_ema = (_EMA_ALPHA*dist) + ((1-_EMA_ALPHA)*dist_ema);

  // map distance into duty
  //duty = map(a_value, 0, 1023, _DUTY_MIN, _DUTY_MAX);
  //myservo.writeMicroseconds(duty);

  // print IR sensor value, distnace, duty !!!
  Serial.print("MIN : "); Serial.print(_DIST_MIN);
  Serial.print(" ,IR : "); Serial.print(a_value);
  Serial.print(" ,dist : "); Serial.print(dist);
  Serial.print(" , ema : "); Serial.print(dist_ema);
  Serial.print(" , servo :"); Serial.print(duty);
  Serial.println(", MAX : "); Serial.print(_DIST_MAX);
  Serial.print("");
}
