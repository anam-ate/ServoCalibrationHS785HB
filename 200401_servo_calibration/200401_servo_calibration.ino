int servoMax = 2200;              // Maximum position for servo  //1150
int servoMin = 800;               // Minimum position for servo  // 595
//1850  1000
int servoPin = 6;                // servo connected to this digital pin 6

int servoCurrentPos;              // Current position of the servo (in pulselength)
int servoGotoPos;                 // Goto position - servo will move towards this position

int servoSpeed = 1;               // current position will change by this value every pulse

long servoStartTime;              // Starting time for this script
long servoLastPulse;              // the time in milliseconds of the last pulse
//left


// RIGHT 
//START = 1075
//END  = 1800


//LEFT
//START = 1575
//END = 800
/**
   Setup this servo.
   Call this once when the arduino starts (in setup())
*/
void setup()
{
  Serial.begin(19200);
  pinMode(servoPin, OUTPUT);

  servoCurrentPos = 1500; // go to start position
  servoGotoPos = 1500; // go to start position
 
}


void loop()
{
  if (Serial.available() > 4) {
    servoGotoPos = Serial.parseInt();
    if (servoGotoPos < servoMin) servoGotoPos = servoMin;
    if (servoGotoPos > servoMax) servoGotoPos = servoMax;
  }

  // we check if we need to increment the current position
  if (servoCurrentPos < servoGotoPos)
  {
    // check if it would overshoot
    if (servoCurrentPos + servoSpeed > servoGotoPos)
    {
      servoCurrentPos = servoGotoPos;
    }
    else
    {
      servoCurrentPos += servoSpeed;
    }
  }

  // we check if we need to increment the current position
  else if (servoCurrentPos > servoGotoPos)
  {
    // check if it would overshoot
    if (servoCurrentPos - servoSpeed < servoGotoPos)
    {
      servoCurrentPos = servoGotoPos;
    }
    else
    {
      servoCurrentPos -= servoSpeed;
    }
  }

  // make sure the current position is not more or less than min or max
  if (servoCurrentPos > servoMax)
  {
    servoCurrentPos = servoMax;
  }
  else if (servoCurrentPos < servoMin)
  {
    servoCurrentPos = servoMin;
  }

  Serial.print("PosV: ");
  Serial.print(servoCurrentPos);
  Serial.print(" - GotoPosV ");
  Serial.print(servoGotoPos);
  Serial.println();

  long t = millis();
  if (t - servoLastPulse >= 20)
  {
    servoLastPulse = t;
    // now we have to actually set the goto position on the servo
    digitalWrite(servoPin, HIGH);               // Turn the motor on
    delayMicroseconds(servoCurrentPos);         // Length of the pulse sets the motor position
    digitalWrite(servoPin, LOW);                // Turn the motor off
  }
}
