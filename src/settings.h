#ifndef SETTINGS_LIB
#define SETTINGS_LIB

/* creates a settings.txt with default values */
void create_default_settings_file(void);
/* returns a stream to the settings.txt config file */
FILE * open_config(const char *);
/* returns 1 if conf file has correct size, else returns 0 */
int8_t conf_file_is_valid(void);
/* change background color with the inputed color */
void background_color_change(const char *);
/* change card color with the inputed color */
void card_color_change(const char *);
/* change font size with the inputed size*/
void font_size_change(const uint8_t);
/* returns a settings struct with fields initialized to current settings */
settings get_current_settings(void);

#endif