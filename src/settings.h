#ifndef SETTINGS_LIB
#define SETTINGS_LIB

void create_default_settings_file(const char *);
FILE * open_config(const char *);
int8_t conf_file_is_valid(const char *);
void background_color_change(const char *);
void card_color_change(const char *);
void font_size_change(const uint8_t);
void sound(void);
void help(void);

#endif