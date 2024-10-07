#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <math.h>
#include <SoftwareSerial.h>


float te=24; //temperatura de encendido


LiquidCrystal_I2C lcd(0x27, 16, 2);


float r_25 = 9900.0;
float aa = 3.354017e-3;
float bb = 2.5617244e-4;
float cc = 2.1400943e-6;
float d = -7.2405219e-8; 

float tt[8]={1,1,1,1,1,1,1,1};
float V[8];
float V0[8];
float V1[8];
float denom[8];
float denom1[8];
float num[8];
float R[8];
float temp[8];

void r2t(float RR[],float g[]) {
   for (int i = 0; i < 8; i++) {
    float resistencia = RR[i];
    g[i]=(1/(aa + bb*log(resistencia/r_25) + cc*pow(log(resistencia/r_25),2) + d*pow(log(resistencia/r_25),3))-273.15);
   }
}

SoftwareSerial espSerial(5, 6); // RX, TX

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("TP:   Ton:   T1: ");
  // put your setup code here, to run once:
  Serial.begin(115200);
  espSerial.begin(115200); 
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  
}

void scal(float a, float b[],float c[]) {
  //float c[8]={1,1,1,1,1,1,1,1};
  for (int i = 0; i < 8; i++) {
    c[i] = a*b[i];
  }
}

void sum(float a, float b[],float c[]) {
  //float c[8]={1,1,1,1,1,1,1,1};
  for (int i = 0; i < 8; i++) {
    c[i] = b[i]+a;
  }
  //return c[8];
}

void mult(float a[], float b[],float c[]) {
  //float c[8]={1,1,1,1,1,1,1,1};
  for (int i = 0; i < 8; i++) {
    c[i] = b[i]*a[i];
  }
  //return c[8];
}


void pwr(float a, float b[], float c[]){
   for (int i = 0; i < 8; i++) {
    c[i] = pow(b[i],a);
  }
}


void dvs(float a[], float b[], float c[]){
   for (int i = 0; i < 8; i++) {
    c[i] = (a[i]/b[i]);
  }
}

void loop() {
  int inc = digitalRead(3);
  int dec = digitalRead(4);

  // Check if the increment button is pressed and the previous state was not pressed
  if (inc == HIGH) {
    // Increment the counter
    te++;
    inc=LOW;
  }
  if (dec == HIGH) {
    // Increment the counter
    te=te-1;
    //dec=LOW;
    //Serial.println(te);
    // Print the updated counter value to the serial monitor
    //Serial.println("Counter increased: " + String(counter));
  }

  
  // put your main code here, to run repeatedly:
  //pressure
  int s0 = analogRead(A0);
  int s1 = analogRead(A1);
  //Temperature
  int s2 = analogRead(A2);
  int s3 = analogRead(A3);
  int s6 = analogRead(A6);
  int s7 = analogRead(A7);

  float p1=map(s0,0,1024,40,120);
  float p2=map(s1,0,1024,150,350);

  float ss[8]={s2,s3,s6,s7,0,0,0,0};//////{t1,t2,t3,t4,t5}
  

  float jj[8]= {1024.0,1024.0,1024.0,1024.0,1024.0,1024.0,1024.0,1024.0};
  scal(5.0,ss,V); //float v = s0* (5.0/1024);
  dvs(V,jj,V0);
  scal(-1,V0,V1);  //float resistencia = (voltage * 10000)/(5 - voltage);
  sum(5.0,V1,denom);
  scal(r_25,V0,num); 
  dvs(num,denom,R);
  r2t(R,temp);

  temp[4]=random(5)+45;
  temp[5]=te-random(5);
  temp[6]=(te-random(3));
  temp[7]=random(5);


  float tp=(temp[0]+temp[1]+temp[2]+temp[3])/4;
  //digitalWrite(8,HIGH);

  if(round(tp-te)>2 && round(tp-te)<5){
    digitalWrite(7,HIGH);
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    
  }
  else if(round(tp-te)>=5){
    digitalWrite(8,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(9,HIGH);
    }

  else if((tp-te)<=-2){
    digitalWrite(7,LOW);
    digitalWrite(8,LOW);
    }
 
  else {
    //digitalWrite(7,LOW);
    //digitalWrite(8,LOW);
    //digitalWrite(9,LOW);
  }


  
  //scal(1000/5-)
  //scal(2.0,test,hola);
  //Serial.print(tp);
  //Serial.print(',');
  Serial.print(temp[0]);
  Serial.print(',');
  Serial.print(temp[1]);
  Serial.print(',');
  Serial.print(temp[2]);
  Serial.print(',');
  Serial.print(temp[3]);
  Serial.print(',');
  Serial.print(temp[4]);
  Serial.print(',');
  Serial.print(temp[5]);
  Serial.print(',');
  Serial.print(temp[6]);
  Serial.print(',');
  Serial.print(temp[7]);
  Serial.print(',');
  Serial.print(p1);
  Serial.print(',');
  Serial.println(p2);
 
  lcd.setCursor(0, 1);
  lcd.print(tp);

  lcd.setCursor(6, 1);
  lcd.print(te);

  lcd.setCursor(12, 1);
  lcd.print(temp[0]);
  
  //String kk= String(temp[0])+','+String(temp[1]);
  espSerial.print(temp[0]);
  espSerial.print(',');
  espSerial.print(temp[1]);
  espSerial.print(',');
  espSerial.print(temp[2]);
  espSerial.print(',');
  espSerial.print(temp[3]);
  espSerial.print(',');
  espSerial.print(temp[4]);
  espSerial.print(',');
  espSerial.print(temp[5]);
  espSerial.print(',');
  espSerial.print(temp[6]);
  espSerial.print(',');
  espSerial.print(temp[7]);
  espSerial.print(',');
  espSerial.print(p1);
  espSerial.print(',');
  espSerial.println(p2);
  //espSerial.println(kk);
  
  delay(3500);

 // float temp1 = r2t(resistencia);
  //temp2 = r2t(resistencia2);
  //Serial.println(temperatura);
}
