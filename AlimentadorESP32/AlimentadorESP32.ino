#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <NTPClient.h>
#include "Defines_Buzzer.h"
#include "Defines.h"

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
