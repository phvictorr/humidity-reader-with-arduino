#include <ESP8266WiFi.h>
#include <Servo.h>

// ===== DEFINIÇÕES DE PINOS =====
// Sensor de umidade do solo
#define UMIDADE_ANALOGICA A0    // Pino A0 para leitura analógica do sensor de umidade
#define UMIDADE_DIGITAL 4       // Pino 4 para leitura digital do sensor de umidade

// LED RGB
const int redPin = 1;           // Pino LED Vermelho
const int greenPin = 12;        // Pino LED Verde  
const int bluePin = 14;         // Pino LED Azul

// Buzzer e Servo
const int buzzerPin = 5;        // Pino do buzzer (corrigido conflito)
const int servoPin = 3;         // Pino do servo motor

// ===== CONSTANTES =====
#define LIMITE_INFERIOR 23
#define LIMITE_SUPERIOR 60

// ===== VARIÁVEIS GLOBAIS =====
// Sensor de umidade
int valorUmidade;               // Valor da umidade lida (analógica)
int valorUmidadeDigital;        // Valor digital do sensor de umidade

// Sensor LDR
int ldrValue = 0;               // Valor lido do LDR
int ldrMin = 1024;              // Valor mínimo do LDR
int ldrMax = 0;                 // Valor máximo do LDR

// Servo motor
Servo servo;
int posicaoServo = 0;
int velocidadeServo = 1;
int tempoServo = velocidadeServo * 10;

// Buzzer
int intervaloBeeep = (2000) / tempoServo;
int contadorBeep = intervaloBeeep;

void setup() {
  // Inicializa comunicação serial
  Serial.begin(9600);
  
  // Configura pinos do sensor de umidade
  pinMode(UMIDADE_ANALOGICA, INPUT);
  pinMode(UMIDADE_DIGITAL, INPUT);
  
  // Configura pinos do LED RGB
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Configura buzzer
  pinMode(buzzerPin, OUTPUT);
  
  // Inicializa servo motor
  servo.attach(servoPin);
  servo.write(posicaoServo);
  
  // Inicia com LED desligado
  setColor(0, 0, 0);
  
  Serial.println("Sistema iniciado!");
}

void loop() {
  // ===== LEITURA DO SENSOR DE UMIDADE =====
  valorUmidade = analogRead(UMIDADE_ANALOGICA);
  valorUmidade = constrain(valorUmidade, 315, 1023);
  valorUmidade = map(valorUmidade, 1023, 315, 0, 100);
  
  Serial.print("Umidade encontrada: ");
  Serial.print(valorUmidade);
  Serial.println(" %");
  
  valorUmidadeDigital = digitalRead(UMIDADE_DIGITAL);
  
  if (valorUmidadeDigital == 0) {
    Serial.println("Status: Solo úmido");
  } else {
    Serial.println("Status: Solo seco");
  }
  
  // ===== LEITURA DO SENSOR LDR =====
  ldrValue = analogRead(A0);  // Usando A0 compartilhado (pode ser alternado)
  
  Serial.print("Valor lido pelo LDR = ");
  Serial.println(ldrValue);
  
  // ===== CONTROLE DO LED RGB BASEADO NA LUMINOSIDADE =====
  if (ldrValue <= 500) {
    // Noite (escuro) - Azul claro
    setColor(100, 200, 255);
    noTone(buzzerPin);
  } 
  else if (ldrValue >= 950) {
    // Luminosidade intensa - Vermelho piscante
    setColor(255, 0, 0);
    tone(buzzerPin, 1000);
    delay(500);
    setColor(0, 0, 0);
    delay(500);
  } 
  else {
    // Luminosidade média - Verde
    setColor(0, 255, 0);
    noTone(buzzerPin);
  }
  
  // ===== CONTROLE DO SERVO BASEADO NA UMIDADE =====
  if (valorUmidade < LIMITE_INFERIOR) {
    // Solo muito seco - ativa buzzer e move servo para 90°
    if (contadorBeep >= intervaloBeeep) {
      tone(buzzerPin, 440, 500);
      contadorBeep = 0;
    }
    contadorBeep++;
    
    // Move servo para 90 graus
    while (posicaoServo < 90) {
      posicaoServo += velocidadeServo;
      servo.write(posicaoServo);
      delay(tempoServo);
    }
  } 
  else if (valorUmidade > LIMITE_SUPERIOR) {
    // Solo muito úmido - move servo para 0°
    while (posicaoServo > 0) {
      posicaoServo -= velocidadeServo;
      servo.write(posicaoServo);
      delay(tempoServo);
    }
  }
  
  Serial.print("Posição do servo: ");
  Serial.println(posicaoServo);
  Serial.println("-------------------");
  
  delay(500);
}

// ===== FUNÇÕES AUXILIARES =====
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

void calibrateLDR() {
  Serial.println("Calibrando LDR...");
  Serial.println("Exponha o LDR a diferentes condições de luz");
  
  for (int i = 0; i < 100; i++) {
    ldrValue = analogRead(A0);
    
    if (ldrValue < ldrMin) {
      ldrMin = ldrValue;
    }
    
    if (ldrValue > ldrMax) {
      ldrMax = ldrValue;
    }
    
    delay(10);
  }
  
  Serial.print("LDR Min: ");
  Serial.println(ldrMin);
  Serial.print("LDR Max: ");
  Serial.println(ldrMax);
}