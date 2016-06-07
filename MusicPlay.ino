//Music Playing Function OF The Beats
//By:slow
//Blog:http://www.slowshiki.me
//Mail:Slowshiki@gmail.com
//Github:Qyc0129


#include <Keypad.h>
#include <SimpleSDAudio.h>
char AudioFileName[16];
#define BIGBUFSIZE (2*512)      // bigger than 2*512 is often only possible on Arduino megas!
uint8_t bigbuf[BIGBUFSIZE];
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
{'1','0','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rowPins[ROWS] = {5, 3, 2, 1}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {10, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
//setting the keypad
void setup(){
  Serial.begin(9600);
  //Serial start for testing
}
  
void loop(){
  int customKey = customKeypad.getKey();
  //Key value
 if (customKey){
    Serial.print(customKey);
  switch(customKey){
   case 67: play1();//67=keypad 4
   break;
   case 57: play2();//57=keypad 5
   break;
   }    
 }
}
void play1() //Play First Song
{ 
  // If your SD card CS-Pin is not at Pin 4, enable and adapt the following line:
  // SdPlay.setSDCSPin(10);
  // Init SdPlay and set audio mode
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO)) {
    while(1); // Error while initialization of SD card -> stop.
 } 
  
  // Select file to play
  if(!SdPlay.setFile("3.AFM")) {//3.AFM is the first song Flower Dance
    while(1); // Error file not found -> stop.
  }   
  // Start playback
  SdPlay.play();
  // Let the worker work until playback is finished
  while(!SdPlay.isStopped()) {
  SdPlay.worker();
  }
}
void play2()//Play Second Song
{ 
  if (!SdPlay.init(SSDA_MODE_FULLRATE | SSDA_MODE_MONO)) {
    while(1); //
  }  
  if(!SdPlay.setFile("2.AFM")) {//2.AFM is the second song JinLiChao
    while(1); // Error file not found -> stop.
  }   
  // Start playback
  SdPlay.play();
  // Let the worker work until playback is finished
  while(!SdPlay.isStopped()) {
    SdPlay.worker();
  }
}
void newsong()//EXTENDED Function For Your New Song
{
  SdPlay.setWorkBuffer(bigbuf, BIGBUFSIZE); 
  uint8_t count=0, c, flag;  
  Serial.println(F("Files on card:"));
  SdPlay.dir(&DirCallback);
//Enter your new song's name
ReEnter: 
  count = 0;
  Serial.println(F("\r\nEnter filename (send newline after input):"));
  do {
    while(!Serial.available()) ;
    c = Serial.read();
    if(c > ' ') AudioFileName[count++] = c;
  } while((c != 0x0d) && (c != 0x0a) && (count < 14));
  AudioFileName[count++] = 0;
//Looking for the new song  
  Serial.print(F("Looking for file... "));
  if(!SdPlay.setFile(AudioFileName)) {
    Serial.println(F(" not found on card! Error code: "));
    Serial.println(SdPlay.getLastError());
    goto ReEnter;
  } else {
   Serial.println(F("found.")); 
  }    
//Enter the function singal
  Serial.println(F("Press s for stop, p for play, h for pause, f to select new file, d for deinit, v to view status.")); 
  flag = 1;
  
  while(flag) {
    SdPlay.worker();
    if(Serial.available()) {
      c = Serial.read();
      switch(c) {
         case 's':
           SdPlay.stop();
           Serial.println(F("Stopped."));
           break; 
           
         case 'p':
           SdPlay.play();
           Serial.println(F("Play."));
           break;
           
         case 'h':
           SdPlay.pause();
           Serial.println(F("Pause."));
           break;   
   
         case 'd':
           SdPlay.deInit();
           Serial.println(F("SdPlay deinitialized. You can now safely remove card. System halted."));
           while(1) ;
           break;  
             
         case 'f':
           flag = 0;
           break; 
     
         case 'v':
           Serial.print(F("Status: isStopped="));
           Serial.print(SdPlay.isStopped());
           Serial.print(F(", isPlaying="));
           Serial.print(SdPlay.isPlaying());
           Serial.print(F(", isPaused="));
           Serial.print(SdPlay.isPaused());
           Serial.print(F(", isUnderrunOccured="));
           Serial.print(SdPlay.isUnderrunOccured());
           Serial.print(F(", getLastError="));
           Serial.println(SdPlay.getLastError());
           Serial.print(F("Free RAM: "));
           Serial.println(freeRam());
           break;      
      } 
    }
  }
  
  
}
//DirCallBack
void DirCallback(char *buf) { 
  Serial.println(buf);
}
//SDcard freeram
int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}
