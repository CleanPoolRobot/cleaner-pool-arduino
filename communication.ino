//#include "Arduino.h"
//#include "communication.h"

#define REAR_DISTANCE_SENSOR 4
#define LEFT_DISTANCE_SENSOR 7
#define RIGHT_DISTANCE_SENSOR 12
#define FRONT_DISTANCE_SENSOR 13
#define INTERNAL_PRESSURE A1
#define EXTERNAL_PRESSURE A5
#define PUMP 8
//change after values
#define REQUEST_INTERNAL_PRESSURE 'A'
#define REQUEST_EXTERNAL_PRESSURE 'B'
#define REQUEST_FRONT_DISTANCE 'C'
#define REQUEST_REAR_DISTANCE 'D'
#define REQUEST_LEFT_DISTANCE 'E'
#define REQUEST_RIGHT_DISTANCE 'F'
#define MOTOR_PUMP_ON 'G'
#define MOTOR_PUMP_OFF 'H'
int output = 3;
int value;
byte data_rpi;

char data_request;

void setup(){
  Serial.begin(115200);
  pinMode(3, OUTPUT);
  pinMode(REAR_DISTANCE_SENSOR,INPUT);  
}


void send_pressure( int pin )
{
  float pressure = readPressure(pin);
  float pressure_result;
  if (pin == A1)
    pressure_result = pressure;
  else
    pressure_result = pressure + 20000;  

  delay(500);
  Serial.println(pressure_result);
  //write_uart(pressure); 
} 

float readPressure(int pin){
    int pressureValue = analogRead(pin);
    //Serial.println(pressureValue); //valor recebido 
    float pressure=((pressureValue/1024.0)+0.04)/0.0000369; //convertendo para pascal
    return pressure;
}


void send_distance (int pin )
{
  Serial.println("Enviando dados sobre distancia");
  int value_write;
  value_write = digitalRead(pin);
  write_uart(value_write); 
}
void write_uart( byte data )
{
  Serial.println(data);
  //byte data_to_rpi = data;
  //Serial.write( data_to_rpi ); // It's kind magic!
}

void turn_on_pump(int pin)
{
   pinMode(pin,OUTPUT);
   digitalWrite(pin,HIGH);
   Serial.println("Ligando bomba");
}

void turn_off_pump(int pin)
{
   pinMode(pin,OUTPUT);
   digitalWrite(pin,LOW);
   Serial.println("Desligando bomba");
}

void loop()
{
  if(Serial.available() > 0){
  data_request = Serial.read();
  //Serial.print("Requisição recebida: ");
  //Serial.println(data_request);

  switch(data_request){
    case REQUEST_INTERNAL_PRESSURE:
      //Serial.println("Requisitando pressao interna...");
      send_pressure(INTERNAL_PRESSURE);
    break;

    case REQUEST_EXTERNAL_PRESSURE:
    //Serial.println("Requisitando pressao externa...");
      send_pressure(EXTERNAL_PRESSURE);
    break;

    case REQUEST_FRONT_DISTANCE:
      Serial.println("Requisitando distancia frontal... \n");
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

    case MOTOR_PUMP_ON:
      turn_on_pump(PUMP);
    break;

    case MOTOR_PUMP_OFF:
      turn_off_pump(PUMP);
    break;
  }
 }
  data_request = Serial.read();
  printf("Valor que será escrito %c\n\n",data_request);
}