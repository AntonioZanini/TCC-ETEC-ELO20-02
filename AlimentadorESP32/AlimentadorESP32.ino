#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <NTPClient.h>
#include "Defines.h"

#define PINO_BUZZER 22
#define PINO_RESERVATORIO_SUPERIOR 24
#define PINO_RESERVATORIO_INFERIOR 26
#define PINO_BUZZER 25

void setup() {
  Serial.begin(9600);

  iniciarPinosAlimentador();
  iniciarDisplay();
  iniciarBuzzer();
  iniciarWifi();
  iniciarNTPClient();
}

void loop() {
  verificarWifi();
  atualizarHorario();
  
  // Quando estiver agendado:

  
  // VERIFICICAR REPETIÇÃO DE ATIVAÇÃO POR HORÁRIO
  //atualizarAlimentador();
  
  // Sempre atualizando a saída de som.
  //atualizarMusica();
  

  //Serial.println(obterTempoAtual());
  delay(200);
}
