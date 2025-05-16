
#ifndef _HOPFNTSRP_H
#define _HOPFNTSRP_H

#include <stdio.h>
#include <stdlib.h>

/* 1D represention of the pattern '9' to be stored in memory. */
#define NUM_NEURONS 77 

void init_hopfield_weights(float weights[][NUM_NEURONS]);

void hebbian_training(float weights[][NUM_NEURONS], int pattern[NUM_NEURONS]);

void synchronous_update(float weights[][NUM_NEURONS], int neurons[NUM_NEURONS]);

void render_pattern(int pattern[NUM_NEURONS]);

#endif