#ifndef MIDI_HPP
#define MIDI_HPP

#include <windows.h>
#include <cstdio>
#include <mmsystem.h>

class MIDIPlayer{
	private:
		HMIDIOUT mid; int currentVoice;
		int velocity;
	public:
		MIDIPlayer();
		void playNote(int note, int octave);
		void stopNote(int note, int octave);
		void setVoice(int voice);	
};

#endif