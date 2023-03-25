//Version 1.1 ---- 3/25/2023


int LEDmega[] = {
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54
};

int LEDmegaoff[] = {
59, 58, 57, 56, 55, 54,
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60
};

int LEDuno[] = {  7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12 , 11, 10, 9, 8 };

int LEDunooff[] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14 };

void setup() {
  
}

void loop() {

  int x = 0;
  int type = 1 ;//0 for mega, 1 for uno
  
while(type == 0){
  for (x = 0; x <= 69; x++) {
    pinMode(LEDmega[x], OUTPUT);
    digitalWrite(LEDmega[x], LOW);
    digitalWrite(LEDmegaoff[x], LOW);
    digitalWrite(LEDmega[x], HIGH);
    delay(50);
  }
  if (x > 69) { x = 0; }
}

while(type == 1){
    int x = 0;
  for (x = 0; x <= 19; x++) {
    pinMode(LEDuno[x], OUTPUT);
    digitalWrite(LEDuno[x], LOW);
    digitalWrite(LEDunooff[x], LOW);
    digitalWrite(LEDuno[x], HIGH);
    delay(75);
  }
  if (x > 19) { x = 0; }
  
}
}
