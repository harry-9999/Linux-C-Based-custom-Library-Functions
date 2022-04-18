#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

// Name: Muhammad Harris Nadeem
// netID: mhn38
// RUID: 204006764

#include <dirent.h>
#include <string.h>
#include <dlfcn.h>
#include <assert.h>

// Creating function definition
static struct dirent *(*real_readdir)(DIR *dir) = 0;

// Function that splits strings into tokens using delimiter and returns tokens in array
char** splitColon(char* stringA, const char colonDelimm){
  // Initializing variables so we can use later
    char** result    = 0; size_t count     = 0; char* tmp = stringA; char* latest_colon = 0; char delim[2]; delim[0] = colonDelimm; delim[1] = 0;
        while (*tmp) {
          // If we find colon delim, update count and add pointer to colon
        if (colonDelimm == *tmp){ count++; latest_colon = tmp;}
        // Updating counter
        tmp++;
        }
    // Adding latest string count based on length
    count += latest_colon < (stringA + strlen(stringA) - 1);
    count++;
    // Allocating size for result array
    result = malloc(sizeof(char*) * count);
    // Splitting string by colon delim
    if (result) { size_t idx  = 0; char* token = strtok(stringA, delim);
        // For each token
        while (token){
          // Making sure if idx is less than the count
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        // Ensuring idx is equal to count -1
        assert(idx == count - 1);
        // Setting pointer
        *(result + idx) = 0;
    }
    // Returning 
    return result;
}








// Custom readdir function
struct dirent *readdir(DIR *dirp){
      // Initializing variables 
        struct dirent *entry = NULL;
        char** tokens;
        // Initalizing for extra credit
        char ch = ':';
        const char* s = getenv("HIDDEN");
        char* str = NULL;
        // Duplicating string
        str = strdup(s);
        strncat(str, &ch, 1);
        // Passing to function which splits based on colon delim and returns array of tokens
        tokens = splitColon(str,':');
        // Loading in real readdir function for reference in current function
        real_readdir = dlsym(RTLD_NEXT, "readdir");
        
        // For each object
        while(entry = (*real_readdir) (dirp)){
                int i;
                int result = 111;
                // Comparing each of the hidden variables (extra credit)
                for (i = 0; *(tokens + i); i++){
                  // Found entry in hidden variable, thus we need to hide
                  if (strcmp(entry->d_name, *(tokens + i)) == 0 ){
                    result = 0;
                    break;
                  }
                }
                // Returning since entry is not contained within hidden variable
                if (result != 0){
                   return entry;
                }
        }

}




