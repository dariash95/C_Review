/*

June 22nd, 2026:

	You are given two positive integers n and k.

	You can choose any bit in the binary representation of n that is equal to 1 and change it to 0.

	Return the number of changes needed to make n equal to k. If it is impossible, return -1.
*/

int minChanges(int n, int k) {

    int changes = 0;

    if (n == k){
        return changes;
    }

    for (int i = 0; i <32; i++){

        if (!(n & 1) & (k&1)){
            // 0 vs 1: they will always be different
            changes = -1;
            return changes;
        } else if ((n&1) & !(k&1)){
            changes++;
        }

        n = n >> 1;
        k = k >> 1;
    }

    return changes;
}


