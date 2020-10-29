// pinoSDA GPIO 21
// pinoSDL GPIO 22
LiquidCrystal_I2C displayLCD(0x27, 16, 2);

void iniciarDisplay() {
   displayLCD.begin();
   displayLCD.setBacklight(HIGH);
}
