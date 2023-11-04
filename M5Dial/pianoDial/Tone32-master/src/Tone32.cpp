#include "Tone32.h"

void tone(uint8_t pin, unsigned int frequency, unsigned long duration, uint8_t channel)
{
  
    ledcAttachPin(pin, channel);
    ledcWriteTone(channel, frequency);
   
     
}

void noTone(uint8_t pin, uint8_t channel)
{
    ledcDetachPin(pin);
    ledcWrite(channel, 0);
}
