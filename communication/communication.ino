//#include "Arduino.h"
//#include "communication.h"

#define REAR_DISTANCE_SENSOR 4
#define LEFT_DISTANCE_SENSOR 7
#define RIGHT_DISTANCE_SENSOR 12
#define FRONT_DISTANCE_SENSOR 13
#define INTERNAL_PRESSURE A1
#define EXTERNAL_PRESSURE A2

int output = 3;
int value;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(REAR_DISTANCE_SENSOR,INPUT);  
}


byte data_rpi;

void read_uart( int size )
{
  int i = 0;
  while( i < size )
  {
    if( Serial.available() )
    {
      data_rpi = Serial.read();
      i++;
    }
  }
}

void write_uart( byte data )
{
  byte data_to_rpi = data;
   
  Serial.write( data_to_rpi ); // It's kind magic!
}

void loop()
{
 for(int i = 0; i < 3; i++)
  {
    value = digitalRead(REAR_DISTANCE_SENSOR);
    digitalWrite(output, HIGH);
    if(value != HIGH)
      write_uart('A');
    else
    {
      write_uart('B');
      digitalWrite(output, LOW);
    }
  }
}

