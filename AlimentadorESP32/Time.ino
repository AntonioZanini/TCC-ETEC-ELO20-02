#define HORA_EM_MS 3600000

String horarioDoSistema = "00:00";
int horasPassadas = 0;

WiFiUDP udpClient;
NTPClient ntpClient(udpClient, "a.st1.ntp.br", -3 * 3600, 60000);

void iniciarNTPClient() {
   ntpClient.begin(); 
   ntpClient.forceUpdate();
   horarioDoSistema = obterHorarioInternet();
}

String obterTempoAtual() {
  return horarioDoSistema;
}

String obterHorarioInternet(){
  return ntpClient.getFormattedTime().substring(0,5);
}

void atualizarHorario(){
  if (temporizar(60000) == false) {
    horarioDoSistema = adicionarMinuto();
  }
  if (millis() % (HORA_EM_MS * horasPassadas + 1) > 0) {
    horasPassadas++;
    horarioDoSistema = obterHorarioInternet();
  }
}

String adicionarMinuto() {
  int horas   = horarioDoSistema.substring(0,2).toInt();
  int minutos = horarioDoSistema.substring(3,5).toInt();

  return formatarHorario(horas, minutos+1);
}

String formatarHorario(int horas, int minutos) {
  if (minutos > 59) {
    minutos = 0;
    horas++;
  }
  if (horas > 23) {
    horas = 0;
  }
  String textoHoras = preencherZeros(horas, 2);
  String textoMinutos = preencherZeros(minutos, 2);

  return textoHoras + ":" + textoMinutos;
}
