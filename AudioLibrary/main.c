#include <stdio.h>
#include <stdlib.h>
#include <portaudio.h>

#define SAMPLE_RATE       44100
#define NUM_CHANNELS      1
#define SAMPLE_FORMAT     paInt16
#define FRAMES_PER_BUFFER 512
#define SECONDS_TO_RECORD 5
#define FILENAME          "recorded_audio.pcm"

typedef short SAMPLE;

int main() {
    PaStream *stream;
    PaError err;
    FILE *pcmFile;
    SAMPLE buffer[FRAMES_PER_BUFFER];
    int total_frames = SAMPLE_RATE * SECONDS_TO_RECORD;
    int total_samples = total_frames * NUM_CHANNELS;

    // Open file for writing raw PCM
    pcmFile = fopen(FILENAME, "wb");
    if (!pcmFile) {
        fprintf(stderr, "Failed to open file for writing\n");
        return 1;
    }

    err = Pa_Initialize();
    if (err != paNoError) goto error;

    // Open input stream
    err = Pa_OpenDefaultStream(&stream, 1, 0, SAMPLE_FORMAT, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, NULL, NULL);
    if (err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;

    printf("Recording...\n");

    int frames_recorded = 0;
    while (frames_recorded < total_frames) {
        int frames_to_read = FRAMES_PER_BUFFER;
        if (frames_recorded + FRAMES_PER_BUFFER > total_frames)
            frames_to_read = total_frames - frames_recorded;

        err = Pa_ReadStream(stream, buffer, frames_to_read);
        if (err != paNoError) goto error;

        fwrite(buffer, sizeof(SAMPLE), frames_to_read, pcmFile);
        frames_recorded += frames_to_read;
    }

    fclose(pcmFile);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);

    printf("Recording complete. Now playing back...\n");

    // Open file for reading raw PCM
    pcmFile = fopen(FILENAME, "rb");
    if (!pcmFile) {
        fprintf(stderr, "Failed to open file for reading\n");
        return 1;
    }

    err = Pa_OpenDefaultStream(&stream, 0, 1, SAMPLE_FORMAT, SAMPLE_RATE,
                               FRAMES_PER_BUFFER, NULL, NULL);
    if (err != paNoError) goto error;

    err = Pa_StartStream(stream);
    if (err != paNoError) goto error;

    int samples_read;
    while ((samples_read = fread(buffer, sizeof(SAMPLE), FRAMES_PER_BUFFER, pcmFile)) > 0) {
        err = Pa_WriteStream(stream, buffer, samples_read);
        if (err != paNoError) {
            fprintf(stderr, "Playback error: %s\n", Pa_GetErrorText(err));
            break;
        }
    }

    fclose(pcmFile);
    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    printf("Playback complete.\n");
    return 0;

error:
    fprintf(stderr, "PortAudio error: %s\n", Pa_GetErrorText(err));
    Pa_Terminate();
    return 1;
}

