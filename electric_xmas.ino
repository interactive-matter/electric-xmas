/*

    Electric XMAS
    This work is licensed under a Creative Commons Attribution-NonCommercial 3.0 Germany License
    http://creativecommons.org/licenses/by-nc/3.0/de/deed.en_US
    
    (c) Bernd Krämer, Cream colored Ponies

*/

#include <Metro.h>

#include <avr/pgmspace.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/sleep.h>

/* Offene To Dos
 - An-/Aussschalt-/Stromspar-Logik implementieren
 - LED-Blinken einbauen
 - Widerstände für Kapazitätsmessung mit Marcus besprechen
 */

//Settings CapacitySensor
#include <CapacitiveSensor.h>
const int sensorPin1 = 2;
const int sensorPin2 = 8;
const int sensorPinC = 4;
const int capTreshold = 150;

CapacitiveSensor   C1 = CapacitiveSensor(sensorPinC,sensorPin1);  
CapacitiveSensor   C2 = CapacitiveSensor(sensorPinC,sensorPin2);  

unsigned int  C1Value = 0;
unsigned int  C2Value = 0;
boolean isC1Touched = false;
boolean isC2Touched = false;
boolean lastC1Touched = false;
boolean lastC2Touched = false;
unsigned int C1TouchedCount = 0;
unsigned int C2TouchedCount = 0;
unsigned int C1UntouchedCount = 0;
unsigned int C2UntouchedCount = 0;
boolean C1ClickedBefore = false;
boolean C2ClickedBefore = false;

//LED
const char led = 10;

Metro sleepMetro = Metro (240ul*60ul*1000ul);

//Settings Synthesizer
#include "the_synth.h"
unsigned int counter=0;
unsigned int twoBarLoop=0;
unsigned char sixteenths=0;
unsigned int  trackMute=1;
unsigned int leadMute=0;

boolean isKick = 1;
boolean leadSound = true;

// Convert MIDI-notes to int-values
#include "noteconverter.h";

// Settings Song
#include "musical_score.h";
int noteDrums;
int noteRhythm;
int noteLead;
int noteBass;

//comm btw int & main
char checkSensor = 0;

void setup() {
  power_all_disable();
  power_timer0_enable();
  power_timer1_enable();
  power_timer2_enable();
  for (char i=0; i<A5; i++) {
    pinMode(i,OUTPUT);
    if (i!=sensorPin1 && i!=sensorPin2 && i!=sensorPinC) 
      digitalWrite(i,LOW);
  }
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  pinMode(9,INPUT);
  digitalWrite(9,LOW);
  analogWrite(led,128);
  initSynth();
  sixteenths = 0;

  //Synthesizer sound settings
  setKickSound();
  setRhythmSound();
  setBassSound();
  setLeadSound(true);
  //  digitalWrite(10,LOW);
  startMusic();
  sleep_enable();
}


void loop() {

  int capacity1;
  int capacity2;  

  if (checkSensor) {
    checkSensor &= 3;
    //copy it over to remove the thread
    char sensor=checkSensor;
    if (sensor==1) {
      C1Value = getCapacity (&C1, &isC1Touched, &lastC1Touched, &C1TouchedCount, &C1UntouchedCount, &C1ClickedBefore, false);

      switch (C1Value) {
      case 1: // Bei Click
        trackMute = trackMute + 1;
        digitalWrite(led,HIGH);
        if (trackMute > 4) 
          trackMute = 1;
        break;
      }
    } 
    else if (sensor==2) {
      C2Value = getCapacity (&C2, &isC2Touched, &lastC2Touched, &C2TouchedCount, &C2UntouchedCount, &C2ClickedBefore, true );

      switch (C2Value) {
      case 1: // Bei Click
        if (leadMute == 0) {// Wenn beim Start alle Spuren gemutet sind, schaltet der erste Klick die Rhythmspur an.
          leadMute = 1;
          digitalWrite(led, LOW);
        }
        if (leadSound == true) {
          leadSound = false;
        }
        else {
          leadSound = true;
        }
        setLeadSound(leadSound);
        break;
      case 2: 
        setLeadSound(leadSound);
        break;
      case 3:
        setLeadSound2(leadSound);
        break;
      case 4:
        setLeadSound3(leadSound);
        break;
      case 5:
        setLeadSound4(leadSound);
        break;
      }
    }
    if (C1TouchedCount==0 && C1TouchedCount==0)
      analogWrite(led,0);
    else {
      analogWrite(led,180);    
      sleepMetro.reset();
    }
    if (sleepMetro.check()==1) {
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_cpu();
    }
  }

}

unsigned int average_c;

int getCapacity (CapacitiveSensor *sensor, boolean *touch, boolean *lastTouch, unsigned int *touchedCount, unsigned int *untouchedCount, boolean *clickedBefore, boolean holdEnabled) {

  int returnValue;
  int holdValue = 2;

  //Kapazität messen
  int c = sensor->capacitiveSensor(30);

  if (c > capTreshold ) {
    analogWrite(led,255);
    *touch = true; 
    *touchedCount = *touchedCount + 1;
    *untouchedCount = 0;

    if (*touchedCount > 2 && holdEnabled == true) { // = Hold
      //Gleitenden Mittelwert speichern
      average_c *= 3;  //15
      average_c += c;
      average_c >>= 2; //4
      int deviation = c-(int)average_c;
      deviation /= (int)average_c/10;
      deviation += 0;
      if (deviation > 5)
        deviation = 5;
      else if (deviation < 2)
        deviation = 2;

      returnValue = deviation; 
    } 
    else {
      //mittelwert initialisieren
      average_c = c;
    }
  }
  else { // Kapazität ist unter Schwellwert, Pflanze wird also nicht berührt.
    *touch = false;  

    if (*touchedCount > 0 && *touchedCount <= 2)   // Wenn sie gerade erst losgelassen wurde
      returnValue = 1; // = Click
    else 
      returnValue = 0;

    *touchedCount = 0;
    *untouchedCount = *untouchedCount + 1;
  }

  *lastTouch = *touch;

  return returnValue;
}

void setKickSound () {
  setup_voice(0,(unsigned int)SinTable,200.0,(unsigned int)Env0,0.25,500); 
}

void setSnareSound () {
  setup_voice(0,(unsigned int)NoiseTable,1.0,(unsigned int)Env1,0.3,2048); 
}

void setRhythmSound () {
  setup_voice(1,(unsigned int)SinTable,100.0,(unsigned int)Env0,0.15,4096); //rhythm  
}

void setBassSound () {
  setup_voice(2,(unsigned int)RampTable,1.0,(unsigned int)Env3,0.4,512); //bass
}

void setLeadSound (boolean myLeadSound) {
  if (myLeadSound == true)
    setup_voice(3,(unsigned int)SinTable,1.0,(unsigned int)Env1,1,500); 
  else
    setup_voice(3,(unsigned int)SawTable,1.0,(unsigned int)Env1,1,500); 

}

void setLeadSound1 (boolean myLeadSound) {
  if (myLeadSound == true)
    setup_voice(3,(unsigned int)SinTable,1.0,(unsigned int)Env1,2,550); 
  else
    setup_voice(3,(unsigned int)SawTable,1.0,(unsigned int)Env1,2,550); 

}

void setLeadSound2 (boolean myLeadSound) {
  if (myLeadSound == true)
    setup_voice(3,(unsigned int)TriangleTable,1.0,(unsigned int)Env1,4,700); 
  else
    setup_voice(3,(unsigned int)SawTable,1.0,(unsigned int)Env1,4,700); 

}

void setLeadSound3 (boolean myLeadSound) {
  if (myLeadSound == true)
    setup_voice(3,(unsigned int)TriangleTable,1.0,(unsigned int)Env2,8,500); 
  else
    setup_voice(3,(unsigned int)SquareTable,1.0,(unsigned int)Env2,8,500); 

}

void setLeadSound4 (boolean myLeadSound) {
  if (myLeadSound == true)
    setup_voice(3,(unsigned int)TriangleTable,1.0,(unsigned int)Env3,2,350); 
  else
    setup_voice(3,(unsigned int)SquareTable,1.0,(unsigned int)Env3,2,350); 
}


















