#define HORA_EM_MS 3600000

volatile byte horaAtual = 0;
volatile byte minutoAtual = 0;
int horasPassadas = 0;

WiFiUDP udpClient;
NTPClient ntpClient(udpClient, "a.st1.ntp.br", -3 * 3600, 60000);

void iniciarNTPClient() {
   ntpClient.begin(); 
   ntpClient.forceUpdate();
   obterHorarioInternet();
}

String obterTempoAtual() {
  String textoHoras = preencherZeros(horaAtual, 2);
  String textoMinutos = preencherZeros(minutoAtual, 2);

  return textoHoras + ":" + textoMinutos;
}

void obterHorarioInternet(){
  String horario = ntpClient.getFormattedTime().substring(0,5);
  horaAtual   = horario.substring(0,2).toInt();
  minutoAtual = horario.substring(3,5).toInt();
}

void atualizarHorario(){
  if (temporizar(60000, TIME) == false) {
    adicionarMinuto();
  }
  if (millis() % (HORA_EM_MS * horasPassadas + 1) > 0) {
    horasPassadas++;
    obterHorarioInternet();
  }
}

void adicionarMinuto() {
  minutoAtual++;
  if (minutoAtual > 59) {
    minutoAtual = 0;
    horaAtual++;
  }
  if (horaAtual > 23) {
    horaAtual = 0;
  }
} 
