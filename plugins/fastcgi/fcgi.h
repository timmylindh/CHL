#ifndef NO_FCGI_DEFINES

#undef  FILE
#define	FILE     FCGI_FILE

#undef  stdin
#define	stdin    FCGI_stdin
#undef  stdout
#define	stdout   FCGI_stdout
#undef  stderr
#define	stderr   FCGI_stderr

#undef  perror
#define	perror   FCGI_perror

#undef  fopen
#define	fopen    FCGI_fopen
#undef  fclose
#define	fclose   FCGI_fclose
#undef  fflush
#define	fflush   FCGI_fflush
#undef  freopen
#define	freopen  FCGI_freopen

#undef  setvbuf
#define	setvbuf  FCGI_setvbuf
#undef  setbuf
#define	setbuf   FCGI_setbuf

#undef  fseek
#define fseek    FCGI_fseek
#undef  ftell
#define ftell    FCGI_ftell
#undef  rewind
#define rewind   FCGI_rewind
#undef  fgetpos
#define fgetpos  FCGI_fgetpos
#undef  fsetpos
#define fsetpos  FCGI_fsetpos

#undef  fgetc
#define	fgetc    FCGI_fgetc
#undef  getc
#define getc     FCGI_fgetc
#undef  getchar
#define	getchar  FCGI_getchar
#undef  ungetc
#define ungetc   FCGI_ungetc

#undef  fgets
#define fgets    FCGI_fgets
#undef  gets
#define	gets     FCGI_gets

#undef  fputc
#define fputc    FCGI_fputc
#undef  putc
#define putc     FCGI_fputc
#undef  putchar
#define	putchar  FCGI_putchar

#undef  fputs
#define	fputs    FCGI_fputs
#undef  puts
#define	puts     FCGI_puts

#undef  fprintf
#define	fprintf  FCGI_fprintf
#undef  printf
#define	printf   FCGI_printf

#undef  vfprintf
#define vfprintf FCGI_vfprintf
#undef  vprintf
#define vprintf  FCGI_vprintf

#undef  fread
#define	fread    FCGI_fread
#undef  fwrite
#define fwrite   FCGI_fwrite

#undef  feof
#define	feof     FCGI_feof
#undef  ferror
#define ferror   FCGI_ferror
#undef  clearerr
#define	clearerr FCGI_clearerr

#undef  tmpfile
#define tmpfile  FCGI_tmpfile

#undef  fileno
#define fileno   FCGI_fileno
#undef  fdopen
#define fdopen   FCGI_fdopen
#undef  popen
#define popen    FCGI_popen
#undef  pclose
#define	pclose   FCGI_pclose

#endif
