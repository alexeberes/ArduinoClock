import processing.serial.*;

Serial port;

int hr;
int min;

void setup(){
    port = new Serial(this, Serial.list()[3], 9600);
}

void draw(){
    hr = hour();
    min = minute();

    int byte1 = hr / 10;
    int byte2 = hr % 10;
    int byte3 = min / 10;
    int byte4 = min % 10;

    port.write(byte4);
    port.write(byte3);
    port.write(byte2);
    port.write(byte1);
}