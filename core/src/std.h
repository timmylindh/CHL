#ifndef STD_H_
#define STD_H_

#define malloc std_malloc
#define realloc std_realloc

void * std_malloc(size_t);
void * std_realloc(void *, size_t);

#endif /* STD_H_ */
