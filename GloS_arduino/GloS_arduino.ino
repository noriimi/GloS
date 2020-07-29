#include<FastLED.h>
const uint8_t header[4] = { 0xDE, 0xAD, 0xBE, 0xEF };
#define NUM_LEDS 60
#define DATA_PIN 2
char XON =17;
char XOFF=19;
uint8_t buff[180];
CRGB leds[NUM_LEDS];
void setup()
{
  LEDS.addLeds<WS2812,DATA_PIN,GRB>(leds,NUM_LEDS);
  Serial.begin(115200);
  for(int i=0;i<60;i++)
  leds[i]=CRGB::Blue;
  FastLED.show();
  Serial.print(XON);
}

void loop() {
  // we're going to read led data directly from serial, after we get our header
  while(true) {
    while(Serial.available() == 0){} // wait for new serial data
    Serial.print(XOFF);
    uint8_t b = Serial.read();
    bool looksLikeHeader = false;
    if(b == header[0]) {
      looksLikeHeader = true;
      for(int i = 1; looksLikeHeader && (i < sizeof(header)); i++) {
        while(Serial.available() == 0){} // wait for new serial data
        b = Serial.read();
        if(b != header[i]) {
          // whoops, not a match, this no longer looks like a header.
          looksLikeHeader = false;
        }
      }
    }

    if(looksLikeHeader) {
      // hey, we read all the header bytes!  Yay!  Now read the frame data
      int bytesRead = 0;
      while(bytesRead < (NUM_LEDS *3)) {
        //bytesRead += Serial.readBytes(((uint8_t*)leds) + bytesRead, (NUM_LEDS*3)-bytesRead);
        bytesRead+=Serial.readBytes(buff+bytesRead,(NUM_LEDS*3)-bytesRead);
      }
      // all bytes are read into led buffer. Now we can break out of while loop
      break;
    }
  }
  
  // now show the led data
  for(int i=0;i<NUM_LEDS;i++)
  {
    leds[i]=CHSV(buff[3*i],buff[3*i+1],buff[3*i+2]);
  }
  
  FastLED.show();

  // finally, flush out any data in the serial buffer, as it may have been interrupted oddly by writing out led data:
  while(Serial.available() > 0) { Serial.read(); }
  Serial.print(XON);

}
