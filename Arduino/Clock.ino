#include <TM1637Display.h>

#define CLK 2
#define DIO 3

TM1637Display display = TM1637Display(CLK, DIO);

unsigned long start_time;
unsigned long elapsed_time;
const unsigned long second_length = 1000;

int hr = 11;
int min = 46;
int sec = 0;


void setup(){
    Serial.begin(9600);
    delay(1000);
    display.setBrightness(1);
    display.clear();
    start_time = millis();
    elapsed_time = millis() - start_time;
}

void loop(){
    elapsed_time = millis() - start_time;

    if(elapsed_time >= second_length){
        sec += 1;
        start_time = millis();
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