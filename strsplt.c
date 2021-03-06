/*
 * Copyright (C) 2019  Weston Berg
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * strsplt - Dynamic splitting of C-String on delimiter
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
 *          which they were split terminated by NULL
 */
char **strsplt(char *str, const char *delim)
{
  size_t arrSz = 2;    /* Keep track of array size -> modifiable */
  size_t arrIndex = 0; /* Keep track of location in array */
  char **spltArr;      /* Array holding split string */
  char **reallocBuf;   /* For making sure no leak w/realloc */
  char *sPtr;          /* Pointer for context in strtok_r call */

  // Allocate space for split string array
  if(!(spltArr = malloc(arrSz * sizeof(*spltArr)))) {
    printf("malloc failed\n");
    return NULL;
  }

  // Populate first index of array before loop to avoid seg fault
  spltArr[arrIndex] = strtok_r(str, delim, &sPtr);
  
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
    spltArr[arrIndex] = strtok_r(NULL, delim, &sPtr);
  }
  return spltArr;
}

/*
 * Example usage of strsplit()
 */
int main(int argc, char *argv[])
{
  const char delim[2] = " ";
  char msg[] = "Dynamically split this string w/ strsplt!";
  size_t index = 0;
  char **splitArr;

  if(!(splitArr = strsplt(msg, delim))) {
    exit(EXIT_FAILURE);
  }

  while(splitArr[index] != NULL) {
    printf("%s\n", splitArr[index++]);
  }

  free(splitArr);

  return 0;
}
