#ifndef VPM_DSTR_H
#define VPM_DSTR_H
typedef struct DYNAMIC_STRING_STRUCT {
    char* value;
} dstr;

dstr* init_dstr();

void dstr_cat(dstr* str, char* value);

void dstr_cat_c(dstr* str, char c);
    
void free_dstr(dstr* str);
#endif
