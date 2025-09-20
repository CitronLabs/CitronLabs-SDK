#pragma once
#include "../../../APIs/XC/core.h"

static u64 subtests_passed = 0;
static u64 subtest_num = 0;
static u64 test_num = 0;
#define loginfoNONEWLINE(...) Logger.logf(Logger.std_logger, LOGGER_INFO, __VA_ARGS__, endprint)

#define INIT_TEST subtests_passed = 0; subtest_num = 0; test_num = 0;
#define TEST(id) bool RUN_##id##_TESTS()
#define NEW_TEST(name) loginfo("--Test ",$(test_num),": ",name); test_num++;
#define NEW_SUBTEST(name) loginfoNONEWLINE("\t-[",name,"]"); subtest_num++;
#define PASS_TEST {loginfoNONEWLINE(GREEN"[PASS]"NC"\n"); subtests_passed++;}
#define FAIL_TEST {loginfoNONEWLINE(RED"[FAIL]"NC"\n");}
#define TEST_RESULT subtests_passed == subtest_num;
#define RUN_TEST(id) Error.Clear(); if(!RUN_##id##_TESTS())
