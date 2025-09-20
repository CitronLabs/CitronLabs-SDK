#pragma once
#include "./libc.h"

#define loop(loopvar, num) for(int loopvar = 0; loopvar < num; loopvar++)
#define loopat(loopvar, init, num) for(int loopvar = init; loopvar < num; loopvar++)
#define iter(array, size, type, item) 	\
type item; 				\
for(int __##item##_iterator = 0; 	\
    __##item##_iterator < size; 	\
    item = ((type*)array)[__##item##_iterator++])

#define getbitflagsinit size_t currentflag = 0, flagschecked = 0; 

#define getbitflags(flags, ...)											\
	currentflag = 0;											\
	flagschecked = 0;											\
	for (size_t bitmask = 1;(flags - flagschecked) > 0; bitmask*=2) 					\
	{													\
		currentflag = flags & bitmask;									\
		switch (currentflag)										\
		__VA_ARGS__											\
		flagschecked |= currentflag;									\
	}
#define getbitflag(flags, flag) (flags & flag) == flag	

#define getopts(argc, argv, ...)		\
	char* OPTARG, *LONGOPT;			\
	for(int i = 1;i < argc; i++){		\
	    if(argv[i][0] == '-'){		\
	      if(i + 1 < argc){			\
		OPTARG = argv[i+1]; 		\
		  if(argv[i][1] == '-') 	\
		    LONGOPT = 			\
			(char*)&argv[i][2]; 	\
     		else 				\
		    LONGOPT = NULL;		\
		}				\
	    switch (argv[i][1])			\
     	    {__VA_ARGS__}			\
	    };					\
	}

#define addrasval(addr) (*(uint64_t*)&addr)


 #define BLACK "\033[0;30m"
 #define RED "\033[0;31m"
 #define GREEN "\033[0;32m"
 #define ORANGE "\033[0;33m"
 #define BLUE "\033[0;34m"
 #define PURPLE "\033[0;35m"
 #define CYAN "\033[0;36m"
 #define LIGHTGRAY "\033[0;37m"   
 #define DARKGRAY "\033[1;30m"   
 #define LIGHTRED "\033[1;31m"   
 #define LIGHTGREEN "\033[1;32m"   
 #define YELLOW "\033[1;33m"   
 #define LIGHTBLUE "\033[1;34m" 
 #define LIGHTPURPLE "\033[1;35m"
 #define LIGHTCYAN "\033[1;36m"
 #define WHITE "\033[1;37m"
 #define NC "\033[1;0m"
#define MacroSingle(...) __VA_ARGS__

#define DO_LATER(...) static_assert(false , __VA_ARGS__);
