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
static const unsigned int ENTRYSELECTION PROGMEM = 2;

//screen selections
static const unsigned int SEL_PLAYER1 PROGMEM = 0;
static const unsigned int SEL_PLAYER2 PROGMEM = 1;
static const unsigned int SEL_PLAYER3 PROGMEM = 2;
static const unsigned int SEL_PLAYER4 PROGMEM = 3;
static const unsigned int SEL_PLAYER5 PROGMEM = 4;
static const unsigned int SEL_PLAYER6 PROGMEM = 5;
static const unsigned int SEL_PLAYER7 PROGMEM = 6;
static const unsigned int SEL_PLAYER8 PROGMEM = 7;

static const unsigned int SEL_LIFE PROGMEM = 8;
static const unsigned int SEL_POISON PROGMEM = 9;
static const unsigned int SEL_COMMANDER1 PROGMEM = 0;
static const unsigned int SEL_COMMANDER2 PROGMEM = 1;
static const unsigned int SEL_COMMANDER3 PROGMEM = 2;
static const unsigned int SEL_COMMANDER4 PROGMEM = 3;
static const unsigned int SEL_COMMANDER5 PROGMEM = 4;
static const unsigned int SEL_COMMANDER6 PROGMEM = 5;
static const unsigned int SEL_COMMANDER7 PROGMEM = 6;
static const unsigned int SEL_COMMANDER8 PROGMEM = 7;

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
    playerValues[w][SEL_LIFE] = 40; //life
    playerValues[w][SEL_POISON] = 0; //poison
  }

}

void draw() {

  //21x8 characters
  //=======================
  //= P1 P2 P3 P4 P5 P6 P7 P8  =
  //=    =
  //=---------------------=
  //= Life-040  Poison-00 =
  //= Comm1-40  Comm2-40  =
  //= Comm3-40  Comm4-40  =
  //= Comm5-40  Comm6-40  =
  //= Comm7-40  Comm8-40  =
  //=======================

  
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
  arduboy.setCursor(2, 2); 
  arduboy.print("P1");

  arduboy.setCursor(18, 2);
  arduboy.print("P2");

  arduboy.setCursor(34, 2); 
  arduboy.print("P3");

  arduboy.setCursor(50, 2);
  arduboy.print("P4");

  arduboy.setCursor(66, 2); 
  arduboy.print("P5");

  arduboy.setCursor(82, 2); 
  arduboy.print("P6");

  arduboy.setCursor(98, 2); 
  arduboy.print("P7");

  arduboy.setCursor(114, 2);
  arduboy.print("P8");

  //arduboy.drawRect(0, 0, 128, 64, WHITE);
  arduboy.drawLine(0, 10, 128, 10, WHITE);
  //arduboy.drawLine(0, 28, 128, 28, WHITE);
  
  switch (selectionPlayer) {
    case SEL_PLAYER1 :
      arduboy.drawRect(0, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER2 :
      arduboy.drawRect(16, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER3 :
      arduboy.drawRect(32, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER4 :
      arduboy.drawRect(48, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER5 :
      arduboy.drawRect(64, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER6 :
      arduboy.drawRect(80, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER7 :
      arduboy.drawRect(96, 0, 15, 11, WHITE);
      break;
    case SEL_PLAYER8 :
      arduboy.drawRect(112, 0, 15, 11, WHITE);
      break;
  } //state


  arduboy.setCursor(12, 14);
  arduboy.print("Life-");
  arduboy.print(playerValues[selectionPlayer][SEL_LIFE]);

  arduboy.setCursor(72, 14);
  arduboy.print("Poison-");
  arduboy.print(playerValues[selectionPlayer][SEL_POISON]);

  arduboy.setCursor(12, 24);
  arduboy.print("Cmdr1-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER1]);

  arduboy.setCursor(72, 24);
  arduboy.print("Cmdr2-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER2]);

  arduboy.setCursor(12, 34);
  arduboy.print("Cmdr3-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER3]);

  arduboy.setCursor(72, 34);
  arduboy.print("Cmdr4-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER4]);

  arduboy.setCursor(12, 44);
  arduboy.print("Cmdr5-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER5]);

  arduboy.setCursor(72, 44);
  arduboy.print("Cmdr6-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER6]);

  arduboy.setCursor(12, 54);
  arduboy.print("Cmdr7-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER7]);

  arduboy.setCursor(72, 54);
  arduboy.print("Cmdr8-");
  arduboy.print(playerValues[selectionPlayer][SEL_COMMANDER8]);

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
        arduboy.setCursor(6, 14);
        break;
      case SEL_POISON :
        arduboy.setCursor(66, 14);
        break;
      case SEL_COMMANDER1 :
        arduboy.setCursor(6, 24);
        break;
      case SEL_COMMANDER2 :
        arduboy.setCursor(66, 24);
        break;
      case SEL_COMMANDER3 :
        arduboy.setCursor(6, 34);
        break;
      case SEL_COMMANDER4 :
        arduboy.setCursor(66, 34);
        break;
      case SEL_COMMANDER5 :
        arduboy.setCursor(6, 44);
        break;
      case SEL_COMMANDER6 :
        arduboy.setCursor(66, 44);
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

  if (state == ENTRYSELECTION) {

    switch (selectionValue) {
      case SEL_LIFE :
        arduboy.setCursor(0, 14);
        break;
      case SEL_POISON :
        arduboy.setCursor(60, 14);
        break;
      case SEL_COMMANDER1 :
        arduboy.setCursor(0, 24);
        break;
      case SEL_COMMANDER2 :
        arduboy.setCursor(60, 24);
        break;
      case SEL_COMMANDER3 :
        arduboy.setCursor(0, 34);
        break;
      case SEL_COMMANDER4 :
        arduboy.setCursor(60, 34);
        break;
      case SEL_COMMANDER5 :
        arduboy.setCursor(0, 44);
        break;
      case SEL_COMMANDER6 :
        arduboy.setCursor(60, 44);
        break;
      case SEL_COMMANDER7 :
        arduboy.setCursor(0, 54);
        break;
      case SEL_COMMANDER8 :
        arduboy.setCursor(60, 54);
        break;
    } //state
    arduboy.print(">>");

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
      
    case ENTRYSELECTION :
      if (playerValues[selectionPlayer][selectionValue] = 999) {
        playerValues[selectionPlayer][selectionValue] = 999;
      } else {
        playerValues[selectionPlayer][selectionValue]++;
      }

      break;
  } //state

}

void down() {

  switch (state) {
    case PLAYERSELECTION :

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
      
    case ENTRYSELECTION :
      if (playerValues[selectionPlayer][selectionValue] <= 1) {
        playerValues[selectionPlayer][selectionValue] = 0;
      } else {
        playerValues[selectionPlayer][selectionValue]--;
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
      } else if (selectionPlayer == SEL_PLAYER5) {
        selectionPlayer = SEL_PLAYER4;
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
      
    case ENTRYSELECTION :
      if (playerValues[selectionPlayer][selectionValue] <= 5) {
        playerValues[selectionPlayer][selectionValue] = 0;
      } else {
        playerValues[selectionPlayer][selectionValue] = playerValues[selectionPlayer][selectionValue] - 5;
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
      } else if (selectionPlayer == SEL_PLAYER4) {
        selectionPlayer = SEL_PLAYER5;
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
      
    case ENTRYSELECTION :
      if (playerValues[selectionPlayer][selectionValue] + 5 > 999) {
        playerValues[selectionPlayer][selectionValue] = 999;
      } else {
        playerValues[selectionPlayer][selectionValue] = playerValues[selectionPlayer][selectionValue] + 5;
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
      state = ENTRYSELECTION;
      break;

  } //state

}

void b() {

  switch (state) {
    case VALUESELECTION :
      state = PLAYERSELECTION;
      break;
    case ENTRYSELECTION :
      state = VALUESELECTION;
      break;

  } //state

}
