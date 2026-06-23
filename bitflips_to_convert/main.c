/*

June 23rd, 2026:

	A bit flip of a number x is choosing a bit in the binary representation of x and flipping it from either 0 to 1 or 1 to 0.

	Given two integers start and goal, return the minimum number of bit flips to convert start to goal.

*/

int minBitFlips(int start, int goal) {

    int flips = 0;

    if (goal == start){
        return flips;
    }

    while ((goal) || (start)){
        if ((goal & 1) && !(start & 1)){
            printf("Goal: %d", goal);
            flips ++;
            printf("Flip 1 to 0\n");
        } else if (!(goal & 1) && (start & 1)){
            printf("Flip 0 to 1\n");
            flips ++;
        }

        goal = goal >> 1;
        start = start >> 1;
    }

    return flips;

}

