// Song "Winter Wonderland"

// Arrays/Loops sind jeweils 2 Takte lang

prog_char drums1[32] PROGMEM =  { c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0};
prog_char drums2[32] PROGMEM =  { c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0};
prog_char drums3[32] PROGMEM =  { c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0};
prog_char drums4[32] PROGMEM =  { c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0, c4,0,0,c4, c5,0,0,0};
  
prog_char drums5[32] PROGMEM =  { c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5, c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5};
prog_char drums6[32] PROGMEM =  { c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5, c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5};
prog_char drums7[32] PROGMEM =  { c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5, c4,0,0,0,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5};
prog_char drums8[32] PROGMEM =  { c4,0,0,c4,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5, c4,0,0,c4,  c5,0,0,c5,  c4,0,0,c4, c5,0,0,c5};
prog_char* drums[8] PROGMEM = {  // drum map: kick = c4 - b4, snare = c5 - b5
  drums1,
  drums2,
  drums3,
  drums4,
  drums5,
  drums6,
  drums7,
  drums8,
};


prog_char rythm1[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 1+2
prog_char rythm2[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 3+4
prog_char rythm3[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; // bar 5+6
prog_char rythm4[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 7+8
  
prog_char rythm5[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; // bar 9+10
prog_char rythm6[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 10+12
prog_char rythm7[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 13+14
prog_char rythm8[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 15+16
prog_char* rhythm[8] PROGMEM  = {
  rythm1,
  rythm2,
  rythm3,
  rythm4,
  rythm5,
  rythm6,
  rythm7,
  rythm8,
};


prog_char bass1[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 1+2
prog_char bass2[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 3+4
prog_char bass3[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 5+6
prog_char bass4[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 7+8
   
prog_char bass5[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 9+10
prog_char bass6[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; //bar 11+12
prog_char bass7[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; // bar 13+14
prog_char bass8[32] PROGMEM =  {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}; // bar 15+16
prog_char* bass[8] PROGMEM = {
  bass1,
  bass2,
  bass3,
  bass4,
  bass5,
  bass6,
  bass7,
  bass8
};

prog_char lead1[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead2[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead3[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead4[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
   
prog_char lead5[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead6[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead7[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char lead8[32] PROGMEM = {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0};
prog_char* lead[8] PROGMEM = {
  lead1,
  lead2,
  lead3,
  lead4,
  lead5,
  lead6,
  lead7,
  lead8
};  
