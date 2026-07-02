/*

July 2nd, 2026:

    Given two integers left and right, return the count of numbers in the inclusive range [left, right] 
    having a prime number of set bits in their binary representation.
*/

int num_set_bits(int number){

    int setBits = 0;

    // Check number of set bits
    for (int i = 0; i < 32; i++){
        if (number & 1){
            setBits++;
        }
        number = number >> 1;
    }

    return setBits;
}

bool is_prime(int number){
    // 2, 3, 5, 7, 11, 13, 17
    
    if (number < 2){
        return false;
    }

    for (int div = 2; div <= number - 1; div++){
        if (number%div == 0){
            return false;
        }
    }

    return true;
}

int countPrimeSetBits(int left, int right) {

    int setBits = 0;
    int primes = 0;

    for (int i = left; i <= right; i++){
        setBits = num_set_bits(i);

        // check if prime
        if (is_prime(setBits)){
            primes++;
        }
    }

    return primes;
}