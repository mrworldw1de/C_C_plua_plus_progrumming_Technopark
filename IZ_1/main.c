#include "IZ_1.h"

int main() 
{
    HTML_teg* ptr = read_HTML_teg();
    printf("Name: %s, OP/CL: %s, nom_of_atr: %d, atr: %s=%s ", ptr->name,ptr->open_or_close_feature,ptr->number_of_attributes,ptr->attributes[0].attribute_name,ptr->attributes[0].attribute_value);
    return 0;

}