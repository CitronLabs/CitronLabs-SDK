#pragma once
#include "../test-utils.h"

#define Async_Check() if(inc_num == 0){FAIL_TEST; println("Fail Async"); goto skip; } inc_num = 0;
				

bool RUN_FILE_TESTS(){

NEW_TEST("File IO Tests"){
	
	inst(File) file = NULL;
	inst(File) filecpy = NULL;

	NEW_SUBTEST("Creation"){
		if((file = File.Create(
			"test.file",
			sizeof(char),
			FFL_READ | FFL_WRITE)
		) == NULL){
			FAIL_TEST
			goto skip;
		}
		PASS_TEST
	}

	NEW_SUBTEST("Closing"){
     		del(file);
		if(errnm != ERR_NONE){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Getting"){
		if((file = new(File,
			"test.file",
			sizeof(char),
			FFL_READ | FFL_WRITE)
		) == NULL){
			FAIL_TEST
			goto skip;
		}
     		del(file);
		if(errnm != ERR_NONE){
			FAIL_TEST
			goto skip;
		}
		FILE* cfile = fopen("test.file", "w+");
		if((file = File.FromC(
			cfile,
			FFL_READ | FFL_WRITE,
			sizeof(char))
		) == NULL){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Reading and Writing"){
		char buffer[sizeof("Hello, World!")] = {0};
		if(File.Write(file, 
	       		"Hello, World!", 
	       		sizeof("Hello, World!") - 1
	       	) == 0){
			FAIL_TEST
			goto skip;

		}
		if(fseek(File.ToC(file), 0, SEEK_SET) == -1){
			FAIL_TEST
			goto skip;
		}
		if(File.Read(file, 
	       		buffer, 
	       		sizeof("Hello, World!") - 1
	       	) == 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Copying"){
		char buffer[sizeof("Hello, World!")] = {0};
		if(File.Copy(file, &filecpy, "test.filecopy")){
			FAIL_TEST
			perror(NULL);
			goto skip;
		}
		if(fseek(File.ToC(filecpy), 0, SEEK_SET) == -1){
			FAIL_TEST
			goto skip;
		}
		if(File.Read(file, 
	       		buffer, 
	       		sizeof("Hello, World!")
	       	) == 0){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(buffer, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Moving"){
		char buffer[sizeof("Hello, World!")] = {0};
		if(fseek(File.ToC(file), 0, SEEK_SET) == -1){
			FAIL_TEST
			goto skip;
		}
		if(File.Move(file, "../test.file")){
			FAIL_TEST
			perror(NULL);
			goto skip;
		}
		if(File.Read(file, 
	       		buffer, 
	       		sizeof("Hello, World!")
	       	) == 0){
			FAIL_TEST
			goto skip;
		}
		if(strncmp(buffer, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Deletetion"){
		if(File.Remove(file)){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
     	del(file);
	if(errnm != ERR_NONE){
		FAIL_TEST
		goto skip;
	}

	char buffer[sizeof("Hello, World! How are you?")] = {0};
	i32 read_write_val = 0;
	u32 inc_num = 0;
	errvt err = ERR_NONE;
	
	NEW_SUBTEST("Async Get"){
		if((file = new(File,
			"test.filecopy",
			sizeof(char),
			FFL_READ | FFL_WRITE | FFL_ASYNC | FFL_APPEND)
		) == NULL){
			FAIL_TEST
			goto skip;
		}
			PASS_TEST
	}
	NEW_SUBTEST("Async Write"){
		while((read_write_val = File.Write(file," How are you?", sizeof(" How are you?"))) < 0){
			println($(read_write_val));
			switch(read_write_val){
			case -2:
				inc_num++;
				break;
			case -1:
			default:
				FAIL_TEST
				println("Fail Write");
				goto skip;
			}
		}
			Async_Check();
			PASS_TEST
	}

	NEW_SUBTEST("Async Read"){

		while((read_write_val = File.Read(file, buffer, sizeof("Hello, World! How are you?"))) < 0){
			switch(read_write_val){
			case -2:
				inc_num++;
				break;
			case -1:
			default:
				FAIL_TEST
				println("Fail Read");
				goto skip;
			}
		}

		if(strncmp(buffer, "Hello, World!", sizeof("Hello, World!")) != 0){
			FAIL_TEST
			goto skip;
		}
			Async_Check();
			PASS_TEST
	}

	NEW_SUBTEST("Async Copy"){

		while((err = File.Copy(file, &filecpy, "test.file")) == IOERR_ASYNC )
				inc_num++;
		if(err  != ERR_NONE){
			FAIL_TEST
			println("Fail Copy");
			goto skip;
		}
			Async_Check();
			PASS_TEST
	}

	NEW_SUBTEST("Async Move"){

		while((err = File.Move(file, "../test.filecopy")) == IOERR_ASYNC )
				inc_num++;
		if(err  != ERR_NONE){
			FAIL_TEST
			println("Fail Move");
			goto skip;
		}
			Async_Check();
			PASS_TEST
	}
	
	File.Remove(file);
	File.Remove(filecpy);

	del(file);
	del(filecpy);
}
skip:

return TEST_RESULT;
}
