#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

// Define o tamanho da tela e configura o display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  // Inicializa o display
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.begin(9600);
    Serial.println(F("Erro ao iniciar o display OLED"));
    while (true); // trava o programa
  }

  OLED.clearDisplay();
}

void loop() {
  float umidade = 13;
  float temperatura = 25;

  OLED.clearDisplay(); // limpa a tela a cada loop
  OLED.setTextSize(1);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setCursor(0, 0);

  OLED.print("UMIDADE: ");
  OLED.println(umidade);
  OLED.println();
  OLED.println();
  OLED.println();
  OLED.print("TEMP: ");
  OLED.println(temperatura);

  OLED.display(); // atualiza a tela
  delay(1000); // espera 1 segundo
}
