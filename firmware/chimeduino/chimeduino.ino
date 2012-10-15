#include <SD.h>

/*
Project: Chimeduino
Description:
A chimesplaying doorbell.
Keywords:Arduino, solenoid, chimes

Author:Kaj Schmidt
Webpage: https://github.com/KajSchmidt/Chimeduino
License: CC-BY-SA 3.0

*/

int SOLENOID_1 = 1;
int SOLENOID_2 = 2;
int SOLENOID_3 = 3;
int SOLENOID_4 = 5;
int SOLENOID_5 = 6;
int SOLENOID_6 = 7;
int SOLENOID_7 = 8;
int SOLENOID_8 = 9;

int CS_SD = 4;
int CS_NW = 10;
//int MOSI = 11;
//int MISO = 12;
//int CLK = 13;


boolean CARD_PRESENT = true;


// Music settings
int NOTE_RETURN = 10;
int NOTE_DELAY = 150;

void setup() {
   
    pinMode(SOLENOID_1,OUTPUT);
    pinMode(SOLENOID_2,OUTPUT);
    pinMode(SOLENOID_3,OUTPUT);
    pinMode(SOLENOID_4,OUTPUT);
    pinMode(SOLENOID_5,OUTPUT);
    pinMode(SOLENOID_6,OUTPUT);
    pinMode(SOLENOID_7,OUTPUT);
    pinMode(SOLENOID_8,OUTPUT);
    
    pinMode(CS_SD, OUTPUT);
    pinMode(CS_NW, OUTPUT);
    
    if (!SD.begin(CS_SD)) CARD_PRESENT = false; //Check if card is present
}

void loop() {
  if (checkBUTTON(0) == true) playSONG("imp.txt");
  //if (checkMAIL() == true) playSONG("mario.txt");
}



void playSONG(char file[]) {  //Take string and open up file on SD
  if (!CARD_PRESENT) playDEFAULT();  //If no card present, play default song
  else {
    File SCORE;
    SCORE = SD.open(file);
    while (SCORE.available()) {
    	playNOTE(TXTtoBIN(SCORE.read()));
        delay(NOTE_DELAY);
    }
    SCORE.close();
  }
}

void playNOTE(byte NOTE) {  //Take byte and output to solenoid ports
       if (bitRead(NOTE, 0) == 1) digitalWrite(SOLENOID_8,HIGH);
       if (bitRead(NOTE, 1) == 1) digitalWrite(SOLENOID_7,HIGH);
       if (bitRead(NOTE, 2) == 1) digitalWrite(SOLENOID_6,HIGH);
       if (bitRead(NOTE, 3) == 1) digitalWrite(SOLENOID_5,HIGH);
       if (bitRead(NOTE, 4) == 1) digitalWrite(SOLENOID_4,HIGH);
       if (bitRead(NOTE, 5) == 1) digitalWrite(SOLENOID_3,HIGH);
       if (bitRead(NOTE, 6) == 1) digitalWrite(SOLENOID_2,HIGH);
       if (bitRead(NOTE, 7) == 1) digitalWrite(SOLENOID_1,HIGH);
       delay(NOTE_RETURN);
       digitalWrite(SOLENOID_1,LOW); //Return soleniods to endstate
       digitalWrite(SOLENOID_2,LOW);
       digitalWrite(SOLENOID_3,LOW);
       digitalWrite(SOLENOID_4,LOW);
       digitalWrite(SOLENOID_5,LOW);
       digitalWrite(SOLENOID_6,LOW);
       digitalWrite(SOLENOID_7,LOW);
       digitalWrite(SOLENOID_8,LOW);
}

byte TXTtoBIN(char sign) {  //Transform ascii char to internal binary code
      byte note;
      
      if (sign == 'N') note = B00000000;
      else if (sign == 'C') note = B00000001;
      else if (sign == 'B') note = B00000010;
      else if (sign == 'A') note = B00000100;
      else if (sign == 'G') note = B00001000;
      else if (sign == 'F') note = B00010000;
      else if (sign == 'E') note = B00100000;
      else if (sign == 'D') note = B01000000;
      else if (sign == 'c') note = B10000000;
      else note = B00000000;
      
      return note;
}

void playDEFAULT() {  // Play default song
  
    byte SONG[] = {'E','N','N','N','E','N','N','N','E','N','N','N','c','N','G','N','E','N','N','N','c','N','G','N','E','N','N','N','N','A','N','N','N','A','N','N','N','A','N','N','C','N','A','N','E','N','N','c','N','G','N','E'};    
    int SONG_END = 53;
    
    for (int SONG_PLACE = 0; SONG_PLACE < SONG_END; SONG_PLACE++) {
       playNOTE(TXTtoBIN(SONG[SONG_PLACE]));
       delay(NOTE_DELAY);
   }
}
