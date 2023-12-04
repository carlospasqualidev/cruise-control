# Controle de Veículo README

## Visão Geral

Este projeto Arduino implementa um sistema de controle de veículo simulado. O código simula a dinâmica de aceleração do veículo, aplicando um controle proporcional-integral (PI). Além disso, o sistema incorpora um filtro passa-baixa para suavizar as leituras de velocidade e introduz ruído randômico para uma simulação mais realista.

## Variáveis e Parâmetros

O código inclui várias variáveis e parâmetros essenciais para o controle do veículo:

- `velocity`: Velocidade atual do veículo.
- `filteredVelocity`: Velocidade filtrada pelo filtro passa-baixa.
- `u`: Vetor de valores de entrada.
- `d`: Vetor de disturbios aplicados.
- `ki` e `kp`: Parâmetros de ganho do controlador proporcional-integral.
- `KiTime`: Intervalo de tempo para o termo integral.
- Outras variáveis para controle de intervalos e tempo.

## Funções Principais

### `generateRandomNoise()`

Gera ruído randômico com amplitude de 0.05 para simular variações na velocidade.

### `applyLowPassFilter()`

Aplica um filtro passa-baixa para suavizar as leituras de velocidade.

### `getVelocity(unsigned long currentTime)`

Atualiza o índice do vetor de valores de entrada (`u`) em intervalos específicos.

### `updateVelocity(unsigned long currentTime)`

Simula a dinâmica de aceleração do veículo, aplica o filtro passa-baixa, e calcula o controle PI. Imprime a velocidade atual e a velocidade filtrada.

## Configuração e Uso

1. Configure um ambiente de desenvolvimento Arduino.
2. Conecte o Arduino ao sistema.
3. Carregue o código neste script no Arduino IDE.
4. Execute o programa no Arduino.

O código imprimirá as leituras de velocidade atual e velocidade filtrada no monitor serial.

## Parâmetros Ajustáveis

- `sampleInterval`: Intervalo de tempo entre as atualizações de velocidade.
- `velocityInterval`: Intervalo de tempo entre as atualizações de índice do vetor de entrada.

## Observações

- Este projeto é uma simulação e pode ser adaptado para experimentos reais de controle de veículos.
- Ajuste os parâmetros de ganho (`ki` e `kp`) para otimizar o desempenho do controlador.

---

**Nota:** Certifique-se de entender os conceitos de controle proporcional-integral (PI) ao trabalhar com este código. Ajuste os parâmetros com cuidado para evitar instabilidades no sistema.
