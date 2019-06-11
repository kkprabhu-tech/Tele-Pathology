// MultiStepper.pde
// -*- mode: C++ -*-
//
// Shows how to multiple simultaneous steppers
// Runs one stepper forwards and backwards, accelerating and decelerating
// at the limits. Runs other steppers at the same time
//
// Copyright (C) 2009 Mike McCauley
// $Id: MultiStepper.pde,v 1.1 2011/01/05 01:51:01 mikem Exp mikem $

#include <AccelStepper.h>

// Define some steppers and the pins the will use
AccelStepper stepper_X (8, 2, 3, 4, 5); // Defaults to AccelStepper::FULL4WIRE (4 pins) on 2, 3, 4, 5
AccelStepper stepper_Y (8, 6, 7, 8, 9);
AccelStepper stepper_Z (8, 30, 32, 34, 36);

int lim_com = 50;
bool lim = HIGH;

int i = 0, j = 0;

int k = 1;

String str;

void setup()
{  
    stepper_X.setMaxSpeed(500);
    stepper_X.setAcceleration(100);
    stepper_X.moveTo(-1480);
    
    stepper_Y.setMaxSpeed(300);
    stepper_Y.setAcceleration(50);
    stepper_Y.moveTo(-460);
    
    stepper_Z.setMaxSpeed(1000);
    stepper_Z.setAcceleration(500);
    stepper_Z.moveTo(8000);

    Serial.begin(9600);

    pinMode(lim_com, INPUT_PULLUP);
}

void loop()
{
    // Change direction at the limits
//    if (stepper_X.distanceToGo() == 0)
//	stepper_X.moveTo(-stepper_X.currentPosition());
    stepper_X.run();
    stepper_Y.run();
    stepper_Z.run();

    //lim = digitalRead(lim_com);

    if(millis() > 10000 && millis() < 12000)  {
      stepper_X.disableOutputs();
      stepper_Y.disableOutputs();
      stepper_Z.disableOutputs();
    }

    while(Serial.available() > 0) {
      str = Serial.readString();

      if(str == "start\n") {
      
        stepper_X.move(270);
        stepper_X.run();

        stepper_Y.move(250);
        stepper_Y.run();

        k = 0;

//        Serial.println(stepper_X.isRunning());

//        delay(5000);

        
      }

      else if (str == "done\n") {
        //Serial.println("HEY");
        for(i; i<10; i++) {

          stepper_Y.move(100);
          stepper_Y.run();

          //Serial.println("Huuuu");

          if(j == 10) {
            j = 0;
          }

          if(i%2 == 0)  {
            for (j; j<10; j++)  {
              //Serial.println("Hwewy");
  
              if(j == 0) {
//                Serial.println("Hope");
                  stepper_X.move(100);
                  stepper_X.run();
                  
                  str = "no";
                  k = 0;
              }
  
              else  {
                if(Serial.available() > 0) {
                  str = Serial.readString();
                  if (str == "done\n") {
//                    Serial.println("Hurray");
                    stepper_X.move(100);
                    stepper_X.run();
                    
                    str = "no";
                    k = 0;
                  }
                }
                else {
                  j = j-1;
                  str = "no";
                }
              }
//              Serial.println(stepper_X.isRunning());

              if (stepper_X.isRunning() == 0)  {
//                Serial.println("my bad");
                for(k; k<1; k++)  {
                  delay(1000);
                  stepper_X.disableOutputs();
                  stepper_Y.disableOutputs();
                  stepper_Z.disableOutputs();
                  Serial.println("Click Picture Now");
                }
              }
            }
          }

          else  {
            for (j; j<10; j++)  {
              //Serial.println("Hwewy");
  
              if(j == 0) {
                Serial.println("brim");
                  stepper_X.move(-10);
                  stepper_X.run();
                  
                  str = "no";
                  k = 0;
              }
  
              else  {
                if(Serial.available() > 0) {
                  str = Serial.readString();
                  if (str == "done\n") {
                    Serial.println("raft");
                    stepper_X.move(-10);
                    stepper_X.run();
                    
                    str = "no";
                    k = 0;
                  }
                }
                else {
                  j = j-1;
                  str = "no";
                }
              }

              if (stepper_X.isRunning() == 0)  {
                for(k; k<1; k++)  {
                  delay(1000);
                  stepper_X.disableOutputs();
                  stepper_Y.disableOutputs();
                  stepper_Z.disableOutputs();
                  Serial.println("Click Picture Now");
                }
              }
            }
          }
        }
      }
    }

    if (stepper_X.isRunning() == 0)  {

      for(k; k<1; k++)  {
        delay(1000);
        stepper_X.disableOutputs();
        stepper_Y.disableOutputs();
        stepper_Z.disableOutputs();
        Serial.println("Click Picture Now");
      }
    }
//    Serial.println(stepper_X.isRunning());
}
