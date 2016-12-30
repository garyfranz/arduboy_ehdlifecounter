//====================================================================================
// EDH Life Counter
//  by Gary Franz
//
// This is a life counter application that can be used for EDH (Elder Dragon Highlander,
// also referred to as Commander) variant games of Magic the Gathering.
//
// v0.1.0 - Dec 30, 2016 - Initial Version
//
//====================================================================================

#include <Arduboy2.h>

//app states
static const unsigned char PLAYERSELECTION PROGMEM = 0;
static const unsigned char VALUESELECTION PROGMEM = 1;
static const unsigned char VALUEENTRY PROGMEM = 2;

//screen selections
static const unsigned char SEL_PLAYER1 PROGMEM = 1;   
static const unsigned char SEL_PLAYER2 PROGMEM = 2;   
static const unsigned char SEL_PLAYER3 PROGMEM = 3;   
static const unsigned char SEL_PLAYER4 PROGMEM = 4;   
static const unsigned char SEL_PLAYER5 PROGMEM = 5;   
static const unsigned char SEL_PLAYER6 PROGMEM = 7;   

static const unsigned char SEL_LIFE PROGMEM = 10;
static const unsigned char SEL_POISON PROGMEM = 11;
static const unsigned char SEL_EXPERIENCE PROGMEM = 12;
static const unsigned char SEL_COMMANDER1 PROGMEM = 13;
static const unsigned char SEL_COMMANDER2 PROGMEM = 14;
static const unsigned char SEL_COMMANDER3 PROGMEM = 15;
static const unsigned char SEL_COMMANDER4 PROGMEM = 16;
static const unsigned char SEL_COMMANDER5 PROGMEM = 17;
static const unsigned char SEL_COMMANDER6 PROGMEM = 18;

static const unsigned char SEL_TENS PROGMEM = 20;
static const unsigned char SEL_ONES PROGMEM = 21;

Arduboy2 arduboy;

unsigned char buttonAvailable;

unsigned char state;

unsigned char selectionPlayer;
unsigned char selectionValue;
unsigned char selectionDigit;

unsigned char lifeP1;
unsigned char lifeP2;
unsigned char lifeP3;
unsigned char lifeP4;
unsigned char lifeP5;
unsigned char lifeP6;

unsigned char poisonP1;
unsigned char poisonP2;
unsigned char poisonP3;
unsigned char poisonP4;
unsigned char poisonP5;
unsigned char poisonP6;

unsigned char expP1;
unsigned char expP2;
unsigned char expP3;
unsigned char expP4;
unsigned char expP5;
unsigned char expP6;

unsigned char cmddamP1_C1;
unsigned char cmddamP1_C2;
unsigned char cmddamP1_C3;
unsigned char cmddamP1_C4;
unsigned char cmddamP1_C5;
unsigned char cmddamP1_C6;

unsigned char cmddamP2_C1;
unsigned char cmddamP2_C2;
unsigned char cmddamP2_C3;
unsigned char cmddamP2_C4;
unsigned char cmddamP2_C5;
unsigned char cmddamP2_C6;

unsigned char cmddamP3_C1;
unsigned char cmddamP3_C2;
unsigned char cmddamP3_C3;
unsigned char cmddamP3_C4;
unsigned char cmddamP3_C5;
unsigned char cmddamP3_C6;

unsigned char cmddamP4_C1;
unsigned char cmddamP4_C2;
unsigned char cmddamP4_C3;
unsigned char cmddamP4_C4;
unsigned char cmddamP4_C5;
unsigned char cmddamP4_C6;

unsigned char cmddamP5_C1;
unsigned char cmddamP5_C2;
unsigned char cmddamP5_C3;
unsigned char cmddamP5_C4;
unsigned char cmddamP5_C5;
unsigned char cmddamP5_C6;

unsigned char cmddamP6_C1;
unsigned char cmddamP6_C2;
unsigned char cmddamP6_C3;
unsigned char cmddamP6_C4;
unsigned char cmddamP6_C5;
unsigned char cmddamP6_C6;

//===================================== SETUP =====================================
void setup() {

  arduboy.begin();
  arduboy.clear();

  arduboy.setFrameRate(10); //not sure if this is needed or should be different for this game
  
  //make sure we start out with buttons available to be pressed
  buttonAvailable = 1; 

  state = PLAYERSELECTION;

  reset();

}

void reset() {

selectionPlayer = SEL_PLAYER1;
selectionValue = SEL_LIFE;
selectionDigit = SEL_ONES;

lifeP1 = 40;
lifeP2 = 40;
lifeP3 = 40;
lifeP4 = 40;
lifeP5 = 40;
lifeP6 = 40;

poisonP1 = 0;
poisonP2 = 0;
poisonP3 = 0;
poisonP4 = 0;
poisonP5 = 0;
poisonP6 = 0;

expP1 = 0;
expP2 = 0;
expP3 = 0;
expP4 = 0;
expP5 = 0;
expP6 = 0;

cmddamP1_C1 = 0;
cmddamP1_C2 = 0;
cmddamP1_C3 = 0;
cmddamP1_C4 = 0;
cmddamP1_C5 = 0;
cmddamP1_C6 = 0;
cmddamP2_C1 = 0;
cmddamP2_C2 = 0;
cmddamP2_C3 = 0;
cmddamP2_C4 = 0;
cmddamP2_C5 = 0;
cmddamP2_C6 = 0;
cmddamP3_C1 = 0;
cmddamP3_C2 = 0;
cmddamP3_C3 = 0;
cmddamP3_C4 = 0;
cmddamP3_C5 = 0;
cmddamP3_C6 = 0;
cmddamP4_C1 = 0;
cmddamP4_C2 = 0;
cmddamP4_C3 = 0;
cmddamP4_C4 = 0;
cmddamP4_C5 = 0;
cmddamP4_C6 = 0;
cmddamP5_C1 = 0;
cmddamP5_C2 = 0;
cmddamP5_C3 = 0;
cmddamP5_C4 = 0;
cmddamP5_C5 = 0;
cmddamP5_C6 = 0;
cmddamP6_C1 = 0;
cmddamP6_C2 = 0;
cmddamP6_C3 = 0;
cmddamP6_C4 = 0;
cmddamP6_C5 = 0;
cmddamP6_C6 = 0;

}

void draw() {
  //21x8 characters
//=======================
//= P1-40  P2-40  P3-40 =  select first - use *      6,0
//= P4-40  P5-40  P6-40 =                            6,9
//----------------------=                            6,19
//= Lf-40  Po-00  Ex-00 =  select second - use *     6,21 
//= C1-00  C2-00  C3-00 =                            6,30
//= C4-00  C5-00  C6-00 =                            6,39
//----------------------=                            6,49
//= Set Value: 00       =  entry - use underline     6,51
//=======================

//always draw top selection area
arduboy.setCursor(6, 0);
arduboy.print("P1-");
arduboy.print(lifeP1);

arduboy.setCursor(54, 0);
arduboy.print("P2-");
arduboy.print(lifeP2);

arduboy.setCursor(96, 0);
arduboy.print("P3-");
arduboy.print(lifeP3);

arduboy.setCursor(6, 8);
arduboy.print("P4-");
arduboy.print(lifeP4);

arduboy.setCursor(54, 8);
arduboy.print("P5-");
arduboy.print(lifeP5);

arduboy.setCursor(96, 8);
arduboy.print("P6-");
arduboy.print(lifeP6);

arduboy.drawLine(0, 9, 0, 128, WHITE);

switch (selectionPlayer) {
    case SEL_PLAYER1 :
      arduboy.setCursor(0, 0);
      break;
    case SEL_PLAYER2 :
      arduboy.setCursor(48, 0);
      break;
    case SEL_PLAYER3 :
      arduboy.setCursor(90, 0);
      break;
    case SEL_PLAYER4 :
      arduboy.setCursor(0, 8);
      break;
    case SEL_PLAYER5 :
      arduboy.setCursor(48, 8);
      break;
    case SEL_PLAYER6 :
      arduboy.setCursor(90, 8);
      break;
  } //state
  arduboy.print(">");

if (state == VALUESELECTION || state == VALUEENTRY)
  //draw middle selection


  if (state == VALUEENTRY) {
    //draw value entry
  
  }
}


//===================================== LOOP =====================================
void loop() {

  if(!arduboy.nextFrame()) {
    return;
  }
  
  arduboy.clear();

    if (arduboy.pressed(UP_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      up();
    }
    if (arduboy.pressed(DOWN_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      down();
    }
    if (arduboy.pressed(LEFT_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      left();
    }
    if (arduboy.pressed(RIGHT_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      right();
    }
    if (arduboy.pressed(A_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      a();
    }
    if (arduboy.pressed(B_BUTTON) && buttonAvailable == 1) {
      buttonAvailable = 0;
      b();
    }

    draw();

    if (buttonAvailable == 0) {
    if (!arduboy.pressed(A_BUTTON) && !arduboy.pressed(B_BUTTON) && !arduboy.pressed(UP_BUTTON) && !arduboy.pressed(DOWN_BUTTON) && !arduboy.pressed(LEFT_BUTTON) && !arduboy.pressed(RIGHT_BUTTON)) {
      buttonAvailable = 1;
    }
  }

  arduboy.display();

}

//===================================== BUTTON HANDLING =====================================
void up() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}

void down() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}

void left() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}

void right() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}

void a() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}

void b() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      //
      break;
    case VALUEENTRY :
      //
      break;
  } //state

}
