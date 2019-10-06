#include <DHT.h>
DHT dht(8, DHT11);

const int aDX=32, bDX=34, aSX=36, bSX=38;

const int toccoDX = 22;
const int toccoSX = 24;

const int pinElica = 28;


void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Motor test!");
  
dht.begin();

  pinMode(toccoDX, INPUT);
  pinMode(toccoSX, INPUT);

 Serial.println("Configuro i motori come spenti");
pinMode(aDX, OUTPUT);digitalWrite(aDX, 1);
pinMode(bDX, OUTPUT);digitalWrite(bDX, 1);

pinMode(aSX, OUTPUT);digitalWrite(aSX, 1);
pinMode(bSX, OUTPUT);digitalWrite(bSX, 1);

pinMode(pinElica, OUTPUT);   // andrò poi ad accendere elica

}


void loop() {  

  Serial.print("Tmp = ");
  Serial.println(dht.readTemperature());
  Serial.print("Hum = ");
  Serial.println(dht.readHumidity()); 

  if(dht.readHumidity() > 80){
    //il tagliaerba dovrebbe tornare in casa e comunque non partire
  }
 



  int buttonStateDX, buttonStateSX;
  buttonStateDX = digitalRead(toccoDX);
  buttonStateSX = digitalRead(toccoSX);

  /*Serial.println(buttonStateDX);
  Serial.println(buttonStateSX);*/

  digitalWrite(pinElica, 0); //accendi elica
 
  if (buttonStateDX == HIGH){
    //procedura di rotazione di qualche grado verso SX
    Serial.println("giro a sx");
    indietro();
    delay(3000);
    stopMarcia();
    
    bkSX();
    fwDX();
    delay(3000);
    stopMarcia();
  }
  if (buttonStateSX == HIGH){
    Serial.println("giro a dx");
    //procedura di rotazione di qualche grado verso DX    
    indietro();   
    delay(3000);    
    stopMarcia();    
    fwSX();
    bkDX();
    delay(3000);
    stopMarcia();
  }


dritto();
//stopMarcia();
}

void dritto(){
  //Serial.println("dritto");
  fwDX();
  fwSX();
}

void indietro(){
stopMarcia();
    delay(1000);
    bkDX();
    bkSX(); 
}




void giraDX(){
  
}


void bkDX(){
  digitalWrite(aDX, 0);
  digitalWrite(bDX, 1);
}

void bkSX(){
  digitalWrite(aSX, 0);
  digitalWrite(bSX, 1);
}

void fwDX(){
  digitalWrite(aDX, 1);
  digitalWrite(bDX, 0);
}

void fwSX(){
  digitalWrite(aSX, 1);
  digitalWrite(bSX, 0);
}

void stopDX(){
    digitalWrite(aDX, 1);
  digitalWrite(bDX, 1);
}
void stopSX(){
  digitalWrite(aSX, 1);
  digitalWrite(bSX, 1);
}

void stopMarcia(){
  Serial.println("Fermo la marcia");
  stopSX();stopDX();
}
