#include <Servo.h>

#define p_servo 3
#define buzzer 5
#define LIMITE_INFERIOR 23
#define LIMITE_SUPERIOR 60

#define potenciometro A0


Servo servo;


int valor_pot = 0;
int pos = 0;
int humidade = 24;
int velocidade = 1;
int tempo_motor = velocidade*10;
int intervalo_beep = 2000/tempo_motor;
int beep = intervalo_beep;

void setup() {
  
  servo.attach(p_servo);
  servo.write(pos);
  Serial.begin(9600);
 

}

void loop() {
  // put your main code here, to run repeatedly:
  valor_pot = analogRead(potenciometro);
  humidade = map(valor_pot, 0, 1003,0,100);

  if (humidade < LIMITE_INFERIOR){
    // ativa o buzzer no com intervalo definido
    if (beep== intervalo_beep){
      tone(buzzer,440,500);
      beep=0;
    }
    beep++;

    // coloca o motor na posicao de 90 graus
    while(pos<90){
      pos = pos + velocidade;
      servo.write(pos);
      delay(tempo_motor);
    }

  

  }else if(humidade > LIMITE_SUPERIOR){
    //coloca o motor na posicao de 0 graus
    while(pos>0){
      pos = pos - velocidade;
      servo.write(pos);
      delay(tempo_motor);
    }
  }

  Serial.print("humidade: ");
  Serial.println(humidade);

}
