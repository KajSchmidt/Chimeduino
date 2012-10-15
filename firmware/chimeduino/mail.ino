boolean checkMAIL() {
  static char data; 
  boolean result = false;
  
  updateClient();
  data = checkAvail();
  if (data >= 10){
    if (getMailNum(data) == true) result = true;  
  }
  return result;
}

/*=================================================
Ethernet POP3 Mail Checker & indicator

Checks how many messages are waiting on the POP 3 server
and flashed LED on Pin 9 to indicate number of messages.

It will handle up to 99 messages in the POP3 mailbox.

Uncomment the serial lines for troubleshooting.

Copyright by Chris Armour
3 September 2009
http://opensourceprojects-torchris.blogspot.com/

===================================================*/
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192,168,0,167 }; // IP address you wish to assign to Arduino
byte server[] = { 192, 168, 0, 1 }; // IP address of your POP3 server
char inString[165]; // Number of characters to be collected
int i = 0;


EthernetClient client; //The default POP port is 110

long updateTimer;
boolean clientConnected = false;



/*========================================
        Functions
=========================================*/

void updateClient() //This function contacts the POP3 server
{
if ((millis() - updateTimer) > 5000)
{
 Ethernet.begin(mac);
//    Serial.println("connecting...");
 delay(1000);
 if (client.connect(server, 110))
 {
//    Serial.println("connected");
 client.println("user Your.Name"); //Insert your usual email login name
 client.println("pass PassWord"); //And your password here
 client.println("quit");
 client.println();
 clientConnected = true;
 }
 else
 {
//    Serial.println("connection failed");
 }
 updateTimer = millis();
}
}

char checkAvail() //This checks if there is data available and returns a char
{
if (clientConnected)
{
 if (client.available())
 {
 char c = client.read();
     return(c);
 }
 if (!client.connected())
 {
 client.stop();
 clientConnected = false;
 }
}
}

int getMailNum(char mail) //This actually loads the char returned by checkAvail() and puts in into an array
{
static int mailNum1 = 0; // First digit of the email number
static int mailNum2 = 0; // Second digit
static int mailTotal = 0; // Total # of messsage  
inString[i] = mail;
i++;
if (i == 165){
   i = 0;
       client.flush();
       mailNum1 = inString[106] - 48; //Array position 106 contains the first digit
       mailNum2 = inString[107] - 48; //Array position 107 contains the 2nd digit if it is available
       if ((mailNum2 >= 0) && (mailNum2 <= 9)) mailTotal = (mailNum1 * 10) + mailNum2; //when 2 digits are present, multiply the 1st by 10 then add to mailTotal
       else if ((mailNum1 >= 0) && (mailNum1 <= 9))mailTotal = mailNum1;
     }
     if (mailTotal > 0) return true;
     else return false;
 }



