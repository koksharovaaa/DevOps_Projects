#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct op {
  char patterns[16][128];
  int pcount;

  int e;  // pattern
  int i;  // ignore case
  int v;  // invert match
  int c;  // output count of matching lines only
  int l;  // outputmatching files only
  int n;  // precede each matching line with a line number

  int h;  // dont print filenames
  int s;  // dont print nonexistemt file
  int f;  // regexes from file
  int o;  // output matching parts of a line
} op;

typedef struct files {
  char fnames[16][128];
  int fcount;
} files;