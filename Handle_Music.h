#ifndef HANDLE_MUSIC_H
#define HANDLE_MUSIC_H
#include "SDL.h"
#include "SDL_mixer.h"

class Handle_Music
{
    public:
        Handle_Music(){
            if (SDL_Init(SDL_INIT_AUDIO) < 0)
            {
                std::cout << "SDL_Init failed: " << SDL_GetError() << std::endl;
            }
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                std::cout << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
            }

            soundtrack = Mix_LoadMUS("music.mp3");
            if (!soundtrack)
            {
                std::cout << "Mix_LoadMUS failed: " << Mix_GetError() << std::endl;
            }
        }

        void play_soundtrack(){
            Mix_PlayMusic(soundtrack, -1);
        }

        void clean_music(){
            Mix_FreeMusic(soundtrack);
            Mix_CloseAudio();
        }

    private:
        Mix_Music* soundtrack = nullptr;
};

#endif // HANDLE_MUSIC_H
