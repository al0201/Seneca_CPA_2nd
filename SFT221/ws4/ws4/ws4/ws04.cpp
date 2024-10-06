/* Workshop 4
Name : Ahram Lee
Email : alee239@myseneca.ca
Student ID : 133849232
Date: 2024-05-31 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_FACTORIALS 10000
#define NUM_FACTS 100

struct FactorialResults
{
	int results[MAX_FACTORIALS];
	int numResults;
};
int factorial(const int n)
{
	// Corrected the condition to n > 1 to ensure the recursion stops when n is 1.
	return (n > 1) ? n * factorial(n - 1) : 1; // correct
}
int reduceFactorial(const int n)
{
	// return n / n; // should avoid division by zero
	return (n > 0) ? (n / n) : 1; // correct
}

// Changed the parameter to a pointer to ensure the original structure is modified.
void computeFactorials(struct FactorialResults* results, int numFactorials)  // correct
{
	int i;
	for (i = 0; i < numFactorials; i++)
	{
		
		results->results[i] = factorial(i); // correct
	}
	results->numResults = numFactorials;  // correct
}
int main(void)
{
	struct FactorialResults results = { {0}, 0 };
	int i;

	computeFactorials(&results, NUM_FACTS);
	for (i = 0; i < NUM_FACTS; i++)
	{
		results.results[i] = reduceFactorial(results.results[i]);

		//Changed %12f to %12d to match the integer type of results.results[i].
		printf("%5d %12d\n", i, results.results[i]);  // correct
	}

	return 0;
}