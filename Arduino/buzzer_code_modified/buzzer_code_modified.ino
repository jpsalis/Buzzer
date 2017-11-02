//timer vars
const int timeToAns = 4000; //in millis
const int timeBuzzerOn = 700; //in millis

//const vars
const int player1Pin = 7;
const int player2Pin = 9;
const int player3Pin = 11;
const int led1 = 8;
const int led2 = 10;
const int led3 = 12;
const int masterSwitchPin = 2;
const int led = 13;

//changing vars
int player1 = 0;
int player2 = 0;
int player3 = 0;
int masterSwitch = 0;
int prevMasterSwitch = 0;
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



//start of loop
void loop() {
  //Serial.print("start of loop, ");
  masterSwitch = digitalRead(masterSwitchPin);
  Serial.print("time im millis: ");
  Serial.println(millis());
  timeSincePress = millis() - timeBuzzerActive;

  if (timeSincePress >= timeToAns && timeSincePress < timeBuzzerOff && msPressed == HIGH) {

    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  if (timeSincePress >= timeBuzzerOff && msPressed == HIGH) {

    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }

  if (masterSwitch == HIGH && prevMasterSwitch != masterSwitch) {

    digitalWrite(led, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    player1 = LOW;
    player2 = LOW;
    player3 = LOW;
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
  }
  prevMasterSwitch = masterSwitch;
  //Serial.println("end of loop");

}

