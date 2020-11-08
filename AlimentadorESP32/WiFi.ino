const char* ssid = "MY_WIFI";
const char* password =  "ITSNOT1234";  

void iniciarWifi() {
  WiFi.begin(ssid, password);
  conectarWifi();
}

void conectarWifi() {
  while (WiFi.status() != WL_CONNECTED && temporizar(2000, WIFI) == true)
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

bool verificarWifi() {
  if (WiFi.status() != WL_CONNECTED) {
    conectarWifi();
    if ((WiFi.status() != WL_CONNECTED)) {
      return false;
    }
  }
  return true;
}

bool verificarConexao() {
  return WiFi.status() == WL_CONNECTED;
}

void notificarFaltaWifi() {
  limparDisplay();
  escreverDisplay("NAO FOI POSSIVEL", 0, 0);
  escreverDisplay("CONECTAR A WI-FI", 1, 0);
}
