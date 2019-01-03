// For emitter pins
int emitter_nLE = 0;
int emitter_nE0 = 1;
int emitter_nE1 = 2;
int emitter_nE2 = 3;
int emitter_nE3 = 4;
int emitter_nE4 = 5;
int emitter_nE5 = 6;
int emitter_ADDR0 = 7;
int emitter_ADDR1 = 8;
int emitter_ADDR2 = 9;
int emitter_ADDR3 = 10;

// for teseting
int led_idx = 0;

void setup() {
  // for emitter pins init
  pinMode(emitter_nLE, OUTPUT);
  pinMode(emitter_nE0, OUTPUT);
  pinMode(emitter_nE1, OUTPUT);
  pinMode(emitter_nE2, OUTPUT);
  pinMode(emitter_nE3, OUTPUT);
  pinMode(emitter_nE4, OUTPUT);
  pinMode(emitter_nE5, OUTPUT);
  pinMode(emitter_ADDR0, OUTPUT);
  pinMode(emitter_ADDR1, OUTPUT);
  pinMode(emitter_ADDR2, OUTPUT);
  pinMode(emitter_ADDR3, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  /*for (int i = 0; i < 77; i++) {
    emitter_on_led(i);
    delay(100);
  }*/
  emitter_on_led(5);
}

// idx : index of led
void emitter_on_led(int idx_org)
{
  int idx;
  // nLE is high
  digitalWrite(emitter_nLE, HIGH);
  // each 74hc4515 has 14 leds
  if (idx_org < 14) {
    idx = idx_org;
    digitalWrite(emitter_nE0, LOW); digitalWrite(emitter_nE1, HIGH); digitalWrite(emitter_nE2, HIGH); digitalWrite(emitter_nE3, HIGH); digitalWrite(emitter_nE4, HIGH); digitalWrite(emitter_nE5, HIGH);// select No0 4515.
  } else if (idx_org >= 14 && idx_org < 28){
    idx = idx_org - 14;  
    digitalWrite(emitter_nE0, HIGH); digitalWrite(emitter_nE1, LOW);  digitalWrite(emitter_nE2, HIGH); digitalWrite(emitter_nE3, HIGH); digitalWrite(emitter_nE4, HIGH); digitalWrite(emitter_nE5, HIGH);// select No1 4515.
  } else if (idx_org >= 28 && idx_org < 42){
    idx = idx_org - 28;  
    digitalWrite(emitter_nE0, HIGH); digitalWrite(emitter_nE1, HIGH);  digitalWrite(emitter_nE2, LOW); digitalWrite(emitter_nE3, HIGH); digitalWrite(emitter_nE4, HIGH); digitalWrite(emitter_nE5, HIGH);// select No2 4515.
  } else if (idx_org >= 42 && idx_org < 56){
    idx = idx_org - 42;  
    digitalWrite(emitter_nE0, HIGH); digitalWrite(emitter_nE1, HIGH);  digitalWrite(emitter_nE2, HIGH); digitalWrite(emitter_nE3, LOW); digitalWrite(emitter_nE4, HIGH); digitalWrite(emitter_nE5, HIGH);// select No3 4515.
  } else if (idx_org >= 56 && idx_org < 70){
    idx = idx_org - 56;  
    digitalWrite(emitter_nE0, HIGH); digitalWrite(emitter_nE1, HIGH);  digitalWrite(emitter_nE2, HIGH); digitalWrite(emitter_nE3, HIGH); digitalWrite(emitter_nE4, LOW); digitalWrite(emitter_nE5, HIGH);// select No4 4515.
  } else if (idx_org >= 70 && idx_org < 77){
    idx = idx_org - 70;  
    digitalWrite(emitter_nE0, HIGH); digitalWrite(emitter_nE1, HIGH);  digitalWrite(emitter_nE2, HIGH); digitalWrite(emitter_nE3, HIGH); digitalWrite(emitter_nE4, HIGH); digitalWrite(emitter_nE5, LOW);// select No5 4515.
  } 
  emitter_addr_func(idx);
}

void emitter_addr_func(int idx) {
  if (idx == 0) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 1) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 2) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 3) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 4) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 5) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 6) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 7) {
    digitalWrite(emitter_ADDR3, LOW); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 8) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 9) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 10) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 11) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, LOW); digitalWrite(emitter_ADDR1, HIGH); digitalWrite(emitter_ADDR0, HIGH);  
  } else if (idx == 12) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, LOW);  
  } else if (idx == 13) {
    digitalWrite(emitter_ADDR3, HIGH); digitalWrite(emitter_ADDR2, HIGH); digitalWrite(emitter_ADDR1, LOW); digitalWrite(emitter_ADDR0, HIGH);  
  } else {
  }
}
