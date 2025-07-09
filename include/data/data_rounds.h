#ifndef DATA_ROUNDS_H
#define DATA_ROUNDS_H

#include <stdint.h>
#include <stdlib.h>

#include "datatypes/round.h"

#define ROUND_COUNT 3

const struct round* data_rounds_get(u16 round);

extern const struct round DATA_ROUNDS_ROUND0;
extern const struct round DATA_ROUNDS_ROUND1;
extern const struct round DATA_ROUNDS_ROUND2;

#endif
