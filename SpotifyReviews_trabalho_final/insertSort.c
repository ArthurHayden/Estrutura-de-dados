#include "header.h"
#include <stdio.h>
#include <string.h>

typedef struct {
  char date[7];
  float average;
} dataset;

int insertSort(void) {
  // Opening and creation of files.
  dataset data[lineCounter("average.csv")];
  FILE *file = fopen("average.csv", "r+");
  if (file == NULL) {
    printf("Error opening file");
    return 1;
  }

  int index = 0;
  char line[100];
  // Storage of data in struct format.
  while (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%[^,],%f", data[index].date, &data[index].average);
    index++;
  }
// Insertion sort
  int i, j;
  dataset key;
  for (i = 1; i < index; i++) {
    key = data[i];
    j = i - 1;

    while (j >= 0 && data[j].average < key.average) {
      data[j + 1] = data[j];
      j = j - 1;
    }
    data[j + 1] = key;
  }
  // Reopens the file in the writting mode
  FILE *file2 = freopen("average.csv", "w", file);
  
  //Printting of values and months
  for (int i = 0; i < index; i++) {
    fprintf(file2, "%s,%.2f\n", data[i].date, data[i].average);
  }

  fclose(file);
  return 0;
}