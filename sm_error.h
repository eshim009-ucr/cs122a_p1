#ifndef SM_ERROR_H
#define SM_ERROR_H


// Display a red LED to indicate an internal fault
void show_error(const char* message);
// Display a state machine error
void show_sm_error(const char* name, int state);
// Display a blue LED to indicate a warning or debugging information
void show_notice(const char* message);
// Clear all illuminated LEDs
void clear_status();


#endif
