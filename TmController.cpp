#include <Joystick.h>

// ---------- config ----------
constexpr uint8_t  POT_PIN  = A1;
constexpr int16_t  DEADZONE = 3;
constexpr uint16_t ADC_MIN  = 0;
constexpr uint16_t ADC_MAX  = 1023;
constexpr int16_t  X_MIN    = -32768;
constexpr int16_t  X_MAX    =  32767;
// ----------------------------------

Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_GAMEPAD,
  0,0, true, false, false, false, false, false, false, false, false, false, false
);

void setup() {
  Joystick.begin();
  Joystick.setXAxisRange(X_MIN, X_MAX);
  Joystick.setXAxis(0);
  ADCSRA = (ADCSRA & 0b11111000) | 0b100;
  analogReference(DEFAULT);
  pinMode(POT_PIN, INPUT);
}

void loop() {
  static uint16_t lastRaw = 0;
  uint16_t raw = analogRead(POT_PIN);

  if (raw <= ADC_MIN + DEADZONE)     raw = ADC_MIN;
  else if (raw >= ADC_MAX - DEADZONE) raw = ADC_MAX;

  if (abs(int16_t(raw) - int16_t(lastRaw)) > DEADZONE) {
    int32_t x = map(raw, ADC_MIN, ADC_MAX, X_MIN, X_MAX);
    Joystick.setXAxis(int16_t(x));
    lastRaw = raw;
  }
}
