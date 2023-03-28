//Version 1.2.1    3/27/2023
//Credits to Freya Mutschler and Diana N. Corsten

constexpr auto MIN = 0;

#if defined(__AVR_ATmega328P__)
constexpr auto MAX = 19;
constexpr auto Shift = 4;
constexpr auto Delay = 100;
int pins[MAX+1] = {  7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12 , 11, 10, 9, 8 };
#endif

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
constexpr auto MAX = 69;
constexpr auto Shift = 6;
constexpr auto Delay = 75;
const int pins[MAX+1] = {
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54};
#endif

int increment(int val, int inc) {
    if (val + inc <= MAX) { return val + inc; }
    else { return MIN + ((val + inc) % MAX-1); }
}
int decrement(int val, int dec) {
    if (val - dec >= MIN) { return val - dec; }
    else {return MAX - (val-dec+1)*-1;}
}

void setup() {}

void loop() {
int  x = 0;
  for (x = MIN; x <= MAX; x++) {
    pinMode(pins[x], OUTPUT);
    digitalWrite(pins[x], LOW);
    digitalWrite(pins[decrement(x,Shift)], LOW);
    digitalWrite(pins[x], HIGH);
    delay(Delay);
  }
  if (x > 69) { x = 0; }
}
