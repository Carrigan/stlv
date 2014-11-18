#include "stlv_test.h"
#include "minunit.h"
#include <stdio.h>

int tests_run = 0;

char *run_all_tests(void)
{
	mu_run_test(stlv_test_bootstrap);
	return 0;
}

int main()
{
	char *message = 0;

	if(message = run_all_tests()) {
		printf("%s", message);
		printf("TESTS FAILED.");
		return 1;
	}

	printf("Tests run: %d\n", tests_run);
	printf("ALL TESTS PASSED.");
	return 0;
}