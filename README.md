# Buzzer

when operated, this code runs a 
this program requires an arduino UNO to operate correctly.

#### Operation
on startup, all LED's will be off. no player's button will operate. 

to run, operator must hit master button, and no player buttons muct be active. 

when true, the onboard LED on pin 13 remains HIGH until a player rings in. the corresponding LED for the player then lights up.

after a set time the lights flash indicating time is up to answer.

at any point, the operator can press the master button as a reset to allow players to ring in again.

#### KNOWN BUGS

I don't know why, but occassionally LED's will auto flash at seemingly random integers after a player has rung in and time has expired.

#### pinouts

Digital pin 2; master button state
Digital pin 7; player 1 button state
Digital pin 9; player 2 button state
Digital pin 11; connect player 3 button state
Digital pin 8; LED saying player 1 has rung in first.
Digital pin 10; LED saying player 2 has rung in first.
Digital pin 12; LED saying player 3 has rung in first.
Digital pin 13; on arduino UNO, it is linked to the onboard LED. tells operator players can currently ring in.


