<<<<<<< HEAD
// SPDX-License-Identifier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utstrtoul64 - String-to-integer conversion support for both
 *                            64-bit and 32-bit integers
 *
 ******************************************************************************/

#include <acpi/acpi.h>
#include "accommon.h"

#define _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstrtoul64")

/*******************************************************************************
 *
 * This module contains the top-level string to 64/32-bit unsigned integer
 * conversion functions:
 *
 *  1) A standard strtoul() function that supports 64-bit integers, base
 *     8/10/16, with integer overflow support. This is used mainly by the
 *     iASL compiler, which implements tighter constraints on integer
 *     constants than the runtime (interpreter) integer-to-string conversions.
 *  2) Runtime "Explicit conversion" as defined in the ACPI specification.
 *  3) Runtime "Implicit conversion" as defined in the ACPI specification.
 *
 * Current users of this module:
 *
 *  iASL        - Preprocessor (constants and math expressions)
 *  iASL        - Main parser, conversion of constants to integers
 *  iASL        - Data Table Compiler parser (constants and math expressions)
 *  interpreter - Implicit and explicit conversions, GPE method names
 *  interpreter - Repair code for return values from predefined names
 *  debugger    - Command line input string conversion
 *  acpi_dump   - ACPI table physical addresses
 *  acpi_exec   - Support for namespace overrides
 *
 * Notes concerning users of these interfaces:
 *
 * acpi_gbl_integer_byte_width is used to set the 32/64 bit limit for explicit
 * and implicit conversions. This global must be set to the proper width.
 * For the core ACPICA code, the width depends on the DSDT version. For the
 * acpi_ut_strtoul64 interface, all conversions are 64 bits. This interface is
 * used primarily for iASL, where the default width is 64 bits for all parsers,
 * but error checking is performed later to flag cases where a 64-bit constant
 * is wrongly defined in a 32-bit DSDT/SSDT.
 *
 * In ACPI, the only place where octal numbers are supported is within
 * the ASL language itself. This is implemented via the main acpi_ut_strtoul64
 * interface. According the ACPI specification, there is no ACPI runtime
 * support (explicit/implicit) for octal string conversions.
 *
 ******************************************************************************/
=======
/*******************************************************************************
 *
 * Module Name: utstrtoul64 - string to 64-bit integer support
 *
 ******************************************************************************/

/*
 * Copyright (C) 2000 - 2017, Intel Corp.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement for further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 */

#include <acpi/acpi.h>
#include "accommon.h"

/*******************************************************************************
 *
 * The functions in this module satisfy the need for 64-bit string-to-integer
 * conversions on both 32-bit and 64-bit platforms.
 *
 ******************************************************************************/

#define _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utstrtoul64")

/* Local prototypes */
static u64 acpi_ut_strtoul_base10(char *string, u32 flags);

static u64 acpi_ut_strtoul_base16(char *string, u32 flags);

/*******************************************************************************
 *
 * String conversion rules as written in the ACPI specification. The error
 * conditions and behavior are different depending on the type of conversion.
 *
 *
 * Implicit data type conversion: string-to-integer
 * --------------------------------------------------
 *
 * Base is always 16. This is the ACPI_STRTOUL_BASE16 case.
 *
 * Example:
 *      Add ("BA98", Arg0, Local0)
 *
 * The integer is initialized to the value zero.
 * The ASCII string is interpreted as a hexadecimal constant.
 *
 *  1)  A "0x" prefix is not allowed. However, ACPICA allows this for
 *      compatibility with previous ACPICA. (NO ERROR)
 *
 *  2)  Terminates when the size of an integer is reached (32 or 64 bits).
 *      (NO ERROR)
 *
 *  3)  The first non-hex character terminates the conversion without error.
 *      (NO ERROR)
 *
 *  4)  Conversion of a null (zero-length) string to an integer is not
 *      allowed. However, ACPICA allows this for compatibility with previous
 *      ACPICA. This conversion returns the value 0. (NO ERROR)
 *
 *
 * Explicit data type conversion:  to_integer() with string operand
 * ---------------------------------------------------------------
 *
 * Base is either 10 (default) or 16 (with 0x prefix)
 *
 * Examples:
 *      to_integer ("1000")
 *      to_integer ("0xABCD")
 *
 *  1)  Can be (must be) either a decimal or hexadecimal numeric string.
 *      A hex value must be prefixed by "0x" or it is interpreted as a decimal.
 *
 *  2)  The value must not exceed the maximum of an integer value. ACPI spec
 *      states the behavior is "unpredictable", so ACPICA matches the behavior
 *      of the implicit conversion case.(NO ERROR)
 *
 *  3)  Behavior on the first non-hex character is not specified by the ACPI
 *      spec, so ACPICA matches the behavior of the implicit conversion case
 *      and terminates. (NO ERROR)
 *
 *  4)  A null (zero-length) string is illegal.
 *      However, ACPICA allows this for compatibility with previous ACPICA.
 *      This conversion returns the value 0. (NO ERROR)
 *
 ******************************************************************************/

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_strtoul64
 *
<<<<<<< HEAD
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid pointer
 *              return_value            - Where the converted integer is
 *                                        returned. Must be a valid pointer
 *
 * RETURN:      Status and converted integer. Returns an exception on a
 *              64-bit numeric overflow
 *
 * DESCRIPTION: Convert a string into an unsigned integer. Always performs a
 *              full 64-bit conversion, regardless of the current global
 *              integer width. Supports Decimal, Hex, and Octal strings.
 *
 * Current users of this function:
 *
 *  iASL        - Preprocessor (constants and math expressions)
 *  iASL        - Main ASL parser, conversion of ASL constants to integers
 *  iASL        - Data Table Compiler parser (constants and math expressions)
 *  interpreter - Repair code for return values from predefined names
 *  acpi_dump   - ACPI table physical addresses
 *  acpi_exec   - Support for namespace overrides
 *
 ******************************************************************************/
acpi_status acpi_ut_strtoul64(char *string, u64 *return_value)
{
	acpi_status status = AE_OK;
	u8 original_bit_width;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_strtoul64, string);

	*return_value = 0;

	/* A NULL return string returns a value of zero */
=======
 * PARAMETERS:  string                  - Null terminated input string
 *              flags                   - Conversion info, see below
 *              return_value            - Where the converted integer is
 *                                        returned
 *
 * RETURN:      Status and Converted value
 *
 * DESCRIPTION: Convert a string into an unsigned value. Performs either a
 *              32-bit or 64-bit conversion, depending on the input integer
 *              size in Flags (often the current mode of the interpreter).
 *
 * Values for Flags:
 *      ACPI_STRTOUL_32BIT      - Max integer value is 32 bits
 *      ACPI_STRTOUL_64BIT      - Max integer value is 64 bits
 *      ACPI_STRTOUL_BASE16     - Input string is hexadecimal. Default
 *                                is 10/16 based on string prefix (0x).
 *
 * NOTES:
 *   Negative numbers are not supported, as they are not supported by ACPI.
 *
 *   Supports only base 16 or base 10 strings/values. Does not
 *   support Octal strings, as these are not supported by ACPI.
 *
 * Current users of this support:
 *
 *  interpreter - Implicit and explicit conversions, GPE method names
 *  debugger    - Command line input string conversion
 *  iASL        - Main parser, conversion of constants to integers
 *  iASL        - Data Table Compiler parser (constant math expressions)
 *  iASL        - Preprocessor (constant math expressions)
 *  acpi_dump   - Input table addresses
 *  acpi_exec   - Testing of the acpi_ut_strtoul64 function
 *
 * Note concerning callers:
 *   acpi_gbl_integer_byte_width can be used to set the 32/64 limit. If used,
 *   this global should be set to the proper width. For the core ACPICA code,
 *   this width depends on the DSDT version. For iASL, the default byte
 *   width is always 8 for the parser, but error checking is performed later
 *   to flag cases where a 64-bit constant is defined in a 32-bit DSDT/SSDT.
 *
 ******************************************************************************/

acpi_status acpi_ut_strtoul64(char *string, u32 flags, u64 *return_value)
{
	acpi_status status = AE_OK;
	u32 base;

	ACPI_FUNCTION_TRACE_STR(ut_strtoul64, string);

	/* Parameter validation */

	if (!string || !return_value) {
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	*return_value = 0;

	/* Check for zero-length string, returns 0 */
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')

	if (*string == 0) {
		return_ACPI_STATUS(AE_OK);
	}

<<<<<<< HEAD
	if (!acpi_ut_remove_whitespace(&string)) {
=======
	/* Skip over any white space at start of string */

	while (isspace((int)*string)) {
		string++;
	}

	/* End of string? return 0 */

	if (*string == 0) {
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
		return_ACPI_STATUS(AE_OK);
	}

	/*
<<<<<<< HEAD
	 * 1) Check for a hex constant. A "0x" prefix indicates base 16.
	 */
	if (acpi_ut_detect_hex_prefix(&string)) {
		base = 16;
	}

	/*
	 * 2) Check for an octal constant, defined to be a leading zero
	 * followed by sequence of octal digits (0-7)
	 */
	else if (acpi_ut_detect_octal_prefix(&string)) {
		base = 8;
	}

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_ACPI_STATUS(AE_OK);	/* Return value 0 */
	}

	/*
	 * Force a full 64-bit conversion. The caller (usually iASL) must
	 * check for a 32-bit overflow later as necessary (If current mode
	 * is 32-bit, meaning a 32-bit DSDT).
	 */
	original_bit_width = acpi_gbl_integer_bit_width;
	acpi_gbl_integer_bit_width = 64;

	/*
	 * Perform the base 8, 10, or 16 conversion. A 64-bit numeric overflow
	 * will return an exception (to allow iASL to flag the statement).
	 */
	switch (base) {
	case 8:
		status = acpi_ut_convert_octal_string(string, return_value);
		break;

	case 10:
		status = acpi_ut_convert_decimal_string(string, return_value);
		break;

	case 16:
	default:
		status = acpi_ut_convert_hex_string(string, return_value);
		break;
	}

	/* Only possible exception from above is a 64-bit overflow */

	acpi_gbl_integer_bit_width = original_bit_width;
=======
	 * 1) The "0x" prefix indicates base 16. Per the ACPI specification,
	 * the "0x" prefix is only allowed for implicit (non-strict) conversions.
	 * However, we always allow it for compatibility with older ACPICA.
	 */
	if ((*string == ACPI_ASCII_ZERO) &&
	    (tolower((int)*(string + 1)) == 'x')) {
		string += 2;	/* Go past the 0x */
		if (*string == 0) {
			return_ACPI_STATUS(AE_OK);	/* Return value 0 */
		}

		base = 16;
	}

	/* 2) Force to base 16 (implicit conversion case) */

	else if (flags & ACPI_STRTOUL_BASE16) {
		base = 16;
	}

	/* 3) Default fallback is to Base 10 */

	else {
		base = 10;
	}

	/* Skip all leading zeros */

	while (*string == ACPI_ASCII_ZERO) {
		string++;
		if (*string == 0) {
			return_ACPI_STATUS(AE_OK);	/* Return value 0 */
		}
	}

	/* Perform the base 16 or 10 conversion */

	if (base == 16) {
		*return_value = acpi_ut_strtoul_base16(string, flags);
	} else {
		*return_value = acpi_ut_strtoul_base10(string, flags);
	}

>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
	return_ACPI_STATUS(status);
}

/*******************************************************************************
 *
<<<<<<< HEAD
 * FUNCTION:    acpi_ut_implicit_strtoul64
 *
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid pointer
 *
 * RETURN:      Converted integer
 *
 * DESCRIPTION: Perform a 64-bit conversion with restrictions placed upon
 *              an "implicit conversion" by the ACPI specification. Used by
 *              many ASL operators that require an integer operand, and support
 *              an automatic (implicit) conversion from a string operand
 *              to the final integer operand. The major restriction is that
 *              only hex strings are supported.
 *
 * -----------------------------------------------------------------------------
 *
 * Base is always 16, either with or without the 0x prefix. Decimal and
 * Octal strings are not supported, as per the ACPI specification.
 *
 * Examples (both are hex values):
 *      Add ("BA98", Arg0, Local0)
 *      Subtract ("0x12345678", Arg1, Local1)
 *
 * Conversion rules as extracted from the ACPI specification:
 *
 *  The converted integer is initialized to the value zero.
 *  The ASCII string is always interpreted as a hexadecimal constant.
 *
 *  1)  According to the ACPI specification, a "0x" prefix is not allowed.
 *      However, ACPICA allows this as an ACPI extension on general
 *      principle. (NO ERROR)
 *
 *  2)  The conversion terminates when the size of an integer is reached
 *      (32 or 64 bits). There are no numeric overflow conditions. (NO ERROR)
 *
 *  3)  The first non-hex character terminates the conversion and returns
 *      the current accumulated value of the converted integer (NO ERROR).
 *
 *  4)  Conversion of a null (zero-length) string to an integer is
 *      technically not allowed. However, ACPICA allows this as an ACPI
 *      extension. The conversion returns the value 0. (NO ERROR)
 *
 * NOTE: There are no error conditions returned by this function. At
 * the minimum, a value of zero is returned.
 *
 * Current users of this function:
 *
 *  interpreter - All runtime implicit conversions, as per ACPI specification
 *  iASL        - Data Table Compiler parser (constants and math expressions)
 *
 ******************************************************************************/

u64 acpi_ut_implicit_strtoul64(char *string)
{
	u64 converted_integer = 0;

	ACPI_FUNCTION_TRACE_STR(ut_implicit_strtoul64, string);

	if (!acpi_ut_remove_whitespace(&string)) {
		return_VALUE(0);
	}

	/*
	 * Per the ACPI specification, only hexadecimal is supported for
	 * implicit conversions, and the "0x" prefix is "not allowed".
	 * However, allow a "0x" prefix as an ACPI extension.
	 */
	acpi_ut_remove_hex_prefix(&string);

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_VALUE(0);
	}

	/*
	 * Ignore overflow as per the ACPI specification. This is implemented by
	 * ignoring the return status from the conversion function called below.
	 * On overflow, the input string is simply truncated.
	 */
	acpi_ut_convert_hex_string(string, &converted_integer);
	return_VALUE(converted_integer);
=======
 * FUNCTION:    acpi_ut_strtoul_base10
 *
 * PARAMETERS:  string                  - Null terminated input string
 *              flags                   - Conversion info
 *
 * RETURN:      64-bit converted integer
 *
 * DESCRIPTION: Performs a base 10 conversion of the input string to an
 *              integer value, either 32 or 64 bits.
 *              Note: String must be valid and non-null.
 *
 ******************************************************************************/

static u64 acpi_ut_strtoul_base10(char *string, u32 flags)
{
	int ascii_digit;
	u64 next_value;
	u64 return_value = 0;

	/* Main loop: convert each ASCII byte in the input string */

	while (*string) {
		ascii_digit = *string;
		if (!isdigit(ascii_digit)) {

			/* Not ASCII 0-9, terminate */

			goto exit;
		}

		/* Convert and insert (add) the decimal digit */

		acpi_ut_short_multiply(return_value, 10, &next_value);
		next_value += (ascii_digit - ACPI_ASCII_ZERO);

		/* Check for overflow (32 or 64 bit) - return current converted value */

		if (((flags & ACPI_STRTOUL_32BIT) && (next_value > ACPI_UINT32_MAX)) || (next_value < return_value)) {	/* 64-bit overflow case */
			goto exit;
		}

		return_value = next_value;
		string++;
	}

exit:
	return (return_value);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}

/*******************************************************************************
 *
<<<<<<< HEAD
 * FUNCTION:    acpi_ut_explicit_strtoul64
 *
 * PARAMETERS:  string                  - Null terminated input string,
 *                                        must be a valid pointer
 *
 * RETURN:      Converted integer
 *
 * DESCRIPTION: Perform a 64-bit conversion with the restrictions placed upon
 *              an "explicit conversion" by the ACPI specification. The
 *              main restriction is that only hex and decimal are supported.
 *
 * -----------------------------------------------------------------------------
 *
 * Base is either 10 (default) or 16 (with 0x prefix). Octal (base 8) strings
 * are not supported, as per the ACPI specification.
 *
 * Examples:
 *      to_integer ("1000")     Decimal
 *      to_integer ("0xABCD")   Hex
 *
 * Conversion rules as extracted from the ACPI specification:
 *
 *  1)  The input string is either a decimal or hexadecimal numeric string.
 *      A hex value must be prefixed by "0x" or it is interpreted as decimal.
 *
 *  2)  The value must not exceed the maximum of an integer value
 *      (32 or 64 bits). The ACPI specification states the behavior is
 *      "unpredictable", so ACPICA matches the behavior of the implicit
 *      conversion case. There are no numeric overflow conditions. (NO ERROR)
 *
 *  3)  Behavior on the first non-hex character is not defined by the ACPI
 *      specification (for the to_integer operator), so ACPICA matches the
 *      behavior of the implicit conversion case. It terminates the
 *      conversion and returns the current accumulated value of the converted
 *      integer. (NO ERROR)
 *
 *  4)  Conversion of a null (zero-length) string to an integer is
 *      technically not allowed. However, ACPICA allows this as an ACPI
 *      extension. The conversion returns the value 0. (NO ERROR)
 *
 * NOTE: There are no error conditions returned by this function. At the
 * minimum, a value of zero is returned.
 *
 * Current users of this function:
 *
 *  interpreter - Runtime ASL to_integer operator, as per the ACPI specification
 *
 ******************************************************************************/

u64 acpi_ut_explicit_strtoul64(char *string)
{
	u64 converted_integer = 0;
	u32 base = 10;		/* Default is decimal */

	ACPI_FUNCTION_TRACE_STR(ut_explicit_strtoul64, string);

	if (!acpi_ut_remove_whitespace(&string)) {
		return_VALUE(0);
	}

	/*
	 * Only Hex and Decimal are supported, as per the ACPI specification.
	 * A "0x" prefix indicates hex; otherwise decimal is assumed.
	 */
	if (acpi_ut_detect_hex_prefix(&string)) {
		base = 16;
	}

	if (!acpi_ut_remove_leading_zeros(&string)) {
		return_VALUE(0);
	}

	/*
	 * Ignore overflow as per the ACPI specification. This is implemented by
	 * ignoring the return status from the conversion functions called below.
	 * On overflow, the input string is simply truncated.
	 */
	switch (base) {
	case 10:
	default:
		acpi_ut_convert_decimal_string(string, &converted_integer);
		break;

	case 16:
		acpi_ut_convert_hex_string(string, &converted_integer);
		break;
	}

	return_VALUE(converted_integer);
=======
 * FUNCTION:    acpi_ut_strtoul_base16
 *
 * PARAMETERS:  string                  - Null terminated input string
 *              flags                   - conversion info
 *
 * RETURN:      64-bit converted integer
 *
 * DESCRIPTION: Performs a base 16 conversion of the input string to an
 *              integer value, either 32 or 64 bits.
 *              Note: String must be valid and non-null.
 *
 ******************************************************************************/

static u64 acpi_ut_strtoul_base16(char *string, u32 flags)
{
	int ascii_digit;
	u32 valid_digits = 1;
	u64 return_value = 0;

	/* Main loop: convert each ASCII byte in the input string */

	while (*string) {

		/* Check for overflow (32 or 64 bit) - return current converted value */

		if ((valid_digits > 16) ||
		    ((valid_digits > 8) && (flags & ACPI_STRTOUL_32BIT))) {
			goto exit;
		}

		ascii_digit = *string;
		if (!isxdigit(ascii_digit)) {

			/* Not Hex ASCII A-F, a-f, or 0-9, terminate */

			goto exit;
		}

		/* Convert and insert the hex digit */

		acpi_ut_short_shift_left(return_value, 4, &return_value);
		return_value |= acpi_ut_ascii_char_to_hex(ascii_digit);

		string++;
		valid_digits++;
	}

exit:
	return (return_value);
>>>>>>> dbca343aea69 (Add 'techpack/audio/' from commit '45d866e7b4650a52c1ef0a5ade30fc194929ea2e')
}
