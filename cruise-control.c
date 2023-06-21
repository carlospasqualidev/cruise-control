// Variáveis globais
float velocity = 0;  // velocidade atual
float filteredVelocity = 0;  // velocidade filtrada
float u[] = {100, 110, 100, 90};  // vetor de valores de entrada u[n]
int uIndex = 0;  // índice atual do vetor de valores de entrada u[n]
float d[] = {10,-20,55,-30};

float ki = 1.8;
float kp = 5.4;
float i = 0;
float p = 0;
float KiTime = 0.05;

float LastI = 0;
float error = 0;
float referenceValue = 0;


// Variaveis para controlar os intervalos
unsigned long previousTimeVelocity = 0;  // velocidade
unsigned long previousTimeSample = 0;  // tempo de coleta

// Intervalos
unsigned long sampleInterval = 50;  // intervalo de tempo entre as atualizações, em milissegundos
unsigned long velocityInterval = 15000;  // intervalo de tempo entre as atualizações, em milissegundos

// Função para gerar ruído randômico com amplitude de 0.05
float generateRandomNoise() {
  return (random(-100, 101) / 100.0) * 0.05; // retorna um valor entre 0 e 1
}

void applyLowPassFilter() {
  // Coeficientes do filtro passa-baixa
  float alpha = 0.05;  // Fator de suavização quanto menor melhor
  //Esse fator influência na qualidade 
  //e na rapidez de adapatação do sinal durante a filtragem

  // O alpha serve para pegar uma porcentagem do valor atual e uma 
  // porcentagem do valor anterior. Quanto menor a contribuição da velocidade 
  // atual no valor filtrado menos frequencias altas passarão, e vice-versa.
  // O complemento de Alpha (1- alpha) serve para reutilizar o valor anterior
  // na média calculada.
  filteredVelocity = alpha * velocity + (1 - alpha) * filteredVelocity;
}

void getVelocity(unsigned long currentTime) {
  if (currentTime - previousTimeVelocity >= velocityInterval) {
    previousTimeVelocity = currentTime;

    // Utiliza o operador % para pegar o resto da divisão
    // do index com o tamanho máximo do array utilizando a função sizeof
    // dividido por uma posição qualquer em bytes
    uIndex = (uIndex + 1) % (sizeof(u) / sizeof(u[0]));
  }
}

void updateVelocity(unsigned long currentTime) {
  if (currentTime - previousTimeSample >= sampleInterval) {
    // uValue recebe a velocidade de referência
    float uValue = u[uIndex];

    //Item 3.b disturbio aplicado
    // float uValue = u[0];
    // float dValue = d[uIndex];

    //Itens 1 e 2
    // Simulação da dinâmica de aceleração do veículo
    velocity = 0.9753 * velocity + 0.02469 * uValue + generateRandomNoise();

    //Item 3
    //velocity = 0.9753 * velocity + 0.02469 * referenceValue + generateRandomNoise();
    
    //Item 3.b disturbio aplicado na saida
    // velocity = 0.9753 * velocity + 0.02469 * referenceValue + generateRandomNoise() +dValue;

    // Aplica o filtro passa-baixa
    applyLowPassFilter();

    previousTimeSample = currentTime;  // atualiza o tempo da última atualização

    error = uValue - filteredVelocity;

    p = kp * error;
    i = LastI + error * ki * KiTime;
    referenceValue = p + i;

    //item 3.b disturbio aplicado na entrada
    //referenceValue = p + i + dValue;
    
    LastI = i;


    Serial.print(velocity);
    Serial.print(",");
    Serial.println(filteredVelocity);
  }
}

void setup() {
  // Inicialização do Arduino
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();  // tempo atual
    
  // Verifica se passaram 15 segundos desde a última atualização
  getVelocity(currentTime);

  // Verifica se é hora de atualizar a velocidade
  updateVelocity(currentTime);

}