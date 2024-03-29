int max(int a, int b){
	if(a >= b){
		return a;
	
	}else {
		return b;
	}
}

int mod(int n, int modulus){
	int remainder = n % modulus;
	
	if(remainder < 0){
		return remainder + modulus;
	
	}else {
		return remainder;
	} 
}

int ntruprime_inv_int(int n, int modulus){
    int new_t = 0;
    int t = 1;
    int b = modulus;

    while (b != 0) {
        int quotient = n / b;

        int temp = n;
        n = b;
        b = temp % b;

        temp = new_t;
        new_t = t - quotient*new_t;
        t = temp;
    }

    if (t < 0){
        t += modulus;
    }

    return t;
}

int is_prime(int n){
	for (int i = 2; i < n; i++){
		if(n % i == 0){
			return 0;
		}
	}

	return 1;
}

int is_2_power(int n){
	if(n == 0){
		return 0;
	}else {
		while(n != 1){
			if(n % 2 != 0){
				return 0;
			}

			n /= 2;
		}

		return 1;
	}
}