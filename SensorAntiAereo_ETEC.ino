#include <Servo.h> // Puxa a biblioteca do Servo Motor
Servo Garra; //radar
Servo servoEixoX; //base
Servo servoMotor; //lazer

//lógica do radar
int pos = 0;
int direcao = 1;
bool travado = false;
int anguloAlvo = 0;
int original =0;

//pinos do radar
const int TRIG_PIN = 12;
const int ECHO_PIN = 11;

const int SERVO_PIN = 3;  //servo radar
const int BASE_PIN = 6;  // servo base
const int LAZER_PIN = 9; //servo lazer

const int LAZER = 4; //lazer

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN,INPUT);
  pinMode(LAZER,OUTPUT);

  Garra.attach(SERVO_PIN);
  servoEixoX.attach(BASE_PIN);
  servoMotor.attach(LAZER_PIN);

  original = lersensor(TRIG_PIN,ECHO_PIN);
  servoEixoX.write(0);

}

void loop()
{
    int diferente = lersensor(TRIG_PIN,ECHO_PIN);

  // Detectou algo
  if(diferente < 20 && !travado){
    travado = true;
    anguloAlvo = pos; // guarda o ândulo
  }
  
 if(diferente >= 20){
    travado = false;
  }
  // Se não travou, continua girando
  if(!travado){
    digitalWrite(LAZER, LOW);
    servoMotor.write(0);
    pos += direcao;

    if(pos >= 180 || pos <= 0){
      direcao *= -1;
    }

    Garra.write(pos);
    delay(30);
  }

  // Se travou, mantém no alvo
  else{
    Garra.write(anguloAlvo);

  Serial.println(anguloAlvo);
//  Move a base pro mesmo ângulo
    servoEixoX.write(anguloAlvo -30);
  
  delay(30);
  servoMotor.write(75);
  digitalWrite(LAZER, HIGH);

    
  }

 
  //Lógica que verifica se tem algo que não tinha antes

  if(abs(diferente != original) > 7){ //O 7 é a margem de erro
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
