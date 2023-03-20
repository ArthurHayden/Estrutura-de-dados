#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

struct dataset {
  char Date_submitted[7];
  int rating;
};

int calcAverage() {
  // Opening and creation of files.
  FILE *file = fopen("reviews.csv", "r");
  FILE *file2 = fopen("average.csv", "w");
  if (file == NULL || file2 == NULL) {
    printf("Error opening file");
    return 1;
  }
  
  // Memory alocation for the data in a struct format.
  struct dataset *data =
      malloc(lineCounter("reviews.csv") * sizeof(struct dataset));
  if (data == NULL) {
    printf("Error alocating memory");
    return 1;
  }

  int i = 0;
  char line[100];
  char *date;
  // Storage of data in struct format.
  while (fgets(line, 100, file) != NULL) {
    fscanf(file, "%19[^,],%d", data[i].Date_submitted, &data[i].rating);
    // tokenizing the Date_submitted string to only the date.
    date = strtok(data[i].Date_submitted, " ");
    // Deleting the time from the string.
    date[7] = '\0';
    // Storing the date in the struct array.
    strcpy(data[i].Date_submitted, date);
    i++;
  }

  int cont = 0;
  // Iterator to find the same date
  int aux = 1;
  while (aux < lineCounter("reviews.csv") - 2) {
    float average = data[cont].rating;
    fputs(data[cont].Date_submitted, file2);

    // Comparing the dates and adding to the average if they are equal
    while (strcmp(data[cont].Date_submitted, data[aux].Date_submitted) == 0) {
      average += data[aux].rating;
      aux++;
    }

    // calculating average
    average = average / (aux - cont);
    fprintf(file2, ",%.2f\n", average);
    cont = aux;
  }

  fclose(file);
  fclose(file2);
  free(data);
  return 0;
}