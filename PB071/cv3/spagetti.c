 
/*
 *  NOTE: This code is INTENSIONALLY BADLY written.
 *  Your task is to correct it!
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Program will print days of the week and its distance from Sunday and Monday in order
 * based on command-line argument:
 * -asc ... ascendingly, starting from Monday
 * -desc ... descendingly, starting from Sunday
 * -friday ... starting from Friday instead of Monday resp. Sunday
 *   order is given by other parameters (either -asc or -desc)
 * Example:
 *   ./binary -asc ... will print "Monday Tuesday Wednesday Thursday Friday Saturday Sunday"
 *   ./binary -asc -friday ... will print "Friday Saturday Sunday Monday Tuesday Wednsday"
 *
 * TODO:
 * 1. Reformat spaggeti code, move code into well-designed functions etc.
 * 2. Remove duplicities and near-duplicities in code
 * 3. Improve function getDaySundayMondayDistance() that should return distance of given day from Sunday and Monday
 *    - no global variables usage
 *    - remove duplicities
 * 4. Improve function swapDays()
 *    - no use of global variables (array myDays should be local in main)
 *    - change function prototype to void swapDays(unsigned char*, unsigned char*)
 *      Not indexes, but addresses of items from array days are passed and modified
 * 5. Correct problems with return value testing and array boundaries
 * 6. Correct problems with multiple command line arguments
 * 7. Try to create as readable code as possible, insert comments
 */

char daySundayDistance = 0;
char dayMondayDistance = 0;

void getDaySundayMondayDistance(int dayNumber) {
	daySundayDistance = 7 - dayNumber;
	dayMondayDistance = 1 - dayNumber;
}

unsigned char myDays[7]; // global array for days

/*
 * vytiskne vzdalenost vsech dnu of nedele
 * @param what 
 * @param order, razeni
 */
void printAllDaysDistances(char* what, int order){
	char days[7][10] = {"Monday","Tuesday","Wendesday","Thursday","Friday","Saturday","Sunday"};

	if(strcmp(what, "-asc") == 0) {
		for(int i = 1; i < 8; i++){
			getDaySundayMondayDistance(i);
			printf("%s, (Sunday distance: %d), (Monday distance: %d\n)", days[i-1], daySundayDistance, dayMondayDistance);
		}
	}
	else if(strcmp(what, "-desc") == 0){
		for(int i = 7; i > 0; i--){
                        getDaySundayMondayDistance(i);
                        printf("%s, (Sunday distance: %d), (Monday distance: %d\n)", days[i-1], daySundayDistance, dayMondayDistance);
                }
	}
}

void swapDays(unsigned char firstDay, unsigned char secondDay) {
	unsigned char temp = myDays[firstDay];
	myDays[firstDay] = myDays[secondDay];
	myDays[secondDay] = temp;
}

/*
 * funkce Main
 * @param argv umoynuje volit zpusob vypisu dat

int main(int argc, char *argv[]) {
   if (strcmp(argv[1], "-asc") == 0) {
      printAllDaysDistances(argv[1]);
   }
    else {
        if (strcmp(argv[1], "-desc")) {
        	// TODO: Should print list of day descendingly
                // Bad spaggetti code will just cut&paste code from "-asc" with minor edit
        }
        else {
            if (strcmp(argv[2], "-friday") && (strcmp(argv[1], "-asc"))) {
                // TODO: Should print list of days ascendingly, starting from Friday
                // Bad spaggetti code will just cut&paste code from "-asc" with minor edit
            }
            if (strcmp(argv[2], "-friday") && (strcmp(argv[1], "-desc"))) {
              	// TODO: Should print list of days descendingly, starting from Friday
                // Bad spaggetti code will just cut&paste code from "-asc" with minor edit
            }
        }
    }

    // Create array with days indexes
    for (int i = 1; i <= 7; i++) myDays[i] = i;
    // use function swapDays to swap some days there
    swapDays(3, 7); // swap 3rd and 7th day
    swapDays(4, 1); // swap 4th and 1st day

    // TODO: Print days from myDays array

    return 0;
}
