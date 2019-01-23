#ifndef KARIN_FILE_CHOOSER_H
#define KARIN_FILE_CHOOSER_H

typedef void (* FileChooserOpenFile_f)(const char *path);

void UI_FileChooserRegisterFunction(void);
void UI_InitFileChooser(const char *path);
void UI_SetFileChooserOpenFileFunction(FileChooserOpenFile_f f);
const char * UI_GetLastFilePath(void);

#endif
