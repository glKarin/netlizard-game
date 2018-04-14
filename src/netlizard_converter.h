#ifndef KARIN_NETLIZARD_COMVERTER_H
#define KARIN_NETLIZARD_COMVERTER_H

extern char *dst_file;
extern char *dst_format;

extern char *dst_string;
extern int *dst_digit_array;
extern int dst_digit_size;

extern char *dst_text_file;
extern char *decode_text;
extern char *src_text_file;

int Converter_DecodeImageFile(const char *game, const char *src, const char *to, const char *format);
int Converter_EncodeImageFile(const char *game, const char *src, const char *to);

int Converter_DecodeIntArrayToString(const char *arr);
int Converter_EncodeStringToIntArray(const char *text);
void Converter_FreeString(void);

int Converter_DecodeTextFile(const char *name, const char *to, int save);
void Converter_FreeText(void);

#endif

