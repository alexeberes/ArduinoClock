import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import processing.serial.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class TimeRecalibrator extends PApplet {



Serial port;

int hr;
int min;

public void setup(){
    port = new Serial(this, Serial.list()[3], 9600);
}

public void draw(){
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
  static public void main(String[] passedArgs) {
    String[] appletArgs = new String[] { "TimeRecalibrator" };
    if (passedArgs != null) {
      PApplet.main(concat(appletArgs, passedArgs));
    } else {
      PApplet.main(appletArgs);
    }
  }
}
