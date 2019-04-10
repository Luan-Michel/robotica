#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 2, 0); // (dir, step) Defaults to AccelStepper::DRIVER (2 pins) on 2, 3

int fimCurso = 4;

int inicioCurso = 5;

int direcao = 1;

int passos = 200;

int voltas = 4;

int angulo = 90;

byte byteRead;

int contador = 0;

char n[5];

float passo_m5 = 0.8;

long pos = 0;

int MAX = 0, MIN=0;

int calculaPos(int mm)
{
  return stepper.currentPosition() + ((int)((float)(((float)(mm)/(float)passo_m5)*passos)));
}

void setup()
{

  Serial.begin(9600);
  
  stepper.setMaxSpeed(80);
  
  stepper.setAcceleration(50);

  pinMode(fimCurso, INPUT);

  pinMode(inicioCurso, INPUT);

  pos = calculaPos(300);

  stepper.moveTo(pos);

}

void loop()
{
  
  if (Serial.available())  //verifica se tem dados diponível para leitura
  {
      n[contador] = Serial.read();
      if(n[contador] == 'G'){
        Serial.read();
        Serial.println(contador);
        pos = (int)((float)(atoi(n))/((float)((float)360/(float)passos)));
        contador = 0;
      }else if(n[contador] == 'C'){
        Serial.read();
        Serial.println(contador);
        int temp = atoi(n);
        pos = calculaPos(temp);
        Serial.println(temp);
        Serial.println(pos);
        if(pos < MIN){
          pos = MIN;
        }
        if(pos > MAX){
          pos = MAX;
        }
        stepper.moveTo(pos);
        contador = 0;
      }else contador++;
      
  }

  if(digitalRead(fimCurso) == HIGH && MAX == 0){
    MAX = stepper.currentPosition();
    Serial.println(MAX);
    MAX = MAX - calculaPos(2);
    pos = calculaPos(-300);
    //stepper.runToNewPosition(MAX-2);
    //delay(20);
    stepper.moveTo(pos);
  }

  if(digitalRead(inicioCurso) == HIGH && MIN == 0){
    MIN = stepper.currentPosition();
    Serial.println(MIN);
    pos = calculaPos(2);
    stepper.stop();
    stepper.setMaxSpeed(600);
    MIN = pos;
    //stepper.runToNewPosition(MIN+2);
    stepper.moveTo(pos);
  }

  /*
  
  if (stepper.distanceToGo() == 0) {
  
  stepper.moveTo(passos * voltas / 2 * direcao);
  direcao *= -1;
  delay(500);
  }
  
  stepper.run();
  
  */
  
  
  
  
  //Serial.println(stepper.currentPosition());
  //stepper.runToNewPosition(pos);
  //pos += 3*direcao;
  //delay(1000);
  
  /*
  
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(angulo * passos / 360 / 2 * direcao);
    direcao *= -1;
    delay(500);
  }
  stepper.run();
  */
  /*
  if (stepper.distanceToGo() == 0) {
    stepper.moveTo(angulo * passos / 360);
    angulo += 6;
    delay(1000);
  }
  */
  stepper.run();
}
