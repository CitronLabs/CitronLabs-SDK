#include "routine_example.h"


__start{
	subroutine(printText, char* text){
		println(text);
	}

	call(printText, "Hi");


return 0;
}
