#include "M5Dial.h"
M5Canvas img(&M5Dial.Display);

void setup() {
    auto cfg = M5.config();
    M5Dial.begin(cfg, true, true);
    M5Dial.Rtc.setDateTime( { { 2023, 10, 25 }, { 15, 56, 56 } } );
    M5Dial.Display.setBrightness(24);
    img.createSprite(240,240);
    img.setTextDatum(5);
    delay(200);
}

long oldPosition = -999;
int mode=0; // 0 is set, 1 ir run , 2 is ringing
int lastS=-999;

int num[3]={0,0,14};  // hours, min, secx
String numS[3]={"","",""};  ///same as num just String
int mm[3]={24,60,60}; // max value for hout, min , sec
int chosen=2;  // chosen in array

bool z=0;
bool deb=0;
bool deb2=0;

void draw()
{
  if(mode==3)
  {
     M5Dial.Speaker.tone(4000,100);
     delay(100);
     z=!z;
     if(z)
     img.fillSprite(WHITE);
     else
     img.fillSprite(BLACK);
     img.drawString(numS[0]+":"+numS[1]+":"+numS[2],120,120,7);
  }
  else{ 
  img.fillSprite(BLACK);
  img.fillRect(0,160,240,60,0x0A2D);
  img.fillRect(0,0,240,80,0x0A2D);
  img.setTextColor(WHITE,0x0A2D);
  img.drawString("START",120,190,4);
  
  img.setTextColor(ORANGE,BLACK);
  img.drawString("RESET",120,232,2);
  img.setTextColor(ORANGE,0x0A2D);
  img.drawString("M5DIAL TIMER",120,60,4);
  img.setTextColor(WHITE,BLACK);
  if(mode==0)
  img.fillRect(14+(chosen*76),150,59,4,GREEN);
  img.drawString(numS[0]+":"+numS[1]+":"+numS[2],120,120,7);
  }
  img.pushSprite(0,0);
}

void updateTime()
{
  if(num[0]<=0 && num[1]<=0 && num[2]<=0 && mode==1)
  mode=3;

  auto dt = M5Dial.Rtc.getDateTime();
  if(lastS!=dt.time.seconds)
  { num[2]--;
    lastS=dt.time.seconds;

    if(num[2]<0) {num[1]--; num[2]=mm[2]-1;}
    if(num[1]<0) {num[0]--; num[1]=mm[1]-1;}
   } 
}

void reset()
      {
        mode=0;
        num[2]=15;
        num[1]=0;
        num[0]=0;
      }

void loop() {

M5Dial.update();

if(M5Dial.BtnA.isPressed())
{M5Dial.Speaker.tone(2800,100);
reset();
delay(200);}

if(mode==0){
  auto t = M5Dial.Touch.getDetail();
  if(t.isPressed())
    {
      if(deb==0)
      { 
        deb=1;
        M5Dial.Speaker.tone(3000,100);
        if(t.y>160) {mode=1;};  
        if(t.y>86 && t.y<150)
          {
          if(t.x>10 && t.x<90) chosen=0;
           if(t.x>90 && t.x<166) chosen=1;
          if(t.x>166 && t.x<224) chosen=2;
          }
      }
    }else deb=0;

    long newPosition = M5Dial.Encoder.read();
    if (newPosition != oldPosition) {
        M5Dial.Speaker.tone(3600,30);
        if(newPosition>oldPosition)  num[chosen]++; else num[chosen]--;
        if(num[chosen]==mm[chosen]) num[chosen]=0;
        if(num[chosen]<0) num[chosen]=mm[chosen]-1;
         oldPosition = newPosition;
    }
}

if(mode==1)
updateTime();

for(int i=0;i<3;i++)
if(num[i]<10) numS[i]="0"+String(num[i]); else numS[i]=String(num[i]);

draw();
}
