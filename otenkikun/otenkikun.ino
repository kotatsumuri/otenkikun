#include <Adafruit_NeoPixel.h>
#define RGBLED_OUTPIN    8
#define NUMRGBLED        1

Adafruit_NeoPixel RGBLED = Adafruit_NeoPixel(NUMRGBLED, RGBLED_OUTPIN, NEO_RGB + NEO_KHZ800);

int bright_var;

int noti_counter=0;
boolean noti_status=0;

int tokidoki_counter=0;
boolean tokidoki_status=0;

byte get_value=0;

int b_status=0;
int b_weather=4;
int a_weather=4;
int weather_status=0;

void setup() {
  Serial.begin(115200);
  RGBLED.begin() ;
  pinMode(9,INPUT);
}

int weather_pattarn[5][3]={{0xff,0x4f,0x00},{0x00,0x60,0xff},{0xb5,0xff,0xff},{0x00,0xff,0xa5},{0,0,0}};
//晴、雨、曇、雪

void loop() {

  if (Serial.available() > 0) { // 受信したデータが存在する
     get_value= Serial.read(); // 受信データを読み込む
  }
  
  
  date_sorting(get_value);

  btn();
  
  if(b_status==1){
      bright_var=bright_volume();
      switch(weather_status){
        case 0:
        only(b_weather,bright_var);
        break;
        
        case 1:
        tokidoki(b_weather,a_weather,bright_var);
        break;
        
        case 2:
        noti(b_weather,a_weather,bright_var);
        break;
      }
  }
  else if(b_status==2){
    status_reset();
    off();
  }
}

void btn(){
  int btn_value=digitalRead(9);
  switch(btn_value){
    case 0:
    Serial.println('0');
    break;
    case 1:
    Serial.println('1');
    break;
  }
}

void status_reset(){
  noti_counter=0;
  noti_status=0;
  tokidoki_counter=0;
  tokidoki_status=0;
}

int bright_volume(){
  int var=analogRead(4);
  
  if(var>512)
    var=512;
    
  int bright=map(var,0,512,0,255);

  return bright;
}

void date_sorting(int var){
  b_status=var/0x40;
  var=var%0x40;
  if(b_status==0){
    a_weather=var/0x10;
    var=var%0x10;
    weather_status=var/0x04;
    var=var%0x04;
    b_weather=var;
  }
}

void only(int weather,int bright){
  RGBLED.setBrightness(bright) ;        
  RGBLED.setPixelColor(0, weather_pattarn[weather][0],weather_pattarn[weather][1],weather_pattarn[weather][2]) ;
  RGBLED.show() ;
  delay(1);
}

void noti(int before,int after,int bright){
  
  int weather[2]={before,after};
  
  RGBLED.setBrightness(bright*(-0.5*cos(PI/180*noti_counter)+0.5)) ;        
  RGBLED.setPixelColor(0, weather_pattarn[weather[noti_status]][0],weather_pattarn[weather[noti_status]][1],weather_pattarn[weather[noti_status]][2]) ;
  RGBLED.show() ; 
  delay(5);
  
  if(noti_status==true&&noti_counter==360)
    delay(1000);
  
  if(noti_counter==360){
    noti_counter=0;
    noti_status=!noti_status;
  }
  
  noti_counter++;
  
}

void tokidoki(int before,int after,int bright){
  
  int weather[2]={before,after};

  if(tokidoki_counter<150||(tokidoki_counter>=250&&tokidoki_counter<400)){
    RGBLED.setBrightness(bright) ;
    RGBLED.setPixelColor(0, weather_pattarn[weather[tokidoki_status]][0],weather_pattarn[weather[tokidoki_status]][1],weather_pattarn[weather[tokidoki_status]][2]) ;
    RGBLED.show();
    delay(1); 
  }
  if((tokidoki_counter>=150&&tokidoki_counter<250)||tokidoki_counter>=400){
  RGBLED.setBrightness(0);
  RGBLED.show() ; 
  delay(1);
  }
  
  tokidoki_counter++;
  if(tokidoki_counter==250 ||tokidoki_counter==1400)
  tokidoki_status=!tokidoki_status;
  if(tokidoki_counter>=1400)
  tokidoki_counter=0;
}

void off(){
  RGBLED.setBrightness(0) ;
  RGBLED.show() ;
}


