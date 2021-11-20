#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct Distance_struct {
int xval;
int yval;
} Distance;

double get_perimeter(FILE* file, int num, Distance* point, double perimeter) {
  while (!feof(file)) {
    for (int i = 0; i < num; ++i) {
      fread(point + i, sizeof(struct Distance_struct), 1, file);
    }
    perimeter = 0;
    for (int i = 0; i < num; ++i) {
      int j = (i + 1) % num;
      perimeter = perimeter + sqrt(pow((point[i].xval - point[j].xval), 2) + pow((point[i].yval - point[j].yval), 2));
    }
  }
  return perimeter;
}

void free_function(Distance* point) {
  free(point);
  point = NULL;
}

void open_file(char** argv) {
  int num;  // number of vertices
  double perimeter = 0;
  struct Distance_struct* point;
  FILE* file = fopen(argv[1], "rb");
  if (file == NULL) {
    exit(0);
  }
  fread(&num, sizeof(int), 1, file);
  point = (struct Distance_struct*)malloc(num * sizeof(struct Distance_struct));  // allocate memory for point
  perimeter = get_perimeter(file, num, point, perimeter);
  printf("The perimeter is %.2f", perimeter);
  free_function(point);
}


int main(int argc, char** argv) {
  if (argc == 2) {
    open_file(argv);
  }
  return 0;
}
