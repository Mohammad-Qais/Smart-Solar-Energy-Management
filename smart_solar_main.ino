#include <LowPower.h>
#include <Servo.h>

Servo myServo;  // create a servo object

int pos;                // position variable for servo motor
int newpos;             // new position
int dir = 1;            // rotating direction
float current = 0; // measured current
float prev_current = 0; // previous current

void setup() {
  Serial.begin(9600);
  pinMode(9,OUTPUT);
  myServo.attach(9);
  delay(1000);
  pos = 90;
}

void loop() {
  myServo.write(pos); // begin at 90 degree position

  current = detect_current();

  if(current > 200){
    
    for(int j=0;j<20;j++){  //run tracking process with 20 movements
      if(pos > 180){  // to make sure angle remains in range of 0 - 180
          pos = 180;
        }
        else if(pos < 0){
          pos = 0;
        }
      current = detect_current();  //get the current at this moment
      
      Serial.print("Current : "); Serial.println(current);
      Serial.print("Prev cur : "); Serial.println(prev_current);
      delay(15);
      
      if(current > prev_current + 4){   //if the current has increased sigificantly
        for (int x = 0; x <= 18; x +=1){
          myServo.write(pos + x*dir);
          delay(20);
          Serial.print("X : ");Serial.println(pos + x*dir);
        }
        pos = pos + 18*dir;
        prev_current = current;
      }
    
      else if(current < prev_current - 4){    
        dir = -dir;
        for (int x = 0; x <= 18; x +=1){
          myServo.write(pos + x*dir);
          delay(20);
          Serial.print("X : ");Serial.println(pos+ x*dir);
        }
        pos = pos + 18*dir;
        prev_current = current;
      }
      Serial.print("pos : ");Serial.println(pos);

    }
  }
  // go to sleep for 112 * 8 seconds (~15 minutes) 
  // k<112;k++
  Serial.println("Sleeping");
  for(int k=0;k<112;k++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
