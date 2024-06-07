//Bebedouro Mineiro
#define trigger 6  // TRIGGER ULTRASONIC
#define echo 3     // ECHO ULTRSONIC
#define Relay 7    // RELAY IN

#include <LiquidCrystal_I2C.h> //Bibilhoteca Display


LiquidCrystal_I2C lcd(0x3F, 16, 2);  // Endereço I2C do LCD e número de colunas/linhas

float time = 0, distance = 0;

void setup() {
  Serial.begin(9600);
  lcd.init();       // Inicializa o LCD
  lcd.backlight();  // Ativa a retroiluminação do LCD
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(Relay, OUTPUT);

  delay(2000);
}

void loop() {
  lcd.clear();          // Limpa o LCD
  lcd.setCursor(0, 0);  // Posiciona o cursor
  measure_distance();

  if (distance < 5) {
    digitalWrite(Relay, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Aguarde..."); // Mensagem Enchendo
    lcd.setCursor(0, 1);
    lcd.print("Enchendo"); // Mensagem Enchendo
    delay(3000);
    digitalWrite(Relay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Retire o Copo"); // Mensagem Tirar o Copo
    delay(3000);

  } else {
    digitalWrite(Relay, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Aproxime o copo"); // Mensagem Tirar o Copo
  }

  delay(500);
}

void measure_distance() {
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  time = pulseIn(echo, HIGH);

  distance = time * 200 / 20000;
}