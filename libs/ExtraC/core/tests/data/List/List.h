#include "../data.h"

#define TestListFor(test_list, string) \
if(strncmp(List.GetPointer(test_list, 0), \
string,sizeof(string)) == 0)

#define TestListNotFor(test_list, string) \
if(strncmp(List.GetPointer(test_list, 0), \
string,sizeof(string)) != 0)



