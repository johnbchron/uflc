#define OUTPUT_PIN_FANS   23
#define OUTPUT_PIN_TEC    22
#define OUTPUT_PIN_PUMPS  21

bool output_fans = false;
bool output_tec = false;
bool output_pumps = false;

void setup() {
  // put your setup code here, to run once:
  setup_outputs();
  set_output_fans(true);
  set_output_tec(true);
  set_output_pumps(true);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void setup_outputs() {
  pinMode(OUTPUT_PIN_FANS, OUTPUT);
  pinMode(OUTPUT_PIN_TEC, OUTPUT);
  pinMode(OUTPUT_PIN_PUMPS, OUTPUT);
}

void set_output_fans(bool enable) {
  digitalWrite(OUTPUT_PIN_FANS, (int)enable);
  output_fans = enable;
}

void set_output_tec(bool enable) {
  digitalWrite(OUTPUT_PIN_TEC, (int)enable);
  output_tec = enable;
}

void set_output_pumps(bool enable) {
  digitalWrite(OUTPUT_PIN_PUMPS, (int)enable);
  output_pumps = enable;
}
