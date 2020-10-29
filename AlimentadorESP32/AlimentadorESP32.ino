#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <NTPClient.h>

byte pinMotor = 22;
byte pinReservatorioAlto = 24;
byte pinReservatorioVazio = 26;
byte pinBuzzer = 25;

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
  AtualizarHorario();
  
  // Quando estiver agendado:

  
  // VERIFICICAR REPETIÇÃO DE ATIVAÇÃO POR HORÁRIO
  //atualizarAlimentador();
  
  // Sempre atualizando a saída de som.
  //atualizarMusica();
  

  //Serial.println(obterTempoAtual());
  delay(200);
}
