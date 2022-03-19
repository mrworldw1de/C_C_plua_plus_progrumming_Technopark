#include "IZ_1.h"

int main(FILE* file) 
{
    
    HTML_teg* ptr = read_HTML_teg(file);
    free_teg_mem(ptr);
    return 0;
}