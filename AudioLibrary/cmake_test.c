#include <stdio.h>
#include <math.h>
#include <portaudio.h>

#define SAMPLE_RATE 44100
#define AMPLITUDE 0.5
#define FREQUENCY 440.0

static int callback(const void *input, void *output,
                    unsigned long frameCount,
                    const PaStreamCallbackTimeInfo* timeInfo,
                    PaStreamCallbackFlags statusFlags,
                    void *userData) {
    float *out = (float*)output;
    static double phase = 0.0;
    for (unsigned int i = 0; i < frameCount; i++) {
        out[i] = AMPLITUDE * sin(phase);
        phase += 2.0 * M_PI * FREQUENCY / SAMPLE_RATE;
    }
    return paContinue;
}

int main() {
    Pa_Initialize();

    PaStream *stream;
    Pa_OpenDefaultStream(&stream, 0, 1, paFloat32, SAMPLE_RATE, 256, callback, NULL);
    Pa_StartStream(stream);

    printf("Playing for 3 seconds...\n");
    Pa_Sleep(3000);

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    printf("Done.\n");
    return 0;
}

