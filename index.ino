#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

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

void setup() {
  Serial.begin(9600);
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erro ao iniciar o display OLED"));
    while (true)
      ;
  }

  OLED.clearDisplay();
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

void loop() {
  float umidade = 13;
  float temperatura = 25;

  OLED.clearDisplay();
  OLED.setTextColor(SSD1306_WHITE);

  exibirUmidade(umidade);
  exibirTemperatura(temperatura);

  OLED.display();
  delay(1000);
}
