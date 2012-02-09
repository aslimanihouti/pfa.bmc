#ifndef PLAYER_H
#define PLAYER_H

/**
 * \file player.h
 * \author Team BMC editor 
 */

void *bmc_play_(void *);

void bmc_play();

void bmc_pause();

void bmc_resume();

void bmc_stop();

void free_mix_music();
#endif
