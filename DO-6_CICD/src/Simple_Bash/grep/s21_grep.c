#include "s21_grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

int S21_Grep(int argc, char **argv);
int Parse_Grep_Op(char *line, op *opt);
int Parse_Grep(int argc, char **argv, files *f, op *opt);
int Grep_Files(char *fname, int fcount, op opt);

int main(int argc, char **argv) {
  S21_Grep(argc, argv);
  return 0;
}

int S21_Grep(int argc, char **argv) {
  files f = {0};
  op opt = {0};
  opt.i = REG_NEWLINE;
  int retval = 0;

  for (int i = 1; i < argc && !retval; i++) {
    if (argv[i][0] == '-') retval = Parse_Grep_Op(argv[i], &opt);
  }
  retval = Parse_Grep(argc, argv, &f, &opt);
  if (!opt.pcount && !retval) {
    fprintf(stderr, "s21_grep: missing pattern\n");
    retval = 1;
  } else if (!f.fcount && !retval) {
    fprintf(stderr, "s21_grep: missing file\n");
    retval = 1;
  }
  for (int i = 0; i < f.fcount && !retval; i++) {
    Grep_Files(f.fnames[i], f.fcount, opt);
  }
  return retval;
}

int Parse_Grep_Op(char *line, op *opt) {
  unsigned long l = strlen(line);
  int retval = 0;

  for (unsigned long i = 1; i < l; i++) {
    if (line[i] == 'e') {
      opt->e++;
    } else if (line[i] == 'i')
      opt->i |= REG_ICASE;
    else if (line[i] == 'v')
      opt->v = 1;
    else if (line[i] == 'c')
      opt->c = 1;
    else if (line[i] == 'l')
      opt->l = 1;
    else if (line[i] == 'n')
      opt->n = 1;
    else if (line[i] == 'h')
      opt->h = 1;
    else if (line[i] == 's')
      opt->s = 1;
    else if (line[i] == 'f')
      opt->f++;
    else if (line[i] == 'o')
      opt->o = 1;
    else
      retval = 1;
  }
  return retval;
}

int Parse_Grep(int argc, char **argv, files *f, op *opt) {
  int fi = 0, pi = 0;
  int i = 1;
  int retval = 0;

  while (i < argc && !retval) {
    if ((argv[i][0] == '-') && strchr(argv[i], 'e')) {
      strcpy(opt->patterns[pi], argv[i + 1]);
      pi++;
      i++;
    } else if ((argv[i][0] == '-') && strchr(argv[i], 'f')) {
      FILE *fp = fopen(argv[i + 1], "r");
      if (!fp) {
        retval = 1;
        fprintf(stderr, "s21_grep: no pattern file\n");
      }
      char *p = NULL;
      while (!retval && (p = fgets(opt->patterns[pi], 128, fp)) != NULL) {
        if ((p = strchr(opt->patterns[pi], '\n')) != NULL) *p = '\0';
        pi++;
      }
      if (fp) fclose(fp);
      i++;
    } else if ((argv[i][0] != '-') && !opt->e && !opt->f) {
      strcpy(opt->patterns[pi], argv[i]);
      opt->e = 1;
      pi++;
    } else if ((argv[i][0] != '-')) {
      strcpy(f->fnames[fi], argv[i]);
      fi++;
    }
    i++;
  }
  opt->pcount = pi;
  f->fcount = fi;
  return retval;
}

int Grep_Files(char *fname, int fcount, op opt) {
  char line[LINESIZE];
  char *p = NULL;
  int linenum = 0, mcount = 0, reg = 1;
  regex_t preg_value;
  regex_t *preg = &preg_value;
  regmatch_t match;
  int retval = 0;

  FILE *fp = fopen(fname, "r");
  if (!fp) {
    retval = 1;
    if (!opt.s)
      fprintf(stderr, "s21_grep: no such file or directory '%s'\n", fname);
  }
  while (!retval && (p = fgets(line, LINESIZE, fp)) != NULL) {
    linenum++;
    reg = 1;
    for (int i = 0; i < opt.pcount; i++) {
      if (regcomp(preg, opt.patterns[i], opt.i))
        fprintf(stderr, "s21_grep: regex compilation failed\n");
      else {
        if (!regexec(preg, line, 1, &match, 0)) reg = 0;
        regfree(preg);
      }
    }
    if ((!reg && !opt.v) || (reg && opt.v)) {
      mcount++;
      if (fcount > 1 && !opt.h && !opt.l && !opt.c) printf("%s:", fname);
      if (opt.n && !opt.l && !opt.c) printf("%d:", linenum);
      if (!opt.l && !opt.c) {
        char *p = NULL;
        if ((p = strchr(line, '\n')) != NULL) *p = '\0';
        printf("%s\n", line);
      }
    }
  }
  if (opt.l && mcount)
    printf("%s\n", fname);
  else if (opt.c && !opt.l) {
    if (fcount > 1 && !opt.h) printf("%s:", fname);
    printf("%d\n", mcount);
  }
  if (fp) fclose(fp);
  return retval;
}
