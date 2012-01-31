#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <pthread.h>

#define MUSIC_FILE "music.mid"

/**
 * \file player.c
 * \author Team BMC editor 
 */



/**
 * \fn Mix_Music *create_mix_music(char *music_file)
 * \brief This function creates and initialize an instance of Mix_Music with the name of the music file. 
 * \param music_file the name of music file.
 */

/**
 * \fn void free_mix_music(Mix_Music *myMus)
 * \brief This function delete an instance of Mix_Music. 
 * \param myMus a pointer to the instance to delete.
 */


void free_mix_music(Mix_Music *myMus)
{
    Mix_FreeMusic(myMus);
    Mix_CloseAudio();
}

/**
 * \fn void *bmc_play_(void *)
 * \brief This function plays the music contained in an instance of Mix_Music. 
 */

void *bmc_play_(void *v)
{   
    //Mix_Music holds the music information.
    Mix_Music* myMus;

    // initialize thz sound
    SDL_Init(SDL_INIT_AUDIO);
    
    // open up an audio device.
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)) {
	printf("Unable to open audio!\n");
	exit(1);
    }
    
    // load the music file
    myMus = Mix_LoadMUS(MUSIC_FILE);

    /* play the music */
    Mix_PlayMusic(myMus, 1);

    while (Mix_PlayingMusic() == 1) {
	//While th music isn't finshed, we do something otherwise the programme exits and stops playing 
	SDL_Delay(10);
    }
    free_mix_music(myMus);
    return NULL;
}

/**
 * \fn void bmc_play()
 * \brief This function calls bmc_play_() in a new thread. 
 */

void bmc_play()
{   
    pthread_t t;
    pthread_create(&t,NULL, bmc_play_, NULL);
}



/**
 * \fn void bmc_pause()
 * \brief This function pauses the music. 
 */

void bmc_pause()
{
    if(Mix_PlayingMusic())
	Mix_PauseMusic();
}

/**
 * \fn void bmc_resume()
 * \brief This function resumes the paused music. 
 */

void bmc_resume()
{
    if(Mix_PausedMusic())
	Mix_ResumeMusic();
}
