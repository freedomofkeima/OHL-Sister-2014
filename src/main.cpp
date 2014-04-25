#include "frame.hpp"
#include "sysfunc.h"
#include "midiplayer.hpp"
#include <fstream>
#include <cstdlib>
#include <map>
using std::ifstream; using std::cout; using std::map;

vector<Frame> frames;
map<string, int> note;

void init_sound(){
	/*note["C"] = NOTE_C;
	note["C#"] = NOTE_Cc;
	note["Db"] = NOTE_Db;
	note["D"] = NOTE_D;
	note["D#"] = NOTE_Dc;
	note["Eb"] = NOTE_Eb;
	note["E"] = NOTE_E;
	note["F"] = NOTE_F;
	note["F#"] = NOTE_Fc;	
	note["Gb"] = NOTE_Gb;
	note["G"] = NOTE_G;
	note["G#"] = NOTE_Gc;
	note["Ab"] = NOTE_Ab;
	note["A"] = NOTE_A;
	note["A#"] = NOTE_Ac;
	note["Bb"] = NOTE_Bb;
	note["B"] = NOTE_B;
	note["0"] = NOTE_MUTE;*/
	
	note["C"] = 0;
	note["C#"] = 1;
	note["Db"] = 1;
	note["D"] = 2;
	note["D#"] = 3;
	note["Eb"] = 3;
	note["E"] = 4;
	note["F"] = 5;
	note["F#"] = 6;	
	note["Gb"] = 6;
	note["G"] = 7;
	note["G#"] = 8;
	note["Ab"] = 8;
	note["A"] = 9;
	note["A#"] = 10;
	note["Bb"] = 10;
	note["B"] = 11;
	note["0"] = -1;
}

int main(int argc, char** argv){

	if (argc < 2){
		cout << "Please insert the video file"<<endl;
		exit(1);
	}

	init_sound();
	show_cursor(false);
	
	for (int k = 1; k < argc; k++){
		ifstream in(argv[k]);
		
		if (!in.is_open()){
			cout << "file not found: " << argv[k] << endl;
			show_cursor(true);
			exit(1);
		}
		
		int num_frames, x, y; 
		string x_shift = "", y_shift = "";
		in >> x; in >> y;
		
		for (int i = 0; i < x; i++) x_shift += " ";
		for (int i = 0; i < y; i++) y_shift += "\n";
		
		while(1){
			Frame frame(x_shift, y_shift);
			in >> frame;
			
			if (frame.size < 0)
				break;
			else
				frames.push_back(frame);
		}
		
		in.close();
	}
	
	int length, last_color = 0;
	
	MIDIPlayer player;
	
	for (int i = 0; i < frames.size(); i++){
		// graphic phase
		cls();
		
		if (last_color != frames[i].color){
			last_color = frames[i].color;
			set_color(last_color);
		}
		
		cout << frames[i];
		
		length = frames[i].length;
		
		// audio phase
		for (int j = 0; j < frames[i].events.size(); j++){
			MidiEvent *tn = &frames[i].events[j];
			//beep(note[tn->note], tn->octave, tn->length);
			if (tn->voice < 0){
				length -= tn->length;
				player.playNote(note[tn->note], tn->octave);
				sleep(tn->length);
				player.stopNote(note[tn->note], tn->octave);
			}else{
				player.setVoice(tn->voice);
			}
		}
		
		// stopping
		/*for (int j = 0; j < frames[i].events.size(); j++){
			MidiEvent *tn = &frames[i].events[j];
			
			if (tn->voice < 0)
				player.stopNote(note[tn->note], tn->octave);
		}*/
		
		if (length < 0) length = 0;
		
		// more sleep
		if (i < frames.size() - 1)
			sleep(length);
	}
	
	show_cursor(true);
}