
// le char escreve float

void setup(){
  Serial.begin(9600);
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
  
  if( data == 'A' )
  {
    data_to_rpi = 'B';
  } else
  {
    data_to_rpi = data;
  }
  
  Serial.write( data_to_rpi ); // It's kind magic!
}

void loop()
{
  read_uart( 1 );
  write_uart( data_rpi );
}

