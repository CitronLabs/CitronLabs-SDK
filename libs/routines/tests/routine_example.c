#include "routine_example.h"
package(routines, .vis = PRIVATE);
depends(
	XC.core 1.0.10 "https://theplatstore.com/blueberry/ExtraC",
	GNU.ncurses,
)
description(
/*
	this package serves as a test for the XC routines module
*/
)

typedef u32(*printFunc)(FILE* out);
typedef printFunc(*arthFunc)(u32 a, u32 b, u32(*resCallback)(u32, ...));


arthFunc parseOperator(cstr op){ 

    fancy(){

	defer{} 

	int subfn(add, u32 add_a, u32 add_b){
	
	}

	int routn(IDK){
	
	}

    freturn (arthFunc)add;
    }



return NULL;
}

void FileNFib(cstr path, u32 num){

    go(file){


    }
    go(fib){
		

    }
}
int main(){
	u32 subfn(resCallback, u32 res){
		res += 10;
	}
	int result = parseOperator("+")(1,2, resCallback)(stdin);
	FileNFib("hello.txt", 42);
}

