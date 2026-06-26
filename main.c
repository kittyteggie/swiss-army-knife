#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]){
	if(argc < 2) {
		printf("Swiss Army Knife\n");
		printf("Multiple mini-programs in one\n\n");
		printf("Avaidable tools:\n");
		printf("unixt	Current Unix time\n");
		printf("unixtc	Unix time to date converter\n");
		printf("dtb	Decimal to binary converter\n");
		printf("btd	Binary to decimal converter\n");
		return 0;
	}
	// VERSION
	if(strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0){
		printf("Swiss Army Knife v0.01\nRepo: https://github.com/kittyteggie/swiss-army-knife\n");
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
	printf("ERROR: Unknown argument: %s\n", argv[1]);
	return 1;
}
