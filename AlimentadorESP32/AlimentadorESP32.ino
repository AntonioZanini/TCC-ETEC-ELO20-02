#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <NTPClient.h>
#include <Preferences.h>
#include "AlimentadorESP32.h"
#include "Buzzer.h"

TaskHandle_t tarefaNucleoSecundario;

void setup() {
  Serial.begin(9600);

  iniciarPinosAlimentador();
  iniciarDisplay();
  iniciarBuzzer();
  iniciarWifi();
  inciarMQTT();
  iniciarNTPClient();

  xTaskCreatePinnedToCore(
    execucaoNucleoSecundario, /* Function to implement the task */
    "Tarefas", /* Name of the task */
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &tarefaNucleoSecundario,  /* Task handle. */
    0); /* Core where the task should run */
}

void loop() {
  verificarWifi();
  verificarMQTT();
  
  // VERIFICICAR REPETIÇÃO DE ATIVAÇÃO POR HORÁRIO
  //atualizarAlimentador();
  
  //atualizarMusica();

  Serial.println(obterTempoAtual());
  delay(200);
}

void execucaoNucleoSecundario(void * parameter) {
  for (;;) {
    atualizarHorario();
  }
}
