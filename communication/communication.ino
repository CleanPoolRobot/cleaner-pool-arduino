//#include "Arduino.h"
//#include "communication.h"

#define REAR_DISTANCE_SENSOR 4
#define LEFT_DISTANCE_SENSOR 7
#define RIGHT_DISTANCE_SENSOR 12
#define FRONT_DISTANCE_SENSOR 13
#define INTERNAL_PRESSURE A1
#define EXTERNAL_PRESSURE A2

//change after values
#define REQUEST_INTERNAL_PRESSURE 'A'
#define REQUEST_EXTERNAL_PRESSURE 'B'
#define REQUEST_FRONT_DISTANCE 'C'
#define REQUEST_REAR_DISTANCE 'D'
#define REQUEST_LEFT_DISTANCE 'E'
#define REQUEST_RIGHT_DISTANCE 'F'

int output = 3;
int value;
byte data_rpi;

unsigned char data_request;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(REAR_DISTANCE_SENSOR,INPUT);  
}


void send_pressure( int pin )
{
  int value_write;
  value_write = analogRead(pin);
  write_uart(value_write); 
} 

void send_distance (int pin )
{
  int value_write;
  value_write = digitalRead(pin);
  write_uart(value_write); 
}
void write_uart( byte data )
{
  byte data_to_rpi = data;
  Serial.write( data_to_rpi ); // It's kind magic!
}

void loop()
{
  if(Serial.available()){
  data_request = Serial.read();
  Serial.print("Requisição recebida: ");
  Serial.println(data_request);

  switch(data_request){
    case REQUEST_INTERNAL_PRESSURE:
      send_pressure(INTERNAL_PRESSURE);
    break;

    case REQUEST_EXTERNAL_PRESSURE:
      send_pressure(EXTERNAL_PRESSURE);
    break;

    case REQUEST_FRONT_DISTANCE:
      send_distance(FRONT_DISTANCE_SENSOR);   
    break;
    
    case REQUEST_REAR_DISTANCE:
      send_distance(REAR_DISTANCE_SENSOR);   
    break;
      
    case REQUEST_LEFT_DISTANCE:
      send_distance(LEFT_DISTANCE_SENSOR);   
    break;
    
    case REQUEST_RIGHT_DISTANCE:
      send_distance(RIGHT_DISTANCE_SENSOR);   
    break;
    
  }
 }
  data_request = Serial.read();
  printf("Valor que será escrito %c\n\n",data_request);
}
