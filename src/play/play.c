#include "play.h"
#include "utils/resolve.h"
#include "utils/playInc.h"

int play(char *musicPath) {

    char real[PATH_MAX];

    if (!resolvePath(musicPath, real)) {
        printf("File not found: %s\n", musicPath);
        return 1;
    }


    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to initialize audio system.\n");
        printf("Technical details: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Could not open audio device.\n");
        printf("Make sure no other application is using the sound device.\n");
        printf("Technical details: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

    Mix_Music* music = Mix_LoadMUS(real);

    if (!music) {
        printf("Could not load music file.\n");
        printf("File path: %s\n", musicPath);
        printf("Make sure the file exists and is a supported format.\n");
        printf("Technical details: %s\n", Mix_GetError());
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    if (Mix_PlayMusic(music, 1) < 0) {
        printf("Failed to play the music.\n");
        printf("Technical details: %s\n", Mix_GetError());
    }

    printf("Playing... press ENTER to exit\n");
    while (getchar() != '\n');
    getchar();


    Mix_FreeMusic(music);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
