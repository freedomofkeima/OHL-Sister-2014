#include "midiplayer.hpp"
#include <cstdlib>

MIDIPlayer::MIDIPlayer(){
	if(midiOutOpen(&mid,(UINT)-1,0,0,0))
		exit(1);
		
	velocity = 127;
	setVoice(0); // default
}

void MIDIPlayer::playNote(int note, int octave){
	if (note < 0) return;
	
	note += octave * 12;

	DWORD msg;
	int event,hi,low;
	event=144;   // event 144 = play sound
	low=(note*256)+event;
	hi=velocity*256*256;
	msg=low+hi;
	midiOutShortMsg(mid,msg);
}

void MIDIPlayer::stopNote(int note, int octave){
	if (note < 0) return;
	
	note += octave * 12;

	DWORD msg;
	int event,low;
	event=144;
	low=(note*256)+event;
	msg = low;
	midiOutShortMsg(mid,msg);
}

void MIDIPlayer::setVoice(int voice){
	if (voice == currentVoice)
		return;
		
	currentVoice = voice;
	
	DWORD msg; int event,velocity,hi,low;
    event=192; // event 192 = voice change
    low=(voice*256)+event;
    hi=velocity*256*256;
    msg=low+hi;
	midiOutShortMsg(mid,msg);
}