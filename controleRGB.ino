/*
 * ======================================================================
 * Projeto de Sinalização com LED RGB e Wemos D1 R1
 * VERSÃO AJUSTADA PARA LED DE ANODO COMUM
 * Data: 04 de Julho de 2025
 * ======================================================================
 *
 * Descrição:
 * Controla a cor de um LED RGB com base em um valor de porcentagem simulado
 * e exibe o status em uma função dedicada.
 * - Abaixo de 23%: Vermelho
 * - Entre 23% e 50%: Amarelo
 * - Acima de 50%: Roxo
 *
 * Conexões Físicas na Placa Wemos D1 R1 (Formato Uno):
 * - Pino FÍSICO D11 (MOSI) -> Resistor 180Ω -> Pino Vermelho (R) do LED
 * - Pino FÍSICO D12 (MISO) -> Resistor 180Ω -> Pino Verde (G) do LED
 * - Pino FÍSICO D13 (SCK)  -> Resistor 180Ω -> Pino Azul (B) do LED
 * - Pino 3.3V             -> Anodo Comum do LED (pino mais longo)
 */

// Define as constantes dos pinos que serão utilizados no CÓDIGO.
const int PINO_VERMELHO = D7; // D7 corresponde ao pino físico D11 (GPIO13)
const int PINO_VERDE    = D6; // D6 corresponde ao pino físico D12 (GPIO12)
const int PINO_AZUL     = D5; // D5 corresponde ao pino físico D13 (GPIO14)

void setup() {
  // Configura os pinos do LED RGB como saídas (OUTPUT).
  pinMode(PINO_VERMELHO, OUTPUT);
  pinMode(PINO_VERDE, OUTPUT);
  pinMode(PINO_AZUL, OUTPUT);

  // Inicia a comunicação serial.
  Serial.begin(115200);
}

void loop() {
  // Simula um valor de porcentagem.
  int porcentagem = random(0, 101);

  // Chama a nova função para exibir a porcentagem no terminal
  exibirPorcentagem(porcentagem);

  // Estrutura condicional para definir a cor do LED.
  if (porcentagem < 23) {
    definirCor(255, 0, 0); 
  } 
  else if (porcentagem <= 50) {
    definirCor(240, 50, 0); 
  } 
  else {
    definirCor(128, 0, 128);
  }
  
  // Aguarda 2 segundos antes de gerar um novo valor.
  delay(2000);
}

/**
 * @brief Exibe o valor da porcentagem e o status da cor no Monitor Serial.
 * @param p O valor da porcentagem a ser exibido.
 */
void exibirPorcentagem(int p) {
  Serial.print("Porcentagem atual: ");
  Serial.print(p);
  Serial.println("%");

  // Adiciona a lógica de texto também para a função de exibição
  if (p < 23) {
    Serial.println("Status: Nível baixo. Cor: Vermelho");
  } 
  else if (p <= 50) {
    Serial.println("Status: Nível médio. Cor: Amarelo");
  } 
  else {
    Serial.println("Status: Nível alto. Cor: Roxo");
  }
  Serial.println("--------------------");
}

/**
 * @brief Função para definir a cor do LED RGB (ANODO COMUM).
 * @param valorVermelho Intensidade da cor vermelha (0-255).
 * @param valorVerde Intensidade da cor verde (0-255).
 * @param valorAzul Intensidade da cor azul (0-255).
 */
void definirCor(int valorVermelho, int valorVerde, int valorAzul) {
  // Para Anodo Comum, a lógica é invertida (0 = brilho máximo, 255 = apagado).
  analogWrite(PINO_VERMELHO, 255 - valorVermelho);
  analogWrite(PINO_VERDE,    255 - valorVerde);
  analogWrite(PINO_AZUL,     255 - valorAzul);
}