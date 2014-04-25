#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>
#include <string>
#include <iostream>

using std::string; using std::vector; using std::endl;
using std::ostream; using std::istream; using std::getline;

typedef struct {
	string note;
	int octave;
	int length;
	int voice;
} MidiEvent;

class Frame{
	public:
		string x_shift; string y_shift;
		
		vector<string> part;
		vector<MidiEvent> events;
		int length; int size; int color;
		
		Frame(){};
		Frame(string xs, string ys) : x_shift(xs), y_shift(ys){}
		
		void readTone(string input);
		
		friend istream& operator>> (istream&, Frame&);
		friend ostream& operator<< (ostream&, Frame&);
		
};

#endif