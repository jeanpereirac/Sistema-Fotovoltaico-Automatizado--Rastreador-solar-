# ☀️ Modelagem Computacional versus Validação Experimental de um Sistema de Rastreamento Fotovoltaico em Salinas-MG

<p align="center">
  <strong>Trabalho de Conclusão de Curso — Bacharelado em Sistemas de Informação</strong>
</p>

<p align="center">
  Desenvolvimento de um protótipo fotovoltaico automatizado, modelagem computacional e validação experimental.
</p>

---

## 📌 Sobre o projeto

Este repositório reúne os arquivos utilizados no desenvolvimento do Trabalho de Conclusão de Curso **“Modelagem Computacional versus Validação Experimental de um Sistema de Rastreamento Fotovoltaico em Salinas-MG”**.

O trabalho apresenta o desenvolvimento de um **protótipo experimental de baixo custo**, baseado na plataforma **Arduino Uno**, capaz de realizar o posicionamento automatizado de um painel fotovoltaico ao longo do dia.

Além do protótipo físico, foi utilizado um **modelo computacional desenvolvido no MATLAB/Simulink**, adaptado a partir do trabalho de Nagi (2023), com o objetivo de comparar os resultados simulados com os dados obtidos experimentalmente.

O projeto foi desenvolvido como uma **Prova de Conceito (PoC)**, utilizando uma abordagem quantitativa e descritiva baseada em prototipagem e experimentação.

---

## 🎯 Objetivo

O objetivo geral do trabalho é:

> Desenvolver um protótipo de sistema fotovoltaico automatizado de baixo custo e validar um modelo computacional por meio da comparação entre resultados simulados e experimentais.

### Objetivos específicos

* Analisar a eficiência energética de um sistema fotovoltaico automatizado;
* Analisar o ganho percentual de eficiência em relação a um sistema com painel fixo;
* Validar o modelo computacional por meio da comparação entre os resultados simulados e os dados experimentais;
* Avaliar o potencial de aplicação do sistema em regiões com elevada incidência de radiação solar.

---

## ⚙️ Funcionamento

O sistema utiliza o **Arduino Uno como unidade central de controle**.

Durante a operação, o microcontrolador:

1. Obtém a data e o horário por meio do módulo RTC;
2. Determina o posicionamento do painel;
3. Controla o servomotor responsável pela movimentação;
4. Realiza a leitura da tensão e da corrente elétrica;
5. Calcula a potência elétrica;
6. Exibe informações no display LCD;
7. Registra os dados no cartão microSD.

As medições são realizadas em intervalos de **um minuto**, durante o período de operação entre **06h00 e 18h00**.

### Fluxo simplificado

```text
              ☀️ Sol
                │
                ▼
       ┌──────────────────┐
       │ Painel            │
       │ Fotovoltaico      │
       └────────┬─────────┘
                │
                ▼
       ┌──────────────────┐
       │ Sensores          │
       │ Tensão + Corrente │
       └────────┬─────────┘
                │
                ▼
       ┌──────────────────┐
       │   Arduino Uno     │
       │ Controle e        │
       │ processamento      │
       └───────┬──────────┘
               │
        ┌──────┴───────┐
        ▼              ▼
  Servo Motor      Registro
  Posicionamento    dos dados
                    │
              ┌─────┴─────┐
              ▼           ▼
           Display      microSD
             LCD
```

---

## 🔧 Hardware utilizado

O protótipo utiliza os seguintes componentes principais:

| Componente                           | Função                                          |
| ------------------------------------ | ----------------------------------------------- |
| **Arduino Uno**                      | Unidade central de controle                     |
| **Painel fotovoltaico**              | Conversão da radiação solar em energia elétrica |
| **Servomotor MG996R**                | Posicionamento automático do painel             |
| **Sensor ACS712**                    | Medição da corrente elétrica                    |
| **Sensor de tensão 0–25 V**          | Medição da tensão elétrica                      |
| **RTC DS1307**                       | Controle de data e horário                      |
| **Display LCD 16×2 I2C**             | Exibição das informações                        |
| **Módulo microSD**                   | Armazenamento dos dados experimentais           |
| **Estrutura mecânica e engrenagens** | Movimentação e sustentação do painel            |

O protótipo utiliza um módulo fotovoltaico policristalino de **3 W e 6 V**, com dimensões aproximadas de **21 cm × 13 cm**. Para a comparação experimental, foram utilizados dois painéis com as mesmas especificações: um automatizado e outro mantido em posição fixa.

---

## 💻 Tecnologias utilizadas

### Arduino

O software embarcado foi desenvolvido para:

* controle do posicionamento do painel;
* aquisição das grandezas elétricas;
* cálculo da potência;
* controle do display;
* registro dos dados;
* sincronização temporal por meio do RTC.

O código principal está disponível em:

```text
Arduino/Codigo/sistema_automatizado.ino
```

### MATLAB/Simulink

O MATLAB/Simulink foi utilizado para a **modelagem computacional do sistema** e para a comparação entre o comportamento simulado e os resultados obtidos no protótipo físico.

O modelo está disponível em:

```text
MATLAB-Simulink/Sistema_Automatizado.slx
```

---

## 🧪 Metodologia

A metodologia do trabalho foi organizada em quatro etapas principais:

```text
┌──────────────────────────────┐
│ Seleção dos materiais e      │
│ construção do protótipo      │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Desenvolvimento da lógica    │
│ de funcionamento             │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Modelagem computacional      │
│ no MATLAB/Simulink           │
└──────────────┬───────────────┘
               │
               ▼
┌──────────────────────────────┐
│ Ensaios experimentais e      │
│ validação do modelo          │
└──────────────────────────────┘
```

O protótipo físico foi utilizado para obter dados experimentais de **tensão, corrente e potência**. Esses dados foram posteriormente organizados e comparados com os resultados produzidos pelo modelo computacional.

---

## 📊 Resultados

### Simulação computacional

A simulação foi realizada considerando um período de **12 horas de operação**.

O modelo MATLAB/Simulink apresentou um ganho energético de aproximadamente:

### **23,94%**

em relação ao sistema com painel fixo.

---

### Experimentos físicos

Os ensaios experimentais foram realizados entre:

**23/05/2026 e 26/05/2026**

com aquisição automática das variáveis elétricas entre **06h00 e 18h00**, em intervalos de um minuto.

Os resultados médios obtidos foram:

| Grandeza | Automatizado |   Fixo |  Diferença |
| -------- | -----------: | -----: | ---------: |
| Tensão   |       5,00 V | 4,12 V | **21,50%** |
| Corrente |       0,06 A | 0,06 A | **13,75%** |
| Potência |       0,41 W | 0,31 W | **29,39%** |

Considerando a energia produzida durante os quatro dias de ensaio:

| Data       | Automatizado |    Fixo |
| ---------- | -----------: | ------: |
| 23/05/2026 |      3,70 Wh | 2,92 Wh |
| 24/05/2026 |      5,56 Wh | 4,39 Wh |
| 25/05/2026 |      6,82 Wh | 4,98 Wh |
| 26/05/2026 |      3,34 Wh | 2,60 Wh |

Ao final do período experimental, o sistema automatizado acumulou aproximadamente **19,42 Wh**, enquanto o sistema fixo produziu cerca de **14,89 Wh**, resultando em um **ganho energético médio de aproximadamente 29,69%**.

> **Observação:** esse ganho representa o aumento da energia produzida pelo painel devido ao reposicionamento automático. O consumo energético dos componentes responsáveis pela automação não foi descontado do resultado.

---

## 🖥️ Simulação × experimento

A comparação entre o modelo computacional e o protótipo apresentou a mesma tendência geral: o sistema automatizado apresentou maior geração de energia em relação ao painel fixo.

| Avaliação          | Ganho energético |
| ------------------ | ---------------: |
| MATLAB/Simulink    |       **23,94%** |
| Experimento físico |       **29,69%** |

A diferença entre os valores está relacionada às simplificações utilizadas no modelo computacional e às condições reais presentes durante os experimentos. O trabalho considera que o modelo apresentou comportamento satisfatório para representar o comportamento geral observado no protótipo.

---

## 📁 Organização do repositório

```text
Sistema-Fotovoltaico-Automatizado--Rastreador-solar-/
│
├── Arduino/
│   └── Codigo/
│       └── sistema_automatizado.ino
│
├── Dados-Experimentais/
│   └── dados_experimentais.xlsx
│
├── MATLAB-Simulink/
│   └── Sistema_Automatizado.slx
│
├── TCC/
│   ├── Capitulos/
│   │   ├── cap1_introducao.tex
│   │   ├── cap2_revisao.tex
│   │   ├── cap3_metodologia.tex
│   │   ├── cap4_resultados.tex
│   │   └── cap5_conclusao.tex
│   │
│   ├── Figuras/
│   ├── pos-textuais/
│   ├── pre-textuais/
│   ├── main.tex
│   └── referencias.bib
│
├── .gitignore
├── LICENSE
└── README.md
```

A estrutura acima corresponde à organização atualmente presente no repositório.

---

## 📂 Conteúdo do repositório

### `Arduino/`

Código-fonte utilizado no sistema embarcado.

### `Dados-Experimentais/`

Planilha contendo os dados utilizados na análise experimental.

### `MATLAB-Simulink/`

Modelo computacional utilizado na simulação.

### `TCC/`

Arquivos da documentação acadêmica, incluindo capítulos, figuras, elementos pré-textuais, pós-textuais, referências e arquivo principal em LaTeX.

---

## ⚠️ Limitações do projeto

O protótipo foi desenvolvido para **fins experimentais**, utilizando um painel de pequena potência e uma estrutura mecânica simplificada.

O trabalho não realizou:

* análise de durabilidade mecânica;
* análise de custos de implantação e manutenção;
* avaliação de viabilidade técnico-econômica;
* balanço energético considerando o consumo dos componentes da automação;
* utilização de medições reais de irradiância e temperatura no modelo computacional.

Portanto, os resultados apresentados devem ser interpretados dentro das condições e limitações do experimento.

---

## 🎓 Informações acadêmicas

**Autor:** Jean Pereira Coelho

**Curso:** Bacharelado em Sistemas de Informação

**Instituição:** Instituto Federal do Norte de Minas Gerais — IFNMG

**Campus:** Salinas

**Orientador:** Jamerson Jardel Macedo Nere

**Local:** Salinas — Minas Gerais, Brasil

---

## 📚 Documentação

A documentação completa do trabalho está disponível na pasta:

```text
TCC/
```

O documento foi desenvolvido em **LaTeX**, utilizando a classe `abntex2` e referências bibliográficas em arquivo `.bib`.

---

## 👨‍💻 Autor

**Jean Pereira Coelho**

Trabalho desenvolvido como Trabalho de Conclusão de Curso do Bacharelado em Sistemas de Informação.

---

<p align="center">
  ☀️ <strong>Energia Solar • Automação • Arduino • MATLAB/Simulink</strong>
</p>
