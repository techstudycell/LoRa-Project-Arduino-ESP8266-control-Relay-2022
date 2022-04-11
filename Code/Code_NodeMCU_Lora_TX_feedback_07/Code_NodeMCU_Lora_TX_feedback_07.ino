 /**********************************************************************************
 *  TITLE: (Transmitting end) LoRa sketch to send signal using Buttons and display feedbacks on OLED
 *  Click on the following links to learn more. 
 *  YouTube Video: https://youtu.be/jU5LDAQ5r2M
 *  Related Blog : https://iotcircuithub.com/tag/lora/
 *  by Tech StudyCell
 *
 *  Download the libraries 
 *  Adafruit_SSD1306 2.5.1 Library:     https://github.com/adafruit/Adafruit_SSD1306
 **********************************************************************************/

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Adafruit_SSD1306.h>

String lora_band = "865000000"; //enter band as per your country
String lora_networkid = "5";    //enter Lora Network ID
String lora_address = "1";      //enter Lora address
String lora_RX_address = "2";   //enter Lora RX address

#define LORA_BAUD_RATE     115200      // Change baudrate to your need


SoftwareSerial mySerial(13, 15); // RX, TX  D7, D8

#define pSwitch_1 10  //SD3
#define pSwitch_2 0   //D3 
#define pSwitch_3 14  //D5
#define pSwitch_4 3   //RX
#define pSwitch_S D6   //D6

#define WIFI_LED   16   //D0
#define sLED       2   //D4

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

String pinStatus = "0000";
//String pinStatus_OLD = "0000";

int i;
String incomingString;
String tempString;
String feedString;
boolean rState;

void manual_control()
{
  if (digitalRead(pSwitch_1) == LOW){      
      if(pinStatus.substring(0,1) == "0"){
        mySerial.println("AT+SEND="+ lora_RX_address +",2,A1");
      }
      else{
        mySerial.println("AT+SEND="+ lora_RX_address +",2,A0");
      }
      getFeedback();
    }
  else if (digitalRead(pSwitch_2) == LOW){
      if(pinStatus.substring(1,2) == "0"){
        mySerial.println("AT+SEND="+ lora_RX_address +",2,B1");
      }
      else{
        mySerial.println("AT+SEND="+ lora_RX_address +",2,B0");
      }
      getFeedback();
    }
  else if (digitalRead(pSwitch_3) == LOW){
      if(pinStatus.substring(2,3)== "0"){
        mySerial.println("AT+SEND="+ lora_RX_address +",2,C1");
      }
      else{
        mySerial.println("AT+SEND="+ lora_RX_address +",2,C0");
      }
      getFeedback();
    }
  else if (digitalRead(pSwitch_4) == LOW){
      if(pinStatus.substring(3,4)== "0"){
        mySerial.println("AT+SEND="+ lora_RX_address +",2,D1");
      }
      else{ 
        mySerial.println("AT+SEND="+ lora_RX_address +",2,D0");
      }
     getFeedback(); 
    }
  else if (digitalRead(pSwitch_S) == LOW){ 
     mySerial.println("AT+SEND="+ lora_RX_address +",2,FS");
     getFeedback();
  }
}

void getFeedback(){
  i = 0;
  incomingString = "";
  tempString = "";
  rState = true;
  digitalWrite(sLED, LOW);

  //Serial.print("Waiting for feedback");
  while(1){
    if(mySerial.available()>0){
      incomingString = mySerial.readString();
      Serial.println(incomingString);
      if(incomingString.indexOf('F') > 0) {
        tempString = incomingString.substring(incomingString.indexOf('F') + 1);
        pinStatus = tempString.substring(0, tempString.indexOf(','));
        Serial.println(pinStatus);
        rState = true; break;
      }
    }
    if (i == 40) {
      mySerial.println("AT+SEND="+ lora_RX_address +",2,FS");   
    }
    if (i > 80) {
      rState = false; break;
    }
    delay(50);
    digitalWrite(sLED, !digitalRead(sLED));
    i++;
    }

    if(rState){
      digitalWrite(sLED, HIGH);
      displayStatus("Received...",relayState(pinStatus));
    }
    else{
      digitalWrite(sLED, LOW);
      displayStatus("Not Received","PRESS STATUS");
      //Serial.println("Not Received");
    }
}

String relayState(String state){
  feedString = "";
  if (state.substring(0,1) == "1"){ feedString = "ON  ";}
  else { feedString = "OFF ";}
  if (state.substring(1,2) == "1"){ feedString = feedString + "ON  ";}
  else { feedString = feedString + "OFF ";}
  if (state.substring(2,3) == "1"){ feedString = feedString + "ON  ";}
  else { feedString = feedString + "OFF ";}
  if (state.substring(3,4) == "1"){ feedString = feedString + "ON  ";}
  else { feedString = feedString + "OFF ";}
  return feedString;
}

void displayStatus(String text1, String text2){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(20,4);
  display.print(text1);
  
  display.drawLine(0,18, display.width()-1,18, WHITE);
  display.setCursor(15,24);
  display.print(text2);
  display.display();
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(LORA_BAUD_RATE);
  
  pinMode(WIFI_LED, OUTPUT);
  pinMode(sLED, OUTPUT);
  
  pinMode(pSwitch_1, INPUT_PULLUP);
  pinMode(pSwitch_2, INPUT_PULLUP);
  pinMode(pSwitch_3, INPUT_PULLUP);
  pinMode(pSwitch_4, INPUT_PULLUP);
  pinMode(pSwitch_S, INPUT_PULLUP);

  digitalWrite(WIFI_LED, HIGH); //Turn off WiFi LED
  digitalWrite(sLED, HIGH);   //Turn on Status LED

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(1000);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  

  delay(1500);
  mySerial.println("AT+BAND=" + lora_band);
  delay(500);
  mySerial.println("AT+ADDRESS=" + lora_address);
  delay(500);
  mySerial.println("AT+NETWORKID=" + lora_networkid);
  delay(1000);
  mySerial.println("AT+SEND="+ lora_RX_address +",2,FS");
  getFeedback();
  
  digitalWrite(sLED, LOW);
}

void loop() {
  manual_control();
}
