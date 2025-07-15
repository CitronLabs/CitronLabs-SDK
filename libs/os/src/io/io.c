#define EXPOSE_INIT
#include "./io.h"
#include "./posix/posix.h"


errvt File_PrintTo(inst(File) file, ...){
	va_list args;
	va_start(args, file);
	inst(StringBuilder) formatted_output = push(StringBuilder, NULL, UINT64_MAX);

	u64 formatted_len = FormatUtils.FormatVArgs(formatted_output, args);
	
	if(formatted_len == 0) return 
		ERR(IOERR_WRITE, "could not format print to this file");

	File.Write(file, StringBuilder.GetStr(formatted_output).txt, formatted_len);

	pop(formatted_output);

return ERR_NONE;
}
