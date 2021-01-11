#include "Arduino.h"

#define SERIAL_DEBUG_ENABLED


#define DEBUG_PRINTER Serial /**< Define where debug output will be printed. */
/* Setup debug printing macros. */
#ifdef SERIAL_DEBUG_ENABLED
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
#define DEBUG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif