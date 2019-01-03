// For receiver pins
#define receiver_S0  24
#define receiver_S1  25
#define receiver_S2  26
#define receiver_S3  27
#define receiver_S4  28
#define receiver_S5  29
#define receiver_S6  30
#define receiver_S7  31
#define receiver_EN0  32
#define receiver_EN1  33
#define receiver_EN2  34
#define receiver_EN3  35
#define receiver_EN4  36
#define receiver_SF  14
// For emitter pins
#define emitter_nLE  0
#define emitter_nE0  1
#define emitter_nE1  2
#define emitter_nE2  3
#define emitter_nE3  4
#define emitter_nE4  5
#define emitter_nE5  6
#define emitter_ADDR0  7
#define emitter_ADDR1  8
#define emitter_ADDR2  9
#define emitter_ADDR3  10

#define th 50

void setup() {
  init_pins();
  Serial.begin(115200);
}

// emitter index is 0~77 (row:0~27, col:28~77)
// receiver index is 0~74 (row:0~47, col:48~74)

void loop() {
  int i;
  int xres[27];
  int yres[48];
  // scan emitters for y-axis
  for (i = 0; i < 27; i++) {
    emitter_on_led(i);
    delayMicroseconds(375);
    xres[i] = receiver_getdata(48+i);
    //String str1 = String(xres[i]);
    //str = str+str1+",";
  }

  // scane for x-axis
  for (i = 47; i >=0; i--) {
    emitter_on_led(i+29);
    delayMicroseconds(375);
    yres[47-i] = receiver_getdata(i);
  }

  // thresolding for x-axis
  int cntx = 0;
  int valx[27], idxx[27];
  String str = "x : ";
  for (i = 0; i < 27 ; i++) {
    if (xres[i]<th) {
      valx[i] = xres[i];
      idxx[i] = i;
      cntx = cntx+1;   
      String str1 = String(idxx[i]);
      str = str + str1 +",";
    }
  }
  str = str + " == y : ";
  // thresolding for y-axis
  int cnty = 0;
  int valy[48], idxy[48];
  for (i = 0; i < 48 ; i++) {
    if (yres[i]<th) {
      valy[i] = yres[i];
      idxy[i] = i;
      cnty = cnty+1;   
      String str1 = String(idxy[i]);
      str = str + str1 +",";
    }
  }
  Serial.println(str);
  delay(10);
}

void init_pins()
{
  // for receiver pins init
  pinMode(receiver_S0, OUTPUT);
  pinMode(receiver_S1, OUTPUT);
  pinMode(receiver_S2, OUTPUT);
  pinMode(receiver_S3, OUTPUT);
  pinMode(receiver_S4, OUTPUT);
  pinMode(receiver_S5, OUTPUT);
  pinMode(receiver_S6, OUTPUT);
  pinMode(receiver_S7, OUTPUT);
  pinMode(receiver_EN0, OUTPUT);
  pinMode(receiver_EN1, OUTPUT);
  pinMode(receiver_EN2, OUTPUT);
  pinMode(receiver_EN3, OUTPUT);
  pinMode(receiver_EN4, OUTPUT);
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

//* this part is for receiver *//
// idx : index of led
int receiver_getdata(int idx_org)
{
  int val;
  int idx;
  // each 74hc4067 has 16 pins
  if (idx_org < 16) {
    idx = idx_org;
    digitalWrite(receiver_EN0, LOW); digitalWrite(receiver_EN1, HIGH); digitalWrite(receiver_EN2, HIGH); digitalWrite(receiver_EN3, HIGH); digitalWrite(receiver_EN4, HIGH); // select No0 4067.
  } else if (idx_org >= 16 && idx_org < 32){
    idx = idx_org - 16;  
    digitalWrite(receiver_EN0, HIGH); digitalWrite(receiver_EN1, LOW); digitalWrite(receiver_EN2, HIGH); digitalWrite(receiver_EN3, HIGH); digitalWrite(receiver_EN4, HIGH); // select No0 4067.
  } else if (idx_org >= 32 && idx_org < 48){
    idx = idx_org - 32;  
    digitalWrite(receiver_EN0, HIGH); digitalWrite(receiver_EN1, HIGH); digitalWrite(receiver_EN2, LOW); digitalWrite(receiver_EN3, HIGH); digitalWrite(receiver_EN4, HIGH); // select No0 4067.
  } else if (idx_org >= 48 && idx_org < 64){
    idx = idx_org - 48;  
    digitalWrite(receiver_EN0, HIGH); digitalWrite(receiver_EN1, HIGH); digitalWrite(receiver_EN2, HIGH); digitalWrite(receiver_EN3, LOW); digitalWrite(receiver_EN4, HIGH); // select No0 4067.
  } else if (idx_org >= 64 && idx_org < 75){
    idx = idx_org - 64;  
    digitalWrite(receiver_EN0, HIGH); digitalWrite(receiver_EN1, HIGH); digitalWrite(receiver_EN2, HIGH); digitalWrite(receiver_EN3, HIGH); digitalWrite(receiver_EN4, LOW); // select No0 4067.
  }
  receiver_addr_func(idx);

  if (idx_org < 16) {
    digitalWrite(receiver_S7, LOW); digitalWrite(receiver_S6, LOW); digitalWrite(receiver_S5, LOW); digitalWrite(receiver_S4, LOW);  
  } else if (idx_org >= 16 && idx_org < 32){
    digitalWrite(receiver_S7, LOW); digitalWrite(receiver_S6, LOW); digitalWrite(receiver_S5, LOW); digitalWrite(receiver_S4, HIGH);  
  } else if (idx_org >= 32 && idx_org < 48){
    digitalWrite(receiver_S7, LOW); digitalWrite(receiver_S6, LOW); digitalWrite(receiver_S5, HIGH); digitalWrite(receiver_S4, LOW);  
  } else if (idx_org >= 48 && idx_org < 64){
    digitalWrite(receiver_S7, LOW); digitalWrite(receiver_S6, LOW); digitalWrite(receiver_S5, HIGH); digitalWrite(receiver_S4, HIGH);  
  } else if (idx_org >= 64 && idx_org < 75){
    digitalWrite(receiver_S7, LOW); digitalWrite(receiver_S6, HIGH); digitalWrite(receiver_S5, LOW); digitalWrite(receiver_S4, LOW);  
  }

  val = analogRead(0);
  return val;
}

void receiver_addr_func(int idx) {
  if (idx == 0) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 1) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 2) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 3) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 4) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 5) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 6) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 7) {
    digitalWrite(receiver_S3, LOW); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 8) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 9) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 10) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 11) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, LOW); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 12) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 13) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, LOW); digitalWrite(receiver_S0, HIGH);  
  } else if (idx == 14) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, LOW);  
  } else if (idx == 15) {
    digitalWrite(receiver_S3, HIGH); digitalWrite(receiver_S2, HIGH); digitalWrite(receiver_S1, HIGH); digitalWrite(receiver_S0, HIGH);  
  } else {
  }
}

//* this part is for emitter *//

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

// algorithm
// find minimum value & index
int get_minidx(int *arr, int len)
{
  int i;
  int min_idx = -1;
  int min_val = 4095;
  for (i = 0;i < len; i++) {
    if (min_val >= arr[i]) {
      min_val = arr[i];
      min_idx = i;  
    }      
  }
  if (min_val > th) min_idx = -1;
  return min_idx;
}

// x0 : n-1 th value
// x1 : n th value
// x2 : n+1 th value
float liner_interp(int x0, int x1, int x2, int idx)
{
  if (idx < 0) return -1.0f;
  int a = x0-x1;
  int b = x2-x1;
  float xx = 2.0f*a/(a+b);
  return idx+xx-1.0f;
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
