const int sensorPin = A0; // Pino analógico onde o LM35 está conectado
const float TEMPERATURA_LIMITE = 27.0; // Define o limite de temperatura em Celsius

void setup() {
  Serial.begin(9600); // Inicia a comunicação serial para exibir os resultados
}

void loop() {
  int valorADC = analogRead(sensorPin); // Lê o valor analógico do sensor (0-1023 para Arduino de 5V)

  // Converte o valor ADC para tensão (considerando 5V de referência e 1024 passos)
  // Voltagem = (valorADC * Tensão_Referência) / 1024
  float voltagem = (valorADC / 1023.0) * 5.0; // Tensão em Volts

  // Converte a tensão para temperatura em Celsius
  // O LM35 tem uma sensibilidade de 10mV/°C, ou seja, 0.01V/°C
  float temperaturaC = voltagem * 100.0; // Temperatura em °C

  Serial.print("Temperatura Atual: ");
  Serial.print(temperaturaC);
  Serial.println(" °C");

  // --- Lógica para verificar a temperatura ---
  if (temperaturaC < TEMPERATURA_LIMITE) {
    Serial.println(">>> TEMPERATURA ABAIXO DE 27°C <<<");
    // Você pode adicionar aqui alguma ação, como ligar um LED, acionar um relé, etc.
    // Ex: digitalWrite(LED_PIN, HIGH);
  } else {
    Serial.println("Temperatura igual ou acima de 27°C.");
    // Ex: digitalWrite(LED_PIN, LOW);
  }
  // --- Fim da lógica de verificação ---

  delay(2000); // Espera 2 segundos antes da próxima leitura para não sobrecarregar o monitor serial
}