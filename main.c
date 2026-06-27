#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Start thingies for the calculator
const char *expr;
void skip_spaces(){
	while (isspace(*expr))
		expr++;
}
double parse_expression();
double parse_number(){
	skip_spaces();
	char *end;
	double value = strtod(expr, &end);
	if(end == expr){
		printf("ERROR: Expected number\n");
		exit(1);
	}
	expr = end;
	return value;
}
double parse_factor(){
	skip_spaces();
	if(*expr == '('){
		expr++;
		double value = parse_expression();
		skip_spaces();
		if(*expr != ')'){
			printf("ERROR: Expected ending the parentheses ')'\n");
			exit(1);
		}
		expr++;
		return value;
	}
	if(*expr == '-'){
		expr++;
		return -parse_factor();
	}
	return parse_number();
}
double parse_term(){
	double value = parse_factor();
	while(1){
		skip_spaces();
		if(*expr == '*'){
			expr++;
			value *= parse_factor();
		}
		else if(*expr == '/'){
			expr++;
			value /= parse_factor();
		}
		else{
			break;
		}
	}
	return value;
}
double parse_expression(){
	double value = parse_term();
	while(1){
		skip_spaces();
		if(*expr == '+'){
			expr++;
			value += parse_term();
		}
		else if(*expr == '-'){
			expr++;
			value -= parse_term();
		}
		else{
			break;
		}
	}
	return value;
}
// End thingies for the calculator
int main(int argc, char *argv[]){
	if(argc < 2) {
		printf("Swiss Army Knife\n");
		printf("Multiple mini-programs in one\n\n");
		printf("Avaidable tools:\n");
		printf("btd	Binary to decimal converter\n");
		printf("calc    Calculator\n");
		printf("dtb	Decimal to binary converter\n");
		printf("fcalc   Factorial calculator\n");
		printf("unixt	Current Unix time\n");
		printf("unixtc	Unix time to date converter\n");
		return 0;
	}
	// VERSION
	if(strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0){
		printf("Swiss Army Knife v0.02\nRepo: https://github.com/kittyteggie/swiss-army-knife\n");
		return 0;
	}
	// UNIX TIME (unixt)
	if(strcmp(argv[1], "unixt") == 0){
        	time_t now = time(NULL);
		printf("%lld\n",(long long)now);
		return 0;
	}
	// UNIX TIME CONVERTER (unixtc)
	if(strcmp(argv[1], "unixtc") == 0){
		if(argc != 3){
			printf("ERROR: Use: %s unixtc <timestamp>\n",argv[0]);
			return 1;
		}
		time_t timestamp = (time_t)atoll(argv[2]);
		struct tm *tm = gmtime(&timestamp);
		if(!tm){
			printf("ERROR: Invalid timestamp\n");
			return 1;
		}
		char buffer[32];
		strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%S",tm);
		printf("%s\n", buffer);
		return 0;
	}
	// DECIMAL TO BINARY (dtb)
	if(strcmp(argv[1], "dtb") == 0){
		if(argc != 3){
			printf("ERROR: Use %s dtb <number>\n", argv[0]);
			return 1;
		}
		uint64_t number = strtoull(argv[2], NULL, 10);
		if(number == 0){
			printf("0\n");
			return 0;
		}
		char binary[65];
		int i = 0;
		while(number > 0){
			binary[i++] = (number % 2) + '0';
			number /= 2;
		}
		while(i > 0){
			putchar(binary[--i]);
		}
		putchar('\n');
		return 0;
	}
	// BINARY TO DECIMAL (btd)
	if(strcmp(argv[1], "btd") == 0){
		if(argc != 3){
			printf("ERROR: Use: %s btd <binary>\n", argv[0]);
			return 1;
		}
		char *binary = argv[2];
		uint64_t decimal = 0;
		for (int i = 0; binary[i] != '\0'; i++) {
			if (binary[i] != '0' && binary[i] != '1') {
				printf("ERROR: Invalid binary number\n");
				return 1;
			}
			decimal = decimal * 2 + (binary[i] - '0');
		}
		printf("%llu\n", (unsigned long long)decimal);
		return 0;
	}
	// CALCULATOR (calc)
	if(strcmp(argv[1], "calc") == 0){
		if(argc != 3){
			printf("ERROR: Use: %s calc <equation>\n", argv[0]);
			return 1;
		}
		expr = argv[2];
		double result = parse_expression();
		skip_spaces();
		if(*expr != '\0'){
			printf("ERROR: Unexpected character '%c'\n", *expr);
			return 1;
		}
		printf("%g\n", result);
		return 0;
	}
	// FACTORIAL CALCULATOR (fcalc)
	if(strcmp(argv[1], "fcalc") == 0){
		if(argc != 3){
			printf("Error: Use %s fcalc <number>\n", argv[0]);
			return 1;
		}
		int number = atoi(argv[2]);
		if(number < 0){
			printf("ERROR: Factorial is not defined by negative numbers\n");
			return 1;
		}
		if(number > 20){
			printf("ERROR: Result is too large for the 'unsigned long long' variable\n");
			return 1;
		}
		unsigned long long result = 1;
		for(int i = 2; i <= number; i++){
			result *= i;
		}
		printf("%llu\n", result);
		return 0;

	}
	printf("ERROR: Unknown argument: %s\n", argv[1]);
	return 1;
}
