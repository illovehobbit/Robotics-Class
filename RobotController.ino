/**
 * Creator: Will Song '20
 * Last Edited Date: 31/10/2017
 * This is the code for a line-follower robot
 * going along a simple path with minimal
 * right or acute turns.
 */

/** Defined Words */
#define FORWARD 0
#define BACKWARD 1
#define MOTOR_A 0
#define MOTOR_B 1
#define DIRA 2
#define PWMA 3
#define DIRB 4
#define PWMB 11
#define LS1 A0
#define LS2 A1
#define LS3 A2

/** Variables */
int ls1Value;
int ls2Value;
int ls3Value;
int prevLS1Value;
int prevLS2Value;
int prevLS3Value;
int endQ;
int lowSpeed = 75;//set low speed to 75
int highSpeed = 150;//set high speed to 150
int superSpeed = 200;//set super speed to 200

/** Setup */
void setup() {
  
  //set all motor pins to output mode
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //set all light sensor pins to input mode
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);

  //set initial to low
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
}

/** Main Code */
void loop() {
  
  //assign light sensor values to the binary value of sensor input
  ls1Value = assignBinary(analogRead(LS1));
  ls2Value = assignBinary(analogRead(LS2));
  ls3Value = assignBinary(analogRead(LS3));
  
  //if light sensor 1 is Dark
  if (ls1Value == 0) {
    
    //if light sensor 2 is Dark
    if (ls2Value == 0) {
      
      //if light sensor 3 is Dark
      if (ls3Value == 0) {
        
        //stop driving both wheels
        stopDrive(MOTOR_A);
        stopDrive(MOTOR_B);
        
      //if light sensor 3 is Light
      } else if (ls3Value == 1) {
        
        //turn right slightly
        drive(MOTOR_A, BACKWARD, lowSpeed);
        drive(MOTOR_B, FORWARD, highSpeed);
      }
      
    //if both light sensor 2 and 3 are Light
    } else if (ls2Value == 1 && ls3Value == 1) {
      
      //turn right more
      drive(MOTOR_A, BACKWARD, lowSpeed);
      drive(MOTOR_B, FORWARD, superSpeed);
    }
    
  //if light sensor 1 is Light
  } else if (ls1Value == 1) {
    
    //if light sensor 2 is Light
    if (ls2Value == 1) {
      
      // if light sensor 3 is Light
      if (ls3Value == 1) {
        
      //if light sensor 3 is Dark
      } else if (ls3Value == 0) {

        //turn left more
        drive(MOTOR_A, FORWARD, superSpeed);
        drive(MOTOR_B, BACKWARD, lowSpeed);
      }
      
    //if light sensor 2 is Dark
    } else if (ls2Value == 0) {
      
      //if light sensor 3 is Dark
      if (ls3Value == 0) {
        
        //turn left slightly
        drive(MOTOR_A, FORWARD, highSpeed);
        drive(MOTOR_B, BACKWARD, lowSpeed);
        
      //if light sensor 3 is Light
      } else if (ls3Value == 1) {
        
        //go forward
        drive(MOTOR_A, FORWARD, 150);
        drive(MOTOR_B, FORWARD, 150);
      }
    }
  }
}

/** Drive indicated motor in the indicated direction and speed */
void drive(byte motor, byte dir, byte spd) {
  
  //if the indicated motor is motor A
  if (motor == MOTOR_A) {
    
    //write indicated direction and speed
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
    
  //if the indicated motor is motor B
  } else if (motor == MOTOR_B) {
    
    //write indicated direction and speed
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }
}

/** Stop driving indicated motor */
void stopDrive(byte motor) {
  
  drive(motor, 0, 0);
}

/** Takes an input value and returns a binary value of the input */
int assignBinary(int input) {
  
  if (input > 350) {
     
    //return 0 for Dark
    return 0;
  } else {
      
    //return 1 for Light
    return 1;//Light
  }
}

