#ifndef DATA_ROUNDS_H
#define DATA_ROUNDS_H

#include <stdint.h>
#include <stdlib.h>

#include "datatypes/round.h"

const struct round* data_rounds_get(u16 round);

extern const struct round DATA_ROUNDS_ROUND0;

#endif
