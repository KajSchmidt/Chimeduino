/*
Project: Chimeduino
Description:
A chimesplaying doorbell.
Keywords:Arduino, solenoid, chimes

Author:Kaj Schmidt
Webpage: https://github.com/KajSchmidt/Chimeduino
License: CC-BY-SA 3.0

*/

int BUTTON_PIN = 13;
int BUTTON_TRIGGER;


int SOLENOID_1 = 9;
int SOLENOID_2 = 8;
int SOLENOID_3 = 7;
int SOLENOID_4 = 6;
int SOLENOID_5 = 5;
int SOLENOID_6 = 4;
int SOLENOID_7 = 3;
int SOLENOID_8 = 2;

int NOTE_RETURN = 10;
int NOTE_DELAY = 200;

void setup() {
    pinMode(SOLENOID_1,OUTPUT);
    pinMode(SOLENOID_2,OUTPUT);
    pinMode(SOLENOID_3,OUTPUT);
    pinMode(SOLENOID_4,OUTPUT);
    pinMode(SOLENOID_5,OUTPUT);
    pinMode(SOLENOID_6,OUTPUT);
    pinMode(SOLENOID_7,OUTPUT);
    pinMode(SOLENOID_8,OUTPUT);

    pinMode(BUTTON_PIN,INPUT);
  
    digitalWrite(BUTTON_PIN, LOW);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == HIGH) {
    if (BUTTON_TRIGGER == 0) playdsong();
    BUTTON_TRIGGER = 1;
  }
  else BUTTON_TRIGGER = 0;
}


void playdsong() {  // Play default song
  
    byte SONG[] = {
      B00100000,
      B00000000,
      B00000000,
      B00000000,
      B00100000,
      B00000000,
      B00000000,
      B00000000,
      B00100000,
      B00000000,
      B00000000,
      B00000000,
      B11000000,
      B00000000,
      B00011000,
      B00000000,
      B00100000,
      B00000000,
      B00000000,
      B00000000,
      B11000000,
      B00000000,
      B00011000,
      B00000000,
      B00100000,
      B00000000,
      B00000000,
      B00000000,
      B00000000,
      B00000100,
      B00000000,
      B00000000,
      B00000000,
      B00000100,
      B00000000,
      B00000000,
      B00000000,
      B00000100,
      B00000000,
      B00000000,
      B00000001,
      B00000000,
      B00000100,
      B00000000,
      B00100000,
      B00000000,
      B00000000,
      B11000000,
      B00000000,
      B00011000,
      B00000000,
      B00100000,
    };    
    int SONG_END = 53;
    
    for (int SONG_PLACE = 0; SONG_PLACE < SONG_END; SONG_PLACE++) {
       playnote(SONG[SONG_PLACE]);
       delay(NOTE_DELAY);
   }
}

void playnote(byte NOTE) {
       if (bitRead(NOTE, 0) == 1) digitalWrite(SOLENOID_1,HIGH);
       if (bitRead(NOTE, 1) == 1) digitalWrite(SOLENOID_2,HIGH);
       if (bitRead(NOTE, 2) == 1) digitalWrite(SOLENOID_3,HIGH);
       if (bitRead(NOTE, 3) == 1) digitalWrite(SOLENOID_4,HIGH);
       if (bitRead(NOTE, 4) == 1) digitalWrite(SOLENOID_5,HIGH);
       if (bitRead(NOTE, 5) == 1) digitalWrite(SOLENOID_6,HIGH);
       if (bitRead(NOTE, 6) == 1) digitalWrite(SOLENOID_7,HIGH);
       if (bitRead(NOTE, 7) == 1) digitalWrite(SOLENOID_8,HIGH);
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
