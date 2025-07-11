#define umidadeAnalogica A0 //Atribui o pino A0 à variável umidade - leitura analógica do sensor
#define umidadeDigital 4 //Atribui o pino 13 à variável umidadeDigital - leitura digital do sensor

int valorumidade; // Variável que armazenará o valor da umidade lida - saída analógica
int valorumidadeDigital; // Variável que armazenará a saída digital do sensor de umidade do solo

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial
  pinMode(umidadeAnalogica, INPUT); // Define umidadeAnalogica como entrada
  pinMode(umidadeDigital, INPUT); // Define umidadeDigital como entrada
} // <-- Esta chave estava faltando

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
}
