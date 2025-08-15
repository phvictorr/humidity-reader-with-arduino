#include <Servo.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define PINO_SERVO 3
#define PINO_BUZZER 5
#define LIMITE_INFERIOR 23
#define LIMITE_SUPERIOR 60

#define sensorTemp A3 // Pino analógico onde o LM35 está conectado
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
// Ícone de gota - 16x16
const unsigned char waterIcon[] PROGMEM = {
  0x00, 0x00, 0x18, 0x00, 0x14, 0x00, 0x24, 0x00, 0x22, 0x00, 0x42, 0x30, 0x42, 0x70, 0x22, 0x48,
  0x1c, 0x88, 0x00, 0x84, 0x01, 0x04, 0x01, 0x02, 0x01, 0x02, 0x01, 0x84, 0x00, 0xd8, 0x00, 0x20
};
// Ícone de termômetro - 16x16
const unsigned char PROGMEM termoIcon[] = {
  0x03, 0x00, 0x04, 0xb0, 0x04, 0x00, 0x04, 0x30, 0x04, 0x00, 0x04, 0x00, 0x07, 0x80, 0x07, 0x80,
  0x07, 0x80, 0x07, 0x80, 0x07, 0xc0, 0x0f, 0xe0, 0x0f, 0xe0, 0x0f, 0xe0, 0x07, 0xc0, 0x03, 0x80
};

Servo servo;

int valor_pot;
int humidade =0;
int posicao_servo = 0;
int velocidade_servo = 1;
int tempo_servo = velocidade_servo*10;
int intervalo_beep = (20)/tempo_servo;  // para alterar o intervalo entre cada beep, altere apenas o valor entre parenteses
int contador_beep = intervalo_beep;

const float TEMPERATURA_LIMITE = 27.0; // Define o limite de temperatura em Celsius


Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);



void setup() {
  
  servo.attach(PINO_SERVO);
  servo.write(posicao_servo);
  Serial.begin(9600);
  Serial.begin(9600);
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erro ao iniciar o display OLED"));
    while (true)
      ;
  }
  OLED.clearDisplay();
}

void loop() {
//alex
int valorADC = analogRead(sensorTemp); // Lê o valor analógico do sensor (0-1023 para Arduino de 5V)

  // Converte o valor ADC para tensão (considerando 5V de referência e 1024 passos)
  // Voltagem = (valorADC * Tensão_Referência) / 1024
  float voltagem = (valorADC / 1023.0) * 5.0; // Tensão em Volts

  // Converte a tensão para temperatura em Celsius
  // O LM35 tem uma sensibilidade de 10mV/°C, ou seja, 0.01V/°C
  float temperaturaC = voltagem * 100.0; // Temperatura em °C

// --- Lógica para verificar a temperatura ---
  if (temperaturaC < TEMPERATURA_LIMITE) {
    Serial.println(">>> TEMPERATURA ABAIXO DE 27°C <<<");
          tone(PINO_BUZZER , 600, 800);

  } else {
    Serial.println("Temperatura igual ou acima de 27°C.");
          tone(PINO_BUZZER , 200, 300);

  }
  // --- Fim da lógica de verificação ---

  delay(2000); // Espera 2 segundos antes da próxima leitura para não sobrecarregar o monitor serial

  // Elian Servo + buzzer
  if (humidade < LIMITE_INFERIOR){
    // ativa o buzzer no com intervalo definido
    Serial.print("contador beep:");
    Serial.println(contador_beep);
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

  // Display Mateus
  Serial.print("humidade: ");
  Serial.println(humidade);

 

  OLED.clearDisplay();
  OLED.setTextColor(SSD1306_WHITE);

  exibirUmidade(humidade);
  exibirTemperatura(temperaturaC);

  OLED.display();
  delay(1000);

}

// Função para exibir umidade com ícone
void exibirUmidade(float valor) {
  OLED.drawBitmap(0, 0, waterIcon, 16, 16, SSD1306_WHITE);
  OLED.setCursor(20, 4);
  OLED.setTextSize(1);
  OLED.print("Umidade: ");
  OLED.print(valor);
  OLED.println(" %");
}

// Função para exibir temperatura com ícone
void exibirTemperatura(float valor) {
  OLED.drawBitmap(0, 24, termoIcon, 16, 16, SSD1306_WHITE);
  OLED.setCursor(20, 28);
  OLED.setTextSize(1);
  OLED.print("Temp: ");
  OLED.print(valor);
  OLED.println(" C");
}
