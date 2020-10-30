const char* ssid = "Net_Core";
const char* password =  "p4554r05";  

void iniciarWifi() {
  WiFi.begin(ssid, password);
  conectarWifi();
}

void conectarWifi() {
  while (WiFi.status() != WL_CONNECTED && temporizar(2000) == true)
  {
    delay(200);
      limparDisplay();
      escreverDisplay("CONECTANDO", 0, 0);
      escreverDisplay("A WI-FI...", 1, 0);
  } 
  if (WiFi.status() != WL_CONNECTED) {
    notificarFaltaWifi();
    return;
  }
  Serial.println("Conectado");
}

void verificarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
}

void notificarFaltaWifi() {
  limparDisplay();
  escreverDisplay("NAO FOI POSSIVEL", 0, 0);
  escreverDisplay("CONECTAR A WI-FI", 1, 0);
}
