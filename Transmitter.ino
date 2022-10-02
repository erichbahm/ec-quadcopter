#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Unique pipe out code
const uint64_t pipeOut = 0xE8E8F0F0E1LL;

// CSN pins
RF24 radio(9, 10);

// 32 byte structure
struct MyData {
  int throttle;
  int yaw;
  int pitch;
  int roll;
  byte AUX1;
  byte AUX2;
};

MyData data;


void resetData() 
{   
  data.throttle = 0;
  data.yaw = 512;
  data.pitch = 512;
  data.roll = 512;
  data.AUX1 = 0;
  data.AUX2 = 0;
}


void setup()
{
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
  
  //Serial.begin(9600);
}

/*
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 1023);
  else
    val = map(val, middle, upper, 512, 1023);
  return ( reverse ? 1023 - val : val );
}
*/

void loop()
{
  data.throttle = map(analogRead(A0),0,667,0,1023);//mapJoystickValues( analogRead(A0), 0, 340, 680, false );
  data.yaw      = map(analogRead(A1),0,667,0,1023);//mapJoystickValues( analogRead(A1),  0, 340, 680, false );
  data.pitch    = map(analogRead(A2),0,667,0,1023);//mapJoystickValues( analogRead(A2), 0, 340, 680, false );
  data.roll     = map(analogRead(A3),0,667,0,1023);//mapJoystickValues( analogRead(A3), 0, 340, 680, false );
  
  data.AUX1     = digitalRead(4); //The 2 toggle switches
  data.AUX2     = digitalRead(5);

  radio.write(&data, sizeof(MyData));
 
/*
  Serial.print("Throttle: ");
  Serial.print(data.throttle);
  Serial.print("               yaw: ");
  Serial.print(data.yaw);
  Serial.print("               Pitch: ");
  Serial.print(data.pitch);
  Serial.print("               Roll: ");
  Serial.println(data.roll);
  delay(100);
 */
 /*
 Serial.print("AUX 1: ");
 Serial.print(data.AUX1);
 Serial.print("          AUX 2: ");
 Serial.println(data.AUX2);
 delay(100);
 */
}
