/*

July 1st, 2026:

    You are given a large integer represented as an integer array digits, where each digits[i] is the ith digit of the integer. 
    The digits are ordered from most significant to least significant in left-to-right order. The large integer does not contain any leading 0's.

    Increment the large integer by one and return the resulting array of digits.
*/

int* plusOne(int* digits, int digitsSize, int* returnSize) {

 bool allNines = true;

    for (int i = 0; i < digitsSize; i++){
        if (digits[i] != 9){
            allNines = false;
            break;
        }
    }

    if (allNines){
        *returnSize = digitsSize + 1;
        int *a_result = (int *)calloc((*returnSize),sizeof(int));
        a_result[0] = 1;
        return a_result;
    }

    *returnSize = digitsSize;
    int *a_result = (int *)malloc((*returnSize)*sizeof(int));

    memcpy(a_result, digits,(*returnSize) * sizeof(int));

    for (int i = digitsSize-1; i >= 0; i--){
        if (a_result[i] == 9){
            a_result[i] = 0;
            continue;
        } else{
            a_result[i] = a_result[i]+1;
            break;
        }
    }

    return a_result;
}