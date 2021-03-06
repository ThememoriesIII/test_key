#include <LiquidCrystal_I2C.h>
#include <Key.h>
#include <Keypad.h>

String A ;
LiquidCrystal_I2C LCD1(0x3F,16,2);
int Buzzer = 11;

const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

volatile int couter=0;
volatile bool state=true;
volatile bool relay=false;
volatile int pin_relay=10;

//-------------------------------------------
void setup(){
  LCD1.begin();
  Serial.begin(9600);
  pinMode(Buzzer,OUTPUT);
  pinMode(pin_relay,OUTPUT);
  digitalWrite(Buzzer,HIGH); //  Off Buzzer 
  digitalWrite(pin_relay,HIGH);
  pinMode (11,OUTPUT);
  digitalWrite (11,HIGH);
}

//--------------------------------------------
void loop()
{
  state=true;
  
  LCD1.clear();
  LCD1.setCursor(0,1);
  if(relay==false)
  {
    digitalWrite(pin_relay,HIGH);
    LCD1.print("SAFE:LOCK");
  }
  else
  {
    digitalWrite(pin_relay,LOW);
    LCD1.print("SAFE:OPEN");
  }
  
  LCD1.setCursor(0,0);
  LCD1.print("PASS:");
  
  while(state==true)
  {
    char key;
    key = keypad.getKey();
  
     if(key != NO_KEY)
     {
      if(key!='A'&&key!='B'&&key!='C'&&key!='D'&&key!='#'&&key!='*'&&couter<4)
      {
        Beep();
        A+=key;
        couter++;  
        LCD1.print("*");
        Serial.println(A+String(couter));
      }
     }
     if(couter==4&&key=='#')
     {
      if(A=="0000")
      {
        relay=true;
      }
      else
      {
        if(A=="1111")
        {
          relay=false;
        }
      }
      A="";
      couter=0;
      state=false;
     }
  }
}
//----------------------------------------------
void Beep()
{
  digitalWrite(Buzzer,LOW);delay(50);
  digitalWrite(Buzzer,HIGH);
}

