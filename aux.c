int max(int a, int b){
	if(a >= b){
		return a;
	
	}else {
		return b;
	}
}

int mod(int a, int m){
	int resto = a % m;
	
	if(resto < 0){
		return resto + m;
	
	}else {
		return resto;
	} 
}

int ntruprime_inv_int(int a, int modulus){
    int x = 0;
    int lastx = 1;
    int y = 1;
    int b = modulus;

    while (b != 0) {
        int quotient = a / b;

        int temp = a;
        a = b;
        b = temp % b;

        temp = x;
        x = lastx - quotient*x;
        lastx = temp;
    }

    if (lastx < 0){
        lastx += modulus;
    }

    return lastx;
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