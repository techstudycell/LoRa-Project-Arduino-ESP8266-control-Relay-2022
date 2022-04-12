# LoRa-Project-Arduino-ESP8266-control-Relay-2022
In this Lora project tutorial, I have shown how to make the LoRa Project using the Arduino ESP8266 control relay with real-time feedback.

So after turning on and off the appliances the receiver circuit will send feedback to the transmitter circuit and you can monitor the real-time feedback in the OLED display.

## Tutorial Video on the LoRa Project using Arduino ESP8266
Video Link: https://youtu.be/jU5LDAQ5r2M

In this article, I have covered the following topics.

1. Explained this ESP8266 Arduino Lora home automation project.
2. Explained Transmitter & Receiver Lora circuit.
3. Explained the basic AT commands and source codes for this LoRA project.
4. Connecting the LoRa module with Arduino and ESP8266.
5. Control high voltage appliances with LoRa.
So if you follow all the steps, you can easily make this Lora Arduino project to control any appliances from 10KM away in the rural areas without Wi-Fi and Bluetooth. So this project is very useful in rural areas.

Although the PCB is not mandatory, I have used PCB for the transmitter LoRa circuit to make the circuit compact and give the project a professional look.

### Required components for the Transmitter Lora circuit:
1. Lora Module REYAX RYLR998 1no
2. ESP8266 NodeMCU 1no
3. 1k Resistors 2no
4. 4.7k Resistor 1no
5. 10k Resistor 1no
6. 5-mm LED 2no
7. Push-button 4no

### Required components for the Receiver Arduino Lora circuit:
1. Lora Module REYAX RYLR998 1no
2. Arduino UNO 1no
3. 5v 4-channel Relay Module 1no
4. 1k Resistor 1no
5. 2k Resistor 1no
6. 4.7k Resistor 1no
7. 5-mm LED 1no
8. Switch or pushbuttons 4no

### Required Components for the PCB used for the transmitter circuit:
1. REYAX RYLR998 or RYLR896 Lora module 1no
2. ESP8266 NodeMCU 1no
3. 1k Resistors 2no
4. 4.7k Resistor 1no
5. 10k Resistor 2no
6. 5-mm LED 2no
7. Push-button 6no
8. Jumper 2no
9. Terminal connector 2 pin 1no
10. OLED Display

## Transmitter Lora Circuit Using NodeMCU ESP8266
In the transmitter LoRa circuit, I have used NodeMCU. I have made a voltage divider using 4.7k and 10k resistors to drop down the 5volt logic level to 3.3volt logic level for the LoRa module.

I have used D7 as RX and D8 as TX for the serial communication with the LoRa module.

The pushbuttons are connected with the SD3, D3, D5, RX, and D6 GPIO pins of the NodeMCU. ( Here SD3, D3, D5, & RX are for controlling the relays, and D6 is used for requesting feedback from receiving side).

The status LED is connected with the D4 GPIO pin.

You can use any 5V DC power supply to supply the circuit.

## Receiver Lora Circuit Using Arduino UNO
On the receiving end, I have used Arduino UNO. In the circuit, I have made a voltage divider using 2k and 4.7k resistors to drop down the 5volt logic level to 3.3volt logic level.

I have used D4, D5, D6 & D7 pins to control the 4-channel relay module.

As per the source code, when the control pins of the relay module receive the LOW signal the respective relay will turn on and the relay will turn off for the HIGH signal in the control pin.

And the GPIO D10, D11, D12 & D13 are connected with switches to control the relay module manually.

The LED is connected with the A3 pin.

I have used a 5V 2Amp power supply to supply the Arduino UNO and relay module.

Please take the proper safety precautions while working with high voltage.

## PCB Used for the Transmitter LoRa Circuit
To make the circuit compact and give a professional look, I have designed the PCB for the transmitter end LoRa circuit.

You can download the PCB Gerber file of this Lora project from the following link:
https://github.com/techstudycell/LoRa-Project-Arduino-ESP8266-control-Relay-2022/tree/main/PCB_Gerber

## Why you should use JLC SMT Service?
On JLCPCB's one-stop online platform, customers enjoy low-cost & high-quality & fast SMT service at an $8.00 setup fee($0.0017 per joint).

$27 New User coupon & $24 SMT coupons every month.
Visit https://jlcpcb.com/RAB

JLCPCB SMT Parts Library 200k+ in-stock components (689 Basic components and 200k+ Extended components)

Parts Pre-Order service https://support.jlcpcb.com/article/164-what-is-jlcpcb-parts-pre-order-service

Build a Personal library Inventory, save parts for now or the future

Assembly will support 10M+ parts from Digikey, mouser.

## Steps to Order the PCB Assembly from JLCPCB
1. Visit https://jlcpcb.com/RAB and Sign in / Sign up.
2. Click on the QUOTE NOW button.
3. Click on the "Add your Gerber file" button. Then browse and select the Gerber file you have downloaded.
4. Set the required parameter like Quantity, PCB masking color, etc.
5. Select the Assemble side and SMT Quantity.
6. Now upload the BOM and PickAndPlace files.
7. Now confirm all the components which you want to be soldered by SMT services.
8. Click on SAVE TO CART button.
9. Type the Shipping Address.
10. Select the Shipping Method suitable for you.
11. Submit the order and proceed with the payment.

You can also track your order from the JLCPCB.
My PCBs took 3 days to get manufactured and arrived within a week using the DHL delivery option.
PCBs were well packed and the quality was really good at this affordable price.

## Codes for This LoRa Project Using Arduino and ESP8266
In this Lora Project, I have used NodeMCU for the transmitter circuit, and Arduino UNO for the receiving circuit.

First, download the source codes from following link: 
https://github.com/techstudycell/LoRa-Project-Arduino-ESP8266-control-Relay-2022/tree/main/Code

Then upload the code for the transmitter circuit to ESP8266 NodeMCU. And upload the code of the receiving circuit to Arduino UNO.

### Important Points:
1. You do not have to configure the Lora modules separately for this project. During the boot process of the microcontroller, the void setup() function will execute all AT commands that are required.
2. Here I have used the 865MHz band. Please enter the BAND in the code as per the eligible LoRa band in your country.
3. Do not disconnect Lora modules from the microcontrollers, and after programming wait till the status LED in both circuits turn OFF.

## Control the Appliances With LoRa
Now you can control the appliances with the transmitter LoRa circuit using pushbuttons and also monitor the real-time feedback from the receiver LoRa circuit.

After receiving the feedback the status LED will turn ON and you can see the current states of each relay on the OLED display.

## Control Relays Manually With Switches
You can also control the appliances from the manual switches. and to monitor the current state of the relays you have to press the STATUS button in the transmitter LoRa circuit.
Then it will request feedback and after receiving the feedback from the receiving LoRa circuit, it will display the current states of each relay on the OLED.

In the future, I will try to add more features to this LoRa project.
I will really appreciate it if you share your valuable feedback. Also if you have any queries please write in the comment section.
Thank you & Happy Learning.
