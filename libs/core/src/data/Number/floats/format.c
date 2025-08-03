#include "../number.h"
#include "error.h"
#include "stringutils.h"
#include "types.h"

/**
 * @brief Converts the Number instance to a decimal string, appending it to a StringBuilder.
 * This is the implementation for the Formatter.Print method.
 * @param self A generic pointer to the Number_Instance to convert.
 * @param formats A pointer to an array of FormatID (ignored for now, always decimal).
 * @param out A pointer to the StringBuilder_Instance to append the formatted string to.
 * @return The number of characters appended to the StringBuilder, or 0 on error.
 */
u64 methodimpl(Number, IntPrintDeci,, inst(StringBuilder) out);
u64 methodimpl(Number, FloatPrint,, inst(StringBuilder) out) {

    	u64 formatted_len = 0;
	u64 mantissa_len = 0;

    	// 1. Append sign
    	if (priv->sign == -1) {
        	StringBuilder.Append(out, s("-"));
        	formatted_len++;
    	}

    	// 2. Get mantissa string
	inst(StringBuilder) mantissa_str = push(StringBuilder);
	if(!isinit(mantissa_str)){
		ERR(ERR_INITFAIL, "could not initialize stringbuilder");
		return 0;
	}

	if((mantissa_len = Number_IntPrintDeci(self, mantissa_str)) == 0){
		pop(mantissa_str);
		return 0;
	}

	data(String) mantissa = StringBuilder.GetStr(mantissa_str);
	u64 integer_part_len = mantissa_len + priv->exponent; // Number of digits before decimal point
	
	// Case: 0.00...mantissa (e.g., 0.00123)
	if (integer_part_len <= 0) {
		formatted_len += StringBuilder.Append(out, s("0."));
		
		// Add leading zeros after decimal point
		for (i64 i = 0; i < -integer_part_len; i++) {
			StringBuilder.Append(out, s("0"));
		}
		formatted_len += -integer_part_len;
		formatted_len += StringBuilder.Append(out, &mantissa);

	// Case: mantissa.00... (e.g., 123.0 or 123000.0)
	} else if (integer_part_len >= mantissa_len) {
		formatted_len += StringBuilder.Append(out, &mantissa);
		
		// Add trailing zeros if exponent is positive
		for (i64 i = 0; i < priv->exponent; i++) {
			StringBuilder.Append(out, s("0"));
			formatted_len++;
		}
		formatted_len += StringBuilder.Append(out, s(".0")); // Always append .0 for integer representations
		
	// Case: integer.decimal (e.g., 123.45)
	} else {
		formatted_len += StringBuilder.Append(out, str_view((&mantissa), 0, integer_part_len));
		formatted_len += StringBuilder.Append(out, s("."));
		formatted_len += StringBuilder.Append(out, str_view((&mantissa), integer_part_len, mantissa_len));
	}
	
	pop(mantissa_str);

return formatted_len;
}
