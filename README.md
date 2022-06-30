# Buzzer

this program is designed for the Arduino Uno board, some changes will be required for other platforms. 

### Operation
on startup, all LED's will be off. no player's button will operate. 

Operator must press the master button to activate buzzers.

when true, the onboard LED on pin 13 remains HIGH until a player rings in. the corresponding LED for the player then lights up.

Otherwise, after a set amount of time, the lights flash indicating time is up to answer.

at any point, the operator can press the master button as a reset to allow players to ring in again.


### Default Pinout 

#### Buttons
Pin 2; Master button.

Pin 5; Player 1 button.

Pin 6; Player 2 button.

Pin 7; Player 3 button.


#### LEDs 
Pin 10; Player 1 LED. 

Pin 11; Player 2 LED.

Pin 12; Player 3 LED.

Pin 13; Onboard LED. Indicates waiting for player response. 
