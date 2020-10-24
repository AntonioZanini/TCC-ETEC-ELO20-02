#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>

byte pinMotor = 22;
byte pinReservatorioAlto = 24;
byte pinReservatorioVazio = 26;
byte pinBuzzer = 25;

int NotasMusica[] = {};
int duracaoNotas[] = {};

int notaAtual = 0;
int duracaoAtual = 0;

// pinoSDA GPIO 21
// pinoSDL GPIO 22

LiquidCrystal_I2C displayLCD(0x27, 16, 2);

void setup() {
   pinMode(pinMotor, OUTPUT);
   pinMode(pinReservatorioAlto, INPUT);
   pinMode(pinReservatorioVazio, INPUT);
   displayLCD.begin();
   displayLCD.setBacklight(HIGH);

   EasyBuzzer.setPin(pinBuzzer);
   
   desligarMotor();
}

void loop() {
  // Quando estiver agendado:
  ligarMotor();

  // Sempre atualizando a saída de som.
  EasyBuzzer.update();
}

int calcularReservatorio() {
  /*
   * VALORES DOS SENSORES:
   * HIGH: Com ração
   * LOW:  Sem ração
   */
  bool sensorSuperior = digitalRead(pinReservatorioAlto);
  bool sensorInferior = digitalRead(pinReservatorioVazio);
  int valorReservatorio = 0;

  if (sensorSuperior == HIGH && sensorInferior == HIGH) {
    valorReservatorio = 2;
  } else if (sensorSuperior == LOW && sensorInferior == HIGH) {
    valorReservatorio = 1;
  } else if (sensorSuperior == LOW && sensorInferior == LOW) {
    valorReservatorio = 0;
  }
  return valorReservatorio;
}

void desligarMotor() {
  digitalWrite(pinMotor, LOW);
}

void ligarMotor() {
  digitalWrite(pinMotor, HIGH);
}

void tocarNota() {
  EasyBuzzer.singleBeep(
    NotasMusica[notaAtual],
    duracaoNotas[duracaoAtual],
    tocarNota
  );
  notaAtual += 1;
  duracaoAtual += 1;
}
