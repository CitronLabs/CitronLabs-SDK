#include "../include/cmdtools.h"


typedef struct std_cmd{
	std_str name;
	std_map(std_str->std_data) args;
	std_map(std_str->std_cmd)  sub_commands;
	std_queue(std_str) var_args;
	void(*func)(std_struct args);
}std_cmd;
