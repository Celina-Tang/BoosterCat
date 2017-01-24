stats menu(stats cat){
  // Initialize Menu
  if (menu_init == 0){
    OrbitOledClear();
    OrbitOledMoveTo(50,0);
    OrbitOledDrawString("Menu");
    OrbitOledMoveTo(0,15);
    OrbitOledDrawString("Feed");
    OrbitOledMoveTo(45,15);
    OrbitOledDrawString("Pet");
    OrbitOledMoveTo(85,15);
    OrbitOledDrawString("Clean");

    OrbitOledMoveTo(UI_x,25);
    OrbitOledDrawChar('^');
    OrbitOledUpdate();
    menu_init ++;
  }

  // Moving the cursor to highlight the desired field
  if (RButtonState == LOW && UI_x < 95) {
    OrbitOledClear();
    OrbitOledMoveTo(50,0);
    OrbitOledDrawString("Menu");
    OrbitOledMoveTo(0,15);
    OrbitOledDrawString("Feed");
    OrbitOledMoveTo(45,15);
    OrbitOledDrawString("Pet");
    OrbitOledMoveTo(85,15);
    OrbitOledDrawString("Clean");

    UI_x += 45;
    OrbitOledMoveTo(UI_x,25);
    OrbitOledDrawChar('^');
    OrbitOledUpdate();
    delay(200);
  }
  else if(LButtonState == LOW && UI_x > 5) {
    OrbitOledClear();
    OrbitOledMoveTo(50,0);
    OrbitOledDrawString("Menu");
    OrbitOledMoveTo(0,15);
    OrbitOledDrawString("Feed");
    OrbitOledMoveTo(45,15);
    OrbitOledDrawString("Pet");
    OrbitOledMoveTo(85,15);
    OrbitOledDrawString("Clean");

    UI_x -= 45;
    OrbitOledMoveTo(UI_x,25);
    OrbitOledDrawChar('^');
    OrbitOledUpdate();
    delay(200);
  }

  // Selecting actions
  if(DButtonState == HIGH && UI_x == 5){
    cat = feed(cat);
  }
  else if (DButtonState == HIGH && UI_x ==50){
    cat = pet(cat);
  }
  else if (DButtonState == HIGH && UI_x == 95){
    cat = clean(cat);
  }
  return cat; 
}

//BoosterCat moves arbitrarily so that user know it's alive.
void moveCat(stats cat){
  delay(1000);
  OrbitOledClear();
  int x= rand()%73, y= rand()%10;
  OrbitOledMoveTo(x,y);
  if (!hunger&&!dirty&&!lonely) OrbitOledDrawString("(- w -)");
  else OrbitOledDrawString("(T w T)"); //it cries to alert status problem
  //This display the statuses of the BoosterCat. 
  char statusbar[20];
  snprintf(statusbar, 20, "F:%d H:%d C:%d ", cat.fullness, cat.happiness, cat.cleanliness);
  OrbitOledMoveTo(0,24);
  OrbitOledDrawString(statusbar);
  OrbitOledUpdate();  
}


