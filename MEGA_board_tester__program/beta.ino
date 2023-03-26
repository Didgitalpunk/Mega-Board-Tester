#define MIN 0

#if defined(__AVR_ATmega328P__)
#define MAX 19
#define Shift 4
#define Delay 100
int pins[MAX + 1] = { 7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12 , 11, 10, 9, 8 };

#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
#define MAX 69
#define Shift 6
#define Delay 75
const int pins[MAX + 1] = {
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54 };

#else // this is the default case so that this actually compiles outside of the Arduino IDE and so I can use print statements to debug
#include <stdio.h>
#define MAX 69
#define Shift 6
#define Delay 75
const int pins[MAX + 1] = {
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54 };
#endif

struct Pin {

	int num = MIN; // number of the Pin *in the array*, not representative of the position on the board
	// bool state = false // you could add a boolean to track whether or not a Pin is currently powered or not. Obviously this is worthless if you're rapidly iterating,
	// but it could be useful if you have a separate Pin object to track a specific pin. 
	void On() {
	//TODO: add the correct text here to activate the output on the pin we are targeting, ie somethingSomethingDigitalWrite(num, HIGH) or some such

	}
	void Off() {
	//TODO: the same thing as above, only for turning it off 

	}
	int operator ++() {    // pre increment // NOTE: ALL the arithmetic operators are boundary checked, meaning they loop by themselves. Using them in a loop will, predictably,
		if (num + 1 <= MAX) { num++; }	// make your loop infinite. You only need these if you are doing raw math that is not being checked by anything else. 
		else { num = MIN; }		// If you are in a situation where you have other forms of boundary checking, simply write to this->num 
		return num; 
	}
	int operator ++(int) { // post increment
		if (num + 1 <= MAX) { num++; }
		else { num = MIN; }
		return num;
	}
	int operator --() {    // pre decrement
		if (num - 1 >= MIN) { num--; }
		else { num = MAX; }
		return num;
	}
	int operator --(int) { // post decrement
		if (num - 1 >= MIN) { num--; }
		else { num = MAX; }
		return num;
	}
	int operator +(int inc) { // adding/subtracting an int to/from the Pin will increase/decrease its num 
		if (num + inc <= MAX) { num = num + inc; }
		else { num = MIN + ((num + inc) % MAX - 1); }
		return num;
	}

	int operator -(int dec) {
		if (num - dec >= MIN) { num = num - dec; }
		else { num = MAX - (num - dec + 1) * -1; }
		return num;
	}
	int operator =(int val) { // assigning to a Pin object manipulates its num
		if (val <= MAX && val >= MIN) { num = val; }
		else { num = MIN; } // if your assignment is out of bounds, you just go back to MIN. This could be changed.
    return num;
	}
	operator int() { // if a Pin object is converted to int, it will be represented by its number
		return num;
	}
	// operator bool() {return state;} // this could potentially be used to evaluate a Pin object as a boolean via its on/off state

	Pin(int pin) { num = pin; } // if invoked with a number, the constructor will set num to what you specify
	Pin() { num = MIN; }        // otherwise, the default constructor will leave it as MIN

};
void explain() { // reading material, will get optimized out because it's not called
	Pin Example; // the Pin object starts out targeting pins[MIN]
	Example = 1; // assignment would make this Pin target pins[1]
	Example++; // inrement to pins[2]
	Example--; // back to 1;
	Example = Example + Example; // combining operators, sets the LED to 2. Note that if you did these multiple times, you'd get odd results, 
				     // for example LED = LED + LED + LED is actually 5 because of how the order of operations works

	if (Example == 2) {} // evaluates to true because the LED is converted to int here, essentially this says if( (int)Example == 2 ) 
	// this also enables you to do the following things:
	int x = pins[Example];
	Example - 3;
	x = 69 - Example;
	Example = 2375; // sets the LED to 0 because 2375 is out of bounds of the array
	Pin Example2(12);
	Example = Example2; // makes this LEDs num identical to LED2s num
	if (Example == Example2) {} // this is true now, since their nums are equal. if you added more class members, like the state bool, 
				    //you'd need to manually implement the operator



}

void setup(){  }

// example of your loop() function only with prints, because I don't have the Arduino IDE or a board.
void loop() {
	Pin LED;
	for (LED = MIN; LED <= MAX; LED.num++) { // you can (in fact, you have to) use the unsafe incrementation in a for loop, because otherwise you end up
						 // with an infinite loop. This is perfectly safe here because the for loop does boundary checking 
						 // by its very nature.
		
		printf("%i\n", pins[LED.num]);	  // comment this and uncomment the rest to test it on the board.  
		// pinMode(pins[LED], OUTPUT);
		// digitalWrite(pins[LED - Shift], LOW);
		// digitalWrite(pins[LED], HIGH);
		// delay(Delay)
	}
	// Ironically, this turned out to be a superfluous implementation. The increment() function did this perfectly well. 
	// You probably shouldn't use any of this for the actual board tester, but it might become useful later if we add more functionality.
	// For now, this was just a fun exercise I did that might teach you some stuff about C++. I'd still be curious to know if this actually works on the board
  	// or if I made any more glaring errors. If you end up trying it, let me know how it goes. Love, Diana 

}
