#include <Servo.h>

Servo servohori; //horizontal servo(BOTTOM SERVO)
int servoh = 0; //assign servo at 0 degree
int servohLimitHigh = 180; //maximum range of servo is 180 degree(it is variable you can also change)
int servohLimitLow = 0;   //minimum range of servo is 10 degree(it is variable you can also change)

Servo servoverti; //vertical servo(TOP SERVO) 
int servov = 0; 
int servovLimitHigh = 115;
int servovLimitLow = 65;

int sensorRight = A0; // select the input pin for LDR
int sensorRightValue = 0; // variable to store the value coming from the sensor

int sensorTop = A2; // select the input pin for LDR
int sensorTopValue = 0; // variable to store the value coming from the sensor

int sensorButtom = A1; // select the input pin for LDR
int sensorButtomValue = 0; // variable to store the value coming from the sensor

int sensorLeft = A3; // select the input pin for LDR
int sensorLeftValue = 0; // variable to store the value coming from the sensor

int pos = 0;    // variable to store the servo position
int sensitivity = 1;
int sampling = 1;
char val = ' ';
char valtemp = ' ';
int led1 = 9;
int led2 = 8;

void setup() {
  servohori.attach(6);  // attaches the servo on pin 9 to the servo object
  servoverti.attach(7); 
  Serial.begin(9600); //sets serial port for communication
  servoverti.write(90);
  servohori.write(90);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
} 

void loop() 
{
  if (Serial.available() > 0) 
  { 
   val = Serial.read(); 
   if (val == '1')
   {
    while(true)
    { 
    sensorRightValue = AverageSample(sensorRightValue, sensorRight, sampling);
    sensorTopValue = AverageSample(sensorTopValue, sensorTop, sampling);
    sensorButtomValue = AverageSample(sensorButtomValue, sensorButtom, sampling);
    sensorLeftValue = AverageSample(sensorLeftValue, sensorLeft, sampling);
    
    //Reading Motors Angles
    servov = servoverti.read();  
    servoh = servohori.read();
     //Value of Top Sensor is Greater and Buttom Sensor
    if (sensorTopValue > sensorButtomValue)
    {
      if (servov < servovLimitLow) 
      { 
       servov = servovLimitLow;
      }
      servov=servov-sensitivity;
      servoverti.write(servov);
      //Serial.print("Vertical Angle: ");
      Serial.print(servov);
      Serial.print("|");
      
      //Left and Right Movement
      if (sensorLeftValue > sensorRightValue)
      {      
        if (servoh > servohLimitHigh-45) 
        { 
        servoh = servohLimitHigh-45;
        }
        servoh=servoh+sensitivity;
        servohori.write(servoh);
        //Serial.print("Horizontal Angle: ");
        Serial.print(servoh);
        Serial.print("|");
      }
      else if (sensorRightValue > sensorLeftValue)
      {
        if (servoh < servohLimitLow+45)
      {
        servoh = servohLimitLow+45;
      }
        servoh=servoh-sensitivity;
        servohori.write(servoh);
        //Serial.print("Horizontal Angle: ");
        Serial.print(servoh);
        Serial.print("|");  
      }
      
       delay(8);
      }
  
   //Value of Top Sensor is Less and Buttom Sensor
    if (sensorTopValue < sensorButtomValue)
    {
      if (servov > servovLimitHigh) 
      { 
       servov = servovLimitHigh;
      }
      servov=servov+sensitivity;
      servoverti.write(servov);
      //Serial.print("Vertical Angle: ");
      Serial.print(servov);
      Serial.print("|");
  
      //Left and Right Movement
      if (sensorLeftValue < sensorRightValue)
      {
        if (servoh > servohLimitHigh-45) 
        { 
        servoh = servohLimitHigh-45;
        }
        servoh=servoh+sensitivity;
        servohori.write(servoh);
        //Serial.print("Horizontal Angle: ");
        Serial.print(servoh);
        Serial.print("|");
  
      }
      else if (sensorRightValue < sensorLeftValue)
      {
        if (servoh < servohLimitLow+45)
      {
        servoh = servohLimitLow+45;
      }
        servoh=servoh-sensitivity;
        servohori.write(servoh);
        //Serial.print("Horizontal Angle: ");
        Serial.print(servoh);
        Serial.print("|");
      }    
       delay(8);
      }    
      print();
      Serial.print("\n"); //prints the values coming from the sensor on the screens
      delay(100);

      if (Serial.available() > 0) {  // check if data is available
        char incomingByte = Serial.read();  // read the incoming byte
        if (incomingByte == '2') {  // if the byte is '0'
          break;  // exit the loop
        }
      }
    }
  }

  if (val == '3')
  {
    servoverti.write(90);    
    servohori.write(90);
  }

  if (val == '4')
  {
    digitalWrite(led1, HIGH); // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, HIGH); // turn the LED on (HIGH is the voltage level)
  }

  else if (val == '5')
  {
    digitalWrite(led1, LOW); // turn the LED on (HIGH is the voltage level)
    digitalWrite(led2, LOW); // turn the LED on (HIGH is the voltage level)
  }
}
}

void sensorReadWithText(int sensor, int value)
{
  value = analogRead(sensor); // read the value from the sensor
  Serial.print(value); //prints the values coming from the sensor on the screen
  Serial.print("|"); //prints the values coming from the sensor on the screen
}

int sensorRead(int sensor, int value)
{
  value = analogRead(sensor); // read the value from the sensor
  return value;
}

void print()
{
  //Serial.print("Right Sensor:");
  sensorReadWithText(sensorRight,sensorRightValue);
  //Serial.print("Left Sensor:");
  sensorReadWithText(sensorLeft,sensorLeftValue);
  //Serial.print("Top Sensor:");
  sensorReadWithText(sensorTop,sensorTopValue);
  //Serial.print("Buttom Sensor:");
  sensorReadWithText(sensorButtom,sensorButtomValue);
}

int AverageSample(int value, int sensor, int sampSize)
{
  int average = 0;
  for(int i = 0; i <= sampSize; i++)
    {
      value = analogRead(sensor);
      average = average + value; // read the value from the sensor
      delay(5);
    }
  return average/sampSize;
}
