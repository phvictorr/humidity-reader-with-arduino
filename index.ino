#include <Servo.h>

#define PINO_SERVO 3
#define PINO_BUZZER 5
#define LIMITE_INFERIOR 23
#define LIMITE_SUPERIOR 60



Servo servo;


int humidade = 0;

int posicao_servo = 0;
int velocidade_servo = 1;
int tempo_servo = velocidade_servo*10;

int intervalo_beep = (2000)/tempo_servo;  // para alterar o intervalo entre cada beep, altere apenas o valor entre parenteses
int contador_beep = intervalo_beep;

void setup() {
  
  servo.attach(PINO_SERVO);
  servo.write(posicao_servo);
  Serial.begin(9600);
 

}

void loop() {
  if (humidade < LIMITE_INFERIOR){
    // ativa o buzzer no com intervalo definido
    if (contador_beep == intervalo_beep){
      tone(PINO_BUZZER , 440, 500);
      contador_beep = 0;
    }
    contador_beep++;

    // coloca o motor na posicao de 90 graus
    while(posicao_servo < 90){
      posicao_servo = posicao_servo + velocidade_servo;
      servo.write(posicao_servo);
      delay(tempo_servo);
    }

  }else if(humidade > LIMITE_SUPERIOR){
    //coloca o motor na posicao de 0 graus
    while(posicao_servo > 0){
      posicao_servo = posicao_servo - velocidade_servo;
      servo.write(posicao_servo);
      delay(tempo_servo);
    }
  }

  Serial.print("humidade: ");
  Serial.println(humidade);

}
