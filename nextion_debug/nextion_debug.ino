#include <SoftwareSerial.h>
#include <DFRobot_sim808.h>

 
SoftwareSerial nextionSerial(10, 11); //Rx, Tx
char msisdn[30], ATcomm[30];
String rawMsg, pageNum, msg, pls;
DFRobot_SIM808 sim808(&Serial);
int debug_led = 13;

void debug_flash1(int numFlash){
  for(int i=0; i<numFlash; i++){
    digitalWrite(debug_led,HIGH);
    delay(200);
    digitalWrite(debug_led,LOW);
    delay(200);
  }
  delay(1000);
}

void setup(){
  pinMode(debug_led, OUTPUT);
  debug_flash1(5);

  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor DIN JARRIN ---");

  nextionSerial.begin(9600); 
}
 
void loop(){

  //debug_flash1(10);

  while(nextionSerial.available()){
    rawMsg.concat(char(nextionSerial.read()));
  }
  delay(10); //Read the SoftwareSerial
  
  if(!nextionSerial.available())
  {                   
    debug_flash1(2);

    if(rawMsg.length())
    {
      Serial.println("Inside STARWARS if rawMsg length block");
      pageNum = rawMsg[rawMsg.length()-4];           //Read Nextion: get the page number.
      msg = rawMsg.substring(1, rawMsg.length()-4);    //Read Nextion: get the Raw Msges from Nextion.
      Serial.println("pageNum:");
      Serial.println(pageNum);
      Serial.println("msg:");
      Serial.println(msg);
      debug_flash1(5);

      

      //Read Nextion: page0, Query all SMS from the GSM Buffer.
      if((pageNum == '1') && (msg.length() != 0)){
        //connectCall(msg);
        Serial.println("BAZOOKS! Inside pageNum 1 block. Dude.");
        debug_flash1(7);
        //connectCallDFRobot(msg);
      }

      // look at rawMsg
    }

  }
}

void writeString(String stringData)
{
//Function to send commands to the Nextion display.
  for(int i=0; i < stringData.length(); i++)
  {
    nextionSerial.write(stringData[i]);
  }
  nextionSerial.write(0xff);
  nextionSerial.write(0xff);
  nextionSerial.write(0xff);
}
