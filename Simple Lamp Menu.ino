#include <LiquidCrystal_I2C.h>
#include "Button.h"
#include "Settings.h"



#define POWER_BUTTON 10
#define UP_BUTTON 11
#define DOWN_BUTTON 12

#define YELLOW_LED 5
#define WHITE_LED 6
#define SIZEOF(x) sizeof(x)/sizeof(x[0])

#define TIME_5SEC 5000

MenuData menuData;

LiquidCrystal_I2C lcd(0x27,16,2);


Button select(POWER_BUTTON);
Button up(UP_BUTTON);
Button down(DOWN_BUTTON);

Button *buttons[] = {&select, &up, &down};
enum ButtonStates { SELECT, UP, DOWN};



void printScreen(){

      switch(menuData.index){
        case 0 :
        if(menuData.editMode){
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     POWER     ");
          lcd.setCursor(0,1);
          if(menuData.value[0] > 1) menuData.value[0] = 0;
          if(menuData.value[0] < 0) menuData.value[0] = 1;
          (menuData.value[0] > 0)  ? lcd.print("      OFF      ") : lcd.print("      ON      ");
          
        }else{
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     SELECT     ");
          lcd.setCursor(0,1);
          lcd.print("     POWER     ");
        }
        break;

        case 1:
        
        if(menuData.editMode){
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     COLOR     ");
          lcd.setCursor(0,1);
          if(menuData.value[1] > 1) menuData.value[1] = 0;
          if(menuData.value[1] < 0) menuData.value[1] = 1;
          menuData.value[1] > 0 ? lcd.print("     WHITE      ") : lcd.print("     YELLOW     ");
         
          lcd.print(menuData.value[1]);
        }else{
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     SELECT     ");
          lcd.setCursor(0,1);
          lcd.print("     COLOR     ");
        }
        break;

        case 2:
        
        if(menuData.editMode){
          String valueString = "";
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("   INTENSITY   ");
          lcd.setCursor(0,1);
          if(menuData.value[2] > 16) menuData.value[2] = 16;
          if(menuData.value[2] < 1) menuData.value[2] = 1;
          for(int i = 0; i< menuData.value[2]; i++) { valueString += (char)0xDB;};
          lcd.print(valueString);
          
         
          
        }else{
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     SELECT     ");
          lcd.setCursor(0,1);
          lcd.print("   INTENSITY   ");
        }
        break;

        case 3:
        
        if(menuData.editMode){
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("MADE BY:");
          lcd.setCursor(0,1);
          lcd.print("PETAR CHICHEV");
        }else{
          lcd.clear();
          lcd.backlight();
          lcd.setCursor(0,0);
          lcd.print("     SELECT     ");
          lcd.setCursor(0,1);
          lcd.print("      ABOUT     ");
        }
        break;


      }

}

void execute(){
  if(menuData.value[0] == 0){
   
    if( menuData.value[1] == 1){
      
      Serial.println();
      analogWrite(WHITE_LED,menuData.value[2] * (255/16));
      analogWrite(YELLOW_LED,0);
     
    }else{
     
      analogWrite(WHITE_LED,0);
      analogWrite(YELLOW_LED,menuData.value[2] * (255/16) );
      
    }
    
  }else{

    analogWrite(YELLOW_LED,0);
    analogWrite(WHITE_LED,0);

  }
}



void setup(){
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(WHITE_LED, OUTPUT);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  menuData.time = millis();
  menuData.value[0] = 0;
  menuData.value[1] = 1;
  menuData.value[2] = 16;
  menuData.index = 0;
  menuData.editMode = false;
  printScreen();
  execute();
  
}

void loop(){

if(menuData.time + TIME_5SEC < millis() ) lcd.noBacklight();

  for(int i = 0; i<SIZEOF(buttons); i++){

      if(buttons[i]->isClicked()){
        switch(i){
            case SELECT:
              
              menuData.editMode = !menuData.editMode;
              printScreen();
              
              //code
             
              while(buttons[i]->isClicked()){
                delay(20);
              }

              menuData.time = millis();
            break;
            case UP:
              

              if(menuData.editMode){
                menuData.value[menuData.index]++;
                printScreen();
                execute();
              }else{
                if(menuData.index < 3) menuData.index++;
                
                 printScreen();
              }
              

              
              //code
              delay(100);
              while(buttons[UP]->isClicked()){
                delay(20);
              }
              menuData.time = millis();
            break;
            case DOWN:
              

              if(menuData.editMode){
                menuData.value[menuData.index]--;
                printScreen();
                execute();
              }else{
                if(menuData.index > 0) menuData.index--;
                
                 printScreen();
              }
              
               
              //code
              delay(100);
              while(buttons[DOWN]->isClicked()){
                delay(100);
              }
              menuData.time = millis();

            break;
        }
      }
      
  };




}