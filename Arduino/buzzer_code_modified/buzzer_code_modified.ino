//timer vars
const int timeToAns = 4000; //in millis
const int timeBuzzerOn = 700; //in millis

/* constant vars */
// GPIO pins for buttons
const int masterSwitchPin = 2;
const int player1Pin = 7;
const int player2Pin = 9;
const int player3Pin = 11;
// LED's corresponding to user buttons
const int led1 = 8;
const int led2 = 10;
const int led3 = 12;

const int led = 13;

/*other vars*/
int player1 = 0; //current state of player 1 button
int player2 = 0; //current state of player 2 button
int player3 = 0; //current state of player 3 button
int masterSwitch = 0; //current state of operator button
int prevMasterSwitch = 0; //state of masterSwitch in last loop
int timeSincePress = 0;
int timeBuzzerActive = 0;
int timeBuzzerOff = timeToAns + timeBuzzerOn;
int msPressed = 0;

void setup() {
  Serial.begin(9600);
  pinMode(player1Pin, INPUT);
  pinMode(player2Pin, INPUT);
  pinMode(player3Pin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(masterSwitchPin, INPUT);
}


void LEDState(int state)
{
  digitalWrite(led1, state);
  digitalWrite(led2, state);
  digitalWrite(led3, state);
}
//start of loop
void loop() {
  masterSwitch = digitalRead(masterSwitchPin);
  Serial.print("time im millis: ");
  Serial.println(millis());
  timeSincePress = millis() - timeBuzzerActive;

  //tests if player answered in timeframe and 
  if (timeSincePress >= timeToAns && timeSincePress < timeBuzzerOff && msPressed == HIGH) {

    LEDState(HIGH);
  }

  if (timeSincePress >= timeBuzzerOff && msPressed == HIGH) {

    LEDState(LOW);
    
  }

  //makes sure that even if master switch is held, players can still ring in.
  if (masterSwitch == HIGH && (prevMasterSwitch != masterSwitch) && (player1 == LOW && player2 == LOW && player3 == LOW)) {
    digitalWrite(led, HIGH);
    LEDState(LOW);
    Serial.print("Who buzzed first: ");
    while (player1 == LOW && player2 == LOW && player3 == LOW) {
      player1 = digitalRead(player1Pin);
      player2 = digitalRead(player2Pin);
      player3 = digitalRead(player3Pin);
    }
    digitalWrite(led, LOW);
    if (player1 == HIGH) {
      Serial.println("player 1");
      digitalWrite(led1, HIGH);
    } 
    else { 
      if (player2 == HIGH) {
        Serial.println("player 2");
        digitalWrite(led2, HIGH);
      } 
      else { 
        if (player3 == HIGH) {
          Serial.println("player 3");
          digitalWrite(led3, HIGH);
          Serial.println("");
        }
      }
    }
    timeBuzzerActive = millis();
    msPressed = masterSwitch;
    player1 == LOW;
    player2 == LOW;
    player3 == LOW;
  }
  
  prevMasterSwitch = masterSwitch;

}

