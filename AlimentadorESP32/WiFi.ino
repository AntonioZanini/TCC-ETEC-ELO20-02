const char* ssid = "Net_Core";
const char* password =  "p4554r05";  

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

void verificarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
  }
}

void notificarFaltaWifi() {
  Serial.println("Falta Wi-Fi");
}
