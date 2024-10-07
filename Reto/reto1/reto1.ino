double ValorA0=0;
double ValorA1=0;
double ValorA2=0;
double ValorA3=0;

//vector<int> a;
void setup()
{
  Serial.begin(9600);
  //pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  float time=micros()/1e6;
  if (Serial.available()>0){
    double inpt=Serial.read();
    if (inpt=='g'){
      ValorA0= analogRead(A0);
      //ValorA1= analogRead(A1);
      double values[] = {ValorA0, ValorA1, ValorA2, ValorA3, 50};
      double V=((5*ValorA0))/1024;
      Serial.print(time);
      Serial.print(", ");
      Serial.print(V/0.01);
      Serial.print(", ");
      Serial.println(V/0.01);
      //Serial.println(V/0.01);


    //Serial.print("Hola");
      //Serial.println(',');
    
      //Serial.println(V*5);

    }

  }
 
 //
 //ValorA2= analogRead(A2);
 //ValorA3= analogRead(A3);

  
 
 //pene=values[:]*5

 
  
 //double Voltaje=(5*ValorA0)/1024;
 //double Valorgay=((Voltaje-0.5)/0.01);
  
 //Serial.println(Valorgay);

 //Serial.print(V);
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(1000); // Wait for 1000 millisecond(s)
  //digitalWrite(LED_BUILTIN, LOW);
  //delay(1000); // Wait for 1000 millisecond(s)
}