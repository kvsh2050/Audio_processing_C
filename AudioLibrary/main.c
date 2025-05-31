//main.c

#include<stdio.h>
#include<portaudio.h>
#include<stdlib.h>

#define SAMPLE_RATE 44100
#define NUM_CHANNELS 1
#define SAMPLE_FORMAT paInt16
#define SECONDS_TO_RECORD 5
#define FRAMES_PER_BUFFER 512 

int main(){

//Initialization
	PaError err;
	Pastream *stream;
	FILE *outputfile;
	
	short buffer[FRAMES_PER_BUFFER];
	int numSamples = SAMPLE_RATE * SECONDS_TO_RECORD;
	int numBuffers = numSamples / FRAMES_PER_BUFFER;
	
//Exception or error code or return type handling 
	err = PaInitialize();     // Initialize the PortAudio and check for its return type 
	if(err != paNoError){
		fprintf(stderr, "PortAudio init error: %s\n", Pa_GetErrorText(err));
        	return 1;
	}
	

} 
