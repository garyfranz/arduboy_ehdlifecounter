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
static const unsigned int PLAYERSELECTION PROGMEM = 0;
static const unsigned int VALUESELECTION PROGMEM = 1;

//screen selections
static const unsigned int SEL_PLAYER1 PROGMEM = 0;
static const unsigned int SEL_PLAYER2 PROGMEM = 1;
static const unsigned int SEL_PLAYER3 PROGMEM = 2;
static const unsigned int SEL_PLAYER4 PROGMEM = 3;
static const unsigned int SEL_PLAYER5 PROGMEM = 4;
static const unsigned int SEL_PLAYER6 PROGMEM = 5;
static const unsigned int SEL_PLAYER7 PROGMEM = 6;
static const unsigned int SEL_PLAYER8 PROGMEM = 7;

static const unsigned int SEL_LIFE PROGMEM = 10;
static const unsigned int SEL_POISON PROGMEM = 11;
static const unsigned int SEL_COMMANDER1 PROGMEM = 12;
static const unsigned int SEL_COMMANDER2 PROGMEM = 13;
static const unsigned int SEL_COMMANDER3 PROGMEM = 14;
static const unsigned int SEL_COMMANDER4 PROGMEM = 15;
static const unsigned int SEL_COMMANDER5 PROGMEM = 16;
static const unsigned int SEL_COMMANDER6 PROGMEM = 17;
static const unsigned int SEL_COMMANDER7 PROGMEM = 18;
static const unsigned int SEL_COMMANDER8 PROGMEM = 19;

Arduboy2 arduboy;

unsigned int buttonAvailable;

unsigned int state;

unsigned int selectionPlayer;
unsigned int selectionValue;

unsigned int playerValues[8][10]; //[player][value]

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

  for (char w = 0; w < 8; w++) {
    for (char h = 0; h < 8; h++) {
      playerValues[w][h] = 0; //commander damage
    }
    playerValues[w][8] = 40; //life
    playerValues[w][9] = 0; //poison
  }

}

void draw() {

  //21x8 characters
  //=======================
  //=  P1   P2   P3   P4  =
  //=  P5   P6   P7   P8  =
  //=---------------------=
  //= Life-040  Poison-00 =
  //= Comm1-40  Comm2-40  =
  //= Comm3-40  Comm4-40  =
  //= Comm5-40  Comm6-40  =
  //= Comm7-40  Comm8-40  =
  //=======================

  //always draw top selection area
  arduboy.setCursor(12, 2); //2
  arduboy.print("P1");

  arduboy.setCursor(42, 2); //7
  arduboy.print("P2");

  arduboy.setCursor(72, 2); //12
  arduboy.print("P3");

  arduboy.setCursor(102, 2); //17
  arduboy.print("P4");

  arduboy.setCursor(12, 10); //2
  arduboy.print("P5");

  arduboy.setCursor(42, 10); //7
  arduboy.print("P6");

  arduboy.setCursor(72, 10); //12
  arduboy.print("P7");

  arduboy.setCursor(102, 10); //17
  arduboy.print("P8");

  arduboy.drawRect(0, 0, 128, 64, WHITE);
  arduboy.drawLine(0, 18, 128, 18, WHITE);
  arduboy.drawLine(0, 28, 128, 28, WHITE);
  
  switch (selectionPlayer) {
    case SEL_PLAYER1 :
      arduboy.setCursor(6, 2);
      break;
    case SEL_PLAYER2 :
      arduboy.setCursor(36, 2);
      break;
    case SEL_PLAYER3 :
      arduboy.setCursor(66, 2);
      break;
    case SEL_PLAYER4 :
      arduboy.setCursor(96, 2);
      break;
    case SEL_PLAYER5 :
      arduboy.setCursor(6, 10);
      break;
    case SEL_PLAYER6 :
      arduboy.setCursor(36, 10);
      break;
    case SEL_PLAYER7 :
      arduboy.setCursor(66, 10);
      break;
    case SEL_PLAYER8 :
      arduboy.setCursor(96, 10);
      break;
  } //state
  arduboy.print(">");


  arduboy.setCursor(12, 20);
  arduboy.print("Life-");
  arduboy.print(playerValues[selectionPlayer][8]);

  arduboy.setCursor(72, 20);
  arduboy.print("Poison-");
  arduboy.print(playerValues[selectionPlayer][9]);

  arduboy.setCursor(12, 30);
  arduboy.print("Cmdr1-");
  arduboy.print(playerValues[selectionPlayer][0]);

  arduboy.setCursor(72, 30);
  arduboy.print("Cmdr2-");
  arduboy.print(playerValues[selectionPlayer][1]);

  arduboy.setCursor(12, 38);
  arduboy.print("Cmdr3-");
  arduboy.print(playerValues[selectionPlayer][2]);

  arduboy.setCursor(72, 38);
  arduboy.print("Cmdr4-");
  arduboy.print(playerValues[selectionPlayer][3]);

  arduboy.setCursor(12, 46);
  arduboy.print("Cmdr5-");
  arduboy.print(playerValues[selectionPlayer][4]);

  arduboy.setCursor(72, 46);
  arduboy.print("Cmdr6-");
  arduboy.print(playerValues[selectionPlayer][5]);

  arduboy.setCursor(12, 54);
  arduboy.print("Cmdr7-");
  arduboy.print(playerValues[selectionPlayer][6]);

  arduboy.setCursor(72, 54);
  arduboy.print("Cmdr8-");
  arduboy.print(playerValues[selectionPlayer][7]);

  //21x8 characters
  //=======================
  //=  P1   P2   P3   P4  =
  //=  P5   P6   P7   P8  =
  //=---------------------=
  //= Life-040  Poison-00 =
  //= Comm1-40  Comm2-40  =
  //= Comm3-40  Comm4-40  =
  //= Comm5-40  Comm6-40  =
  //= Comm7-40  Comm8-40  =
  //=======================

  if (state == VALUESELECTION) {
    //draw middle selection
    

    switch (selectionValue) {
      case SEL_LIFE :
        arduboy.setCursor(6, 20);
        break;
      case SEL_POISON :
        arduboy.setCursor(66, 20);
        break;
      case SEL_COMMANDER1 :
        arduboy.setCursor(6, 30);
        break;
      case SEL_COMMANDER2 :
        arduboy.setCursor(66, 30);
        break;
      case SEL_COMMANDER3 :
        arduboy.setCursor(6, 38);
        break;
      case SEL_COMMANDER4 :
        arduboy.setCursor(66, 38);
        break;
      case SEL_COMMANDER5 :
        arduboy.setCursor(6, 46);
        break;
      case SEL_COMMANDER6 :
        arduboy.setCursor(66, 46);
        break;
      case SEL_COMMANDER7 :
        arduboy.setCursor(6, 54);
        break;
      case SEL_COMMANDER8 :
        arduboy.setCursor(66, 54);
        break;
    } //state
    arduboy.print(">");

  }

}


//===================================== LOOP =====================================
void loop() {

  if (!arduboy.nextFrame()) {
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
      if (selectionPlayer == SEL_PLAYER5) {
        selectionPlayer = SEL_PLAYER1;
      } else  if (selectionPlayer == SEL_PLAYER6) {
        selectionPlayer = SEL_PLAYER2;
      } else if (selectionPlayer == SEL_PLAYER7) {
        selectionPlayer = SEL_PLAYER3;
      } else if (selectionPlayer == SEL_PLAYER8) {
        selectionPlayer = SEL_PLAYER4;
      }
      break;

    case VALUESELECTION :
      if (selectionValue == SEL_COMMANDER1) {
        selectionValue = SEL_LIFE;
      } else  if (selectionValue == SEL_COMMANDER2) {
        selectionValue = SEL_POISON;
      } else  if (selectionValue == SEL_COMMANDER3) {
        selectionValue = SEL_COMMANDER1;
      } else if (selectionValue == SEL_COMMANDER5) {
        selectionValue = SEL_COMMANDER3;
      } else  if (selectionValue == SEL_COMMANDER7) {
        selectionValue = SEL_COMMANDER5;
      } else  if (selectionValue == SEL_COMMANDER4) {
        selectionValue = SEL_COMMANDER2;
      } else  if (selectionValue == SEL_COMMANDER6) {
        selectionValue = SEL_COMMANDER4;
      } else  if (selectionValue == SEL_COMMANDER8) {
        selectionValue = SEL_COMMANDER6;
      }

      break;
  } //state

}

void down() {

  switch (state) {
    case PLAYERSELECTION :
      if (selectionPlayer == SEL_PLAYER1) {
        selectionPlayer = SEL_PLAYER5;
      } else if (selectionPlayer == SEL_PLAYER2) {
        selectionPlayer = SEL_PLAYER6;
      } else if (selectionPlayer == SEL_PLAYER3) {
        selectionPlayer = SEL_PLAYER7;
      } else if (selectionPlayer == SEL_PLAYER4) {
        selectionPlayer = SEL_PLAYER8;
      }

      break;
      
    case VALUESELECTION :
      if (selectionValue == SEL_LIFE) {
        selectionValue = SEL_COMMANDER1;
      } else  if (selectionValue == SEL_POISON) {
        selectionValue = SEL_COMMANDER2;
      } else  if (selectionValue == SEL_COMMANDER1) {
        selectionValue = SEL_COMMANDER3;
      } else if (selectionValue == SEL_COMMANDER3) {
        selectionValue = SEL_COMMANDER5;
      } else  if (selectionValue == SEL_COMMANDER5) {
        selectionValue = SEL_COMMANDER7;
      } else  if (selectionValue == SEL_COMMANDER2) {
        selectionValue = SEL_COMMANDER4;
      } else  if (selectionValue == SEL_COMMANDER4) {
        selectionValue = SEL_COMMANDER6;
      } else  if (selectionValue == SEL_COMMANDER6) {
        selectionValue = SEL_COMMANDER8;
      }

      break;

  } //state

}

void left() {

  switch (state) {
    case PLAYERSELECTION :
      if (selectionPlayer == SEL_PLAYER2) {
        selectionPlayer = SEL_PLAYER1;
      } else if (selectionPlayer == SEL_PLAYER3) {
        selectionPlayer = SEL_PLAYER2;
      } else if (selectionPlayer == SEL_PLAYER4) {
        selectionPlayer = SEL_PLAYER3;
      } else if (selectionPlayer == SEL_PLAYER6) {
        selectionPlayer = SEL_PLAYER5;
      } else if (selectionPlayer == SEL_PLAYER7) {
        selectionPlayer = SEL_PLAYER6;
      } else if (selectionPlayer == SEL_PLAYER8) {
        selectionPlayer = SEL_PLAYER7;
      }

      break;
      
    case VALUESELECTION :
      if (selectionValue == SEL_POISON) {
        selectionValue = SEL_LIFE;
      } else  if (selectionValue == SEL_COMMANDER2) {
        selectionValue = SEL_COMMANDER1;
      } else if (selectionValue == SEL_COMMANDER4) {
        selectionValue = SEL_COMMANDER3;
      } else  if (selectionValue == SEL_COMMANDER6) {
        selectionValue = SEL_COMMANDER5;
      } else  if (selectionValue == SEL_COMMANDER8) {
        selectionValue = SEL_COMMANDER7;
      }

      break;

  } //state

}

void right() {

  switch (state) {
    case PLAYERSELECTION :
      if (selectionPlayer == SEL_PLAYER1) {
        selectionPlayer = SEL_PLAYER2;
      } else if (selectionPlayer == SEL_PLAYER2) {
        selectionPlayer = SEL_PLAYER3;
      } else if (selectionPlayer == SEL_PLAYER3) {
        selectionPlayer = SEL_PLAYER4;
      } else if (selectionPlayer == SEL_PLAYER5) {
        selectionPlayer = SEL_PLAYER6;
      } else if (selectionPlayer == SEL_PLAYER6) {
        selectionPlayer = SEL_PLAYER7;
      } else if (selectionPlayer == SEL_PLAYER7) {
        selectionPlayer = SEL_PLAYER8;
      }

      break;
      
    case VALUESELECTION :
      if (selectionValue == SEL_LIFE) {
        selectionValue = SEL_POISON;
      } else  if (selectionValue == SEL_COMMANDER1) {
        selectionValue = SEL_COMMANDER2;
      } else  if (selectionValue == SEL_COMMANDER3) {
        selectionValue = SEL_COMMANDER4;
      } else if (selectionValue == SEL_COMMANDER5) {
        selectionValue = SEL_COMMANDER6;
      } else  if (selectionValue == SEL_COMMANDER7) {
        selectionValue = SEL_COMMANDER8;
      }

      break;

  } //state

}

void a() {

  switch (state) {
    case PLAYERSELECTION :
      state = VALUESELECTION;
      break;
    case VALUESELECTION :

      break;

  } //state

}

void b() {

  switch (state) {
    case PLAYERSELECTION :
      //
      break;
    case VALUESELECTION :
      state = PLAYERSELECTION;
      break;

  } //state

}
