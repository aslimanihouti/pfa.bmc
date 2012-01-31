#ifndef PLAYER_H
#define PLAYER_H

/**
 * \file player.h
 * \author Team BMC editor 
 */

void free_mix_music(Mix_Music *myMus);

void *bmc_play_(void *);

void bmc_play();

void bmc_pause();

void bmc_resume();

#endif
