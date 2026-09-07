#include "s21_cat.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int S21_Cat(int argc, char **argv);
int Parse_Cat_Op(char *option, op *opts);
int Read_Files(op opt, char *fname, int *linecount, int *nlcount);

int main(int argc, char **argv) {
  S21_Cat(argc, argv);
  return 0;
}

int S21_Cat(int argc, char **argv) {
  op opt = {0};
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') Parse_Cat_Op(argv[i], &opt);
  }
  int linecount = 0, nlcount = 1;
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') Read_Files(opt, argv[i], &linecount, &nlcount);
  }
  return 0;
}

int Parse_Cat_Op(char *option, op *opt) {
  op empty = {0};
  int res = 0;
  if (option[1] == '-') {
    if (strcmp(option, "--number") == 0)
      opt->n = 1;
    else if (strcmp(option, "--number-nonblank") == 0)
      opt->b = 1;
    else if (strcmp(option, "--squeeze-blank") == 0)
      opt->s = 1;
    else
      res = 1;
  } else {
    unsigned long l = 0;
    l = strlen(option);
    for (unsigned long i = 1; i < l && res == 0; i++) {
      if (option[i] == 'b')
        opt->b = 1;
      else if (option[i] == 'e') {
        opt->e = 1;
        opt->v = 1;
      } else if (option[i] == 'E')
        opt->e = 1;
      else if (option[i] == 'n')
        opt->n = 1;
      else if (option[i] == 's')
        opt->s = 1;
      else if (option[i] == 't') {
        opt->t = 1;
        opt->v = 1;
      } else if (option[i] == 'T')
        opt->t = 1;
      else if (option[i] == 'v')
        opt->v = 1;
      else
        res = 1;
    }
  }
  if (opt->b) opt->n = 0;
  if (res == 1) {
    fprintf(stderr, "s21_cat: invalid option '%s'\n", option);
    *opt = empty;
  }
  return res;
}

int Read_Files(op opt, char *fname, int *lc, int *nlc) {
  int ch = '\0';
  int pr = '\0';
  int nl = *nlc;
  int retval = 0;
  if (nl) pr = '\n';
  FILE *fp = fopen(fname, "r");
  if (!fp)
    retval = 1;
  else
    ch = fgetc(fp);
  while (ch != EOF && !retval) {
    if (ch == '\n')
      nl++;
    else
      nl = 0;
    if ((opt.s && nl <= 2) || (!opt.s)) {
      if (opt.b && pr == '\n' && ch != '\n')
        printf("%6d\t", ++(*lc));
      else if (opt.n && pr == '\n')
        printf("%6d\t", ++(*lc));
      if (opt.v && ch != '\n' && ch != '\t') {
        if (ch < 32)
          printf("^%c", ch + 64);
        else if (ch == 127)
          printf("^?");
        else if (ch > 127 && ch < 160)
          printf("M-^%c", ch - 64);
        else if (ch >= 160 && ch < 255)
          printf("M-%c", ch - 128);
        else if (ch == 255)
          printf("M-^?");
        else
          printf("%c", ch);
      } else if (opt.t && ch == '\t')
        printf("^I");
      else if (opt.e && ch == '\n')
        printf("$%c", ch);
      else
        printf("%c", ch);
    }
    if (opt.s && nl > 2) {
      while (ch == '\n') {
        pr = ch;
        ch = fgetc(fp);
      }
    } else {
      pr = ch;
      ch = fgetc(fp);
    }
  }
  *nlc = nl;
  if (!fp) fprintf(stderr, "s21_cat: %s: no such file or directory\n", fname);
  if (fp) fclose(fp);
  return retval;
}
