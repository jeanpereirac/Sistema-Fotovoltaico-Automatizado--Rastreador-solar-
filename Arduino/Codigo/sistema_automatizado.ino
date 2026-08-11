
#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <SD.h>

// ===== OBJETOS =====
RTC_DS1307 rtc;
Servo servoMotor;
LiquidCrystal_I2C lcd(0x27, 16, 2);
File dataFile;

// ===== PINOS =====
#define SERVO_PIN 3
#define VOLT_PIN A3
#define ACS712_PIN A0
#define SD_CS 4

// ===== ARQUIVO FIXO =====
char nomeTXT[] = "LOG.TXT";

// ===== VARIÁVEIS =====
float anguloAtual = 90;
float anguloAlvo = 90;

unsigned long tempoAnterior = 0;
unsigned long tempoGravacao = 0;
unsigned long tempoOtimizacao = 0;

int tela = 0;

// FILTROS
float tensaoFiltrada = 0;
float correnteFiltrada = 0;

// ===== AJUSTES =====
int anguloInicio = 25;
int anguloMeio = 90;
int anguloFim = 150;

// ===== FUNÇÃO DO ÂNGULO =====
float calcularAngulo(DateTime now) {

  int minutosAtual =
    now.hour() * 60 + now.minute();

  int inicio = 6 * 60;
  int meio = 12 * 60;
  int fim = 19 * 60;

  if (minutosAtual < inicio)
    return anguloInicio;

  if (minutosAtual <= meio) {

    float p =
      (float)(minutosAtual - inicio) /
      (meio - inicio);

    return
      anguloInicio +
      p * (anguloMeio - anguloInicio);
  }

  if (minutosAtual <= fim) {

    float p =
      (float)(minutosAtual - meio) /
      (fim - meio);

    return
      anguloMeio +
      p * (anguloFim - anguloMeio);
  }

  return anguloInicio;
}

// ===== MOVIMENTO SUAVE =====
void atualizarServo() {

  float diferenca =
    anguloAlvo - anguloAtual;

  if (abs(diferenca) > 0.2) {

    float passo = diferenca * 0.03;

    if (passo > 1)
      passo = 1;

    if (passo < -1)
      passo = -1;

    anguloAtual += passo;

    servoMotor.write((int)anguloAtual);
  }
}

// ===== LEITURA TENSÃO =====
float lerTensao() {

  long soma = 0;

  for (int i = 0; i < 10; i++) {

    soma += analogRead(VOLT_PIN);

    delay(2);
  }

  float media = soma / 10.0;

  return
    media *
    (5.0 / 1023.0) *
    5.0;
}

// ===== LEITURA CORRENTE =====
float lerCorrente() {

  long soma = 0;

  for (int i = 0; i < 20; i++) {

    soma += analogRead(ACS712_PIN);

    delay(2);
  }

  float media = soma / 20.0;

  float corrente =
    (media - 512) *
    (5.0 / 1023.0) /
    0.185;

  if (corrente < 0)
    corrente = 0;

  return corrente;
}

// ===== MEDIR POTÊNCIA =====
float medirPotencia() {

  float V = lerTensao();

  float I = lerCorrente();

  return V * I;
}

// ===== OTIMIZAÇÃO =====
float otimizarAngulo(float anguloBase) {

  float melhorAngulo = anguloBase;

  float melhorPotencia = 0;

  for (int ajuste = -15;
       ajuste <= 15;
       ajuste += 3) {

    float anguloTeste =
      anguloBase + ajuste;

    if (anguloTeste < 0)
      anguloTeste = 0;

    if (anguloTeste > 180)
      anguloTeste = 180;

    servoMotor.write((int)anguloTeste);

    delay(300);

    float potencia =
      medirPotencia();

    if (potencia > melhorPotencia) {

      melhorPotencia = potencia;

      melhorAngulo = anguloTeste;
    }
  }

  return melhorAngulo;
}

// ===== SALVAR SD =====
void salvarSD(
  DateTime now,
  float V,
  float I,
  float P,
  float A
) {

  dataFile =
    SD.open(nomeTXT, FILE_WRITE);

  if (dataFile) {

    // DATA
    if (now.day() < 10)
      dataFile.print('0');

    dataFile.print(now.day());

    dataFile.print('/');

    if (now.month() < 10)
      dataFile.print('0');

    dataFile.print(now.month());

    dataFile.print('/');

    dataFile.print(now.year());

    dataFile.print(' ');

    // HORA
    if (now.hour() < 10)
      dataFile.print('0');

    dataFile.print(now.hour());

    dataFile.print(':');

    if (now.minute() < 10)
      dataFile.print('0');

    dataFile.print(now.minute());

    // DADOS
    dataFile.print(F(" V="));
    dataFile.print(V, 1);

    dataFile.print(F(" I="));
    dataFile.print(I, 2);

    dataFile.print(F(" P="));
    dataFile.print(P, 1);

    dataFile.print(F(" A="));
    dataFile.println((int)A);

    dataFile.flush();

    dataFile.close();
  }
}

// ===== SETUP =====
void setup() {

  Serial.begin(9600);

  Wire.begin();

  rtc.begin();

  lcd.init();

  lcd.backlight();

  servoMotor.attach(SERVO_PIN);

  // ===== TESTE SERVO =====
  for (int pos = 60;
       pos <= 120;
       pos++) {

    servoMotor.write(pos);

    delay(20);
  }

  for (int pos = 120;
       pos >= 60;
       pos--) {

    servoMotor.write(pos);

    delay(20);
  }

  // ===== POSIÇÃO INICIAL =====
  DateTime now = rtc.now();

  anguloAtual =
    calcularAngulo(now);

  anguloAlvo =
    anguloAtual;

  servoMotor.write(
    (int)anguloAtual
  );

  // ===== SD =====
  if (!SD.begin(SD_CS)) {

    lcd.clear();

    lcd.print(F("Erro SD"));

    while (1);
  }

  lcd.clear();

  lcd.print(F("Sistema OK"));

  delay(1500);

  lcd.clear();
}

// ===== LOOP =====
void loop() {

  DateTime now = rtc.now();

  // ===== ÂNGULO BASE =====
  float anguloBase =
    calcularAngulo(now);

  // ===== OTIMIZAÇÃO TEMPO =====
  if (
    millis() -
    tempoOtimizacao >= 600000
  ) {

    tempoOtimizacao = millis();

    anguloAlvo =
      otimizarAngulo(
        anguloBase
      );
  }

  atualizarServo();

  // ===== LEITURAS =====
  float tensao =
    lerTensao();

  float corrente =
    lerCorrente();

  tensaoFiltrada =
    tensaoFiltrada * 0.9 +
    tensao * 0.1;

  correnteFiltrada =
    correnteFiltrada * 0.9 +
    corrente * 0.1;

  float potencia =
    tensaoFiltrada *
    correnteFiltrada;

  // ===== GRAVAÇÃO =====
  int horaAtual =
    now.hour();

  if (
    horaAtual >= 6 &&
    horaAtual < 18
  ) {

    if (
      millis() -
      tempoGravacao >= 60000
    ) {

      tempoGravacao =
        millis();

      salvarSD(
        now,
        tensaoFiltrada,
        correnteFiltrada,
        potencia,
        anguloAtual
      );
    }
  }

  // ===== TROCA TELAS =====
  if (
    millis() -
    tempoAnterior > 3000
  ) {

    tela++;

    if (tela > 1)
      tela = 0;

    tempoAnterior =
      millis();

    lcd.clear();
  }

  // ===== TELA DATA =====
  if (tela == 0) {

    lcd.setCursor(0, 0);

    if (now.day() < 10)
      lcd.print('0');

    lcd.print(now.day());

    lcd.print('/');

    if (now.month() < 10)
      lcd.print('0');

    lcd.print(now.month());

    lcd.print(' ');

    if (now.hour() < 10)
      lcd.print('0');

    lcd.print(now.hour());

    lcd.print(':');

    if (now.minute() < 10)
      lcd.print('0');

    lcd.print(now.minute());

    lcd.setCursor(0, 1);

    lcd.print(F("ANG:"));

    lcd.print((int)anguloAtual);
  }

  // ===== TELA POTÊNCIA =====
  if (tela == 1) {

    lcd.setCursor(0, 0);

    lcd.print(F("V="));

    lcd.print(
      tensaoFiltrada,
      1
    );

    lcd.print(F(" I="));

    lcd.print(
      correnteFiltrada,
      2
    );

    lcd.setCursor(0, 1);

    lcd.print(F("P="));

    lcd.print(
      potencia,
      1
    );
  }

  delay(200);
}
