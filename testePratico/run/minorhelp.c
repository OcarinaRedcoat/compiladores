int _pow(int base, int pow) { 
	if (pow == 0) return 1;
	int c = pow;
	int res = 1;
	while (c != 0){
		res = res * base;
		c = c - 1;
	}
	return res;
}

int _strcmp(char* firstString,char* secondString){
	while(*firstString && (*firstString == *secondString)) {
		firstString++;
		secondString++;
	}
	return *(unsigned char*)firstString == *(unsigned char*)secondString;
}

int _strncmp(char* firstString,char* secondString){
	while(*firstString && (*firstString == *secondString)) {
		firstString++;
		secondString++;
	}
	return *(unsigned char*)firstString != *(unsigned char*)secondString;
}
