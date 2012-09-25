boolean checkBUTTON(int btn) {  //Take int and look for positive flank in analog inputs
  static int BUTTON_TRIGGER[6];
  boolean result = false;
  if (analogRead(BUTTON_PIN[btn]) > 500) {
    if (BUTTON_TRIGGER[btn] == 0) 
      result = true;
    BUTTON_TRIGGER[btn] = 1;
  }
  else BUTTON_TRIGGER[btn] = 0;
  
  return result;
}
