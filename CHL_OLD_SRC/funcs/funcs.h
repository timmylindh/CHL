#ifndef FUNCS_H_
#define FUNCS_H_

#include "../core/types.h"

typedef struct {
	ARGS argument;
	t_STATE type;
} Argument;

// Execute function [name]
t_STATE function(char * name, ARGS args);

#endif /* FUNCS_H_ */
