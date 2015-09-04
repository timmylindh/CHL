#ifndef ERROR_H_
#define ERROR_H_

#define ERROR_LIM 100
#define SET_ERROR(...) snprintf(CHL_ERROR, ERROR_LIM, __VA_ARGS__)

extern char CHL_ERROR[ERROR_LIM];

void print_error();

#endif /* ERROR_H_ */
