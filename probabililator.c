#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

//Function to generate a (hopefully) unbiased random number between min and max
int randint(int min, int max) {
    int range = max - min + 1;

    // Largest value that when multiplied by "range"
    // is less than or equal to RAND_MAX
    int chunkSize = RAND_MAX / range; 
    int endOfLastChunk = chunkSize * range;

    int r = rand();
    while(r >= endOfLastChunk){
        r = rand();
    }
    return min + r / chunkSize;
}

int main() {
    time_t t;
    int starttime = time(NULL);
    int max_count_ones = 0;
    int random_number;
    int rolls = 0;
    int results[4];
    int dice_sides = 4;
    int max_rolls = 1000000000;
    int i;
    
    time(&t);
    printf("Start time: %s\n\n", ctime(&t));
    
    // Seed the random number generator
    srand(time(NULL));

    while ((max_count_ones < 177) && (rolls < max_rolls)) {
        memset(results, 0, sizeof results);
        for (i = 0; i < 231; i++) {
            random_number = randint(1, dice_sides);
            //printf("%d\n", random_number);
            // Check if the generated number is 1
            results[random_number - 1]++;
        }
        if (results[0] > max_count_ones) {
            max_count_ones = results[0];
            printf("New record: %d at roll %d. \n", max_count_ones, rolls);
        }
        rolls++;
    }
    
    // Print the result
    printf("Highest ones roll: %d in %d tries.\n", max_count_ones, rolls);
    int endtime = time(NULL);
    int runtime = endtime - starttime;
    
    time(&t);
    printf("\n\nEnd time: %s", ctime(&t));
    
    printf("The program ran for %d seconds. \n", runtime);
    return 0;
}
