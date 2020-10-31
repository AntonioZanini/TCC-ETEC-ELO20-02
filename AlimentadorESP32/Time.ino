#define HORA_EM_MS 3600000

volatile byte horaAtual = 0;
volatile byte minutoAtual = 0;
volatile byte segundoAtual = 0;
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
  if (verificarWifi() == true) {
    ntpClient.forceUpdate();
    horaAtual    = ntpClient.getHours();
    minutoAtual  = ntpClient.getMinutes();
    segundoAtual = ntpClient.getSeconds();  
  }
}

void atualizarHorario(){
  if (temporizar(1000, TIME) == false) {
    adicionarSegundo();
  }
  if (millis() % (HORA_EM_MS * horasPassadas + 1) > 0) {
    horasPassadas++;
    obterHorarioInternet();
  }
  
}

void adicionarSegundo() {
  segundoAtual++;
  if (segundoAtual > 59) {
    segundoAtual = 0;
    minutoAtual++;
  }
  if (minutoAtual > 59) {
    minutoAtual = 0;
    horaAtual++;
  }
  if (horaAtual > 23) {
    horaAtual = 0;
  }
} 
