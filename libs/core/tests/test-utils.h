#pragma once
#include "../../APIs/XC/core.h"

static u64 subtests_passed = 0;
static u64 subtest_num = 0;
static u64 test_num = 0;

#define INIT_TEST subtests_passed = 0; subtest_num = 0; test_num = 0;
#define NEW_TEST(name) print("--Test ",$(test_num),": ",name,"\n"); test_num++;
#define NEW_SUBTEST(name) print("\t-[",name,"]"); subtest_num++;
#define PASS_TEST {println(GREEN"[PASS]"NC); subtests_passed++;}
#define FAIL_TEST {println(RED"[FAIL]"NC);}
#define TEST_RESULT subtests_passed == subtest_num;
