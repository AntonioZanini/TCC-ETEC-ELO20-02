#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EasyBuzzer.h>
#include <WiFi.h>
#include <NTPClient.h>

WiFiUDP udpClient;
NTPClient ntpClient(udpClient, "a.st1.ntp.br", -3 * 3600, 60000);

const char* ssid = "Net_Core";
const char* password =  "p4554r05";  

byte pinMotor = 22;
byte pinReservatorioAlto = 24;
byte pinReservatorioVazio = 26;
byte pinBuzzer = 25;

int totalNotas = 200;
int NotasMusica[] = {};
int duracaoNotas[] = {};

int notaAtual = 0;
bool pararSom = false;
// pinoSDA GPIO 21
// pinoSDL GPIO 22

byte tempoAbastecimento = 0;

unsigned long tempoAtivacao = 0;

LiquidCrystal_I2C displayLCD(0x27, 16, 2);

void setup() {
   pinMode(pinMotor, OUTPUT);
   pinMode(pinReservatorioAlto, INPUT);
   pinMode(pinReservatorioVazio, INPUT);
   displayLCD.begin();
   displayLCD.setBacklight(HIGH);

   EasyBuzzer.setPin(pinBuzzer);
   
   Serial.begin(9600);
   
   iniciarWifi();
   
   desligarMotor();

   ntpClient.begin(); 
   ntpClient.forceUpdate();
}

void loop() {
  // Quando estiver agendado:
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
  
  // VERIFICICAR REPETIÇÃO DE ATIVAÇÃO POR HORÁRIO
  if (verificarAgendamento() == true) {
    while(temporizador(tempoAbastecimento * 1000)){
      alimentacao();
    }
    desligarMotor();
    delay(60000);
  }

  Serial.println(ntpClient.getFormattedTime());
  delay(200);
  
  // Sempre atualizando a saída de som.
  EasyBuzzer.update();
}

void iniciarWifi() {
  WiFi.begin(ssid, password);
  conectarWifi();
}

void conectarWifi() {
  while (WiFi.status() != WL_CONNECTED && temporizador(2000) == true)
  {
    delay(200);                                 // Aguarda meio segundo
    Serial.println("Conectando ao WiFi...");     // Conectando
  } 
  if (WiFi.status() != WL_CONNECTED) {
    notificarFaltaWifi();
    return;
  }
  Serial.println("Conectado");
}

bool verificarAgendamento() {
  return false;
}

bool temporizador(int milissegundos)
{
  unsigned long tempoAtual = millis();
  if (tempoAtivacao == 0) {
    tempoAtivacao = tempoAtual;
  }
  if (tempoAtual - tempoAtivacao > milissegundos)
  {
    tempoAtivacao = 0;
    return false;
  }
  return true;
}

void alimentacao() {
  if (calcularReservatorio() >= 1) {   
    ligarMotor();
  } else {
    desligarMotor();
    notificarFaltaRacao();
  }
}

void notificarFaltaWifi() {
  Serial.println("Falta Wi-Fi");
}

void notificarFaltaRacao() {
  // ESCREVER NO DISPLAY
  // ENVIAR PARA O APP?
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

void pararMusica() {
  EasyBuzzer.stopBeep();
  pararSom = true;
}


void tocarNota() {
  if (pararSom == true) {
    return;
  }
  if (notaAtual == totalNotas) {
    notaAtual = 0;
  }
  EasyBuzzer.singleBeep(
    NotasMusica[notaAtual],
    duracaoNotas[notaAtual],
    tocarNota
  );
  notaAtual += 1;
}
