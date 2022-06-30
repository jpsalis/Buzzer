//#define ENABLE_DISP_FLASH // Lights will flash regardless of intended mode
//#define LOG // Write to serial when data found

#define NUMPLAYERS 3
#define RESPONSE_DUR 5000 // Amount of time for questions
#define DISPLAY_DUR 2000 // Amount of time buzzed player is displayed
#define RESET_DUR 1000 // Timer expired and round finished dur if ENABLE_DISP_FLASH

// Definitions
void setAllLEDs(bool);
enum gameState {
  Initial = 0,
  Response,
  Display,
  Reset
};
struct user {
  const uint8_t btnPin;
  const uint8_t ledPin;
  bool btn      : 1;
  bool prevBtn : 1;
  public:
    void updateBtn() {
      prevBtn = btn;
      btn = !digitalRead(btnPin);
    }
    bool edgeDetected() {
      return btn && !prevBtn;
    }
};
struct timer {
  uint32_t end;
  void setTimer(uint32_t dur) {
    end = millis() + dur;
  }
};

// Declarations
struct user master = {btnPin:2, ledPin:13};
struct user players[] = {
  {btnPin:5, ledPin:10}, 
  {btnPin:6, ledPin:11}, 
  {btnPin:7, ledPin:12}
};
enum gameState curMode = Initial;
enum gameState nextMode = curMode;
struct timer t;


void setup() {
  #ifdef LOG
    Serial.begin(9600);
  #endif

  // Game Operator
  pinMode(master.btnPin, INPUT_PULLUP);
  pinMode(master.ledPin, OUTPUT);

  // Players
  for(int i = 0; i < NUMPLAYERS; i++) {
    pinMode(players[i].btnPin, INPUT_PULLUP);
    pinMode(players[i].ledPin, OUTPUT);
  }
}


void loop() {
  master.updateBtn();

  for(int i = 0; i < NUMPLAYERS; i++) {
    players[i].updateBtn();
  }

  // Begin Questionare Logic
  if(master.edgeDetected()) {
    // TODO: Make state reset to response in all cases except response
    switch (curMode) {
      case Initial:
        nextMode = Response;
        #ifdef LOG
          Serial.println(F("Begin:"));
        #endif
        break;
      default:
        nextMode = Initial;
        #ifdef LOG
          Serial.println(F("  Reset."));
        #endif
    }
  }

  // Timer Logic
  if(curMode != Initial && millis() > t.end) {
    switch(curMode) {
    
      case Response:
        #ifdef LOG
          Serial.println(F("  Timeout."));
        #endif
        nextMode = Reset;
        break;
    
    #ifdef ENABLE_DISP_FLASH
      case Display:
        nextMode = Reset;
        break;
    #endif
      default:
        nextMode = Initial;
        break;
    }
  }

  if(curMode == Response) {
    // check player input
    // if valid, break and light up their led.
    for(int i = 0; i < NUMPLAYERS; i++) {
      if (players[i].edgeDetected()) {
        digitalWrite(players[i].ledPin, HIGH);
        nextMode = Display;
        #ifdef LOG
          Serial.print(F("  Player "));
          Serial.print(i + 1);
          Serial.println(F(" buzzed in."));
        #endif
        break;
      }
    }
  }

  if(curMode != nextMode) {
    switch(nextMode) {
      case Initial:
        digitalWrite(master.ledPin, LOW);
        setAllLEDs(LOW);
        break;
      case Response:
        digitalWrite(master.ledPin, HIGH);
        t.setTimer(RESPONSE_DUR);
        break;
      case Display:
        digitalWrite(master.ledPin, LOW);
        t.setTimer(DISPLAY_DUR);
        break;
      case Reset:
        digitalWrite(master.ledPin, LOW);
        setAllLEDs(HIGH);
        t.setTimer(RESET_DUR);
        break;
    }
    curMode = nextMode;
  }
  delay(10);
}


void setAllLEDs(bool state) {
  for(int i = 0; i < NUMPLAYERS; i++)
  {
    digitalWrite(players[i].ledPin, state);
  }
}