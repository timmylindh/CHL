#ifndef INLINE_H_
#define INLINE_H_

char parse_inline(char **, char *, int *);
void chl_func_append(char *, void (*)(char *));
char chl_func(char *, char *);
char * chl_next_arg(char *);
char chl_get_args(char *(**), char *);

#endif /* INLINE_H_ */
