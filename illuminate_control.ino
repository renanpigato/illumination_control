/**
 * Control variables with current state of lamps 
 * and the lamps that was triggered
 */
int lampSwitch;
int lampTriggered;
int oldLampTriggered;

/**
 * Speed of serial connection
 */
int baudRate = 9600;

/**
 * Control variables of lamps
 */
bool lampONE;
bool lampTWO;
bool lampTHREE;
bool lampFOUR;
bool lampFIVE;
bool lampSIX;
bool lampSEVEN;
bool lampEIGHT;

void setup() {

  /** 
   * Input's pin, the buttons of control lamps,
   * set of pins are a binary of lamp ender to 
   * power on/off
   */
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);

  // Output pin's to control the lamps
  pinMode(6,  OUTPUT);
  pinMode(7,  OUTPUT);
  pinMode(8,  OUTPUT);
  pinMode(9,  OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  // Initialize the lamps on power off mode
  digitalWrite(6,  LOW);
  digitalWrite(7,  LOW);
  digitalWrite(8,  LOW);
  digitalWrite(9,  LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);

  Serial.begin(baudRate);

  // Initialize the control variables
  lampSwitch = -1;
  lampTriggered = 0;
  oldLampTriggered = 0;
  lampONE    = false;
  lampTWO    = false;
  lampTHREE  = false;
  lampFOUR   = false;
  lampFIVE   = false;
  lampSIX    = false;
  lampSEVEN  = false;
  lampEIGHT  = false;
}

void loop() {

  lampTriggered = readLampTriggered();

  switch (lampTriggered) {
    case 1:
      lampSwitch = 6;
      break;
    case 2:
      lampSwitch = 7;
      break;
    case 3:
      lampSwitch = 8;
      break;
    case 4:
      lampSwitch = 9;
      break;
    case 5:
      lampSwitch = 10;
      break;
    case 6:
      lampSwitch = 11;
      break;
    case 7:
      lampSwitch = 12;
      break;
    case 8:
      lampSwitch = 13;
      break;
    default:
      lampSwitch = -1;
      oldLampTriggered = 0;
      break;
  }

  if (oldLampTriggered == 0 && oldLampTriggered != lampTriggered) {

    oldLampTriggered = lampTriggered;
    
    if (lampSwitch >= 6 && lampSwitch <= 13) {

      int action = LOW;
      
      if (switchLampState(lampTriggered)) {
        action = HIGH;
      }

      digitalWrite(lampSwitch, action);
      lampSwitch = -1;

      /**
       * DEBUG
       */
      Serial.print("'Lamp': ");
      Serial.print(lampTriggered, DEC);
      Serial.print(",");
      Serial.print("'ACTION': ");
      Serial.println(action, DEC);
    }
  }
}

bool switchSignalToBoolean(int signal)
{
  if (signal == HIGH) {
    return true;
  }

  return false;
}

bool switchLampState(int lamp)
{
  switch (lamp) {
    case 1:
      lampONE = !lampONE;
      return lampONE;
    case 2:
      lampTWO = !lampTWO;
      return lampTWO;
    case 3:
      lampTHREE = !lampTHREE;
      return lampTHREE;
    case 4:
      lampFOUR = !lampFOUR;
      return lampFOUR;
    case 5:
      lampFIVE = !lampFIVE;
      return lampFIVE;
    case 6:
      lampSIX = !lampSIX;
      return lampSIX;
    case 7:
      lampSEVEN = !lampSEVEN;
      return lampSEVEN;
    case 8:
      lampEIGHT = !lampEIGHT;
      return lampEIGHT;
  }
}

int readLampTriggered()
{
  if (Serial.available() > 0) {
    
    int in = Serial.read();
    
    if (in > -1) {

      /**
       * DEBUG
       */
      // Serial.print("Received: ");
      // Serial.println(in, DEC);
      // return 0;
          
      switch (in) {
        case 49:
          return 1;
        case 50:
          return 2;
        case 51:
          return 3;
        case 52:
          return 4;
        case 53:
          return 5;
        case 54:
          return 6;
        case 55:
          return 7;
        case 56:
          return 8;
        default:
          return 0;
      }
    }
    
  } else {
    return readLampTriggeredPin();
  }
  
  return 0;
}

int readLampTriggeredPin()
{
  bool pinY0 = switchSignalToBoolean(digitalRead(2));
  bool pinY1 = switchSignalToBoolean(digitalRead(3));
  bool pinY2 = switchSignalToBoolean(digitalRead(4));
  bool pinY3 = switchSignalToBoolean(digitalRead(5));

  // LAMPADA 8 (1000)
  if (pinY3) {
  
    return 8;
  
  } else {

    // LAMPADA 7 (0111)
    if (pinY2 && pinY1 && pinY0) {
      return 7;
    }

    // LAMPADA 6 (0110)
    if (pinY2 && pinY1 && !pinY0) {
      return 6;
    }

    // LAMPADA 5 (0101)
    if (pinY2 && !pinY1 && pinY0) {
      return 5;
    }

    // LAMPADA 4 (0100)
    if (pinY2 && !pinY1 && !pinY0) {
      return 4;
    }

    // LAMPADA 3 (0011)
    if (!pinY2 && pinY1 && pinY0) {
      return 3;
    }

    // LAMPADA 2 (0010)
    if (!pinY2 && pinY1 && !pinY0) {
      return 2;
    }

    // LAMPADA 1 (0001)
    if (!pinY2 && !pinY1 && pinY0) {
      return 1;
    }
  }

  return 0;
}

