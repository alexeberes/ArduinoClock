#include <TM1637Display.h>
#include <Keypad.h>

#define CLK 2
#define DIO 3

TM1637Display display = TM1637Display(CLK, DIO);

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {11, 10, 9, 8};
byte colPins[COLS] ={7, 6, 5, 4};

Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

unsigned long start_time;
unsigned long elapsed_time;
const unsigned long second_length = 1000;

int hr = 0;
int min = 0;
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
    char key = keypad.getKey();

    if(key){
        if(key == '*'){
            int hr1 = -1;
            int hr2 = -1;
            int min1 = -1;
            int min2 = -1;
            while(hr1 == -1){
                char key2 = keypad.getKey();
                if(key2){
                    hr1 = key2 - 48;
                }
            }
            while(hr1 == -1){
                char key2 = keypad.getKey();
                if(key2){
                    hr2 = key2 - 48;
                }
            }
            while(hr1 == -1){
                char key2 = keypad.getKey();
                if(key2){
                    min1 = key2 - 48;
                }
            }
            while(hr1 == -1){
                char key2 = keypad.getKey();
                if(key2){
                    min2 = key2 - 48;
                }
            }
            hr = hr1 * 10 + hr2;
            min = min1 *10 + min2;
            sec = 0;
        }
    }

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