// led
#define LED_PIN_1 10
// buttons
#define KEY1 A1
#define KEY2 A2
#define KEY3 A3

// debounce treatment
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// led variables
int state = HIGH;
int vel = 2000;
unsigned long lastStateChangeTime = 0;

// buttons variables
int lastKey1State = LOW;
unsigned long lastKey1Press = 0;
int lastKey2State = LOW;
unsigned long lastKey2Press = 1000;
 
void setup() {
  pinMode(LED_PIN_1, OUTPUT);

  // setting the buttons inverts the led HIGH-LOW 
  pinMode(KEY1, INPUT_PULLUP);
  pinMode(KEY2, INPUT_PULLUP);
  pinMode(KEY3, INPUT_PULLUP);

  //Serial.begin(9600);
}

void loop() {

  int key1State = digitalRead(KEY1);
  int key2State = digitalRead(KEY2);
  
  // check if button has been pressed with debounce
  if(key1State != lastKey1State) {
    vel += 100;
    lastKey1Press = millis();
    lastDebounceTime = millis();
  }

  if(key2State != lastKey2State) {
    vel -= 100;
    lastKey2Press = millis();
    lastDebounceTime = millis();
  }

  // debounce
  if((millis() - lastDebounceTime) > debounceDelay) {
    // if the buttons are almost simultaneous  turn off
    if(abs(lastKey1Press - lastKey2Press) <= 500) {
      digitalWrite(LED_PIN_1, HIGH);
      Serial.println(abs(lastKey1Press - lastKey2Press));
      while(1);
    }
    // change button state if has passed more time than speed
    unsigned long newStateChangeTime = millis();
    if(newStateChangeTime >= (lastStateChangeTime + vel)) {
      lastStateChangeTime = newStateChangeTime;
      state = !state;
      digitalWrite(LED_PIN_1, state);
    }
  }
}
