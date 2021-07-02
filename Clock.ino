#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display = TM1637Display(CLK, DIO);

unsigned long start_time;
unsigned long elapsed_time;
const unsigned long second_length = 1000;

int hr = 0;
int min = 0;
int sec = 0;

void recalibrateTime(){
    int byte4 = 0;
    int byte3 = 0;
    int byte2 = 0;
    int byte1 = 0;
    if(Serial.available() > 0){
        byte4 = Serial.read();
    }
    if(Serial.available() > 0){
        byte3 = Serial.read();
    }
    if(Serial.available() > 0){
        byte2 = Serial.read();
    }
    if(Serial.available() > 0){
        byte1 = Serial.read();
    }
    hr = byte1 * 10 + byte2;
    min = byte3 * 10 + byte4;
}

void setup(){
    Serial.begin(9600);
    delay(1000);
    display.setBrightness(7);
    display.clear();
    start_time = millis();
    elapsed_time = millis() - start_time;
}

void loop(){
    if(Serial){
        recalibrateTime();
    }
    elapsed_time = millis() - start_time;

    if(elapsed_time > second_length){
        sec += 1;
    }

    if(sec == 60){
        sec = 0; 
        min += 1;
    }

    if(min == 60){
        min = 0;
        hr += 1;
    }

    if(hr == 24){
        hr = 0;
    }

    display.showNumberDecEx((hr * 100 + min), 0b11100000, true);

    delay(500);
}