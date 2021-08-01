#define OUTPUT_PIN_FANS   23
#define OUTPUT_PIN_TEC    22
#define OUTPUT_PIN_PUMPS  21
#define INPUT_PIN_FANS    18
#define INPUT_PIN_TEC     17
#define INPUT_PIN_PUMPS   16

bool output_fans = false;
bool output_tec = false;
bool output_pumps = false;
bool input_fans = false;
bool input_tec = false;
bool input_pumps = false;

void update_inputs(void * pvParameters);
void update_outputs(void * pvParameters);

void setup() {
  Serial.begin(115200);

  xTaskCreate(update_inputs, "update_inputs", 1024, NULL, 2, NULL);
  xTaskCreate(update_outputs, "update_outputs", 512, NULL, 2, NULL);
}

void loop() {  
  delay(25);
}

void update_inputs(void * pvParameters) {
  setup_inputs();

  bool input_last_fans = false;
  bool input_last_tec = false;
  bool input_last_pumps = false;

  for (;;) {
    input_last_fans = input_fans;
    input_last_tec = input_tec;
    input_last_pumps = input_pumps;
    
    input_fans = read_input_fans();
    input_tec = read_input_tec();
    input_pumps = read_input_pumps();

    if (input_last_fans && !input_fans) {
      output_fans = !output_fans;
    }

    if (input_last_tec && !input_tec) {
      output_tec = !output_tec;
    }

    if (input_last_pumps && !input_pumps) {
      output_pumps = !output_pumps;
    }

    delay(50);
  }
}

void update_outputs(void * pvParameters) {
  setup_outputs();

  for (;;) {
    set_output_fans(output_fans);
    set_output_tec(output_tec);
    set_output_pumps(output_pumps);

    delay(100);
  }
}

void setup_outputs() {
  pinMode(OUTPUT_PIN_FANS, OUTPUT);
  pinMode(OUTPUT_PIN_TEC, OUTPUT);
  pinMode(OUTPUT_PIN_PUMPS, OUTPUT);
}

void setup_inputs() {
  pinMode(INPUT_PIN_FANS, INPUT_PULLUP);
  pinMode(INPUT_PIN_TEC, INPUT_PULLUP);
  pinMode(INPUT_PIN_PUMPS, INPUT_PULLUP);
}

bool read_input_fans() {
  return !(bool)digitalRead(INPUT_PIN_FANS);
}

bool read_input_tec() {
  return !(bool)digitalRead(INPUT_PIN_TEC);
}

bool read_input_pumps() {
  return !(bool)digitalRead(INPUT_PIN_PUMPS);
}

void set_output_fans(bool enable) {
  if (enable) {
    digitalWrite(OUTPUT_PIN_FANS, HIGH);
  } else {
    digitalWrite(OUTPUT_PIN_FANS, LOW);
  }
}

void set_output_tec(bool enable) {
  if (enable) {
    digitalWrite(OUTPUT_PIN_TEC, HIGH);
  } else {
    digitalWrite(OUTPUT_PIN_TEC, LOW);
  }
}

void set_output_pumps(bool enable) {
  if (enable) {
    digitalWrite(OUTPUT_PIN_PUMPS, HIGH);
  } else {
    digitalWrite(OUTPUT_PIN_PUMPS, LOW);
  }
}
