#include<stdio.h>

static void counter() { // Made the 'counter' function static to address VCR003
	int counter = 0;
	static int global_counter = 0; // Added 'int' to declare the static variable properly

	counter++;
	global_counter++;

	printf("counter:%d\n", counter);
	printf("global_counter:%d\n", global_counter);
}

int main() { // Moved 'main' function outside of 'counter' function
	counter();
	counter();
	counter();
	counter();
	return 0;
}