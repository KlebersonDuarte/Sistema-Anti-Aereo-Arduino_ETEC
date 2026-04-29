#include <Servo.h> // Puxa a biblioteca do Servo Motor
Servo Garra; 

int original =0;
void setup()
{
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(11,INPUT);
Garra.attach(3);
  original = lersensor(12,11);


}

void loop()
{
  //Gira o motor em 180°
    for(int i = 0;i <=180;i++){
     Garra.write(i);
	delay(30);
      }
  
  //Gira o motor em -180°
  for(int j= 180; j>=0;j--){
  Garra.write(j);
   delay(30);
    }
  
  //Lógica que verifica se tem algo que não tinha antes
  //não ser se tá funcionando, pois não deu para testar
  int diferente = lersensor(12,11);
  if((diferente != original) > 7){ //O 7 é a margem de erro
  Serial.print("Tem algo novo ai");
  }
  
}

//Função do sensor ultrassoônico que detecta os objetos
int lersensor(int pinotring, int pinoecho){
 digitalWrite(pinotring,LOW);
    delay(2);
    digitalWrite(pinotring,HIGH);
    delay(10);
    digitalWrite(pinotring,LOW);
    return pulseIn(pinoecho,HIGH)/ 58;
}