#include "M5Dial.h"
#include <Tone32.h>

#define BUZZER_PIN 3
#define BUZZER_CHANNEL 0

int x[17]={35,92,149,6,63,120,177,35,92,149,92,149,63,120,177,92,149};
int y[17]={40,40,40,105,105,105,105,170,170,170,15,15,80,80,80,145,145};
int w[17]={55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55,55};
int h[17]={40,40,40,40,40,40,40,40,40,40,25,25,25,25,25,25,25};
int cls[17]={WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK};
int cls2[17]={BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE};
int notes[17]={NOTE_B4,NOTE_C5,NOTE_D5,NOTE_E5,NOTE_F5,NOTE_G5,NOTE_A5,NOTE_B5,NOTE_C6,NOTE_D6,NOTE_CS5,NOTE_DS5,NOTE_FS5,NOTE_GS5,NOTE_AS5,NOTE_CS6,NOTE_DS6};
String lbl[17]={"b","c","d","e","f","g","a","b","c","d","c#","d#","f#","g#","a#","c#","d#"};

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, true);
    M5Dial.Display.setBrightness(34);
    M5Dial.Display.fillScreen(0xABE1);
    M5Dial.Display.setTextDatum(4);

    for(int i=0;i<17;i++){
    M5Dial.Display.fillRect(x[i],y[i],w[i],h[i],cls[i]);
    M5Dial.Display.setTextColor(cls2[i],cls[i]);
    M5Dial.Display.drawString(lbl[i],x[i]+(w[i]/2),y[i]+(h[i]/2),2);
    }
    
}

int deb=0;
void loop() {
 M5Dial.update();
auto t = M5Dial.Touch.getDetail();
if(t.isPressed()){
for(int i=0;i<17;i++)
  if(t.x>x[i] && t.x<x[i]+48 && t.y>y[i] && t.y<y[i]+38 )
  {
    if(deb==0) 
    {
        deb=1;  
        tone(BUZZER_PIN, notes[i], 50, BUZZER_CHANNEL);
    }
  }
 }else{
   noTone(BUZZER_PIN, BUZZER_CHANNEL);
  deb=0;}


}
