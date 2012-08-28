/*
Project: Chimeduino
Description:
A chimesplaying doorbell.
Keywords:Arduino, solenoid, chimes

Author:Kaj Schmidt
Webpage: https://github.com/KajSchmidt/Chimeduino
License: CC-BY-SA 3.0

*/

int BUTTON_PIN = 9;
int BUTTON_TRIGGER;


int SOLENOID_1 = 1;
int SOLENOID_2 = 2;
int SOLENOID_3 = 3;
int SOLENOID_4 = 4;
int SOLENOID_5 = 5;
int SOLENOID_6 = 6;
int SOLENOID_7 = 7;
int SOLENOID_8 = 8;

int NOTE_RETURN = 10;
int NOTE_DELAY = 10;

void setup() {
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
    B00000001,
    B00000010,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01000000,
    B10000000};
    
    int SONG_END = 8;
    int SONG_PLACE = 0;
    
    for (SONG_PLACE = 0; SONG_PLACE > SONG_END, SONG_PLACE++) {
       playnote(SONG[SONG_PLACE]);
       delay(NOTE_DELAY);
   }
}

void playnote(byte NOTE) {
       if (BitRead(NOTE, 0) == 1) digitalWrite(SOLENOID_1,HIGH);
       if (BitRead(NOTE, 1) == 1) digitalWrite(SOLENOID_2,HIGH);
       if (BitRead(NOTE, 2) == 1) digitalWrite(SOLENOID_3,HIGH);
       if (BitRead(NOTE, 3) == 1) digitalWrite(SOLENOID_4,HIGH);
       if (BitRead(NOTE, 4) == 1) digitalWrite(SOLENOID_5,HIGH);
       if (BitRead(NOTE, 5) == 1) digitalWrite(SOLENOID_6,HIGH);
       if (BitRead(NOTE, 6) == 1) digitalWrite(SOLENOID_7,HIGH);
       if (BitRead(NOTE, 7) == 1) digitalWrite(SOLENOID_8,HIGH);
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
