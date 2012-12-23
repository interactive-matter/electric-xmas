/*

    Electric XMAS
    This work is licensed under a Creative Commons Attribution-NonCommercial 3.0 Germany License
    http://creativecommons.org/licenses/by-nc/3.0/de/deed.en_US
    
    (c) Bernd Krämer, Cream colored Ponies; Marcus Nowotny, Interactive Matter

*/

#include <avr/interrupt.h>
#include <avr/io.h>

void startMusic() {
  TCCR2B = 0x00;        //Disbale Timer2 while we set it up
  TCNT2  = 130;         //Reset Timer Count to 130 out of 255
  TIFR2  = 0x00;        //Timer2 INT Flag Reg: Clear Timer Overflow Flag
  TIMSK2 = 0x01;        //Timer2 INT Reg: Timer2 Overflow Interrupt Enable
  TCCR2A = 0x00;        //Timer2 Control Reg A: Wave Gen Mode normal
  TCCR2B = 0x06;        //Timer2 Control Reg B: Timer Prescaler set to 128  
}

ISR(TIMER2_OVF_vect) {
  if(synthTick()) {

    sixteenths = counter&0x1F;

    uint16_t rhythm_addr = pgm_read_word(&(rhythm[twoBarLoop-1]));
    noteRhythm =  pgm_read_byte(rhythm_addr+sixteenths);

    if (trackMute==2 || trackMute==3) {
      uint16_t drums_addr = pgm_read_word(&(drums[twoBarLoop-1]));
      noteDrums =  pgm_read_byte(drums_addr+sixteenths);
    }

    if (trackMute==3 || trackMute==4) {
      uint16_t bass_addr = pgm_read_word(&(bass[twoBarLoop-1]));
      noteBass =  pgm_read_byte(bass_addr+sixteenths);
    }

    if (leadMute==1) {
      uint16_t lead_addr = pgm_read_word(&(lead[twoBarLoop-1]));
      noteLead =  pgm_read_byte(lead_addr+sixteenths);
    }
    if (noteDrums > 0) {

      if (noteDrums >= c4 && noteDrums <= b4) { //Wenn Kickdrum getriggert wird
        if (!isKick) // Kicksound eingestellt?
          setKickSound(); // Sound auf Kickdrum umschalten              
        isKick = 1;
      };

      if (noteDrums >= c5 && noteDrums <= c9) { //Wenn Snaredrum getriggert wird 
        if (isKick) // Kicksound eingestellt?
          setSnareSound(); // Dann Sound auf Snaredrum umschalten             
        isKick = 0;
      };

      mtrigger(0, noteDrums);            

    };

    if (noteRhythm > 0)
      mtrigger(1, noteRhythm + 24); 

    if (noteBass > 0)
      mtrigger(2, noteBass + 24);

    if (noteLead) {
    analogWrite(led,64);
      mtrigger(3, noteLead + 36);
    }

    noteBass = 0;
    noteDrums = 0;
    noteLead = 0;
    noteRhythm = 0;

    tim=0;
    counter++;
    if (sixteenths==0) twoBarLoop++;
    if (twoBarLoop==9) twoBarLoop = 1;
    //tell the sensor to check the value
    checkSensor++;
  }
};






