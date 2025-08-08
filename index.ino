#define umidadeAnalogica A0 //Atribui o pino A0 à variável umidade - leitura analógica do sensor
#define umidadeDigital 4 //Atribui o pino 13 à variável umidadeDigital - leitura digital do sensor
#include <ESP8266WiFi.h>

int valorumidade; // Variável que armazenará o valor da umidade lida - saída analógica
int valorumidadeDigital; // Variável que armazenará a saída digital do sensor de umidade do solo

// Definição dos pinos
const int ldrPin = A0;       // Pino do LDR
const int redPin = 1;       // Pino LED Vermelho
const int greenPin = 12;     // Pino LED Verde
const int bluePin = 14;      // Pino LED Azul
const int buzzerPin = D8;    // Pino do buzzer 

// Variáveis
int ldrValue = 0;           // Valor lido do LDR
int ldrMin = 1024;          // Valor mínimo do LDR (ajustar conforme necessário)
int ldrMax = 0;             // Valor máximo do LDR (ajustar conforme necessário)
int valorldr = 0;//Declara a variável valorldr como inteiro

void setup() {
  // Elian sensor umidade
  Serial.begin(9600); // Inicia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); // Define umidadeAnalogica como entrada
  pinMode(umidadeDigital, INPUT); // Define umidadeDigital como entrada

  // Diego
  Serial.begin(19200);
  
  // Configura os pinos do LED RGB como saída
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ldrPin, INPUT);


  // Inicia com o LED desligado
  setColor(0, 0, 0);
  //Dados
}

void loop() {
  valorumidade = analogRead(umidadeAnalogica); // Leitura analógica
  valorumidade = constrain(valorumidade, 315, 1023); // Limita o valor dentro do intervalo esperado
  valorumidade = map(valorumidade, 1023, 315, 0, 100); // Converte para escala de 0 a 100

  Serial.print("Umidade encontrada: ");
  Serial.print(valorumidade);
  Serial.println(" %");

  valorumidadeDigital = digitalRead(umidadeDigital); // Leitura digital

  if (valorumidadeDigital == 0) {
    Serial.println("Status: Solo úmido");
    // digitalWrite(LedVermelho, LOW);
    // digitalWrite(LedVerde, HIGH);
  } else {
    Serial.println("Status: Solo seco");
    // digitalWrite(LedVermelho, HIGH);
    // digitalWrite(LedVerde, LOW);
  }

  delay(500); // Atraso de 500ms

  // DIEGO

  delay(500);
  Serial.println("123");
  ldrValue = analogRead(ldrPin);

  
  // Lógica de controle do LED RGB
  if (ldrValue <= 500) { // Noite (escuro)
    setColor(100, 200,255); // Laranja
    noTone(buzzerPin);
  } 
  else if (ldrValue >= 950) { // Luminosidade intensa (máxima)
    setColor(0, 255,255); // Vermelho
    tone(buzzerPin, 1000); // Emite tom de 1kHz
    delay(500); // Espera 0.5s
    setColor(255, 255,255);
    delay(500); // Espera 0.5s
  } 
    else if (ldrValue >= 501 <= 950) { // Luminosidade intensa (media)
    setColor(0,125,0); // branco
    tone(buzzerPin, 1000); // Emite tom de 1kHz
    
  } 
  
  delay(100); // Pequena pausa entre leituras

   valorldr=analogRead(ldrPin);//Lê o valor do sensor ldr e armazena na variável valorldr
   Serial.print("Valor lido pelo LDR = ");//Imprime na serial a mensagem Valor lido pelo LDR
   Serial.println(valorldr);//Imprime na serial os dados de valorldr
}

// Função para definir a cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

// Função para calibrar os valores mínimo e máximo do LDR (opcional)
void calibrateLDR() {
  Serial.println("Calibrando LDR...");
  Serial.println("Exponha o LDR a diferentes condições de luz");
  
  for (int i = 0; i < 100; i++) {
    ldrValue = analogRead(ldrPin);
    
    if (ldrValue < ldrMin) {
      ldrMin = ldrValue;
    }
    
    if (ldrValue > ldrMax) {
      ldrMax = ldrValue;
    }
    
    delay(10);
  }
  
 
}
