#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

typedef enum {
	FAILURE,
	PASS,
} TestStatus;

#define CLR_RED     "\x1b[31m"
#define CLR_GREEN   "\x1b[32m"
#define CLR_RESET   "\x1b[0m"
#define CLR_BOLD    "\x1b[1m"

#define STRINGIFY(name) #name

#define TEST_CASE(name, block)\
	case_status = PASS;\
	test_case_name = STRINGIFY(name);\
	assertion_count = 0;\
	assert_fail_count = 0;\
	case_count++;\
	printf(CLR_BOLD "\n	[ %s ] ( %s ) \n" CLR_RESET, test_name, test_case_name);\
	do {\
		block\
	} while(0);\
	switch (case_status) {\
		case FAILURE:\
			printf(CLR_RED CLR_BOLD "	[ %s ] ( %s ) failed (%d/%d)\n" CLR_RESET, test_name, test_case_name, assert_fail_count, assertion_count);\
			status = FAILURE;\
			fail_count++;\
			break;\
		case PASS:\
			printf(CLR_GREEN CLR_BOLD "	[ %s ] ( %s ) passed\n" CLR_RESET, test_name, test_case_name);\
			break;\
	}

#define TEST(name, block)\
	int main(void) {\
		printf(CLR_BOLD "\n[ %s ]\n" CLR_RESET, STRINGIFY(name));\
		int result = 1;\
		(void)result;\
		TestStatus status = PASS;\
		(void)status;\
		TestStatus case_status = PASS;\
		(void)case_status;\
		const char *test_name = STRINGIFY(name);\
		(void)test_name;\
		const char *test_case_name = "";\
		(void)test_case_name;\
		int case_count = 0;\
		(void)case_count;\
		int fail_count = 0;\
		(void)fail_count;\
		int assertion_count = 0;\
		(void)assertion_count;\
		int assert_fail_count = 0;\
		(void)assert_fail_count;\
		block\
		switch (status) {\
			case FAILURE:\
						 printf(CLR_RED CLR_BOLD "\n[ %s ] failed (%d/%d)\n" CLR_RESET, STRINGIFY(name), fail_count, case_count);\
			break;\
			case PASS:\
					  printf(CLR_GREEN CLR_BOLD "\n[ %s ] passed\n" CLR_RESET, STRINGIFY(name));\
			break;\
		}\
		return 0;\
	}

#define ASSERT(condition, message)\
	result = condition;\
	assertion_count++;\
	if (result == 1) {\
		printf(CLR_GREEN "		[ %s ] ( %s ) -- Assertion %s passed\n" CLR_RESET, test_name, test_case_name, STRINGIFY(condition));\
	} else {\
		assert_fail_count++;\
		printf(CLR_RED "		[ %s ] ( %s ) -- Assertion %s failed: %s\n" CLR_RESET, test_name, test_case_name, STRINGIFY(condition), message);\
		case_status = FAILURE;\
	}

#endif
