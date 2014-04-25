#include "frame.hpp"
#include <sstream>

using std::stringstream;

void Frame::readTone(string input){
	stringstream ss(input);
	string read;
	do{
		read = "";
		ss >> read;
		if (read.length() > 0){
			MidiEvent t;
			
			if (read == "0"){
				t.octave = 0; t.note = "0";
				ss >> t.length;
				t.voice = -1;
			}else if(read == "VC"){
				ss >> t.voice;
			}else{
				t.octave = read[read.length() - 1] - '0';			
				t.note = read.substr(0, read.length() - 1);
				ss >> t.length;
				t.voice = -1;
			}
			
			events.push_back(t);
		}		
	}while (read.length() > 0);
}

istream& operator>> (istream& in, Frame& frm){
	in >> frm.size;
	
	if (frm.size < 0)
		return in;
	
	in >> frm.length;
	in >> frm.color;
	
	string line;
	getline(in, line); frm.readTone(line);
	
	for (int i = 0; i < frm.size; i++){
		getline(in, line);
		frm.part.push_back(line);
	}
	
	return in;
}

ostream& operator<< (ostream& out, Frame& frm){
	out << frm.y_shift;
	for (int i = 0; i < frm.size; i++){
		out << frm.x_shift << frm.part[i] << endl;
	}
	
	return out;
}