#include <LiquidCrystal.h>
#include <dht_nonblocking.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11

// LCD pins
const int LCD_RS = 7, LCD_E = 8, LCD_EB4 = 13, LCD_EB5 = 12, LCD_EB6 = 11, LCD_EB7 = 10;
LiquidCrystal lcd(LCD_RS, LCD_E, LCD_EB4, LCD_EB5, LCD_EB6, LCD_EB7);

// DHT11 Sensor
const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_TYPE_11);

// Analog Joystick
const int SWITCH_PIN = 3;
const int X_PIN = A0;
const int Y_PIN = A1;

// Vars
float temperature;
float humidity;

void setup()
{
  // LCD
  lcd.begin(16, 2);
  lcd.print("Test Screen");
  lcd.setCursor(0, 1);
  lcd.print("Test-Screen");

  // DHT11 Sensor
  
  // Analog Joystick
  pinMode(SWITCH_PIN, INPUT);
  digitalWrite(SWITCH_PIN, HIGH);

  // Serial Plotter/Monitor
  Serial.begin(9600);
}

// temporary test code

// Poll for a measurement, keeping the state machine alive. Return true if a measurement is available.
static bool sensorTest(float *temperature, float *humidity)
{
  static unsigned long measurement_timestamp = millis();

  /* Measure once every four seconds. */
  if(millis() - measurement_timestamp > 3000ul)
  {
    if( dht_sensor.measure(temperature, humidity))
    {
      measurement_timestamp = millis( );
      return(true);
    }
  }
  return(false);
}

static void sensorData() {
  Serial.print("T = ");
  Serial.print(temperature, 1);
  Serial.print(" deg. C, H = ");
  Serial.print(humidity, 1);
  Serial.println("%");
}

static void joystickTest() {
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SWITCH_PIN));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_PIN));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_PIN));
  Serial.print("\n\n");
  delay(500);
}

void loop()
{
  // joystickTest();

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if(sensorTest(&temperature, &humidity)) {sensorData();}
}