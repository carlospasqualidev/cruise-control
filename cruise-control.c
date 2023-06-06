// Variáveis globais
float v = 0;  // velocidade atual
float u[] = {100, 110, 100, 90};  // vetor de valores de entrada u[n]
int uIndex = 0;  // índice atual do vetor de valores de entrada u[n]
unsigned long previousTimeVelocity = 0;  // variável para controle do tempo para velocidade
unsigned long previousTimeSample = 0;  // variável para controle do tempo para coleta da amostra
unsigned long interval = 50;  // intervalo de tempo entre as atualizações, em milissegundos

// Função para gerar ruído randômico com amplitude de 0.05
float generateRandomNoise() {
  return (random(-100, 101) / 100.0) * 0.05;
}

void setup() {
  // Inicialização do Arduino
  Serial.begin(9600);
}

void getVelocity(unsigned long currentTime){

  if (currentTime - previousTimeVelocity >= 15000) {
    previousTimeVelocity = currentTime;

    // Atualiza o valor de entrada u[n]
   
    uIndex = (uIndex + 1) % (sizeof(u) / sizeof(u[0]));

    Serial.println(uIndex);
  }

}

void updateVelocity(unsigned long currentTime){

   if (currentTime - previousTimeSample >= interval) {
    // Atualiza o valor de entrada u[n]
    float uValue = u[uIndex];

    // Simulação da dinâmica do veículo
    v = 0.9753 * v + 0.02469 * uValue + generateRandomNoise();

    // Imprime a velocidade atual

    previousTimeSample = currentTime;  // atualiza o tempo da última atualização
  Serial.println(v);
  }
}

void loop() {
  unsigned long currentTime = millis();  // tempo atual
    
  // Verifica se passaram 15 segundos desde a última atualização
  getVelocity(currentTime);


  // Verifica se é hora de atualizar a velocidade
  updateVelocity(currentTime);
  // if (currentTime - previousTimeSample >= interval) {
  //   // Atualiza o valor de entrada u[n]
  //   float uValue = u[uIndex];

  //   // Simulação da dinâmica do veículo
  //   v = 0.9753 * v + 0.02469 * uValue + generateRandomNoise();

  //   // Imprime a velocidade atual

  //   previousTimeSample = currentTime;  // atualiza o tempo da última atualização
  // }
}
