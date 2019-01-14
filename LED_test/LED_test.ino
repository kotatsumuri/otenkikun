#include <Adafruit_NeoPixel.h>
#define RGBLED_OUTPIN    4
#define NUMRGBLED        1

Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN, NEO_RGB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  RGBLED.begin() ;
  pinMode(6,INPUT);
}
int val;
void loop() {
    /*int var=analogRead(0);
    if(var>512)
    var=512;
    int bright=map(var,0,512,0,255);
    //Serial.println(var);
  RGBLED.setBrightness(bright) ;         
  RGBLED.setPixelColor(0, 255,255,255) ; 
  RGBLED.show() ; */
  val=digitalRead(6);
  Serial.println(val);
}
