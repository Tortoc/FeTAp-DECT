#include <Wire.h>
#include <Adafruit_MCP23017.h>

Adafruit_MCP23017 mcp;
Adafruit_MCP23017 mcp1;
 
const int w_pin1 = 11;
const int w_pin2 = 10;
const int g_pin = 9;

int w1_state = 0;
int w1_last_state = 0;
int w2_state = 0;
int w2_last_state = 1;

int g_state = 0;
int g_last_state = 0;

int counter = 0;

void setup() {
  Serial.begin(9600);
  mcp.begin(0);
  mcp1.begin(1);
  configurePinsWithPinMode();
  configureMCP1pinMode();
  
  pinMode(w_pin1, INPUT);
  pinMode(w_pin2, INPUT);
}

void loop() {
  //SERIAL CONSOLE INPUT - START
  while(Serial.available()){
    String a = Serial.readString();
    a = a.substring(0,1);
    Serial.println(">"+a+"<");
    checkSerialInput(a);
  }
  //SERIAL CONSOLE INPUT - END

  //BUTTON INPUT - START
  checkDigitalInput();
  //BUTTON INPUT - END
  
  //GABEL READ - START
  g_state = digitalRead(g_pin);
  if(g_state != g_last_state){
    if(g_state == HIGH){
      //Serial.println("ABGENOMMEN");
      delay(40);
      toggleMCP(4);
    }
    if(g_state == LOW){
      //Serial.println("AUFGELEGT");
      delay(40);
      toggleMCP(3);
    }
  }
  g_last_state = g_state;
  //GABEL READ - END
 
  // WÄHLSCHEIBE READ - START
  w1_state = digitalRead(w_pin1);  
  if(w1_state != w1_last_state){
    if(w1_state == LOW){
      if(counter == 10){
        counter = 0;
      }
      Serial.println(counter);
      switch(counter){
        case 1:
            toggleMCP(6);
            break;
        case 2:  
            toggleMCP(7);
            break;
        case 3:  
            toggleMCP(15);
            break;
        case 4:  
            toggleMCP(14);
            break;
        case 5:  
            toggleMCP(13);
            break;
        case 6:  
            toggleMCP(12);
            break;
        case 7:  
            toggleMCP(11);
            break;
        case 8:  
            toggleMCP(10);
            break;
        case 9:  
            toggleMCP(8);
            break;
        case 0:  
            toggleMCP(9);
            break;
      }
      counter = 0;
    }
    delay(40); //debounce
    w1_last_state = w1_state;
  }

  w2_state = digitalRead(w_pin2);  
  if(w2_state != w2_last_state){
    if(w2_state == HIGH){
      counter++;
    }
    delay(40); //debounce
    w2_last_state = w2_state;
  }
  // WÄHLSCHEIBE READ - END
}

void checkDigitalInput(){
  /* 
   * 8  - L
   * 9  - R
   * 10 - U
   * 11 - A
   * 12 - H
   * 13 - D
   * 14 - *
   * 15 - #
   */

  if(mcp1.digitalRead(8) == HIGH){
    delay(100);
    toggleMCP(1);
  }
  if(mcp1.digitalRead(9) == HIGH){
    delay(100);
    toggleMCP(0);
  }
  if(mcp1.digitalRead(10) == HIGH){
    delay(100);
    toggleMCP(2);
  }
  if(mcp1.digitalRead(11) == HIGH){
    delay(100);
    toggleMCP(4);
  }
  if(mcp1.digitalRead(12) == HIGH){
    delay(100);
    toggleMCP(3);
  }
  if(mcp1.digitalRead(13) == HIGH){
    delay(100);
    toggleMCP(5);
  }
  if(mcp1.digitalRead(14) == HIGH){
    delay(100);
    toggleMCP1(0);
  }
  if(mcp1.digitalRead(15) == HIGH){
    delay(100);
    toggleMCP1(1);
  }
}

void checkSerialInput(String a){
  if(a.equals("*")){
      toggleMCP1(0);
  }
  if(a.equals("0")){
      toggleMCP(9);
  }
  if(a.equals("#")){
      toggleMCP1(1);
  }
  if(a.equals("7")){
      toggleMCP(11);
  }
  if(a.equals("8")){
      toggleMCP(10);
  }
  if(a.equals("9")){
      toggleMCP(8);
  }
  if(a.equals("4")){
      toggleMCP(14);
  }
  if(a.equals("5")){
      toggleMCP(13);
  }
  if(a.equals("6")){
      toggleMCP(12);
  }
  if(a.equals("1")){
      toggleMCP(6);
  }
  if(a.equals("2")){
      toggleMCP(7);
  }
  if(a.equals("3")){
      toggleMCP(15);
  }
  if(a.equals("A")){ //ABHEBEN
      toggleMCP(4);
  }
  if(a.equals("H")){ //AUFLEGEN
      toggleMCP(3);
  }
  if(a.equals("U")){
      toggleMCP(2);
  }
  if(a.equals("D")){
      toggleMCP(5);
  }
  if(a.equals("L")){
      toggleMCP(1);
  }
  if(a.equals("R")){
      toggleMCP(0);
  }
}

void toggleMCP(int number){
  mcp.digitalWrite(number,HIGH);
  delay(100);
  mcp.digitalWrite(number,LOW);
}

void toggleMCP1(int number){
  mcp1.digitalWrite(number,HIGH);
  delay(100);
  mcp1.digitalWrite(number,LOW);
}

void configurePinsWithPinMode() {
  for(byte i = 0; i<16; i++){
    mcp.pinMode(i, OUTPUT);
  } 
}

void configureMCP1pinMode(){
  mcp1.pinMode(0,OUTPUT);
  mcp1.pinMode(1,OUTPUT);

  mcp1.pinMode(8,INPUT);
  mcp1.pinMode(9,INPUT);
  mcp1.pinMode(10,INPUT);
  mcp1.pinMode(11,INPUT);
  mcp1.pinMode(12,INPUT);
  mcp1.pinMode(13,INPUT);
  mcp1.pinMode(14,INPUT);
  mcp1.pinMode(15,INPUT);
}
