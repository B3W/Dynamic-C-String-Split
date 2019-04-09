/*
 * strsplt - Dynamic splitting of C-String on delimiter
 * Copyright (C) 2019  Weston Berg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Splits given C-string, str, on delimiter, delim, and stores
 * the split tokens in a dynamically sized array of C-strings.
 * The returned array must be freed by the caller.
 *
 * @param   str    C-string to split
 * @param   delim  Delimiter to split string on
 * @return  Array of C-strings containing all string tokens in order
 *          which they were split
 */
char **strsplit(char *str, const char *delim)
{
  size_t arrSz = 2;    /* Keep track of array size -> modifiable */
  size_t arrIndex = 0; /* Keep track of location in array */
  char **spltArr;      /* Array holding split string */
  char **reallocBuf;   /* For making sure no leak w/realloc */

  // Allocate space for split string array
  if(!(spltArr = malloc(arrSz * sizeof(*spltArr)))) {
    printf("malloc failed\n");
    return NULL;
  }

  // Populate first index of array before loop to avoid seg fault
  spltArr[arrIndex] = strtok(str, delim);
  
  // Split until end of string
  while(spltArr[arrIndex] != NULL) {
    arrIndex++;
    // Resize spltArr if necessary
    if(arrIndex >= arrSz) {
      // Modifiable resize logic
      // Change depending on whether space or time efficiency is preferred
      arrSz = arrSz << 1;
      // 'realloc' does not free buffer on error so need temp to avoid mem leak
      if(!(reallocBuf = realloc(spltArr, (arrSz * sizeof(*spltArr))))) {
	printf("realloc failed\n");
	free(spltArr);
	return NULL;
      }
      spltArr = reallocBuf;
    }
    spltArr[arrIndex] = strtok(NULL, delim);
  }
  return spltArr;
}

/*
 * Example usage of strsplit()
 */
int main(int argc, char *argv[])
{
  const char delim[2] = " ";
  char msg[] = "Dynamically split this string w/ strsplit!";
  size_t index = 0;
  char **splitArr;

  if(!(splitArr = strsplit(msg, delim))) {
    exit(EXIT_FAILURE);
  }

  while(splitArr[index] != NULL) {
    printf("%s\n", splitArr[index++]);
  }

  free(splitArr);

  return 0;
}
