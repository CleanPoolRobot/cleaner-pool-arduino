void setup() {
    Serial.begin(9600);
}
 
void loop(){
    float pressure = readPressure(A5);
    float millibars = pressure/100;
 
    Serial.println();
    Serial.print("Pressure = ");
    Serial.print(pressure);
    Serial.println(" pascals");
    Serial.print("Pressure = ");
    Serial.print(millibars);
    Serial.println(" millibars");
    delay(1000);
}
 
/* Reads pressure from the given pin.
* Returns a value in Pascals
*/
float readPressure(int pin){
    int pressureValue = analogRead(pin);
    Serial.println(pressureValue);
    float pressure=((pressureValue/1024.0)+0.04)/0.0000369;
    return pressure;
}
