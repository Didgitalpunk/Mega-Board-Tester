// And now I see with eye serene, the very pulse of the machine

// Arduino Board Tester Program Version 2.0 March 31 2023 
// Design and Fabrication by Freya Mutschler
// Code by Diana N. Corsten and Freya Mutschler

constexpr auto MIN = 0;

#if defined(__AVR_ATmega328P__)
// Arduino Uno (R1, R2, R3), Arduino Nano 
constexpr auto MAX = 19;
constexpr auto SHIFT = 4;
constexpr auto DELAY = 100;
int pins[MAX+1] = {  7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14, 13, 12 , 11, 10, 9, 8 };

#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1284__) || defined(__AVR_ATmega1284P__) || defined(__AVR_ATmega644__) || defined(__AVR_ATmega644A__) || defined(__AVR_ATmega644P__) || defined(__AVR_ATmega644PA__)
// Arduino Mega
constexpr auto MAX = 69;
constexpr auto SHIFT = 6;
constexpr auto DELAY = 75;
const int pins[MAX+1] = {
13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2,
1, 0, 14, 15, 16, 17, 18, 19,
20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
50, 51, 52, 53,
69, 68, 67, 66, 65, 64,
63, 62, 61, 60, 59, 58, 57, 56, 55, 54};

#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__)
//Arduino Leonardo, not yet implemented

#elif defined(NYI)
// Arduino Zero, not yet implemented
constexpr auto MAX = 21;
constexpr auto SHIFT = 4;
constexpr auto DELAY = 100;
int pins[MAX+1] = { 21, 20, 13, 12 , 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 19, 18, 17, 16, 15, 14 };
#endif

class Pin{
    int _num; 

public:
    // Constructors
    Pin() { _num = MIN; }
    Pin(unsigned num) {
		if (num <= MAX && num >= MIN) { _num = num; } // Incorrect initialization via assignment is handled by setting _num to MIN and then adding the incorrect assignment
		else { _num = MIN; this->operator+=(num); }    
	}
    Pin(const Pin& otherpin) : _num(otherpin._num) {} 
    
    // Int Conversion
    operator int() { return _num; }
    
    // Operators
    bool operator == (const Pin& otherpin) const { return this->_num == otherpin._num; }
	bool operator == (const int rhs) const { return _num == rhs; }
    
    Pin& operator = (const Pin& otherpin) {
		if (this != &otherpin) { _num = otherpin._num; } 
		return *this;
	}

    Pin& operator =(int set) {
		if (set != this->_num) {
			if (set <= MAX && set >= MIN) { _num = set; } 
			else { _num = MIN; return this->operator+(set); } // incorrect assignment is handled by setting _num to MIN and then adding the incorrect assignment, thus producing a valid result
		}
		return *this;
	}

    Pin& operator +=(int add) {
		if (add != 0) {
			if (add < 0) { return this->operator-=(abs(add)); } // attempting to use a negative number will simply invoke the - operator
			_num = (_num + add - MIN) % (MAX - MIN + 1) + MIN;
		}
		return *this;
	}

    Pin& operator -=(int sub) {
		if (sub != 0) {
			if (sub < 0) { return this->operator+=(abs(sub)); } // attempting to use a negative number will simply invoke the += operator
			_num = ((_num - sub - MIN) % (MAX - MIN + 1) + (MAX - MIN + 1)) % (MAX - MIN + 1) + MIN; // The % operator can not handle negatives like it does overflowing positives,
		}                                                                                            // so this part looks a lot more complicated.       
		return *this;                                                                                // The added complexity of `+/- MIN` is to ensure that MIN != 0 would still produce       
	}                                                                                                    // the desired results.
    	int operator-(int sub) {
        return ((_num - sub - MIN) % (MAX - MIN + 1) + (MAX - MIN + 1)) % (MAX - MIN + 1) + MIN;
    }
    	int operator+(int add) {
        return (_num + add - MIN) % (MAX - MIN + 1) + MIN;
    }
	
	Pin& operator++() { 
        _num = _num == MAX ? MIN : _num + 1;
        return *this;
	}

	Pin operator++(int) { 
		Pin temp(*this);
		_num = _num == MAX ? MIN : _num + 1;
		return temp;
	}

    Pin& operator --() {
            _num = _num == MIN ? MAX : _num - 1;
            return *this;
	}

    Pin operator --(int) {
            Pin temp(*this);
            _num = _num == MIN ? MAX : _num - 1;
            return temp;
	}
};

void setup(){
    
    for(int i; i <= MAX; i++){
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], LOW);
    }
}

void loop(){

    Pin p1;
    for(p1 = MIN; p1 <= MAX; p1++){
               
        digitalWrite(pins[p1 - SHIFT], LOW);
        digitalWrite(pins[p1], HIGH);
        delay(DELAY);
        if(p1 == MAX) {break;}

    }

}
