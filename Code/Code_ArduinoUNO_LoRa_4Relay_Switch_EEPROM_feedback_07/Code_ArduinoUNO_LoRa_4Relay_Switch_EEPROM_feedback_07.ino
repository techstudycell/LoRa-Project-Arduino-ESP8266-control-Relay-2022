/**********************************************************************************
 *  TITLE: (Receiving end) Arduino LoRa control 4 Relays with real-time feedback & EEPROM 
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/jU5LDAQ5r2M
 *  Related Blog : https://iotcircuithub.com/tag/lora/
 *  by Tech StudyCell
 *
 *  Download the libraries : N/A
 **********************************************************************************/

#include <EEPROM.h>
#include <SoftwareSerial.h>

String lora_band = "865000000"; //enter band as per your country
String lora_networkid = "5";    //enter Lora Network ID
String lora_address = "2";      //enter Lora address
String lora_RX_address = "1";   //enter Lora RX address (for sending)

SoftwareSerial mySerial(2, 3); // RX, TX D2, D3

// define the GPIO connected with Relays and switches
#define RelayPin1 4  //D4
#define RelayPin2 5  //D5
#define RelayPin3 6  //D6
#define RelayPin4 7  //D7

#define SwitchPin1 10  //D10
#define SwitchPin2 11  //D11
#define SwitchPin3 12  //D12
#define SwitchPin4 13  //D13

#define sLed   A3   //A13

// Switch State
bool SwitchState_1 = LOW;
bool SwitchState_2 = LOW;
bool SwitchState_3 = LOW;
bool SwitchState_4 = LOW;

String bt_data; // variable for storing bluetooth data
String pinStatus = "0000";

void eepromState()
{
  digitalWrite(RelayPin1, EEPROM.read(0)); delay(200);
  digitalWrite(RelayPin2, EEPROM.read(1)); delay(200);
  digitalWrite(RelayPin3, EEPROM.read(2)); delay(200);
  digitalWrite(RelayPin4, EEPROM.read(3)); delay(200);
  updateStatus();
}  

void lora_control()
{
  if(mySerial.available()) {
    bt_data = mySerial.readString();
    //Serial.println("NO"+bt_data + "samplple");
        if(bt_data.indexOf("A1") >0) { digitalWrite(RelayPin1, LOW);  EEPROM.update(0,LOW); updateStatus(); sendStatus();} // if 'A1' received Turn on Relay1
        if(bt_data.indexOf("A0") >0) { digitalWrite(RelayPin1, HIGH); EEPROM.update(0,HIGH); updateStatus(); sendStatus();} // if 'A0' received Turn off Relay1
        if(bt_data.indexOf("B1") >0) { digitalWrite(RelayPin2, LOW);  EEPROM.update(1,LOW); updateStatus(); sendStatus();} // if 'B1' received Turn on Relay2
        if(bt_data.indexOf("B0") >0) { digitalWrite(RelayPin2, HIGH); EEPROM.update(1,HIGH); updateStatus(); sendStatus();} // if 'B0' received Turn off Relay2
        if(bt_data.indexOf("C1") >0) { digitalWrite(RelayPin3, LOW);  EEPROM.update(2,LOW); updateStatus(); sendStatus();} // if 'C1' received Turn on Relay3
        if(bt_data.indexOf("C0") >0) { digitalWrite(RelayPin3, HIGH); EEPROM.update(2,HIGH); updateStatus(); sendStatus();} // if 'C0' received Turn off Relay3
        if(bt_data.indexOf("D1") >0) { digitalWrite(RelayPin4, LOW);  EEPROM.update(3,LOW); updateStatus(); sendStatus();} // if 'D1' received Turn on Relay4
        if(bt_data.indexOf("D0") >0) { digitalWrite(RelayPin4, HIGH); EEPROM.update(3,HIGH); updateStatus(); sendStatus();} // if 'D0' received Turn off Relay4
        if(bt_data.indexOf("FS") >0) { updateStatus(); sendStatus(); } // if 'FS' send the relay status
        delay(20);
  }
}


void manual_control()
{
  if (digitalRead(SwitchPin1) == LOW && SwitchState_1 == LOW) {
    digitalWrite(RelayPin1, LOW);
    EEPROM.update(0,LOW);
    SwitchState_1 = HIGH;
    updateStatus();
  }
  if (digitalRead(SwitchPin1) == HIGH && SwitchState_1 == HIGH) {
    digitalWrite(RelayPin1, HIGH);
    EEPROM.update(0,HIGH);
    SwitchState_1 = LOW;
    updateStatus();
  }
  if (digitalRead(SwitchPin2) == LOW && SwitchState_2 == LOW) {
    digitalWrite(RelayPin2, LOW);
    EEPROM.update(1,LOW);
    SwitchState_2 = HIGH;
    updateStatus();
  }
  if (digitalRead(SwitchPin2) == HIGH && SwitchState_2 == HIGH) {
    digitalWrite(RelayPin2, HIGH);
    EEPROM.update(1,HIGH);
    SwitchState_2 = LOW;
    updateStatus();
  }
  if (digitalRead(SwitchPin3) == LOW && SwitchState_3 == LOW) {
    digitalWrite(RelayPin3, LOW);
    EEPROM.update(2,LOW);
    SwitchState_3 = HIGH;
    updateStatus();
  }
  if (digitalRead(SwitchPin3) == HIGH && SwitchState_3 == HIGH) {
    digitalWrite(RelayPin3, HIGH);
    EEPROM.update(2,HIGH);
    SwitchState_3 = LOW;
    updateStatus();
  }
  if (digitalRead(SwitchPin4) == LOW && SwitchState_4 == LOW) {
    digitalWrite(RelayPin4, LOW);
    EEPROM.update(3,LOW);
    SwitchState_4 = HIGH;
    updateStatus();
  }
  if (digitalRead(SwitchPin4) == HIGH && SwitchState_4 == HIGH) {
    digitalWrite(RelayPin4, HIGH);
    EEPROM.update(3,HIGH);
    SwitchState_4 = LOW;
    updateStatus();
  }
}

void updateStatus(){  
  pinStatus = String(!digitalRead(RelayPin1)) + String(!digitalRead(RelayPin2)) + String(!digitalRead(RelayPin3)) + String(!digitalRead(RelayPin4));
}

void sendStatus(){  
  //mySerial.print(pinStatus);
  mySerial.println("AT+SEND="+ lora_RX_address +",5,F" + pinStatus);
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(115200);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);
  pinMode(sLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(sLed, HIGH);
  
  delay(1500);
  mySerial.println("AT+BAND=" + lora_band);
  delay(500);
  mySerial.println("AT+NETWORKID=" + lora_networkid);
  delay(500);
  mySerial.println("AT+ADDRESS=" + lora_address);
  
  delay(500);
  eepromState(); 
  
  digitalWrite(sLed, LOW);
}

void loop() {
  lora_control();
  manual_control();
}
