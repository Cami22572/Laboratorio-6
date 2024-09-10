#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <HardwareSerial.h>  // Agrega esta línea para el ESP32

// Configuración de la pantalla LCD con la dirección I2C 0x27, 20 columnas y 4 filas
LiquidCrystal_I2C lcd(0x27, 20, 4);

#define Pot1 33
#define Pot2 32
#define bot1 34
#define bot2 35

uint8_t decenas, unidades, decimal, decenas1, unidades1, decimal1;
float voltaje, voltaje2;
unsigned long counter = 0;
unsigned long lastButtonUpState = LOW;
unsigned long lastButtonDownState = LOW;

void setup()
{
    // Configuración de los pines de los botones
    pinMode(bot1, INPUT);
    pinMode(bot2, INPUT);
    
    // Inicialización del monitor serie
    Serial.begin(115200);
    
    // Inicialización de la pantalla LCD
    lcd.init();
    lcd.backlight();
    
    lcd.clear();
    lcd.print("hello world!");  // Mensaje inicial en la pantalla LCD

    delay(3000);
    lcd.clear();
}

void loop()
{
    // Lectura del primer potenciómetro
    voltaje = analogReadMilliVolts(Pot1) / 10.0;
    int temp = voltaje;
    decenas = temp / 100;
    temp = temp - decenas * 100;
    unidades = temp / 10;
    temp = temp - unidades * 10;
    decimal = temp;

    // Mostrar el primer voltaje en la LCD
    Serial.print(voltaje);
    Serial.print("\t");
    Serial.print(decenas);
    Serial.print("\t");
    Serial.print(unidades);
    Serial.print("\t");
    Serial.print(decimal);

    lcd.setCursor(0, 0);
    lcd.print("V1:");
    lcd.print(decenas);
    lcd.print('.');
    lcd.print(unidades);
    lcd.print(decimal);

    delay(250);

    // Lectura del segundo potenciómetro
    voltaje2 = analogReadMilliVolts(Pot2) / 10.0;
    int temp2 = voltaje2;
    decenas1 = temp2 / 100;
    temp2 = temp2 - decenas1 * 100;
    unidades1 = temp2 / 10;
    temp2 = temp2 - unidades1 * 10;
    decimal1 = temp2;

    // Mostrar el segundo voltaje en la LCD
    Serial.print("\t");
    Serial.print(voltaje2);
    Serial.print("\t");
    Serial.print(decenas1);
    Serial.print("\t");
    Serial.print(unidades1);
    Serial.print("\t");
    Serial.print(decimal1);

    lcd.setCursor(8, 0); // Ajusta la posición del segundo voltaje
    lcd.print("V2:");
    lcd.print(decenas1);
    lcd.print('.');
    lcd.print(unidades1);
    lcd.print(decimal1);

    delay(250);

    // Lectura del estado de los botones
    int buttonUpState = digitalRead(bot1);
    int buttonDownState = digitalRead(bot2);

    // Mostrar el contador en la LCD
    lcd.setCursor(0, 1);
    lcd.print("Contador: ");

    // Incrementar el contador
    if (buttonUpState == HIGH && lastButtonUpState == LOW) {
        counter++;
        lcd.setCursor(10, 1);
        lcd.print(counter);
    }

    // Decrementar el contador
    if (buttonDownState == HIGH && lastButtonDownState == LOW) {
        counter--;
        lcd.setCursor(10, 1);
        lcd.print(counter);
    }

    // Actualizar el estado de los botones
    lastButtonUpState = buttonUpState;
    lastButtonDownState = buttonDownState;

    delay(400);
}
