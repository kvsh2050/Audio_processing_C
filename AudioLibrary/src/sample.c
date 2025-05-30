#include <stdio.h>
#include <portaudio.h>

int main() {
    Pa_Initialize();
    printf("PortAudio initialized successfully!\n");
    Pa_Terminate();
    return 0;
}
