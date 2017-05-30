#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int deed_id;
    char deed_name[55];
    int points_for_deed;
    int total_times_done;
    int total_points_earned;
} deed;

void printList (deed *(deedPrint)){			//function for printing
    int i;
	for (i = 0; i < 18; i++){
    	if(deedPrint[i].total_times_done != 0){		//excluding deeds that were never performed
    		printf("%5i %50s %5i %5i %5i\n", deedPrint[i].deed_id, deedPrint[i].deed_name, deedPrint[i].points_for_deed, deedPrint[i].total_times_done, deedPrint[i].total_points_earned);
    	}
    }
}

int binarySearch(deed *list, char key[]){	//binary search function for task 6, taken from sst-csci.com/csci151, Lesson 27
    int min = 0;
    int max = 18;
    int result;
    while (min < max) {
        int guess = (min + max) / 2;
        result = strcmp(list[guess].deed_name, key);	// "result" is the output of strcmp function
        if (result == 0) {
        	return guess;
        } else if (result > 0) {
            max = guess - 1;
        } else {
            min = guess + 1;
        }
    }
    return -1;
}

int main (void){
	setvbuf(stdout, NULL, _IONBF, 0);
	FILE *deedList;		//plugging in first file
	deedList = fopen("deed_list.txt", "r");

	FILE *dayLog;		//plugging in second file
	dayLog = fopen("daylog.txt", "r");

	int deedsNumber;
	fscanf(deedList, "%i", &deedsNumber);	//scanning only the first row of the deed_list file

	deed dd[deedsNumber];	//creating an array of deed elements

	int i;
	for(i = 1; i < 19; i++){
		fscanf(deedList, "%i %s %i", &dd[i].deed_id, dd[i].deed_name, &dd[i].points_for_deed);	//scanning the first file
	}

	int *arr1 = malloc(28*sizeof(int));		//corresponds to the deed_id
	int *arr2 = malloc(28*sizeof(int));		//corresponds to the total_times_done

	for(i = 0; i < 28; i++){
		fscanf(dayLog, "%i %i", &arr1[i], &arr2[i]);	//scanning the second file
	}

	for(i = 1; i < 19; i++){	//setting to zero last two elements of the "deed" structure
		dd[i].total_times_done = 0;
		dd[i].total_points_earned = 0;
	}

	int j;
	for(i = 0; i < 28; i++){				//this nested loop goes over dayLog file
		for(j = 1; j < 19; j++){			//and calculates the amount of total times done for every deed id
			if(arr1[i] == j){
				dd[j].total_times_done += arr2[i];
			}
		}
	}

	for(i = 1; i < 19; i++){ //calculates the amount of total points earned
		dd[i].total_points_earned = dd[i].points_for_deed * dd[i].total_times_done;
	}

	printf("TASK 1: SORTING BY TOTAL TIMES DONE\n\n");
	printf("   id                    deed name                    deed pt|times|total pts\n");
    for (i = 1; i < 19; i++) {	//sorting by selection sort

         int mindex = i;
         for (j = i + 1; j < 17; j++) {
              if (dd[j].total_times_done > dd[mindex].total_times_done) {
                   mindex = j;
			   }
         }

         int temp = dd[i].deed_id;		//swapping variables
         dd[i].deed_id = dd[mindex].deed_id;
         dd[mindex].deed_id = temp;

         char tempS[100];
         strcpy(tempS, dd[i].deed_name);
         strcpy(dd[i].deed_name, dd[mindex].deed_name);
         strcpy(dd[mindex].deed_name, tempS);

         temp = dd[i].points_for_deed;
         dd[i].points_for_deed = dd[mindex].points_for_deed;
         dd[mindex].points_for_deed = temp;

         temp = dd[i].total_times_done;
         dd[i].total_times_done = dd[mindex].total_times_done;
         dd[mindex].total_times_done = temp;

         temp = dd[i].total_points_earned;
         dd[i].total_points_earned = dd[mindex].total_points_earned;
         dd[mindex].total_points_earned = temp;
    }

    printList(&dd); //printing the results

	printf("\n\n");

	printf("TASK 2: SORTING BY TOTAL NUMBER OF DEED POINTS\n\n");
	printf("   id                    deed name                    deed pt|times|total pts\n");
    for (i = 0; i < 17; i++) {		//sorting by selection sort

         int mindex = i;
         for (j = i + 1; j < 18; j++) {
              if (dd[j].total_points_earned > dd[mindex].total_points_earned) {
                   mindex = j;
			   }
         }

         int temp = dd[i].deed_id;		//swapping variables
         dd[i].deed_id = dd[mindex].deed_id;
         dd[mindex].deed_id = temp;

         char tempS[100];
         strcpy(tempS, dd[i].deed_name);
         strcpy(dd[i].deed_name, dd[mindex].deed_name);
         strcpy(dd[mindex].deed_name, tempS);

         temp = dd[i].points_for_deed;
         dd[i].points_for_deed = dd[mindex].points_for_deed;
         dd[mindex].points_for_deed = temp;

         temp = dd[i].total_times_done;
         dd[i].total_times_done = dd[mindex].total_times_done;
         dd[mindex].total_times_done = temp;

         temp = dd[i].total_points_earned;
         dd[i].total_points_earned = dd[mindex].total_points_earned;
         dd[mindex].total_points_earned = temp;
    }

    printList(&dd);   //printing the results

    printf("\n\n");
    int sum = 0;
    for(i=0; i<18; i++){
    	sum += dd[i].total_times_done; // finding the total number of deeds
    }
    printf("TASK 3, TOTAL NUMBER OF DEEDS DURING THE WEEK: %i deeds", sum);

    printf("\n\n");
    int sumT = 0;
    for(i=1; i<18; i++){
    	sumT += dd[i].total_points_earned; // finding the total number of deed points
    }
    printf("TASK 4, TOTAL NUMBER OF DEED POINTS DURING THE WEEK: %i points", sumT);

	printf("\n\n");

	printf("TASK 5: SORTING BY ALPHABETICAL ORDER\n\n");
	printf("   id                    deed name                    deed pt|times|total pts\n");
	for (i = 0; i < 17; i++) {	//sorting deed_name by alphabetical order using strcmp
         for (j = 1; j < 18; j++) {
        	 int result;
        	 result = strcmp(dd[j].deed_name, dd[j-1].deed_name);
        	 if (result < 0) {
                 char tempS[100];
                 strcpy(tempS, dd[j].deed_name); 		//swapping variables
                 strcpy(dd[j].deed_name, dd[j-1].deed_name);
                 strcpy(dd[j-1].deed_name, tempS);

                 int temp = dd[j].deed_id;
                 dd[j].deed_id = dd[j-1].deed_id;
                 dd[j-1].deed_id = temp;

                 temp = dd[j].points_for_deed;
                 dd[j].points_for_deed = dd[j-1].points_for_deed;
                 dd[j-1].points_for_deed = temp;

                 temp = dd[j].total_times_done;
                 dd[j].total_times_done = dd[j-1].total_times_done;
                 dd[j-1].total_times_done = temp;

                 temp = dd[j].total_points_earned;
                 dd[j].total_points_earned = dd[j-1].total_points_earned;
                 dd[j-1].total_points_earned = temp;
			 }
         }
    }

    printList(&dd);  //printing the results

	printf("\n\n");

	printf("TASK 6:");

	char deedName[55];
	printf("Enter the name of one of the deeds");
	scanf("%s",deedName);  //string typed in by a user

	int guess = binarySearch(dd, deedName);		//calling a binary search function
	if(guess != -1 ){
		printf("%i times done \n and %i points earned", dd[guess].total_times_done, dd[guess].total_points_earned);
	}
	else {
		printf("\n ERROR. SUCH DEED DOES NOT EXIST");
	}

	free(arr1);
	free(arr2);
	fclose(deedList);
	fclose(dayLog);
	return 0;
}	//unfortunately, I could not read in the values for id-18, which is the last member of the array.
	//That is why the output is a little bit different from the actual value.


