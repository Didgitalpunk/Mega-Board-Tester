#define MAX 69
#define MIN 0

const int pins[MAX+1] = { 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54};
const int* pin = &pins[0];

int increment(int val, int inc) {
    if (val + inc <= MAX) { return val + inc; }
    else { return MIN + ((val + inc) % MAX-1); }
}
int decrement(int val, int dec) {
    if (val - dec >= MIN) { return val - dec; }
    else {return MAX - (val-dec+1)*-1;}
}
void pointerincrement(int inc) {
    int val = (pin - pins);
    if (val + inc <= MAX) { pin = &pins[val + inc]; }
    else { pin = &pins[MIN + ((val + inc) % MAX - 1)]; }
}
void pointerdecrement(int dec) {
    int val = (pin - pins);
    if (val - dec >= MIN) { pin = &pins[val - dec]; }
    else { pin = &pins[MAX - (val - dec + 1) * -1]; }
}