/*

June 25th, 2026:

	Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

	You may assume that each input would have exactly one solution, and you may not use the same element twice.

	You can return the answer in any order.

*/

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {

    int *a_result = (int*)malloc(2*(sizeof(int)));
    *returnSize = 2;

    bool found = false;

    for (int i = 0; i < numsSize; i++){
        for (int j = 1; j < numsSize; j++){
            if (i == j){
                continue;
            }

            if (nums[i] + nums[j] == target){
                a_result[0] = i;
                a_result[1] = j;
                found = true;
                break;
            }
        }

        if (found){
            break;
        }
    }

    return a_result;

}

