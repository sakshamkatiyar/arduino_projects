#include <RFID.h>

/*
* Read a card using a mfrc522 reader on your SPI interface
* Pin layout should be as follows (on Arduino Uno):
* MOSI: Pin 11 / ICSP-4
* MISO: Pin 12 / ICSP-1
* SCK: Pin 13 / ISCP-3
* SS/SDA: Pin 10
* RST: Pin 9
*/

#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9


RFID rfid(SS_PIN,RST_PIN);
int pizflag=0;
int relaysafety=2;
int relay = 6;
int buzzer = 7;
int serNum[5];
int thresh = 400;
int cards[][5] = {
  {144,34,90,168,64}
  
};

bool access = false;

void setup(){

    Serial.begin(9600);
    SPI.begin();
    rfid.init();
    
    pinMode(relaysafety, OUTPUT);
    pinMode(relay, OUTPUT);
    pinMode(A1, INPUT);
    pinMode(buzzer,OUTPUT);
//    pinMode()
    //digitalWrite(relaysafety,HIGH);
   
}

void loop(){
//    analogWrite(relay, 0);/
    if(rfid.isCard()){
    
        if(rfid.readCardSerial()){
            Serial.print(rfid.serNum[0]);
            Serial.print(" ");
            Serial.print(rfid.serNum[1]);
            Serial.print(" ");
            Serial.print(rfid.serNum[2]);
            Serial.print(" ");
            Serial.print(rfid.serNum[3]);
            Serial.print(" ");
            Serial.print(rfid.serNum[4]);
            Serial.println("");
            
            for(int x = 0; x < sizeof(cards); x++){
              for(int i = 0; i < sizeof(rfid.serNum); i++ ){
                  if(rfid.serNum[i] != cards[x][i]) {
                      access = false;
                      break;
                  } else {
                      access = true;
                  }
              }
              if(access) break;
            }
           
        }
        
       if(access){
          Serial.println("Welcome!");
           digitalWrite(relay, HIGH);
      } else {
           Serial.println("Not allowed!"); 
           digitalWrite(buzzer, HIGH);
       }        
    }
    else{
      digitalWrite(relay, LOW);
    }
    
    rfid.halt();

//    pizo
    int pizval=analogRead(A1);
    Serial.println(pizval);
    
//    for(int pizval=10;pizval<170;pizval++)
    if(pizval>thresh && pizflag==0){
      
      digitalWrite(relaysafety, HIGH);
      delay(1000);
      pizflag=1;
    }
//    else{
//      digitalWrite(relay, LOW);
//    }

 
digitalWrite(buzzer, LOW);
 }


