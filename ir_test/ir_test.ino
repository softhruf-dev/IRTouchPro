uint16_t val0[128];
uint16_t val1[128];
uint16_t val2[128];
uint16_t val[128];
float div_vals[128];
uint16_t ref_val[128];

uint8_t i;

const int S00 = 0;
const int S01 = 1;
const int S02 = 2;
const int S03 = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(S00, OUTPUT);
  pinMode(S01, OUTPUT);
  pinMode(S02, OUTPUT);
  pinMode(S03, OUTPUT);
  
  for (i = 0;i<128; i++) {
    val1[i] = 0; 
    val2[i] = 0; 
    val0[i] = 0;  
    val[i] = 0;
    div_vals[i] = 0.0;
  }
  delay(100);
  
  for (i = 0;i < 16; i++) {
    digital_output(i);
    ref_val[i] = analogRead(0);
  }
}

void loop() {
  
  for (i = 0;i < 16; i++) {
    digital_output(i);
    val2[i] = val1[i];
    val1[i] = val0[i];
    val0[i] = analogRead(0);
  }

  for (i = 0;i < 16; i++) {
    val[i] = (val0[i]+val1[i]+val2[i])/3;
    div_vals[i] = (ref_val[i] * 1.0f) / val[i];
  }  
/*
  for (i < 0;i < 16; i++) {
    Serial.print(val[i]);
    Serial.print(",");  
    delay(10);
  }
  */
  
  for (i = 0;i < 16; i++)
    print_datas(i);
  Serial.println();
  
  delay(100);
}

void print_datas(uint8_t val_idx) {
  printFloat(div_vals[val_idx], 2);
  Serial.print(",");
}

void printFloat( float val, byte precision){
 // prints val with number of decimal places determine by precision
 // precision is a number from 0 to 6 indicating the desired decimial places
 // example: lcdPrintDouble( 3.1415, 2); // prints 3.14 (two decimal places)

 if(val < 0.0){
   Serial.print('-');
   val = -val;
 }

 Serial.print (int(val));  //prints the int part
 if( precision > 0) {
   Serial.print("."); // print the decimal point
   unsigned long frac;
   unsigned long mult = 1;
   byte padding = precision -1;
   while(precision--)
    mult *=10;

   if(val >= 0)
      frac = (val - int(val)) * mult;
   else
      frac = (int(val)- val ) * mult;
   unsigned long frac1 = frac;
   while( frac1 /= 10 )
      padding--;
   while(  padding--)
      Serial.print("0");
   Serial.print(frac,DEC) ;
 }
}

float find_max( float* vals, int n ) {
  float tmp = 0.0;
  for (i = 0; i < n; i++) {
      if (tmp > vals[i]) {
        tmp = vals[i];  
      }
  }
}
void digital_output(uint8_t vv) {
  if (vv == 0) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, LOW);
    digitalWrite(S02, LOW);
    digitalWrite(S03, LOW);  
  } else if( vv == 1 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, LOW);
    digitalWrite(S02, LOW);
    digitalWrite(S03, LOW); 
  } else if( vv == 2 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, LOW);
    digitalWrite(S03, LOW); 
  } else if( vv == 3 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, LOW);
    digitalWrite(S03, LOW); 
  } else if( vv == 4 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, LOW);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, LOW); 
  } else if( vv == 5 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, LOW);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, LOW); 
  } else if( vv == 6 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, LOW); 
  } else if( vv == 7 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, LOW); 
  } else if( vv == 8 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, LOW);
    digitalWrite(S02, LOW);
    digitalWrite(S03, HIGH); 
  } else if( vv == 9 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, LOW);
    digitalWrite(S02, LOW);
    digitalWrite(S03, HIGH); 
  } else if( vv == 10 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, LOW);
    digitalWrite(S03, HIGH); 
  } else if( vv == 11 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, LOW);
    digitalWrite(S03, HIGH); 
  } else if( vv == 12 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, LOW);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, HIGH); 
  } else if( vv == 13 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, LOW);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, HIGH); 
  } else if( vv == 14 ) {
    digitalWrite(S00, LOW);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, HIGH); 
  } else if( vv == 15 ) {
    digitalWrite(S00, HIGH);
    digitalWrite(S01, HIGH);
    digitalWrite(S02, HIGH);
    digitalWrite(S03, HIGH); 
  } else {}
}


