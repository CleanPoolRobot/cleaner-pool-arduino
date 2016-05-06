
// le char escreve float

void setup(){
  Serial1.begin(9600);
}

unsigned char data_rpi[50];

typedef union {
 float data;
 byte bytes[4];
} bytesFloat;

void read_uart(int size) {
  int i = 0;
  while(i < size) {
    if(Serial1.available()) {
      data_rpi[i] = Serial1.read();
      Serial.print(data_rpi[i]);
      i++;
    }
  }
}

void write_uart(float data) {
  bytesFloat data_to_rpi;
  data_to_rpi.data = data;
  Serial1.write(data_to_rpi.bytes,4); // It's kind magic!
}

void loop(){








}

