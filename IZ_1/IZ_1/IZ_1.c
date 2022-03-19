#include "IZ_1.h"
  
void del_symbol(char** string, int** len)
{
    if((*string)[0]!='\0')
    {
    ++(*string);
    --(*len);
    }
}

//функция получения строки из консоли
char* get_string_from_file(int* len, FILE* fin) 
{
    *len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* s = (char*)malloc(sizeof(char)); // динамическая пустая строка
    char c ; // символ для чтения данных
    // читаем символы, пока не получим символ переноса строки (\n)
    while ( (c = fgetc(fin)) != EOF) {
        s[(*len)++] = c; // заносим в строку новый символ
        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }
        //c = (char)fgets(*fin); // считываем следующий символ          
    }
    s[*len] = '\0'; // завершаем строку символом конца строки
    return s; // возвращаем указатель на считанную строку
}






//функция получения строки из консоли
char* get_string(int* len) 
{
    *len = 0; // изначально строка пуста
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* s = (char*)malloc(sizeof(char)); // динамическая пустая строка
    char c = getchar(); // символ для чтения данных
    // читаем символы, пока не получим символ переноса строки (\n)
    while (c != '\n') {
        s[(*len)++] = c; // заносим в строку новый символ
        // если реальный размер больше размера контейнера, то увеличим его размер
        if (*len >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }
        c = getchar(); // считываем следующий символ          
    }
    s[*len] = '\0'; // завершаем строку символом конца строки
    return s; // возвращаем указатель на считанную строку
}
//функция устанавливает по введенной строке, открывающийся или закрывающийся html тег
void set_open_or_close_teg(char ** string, int *len, HTML_teg * teg)
{
    if ((*string)[0] == '/')//проверяем 1 символ строки
    {
        teg->open_or_close_feature = strdup ("close\0");  //указываем на строку
        del_symbol(string, &len);
    }
    else
    {
        teg->open_or_close_feature = strdup ("open\0");
    }
}
//функция принимает строку right_string и отрезает от нее все символы с начала строки до символа mark, либо до конца строки и возвращает указатель на отрезанную строку
char* devide_string (char ** right_string, int* len, char mark)
{
    int len_of_string = 0;
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* left_string = "";
    while (((*right_string)[0] != mark) && ((*right_string)[0] != '\0'))
    {
        left_string[len_of_string++] = (*right_string)[0];
     
        if (len_of_string >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            left_string = (char*)realloc(left_string, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }
        del_symbol(right_string, &len);
    }
    left_string[len_of_string] = '\0';
    return strdup(left_string);
}
//функция удаляет пробелы в строке
void del_gap(char** string, int** len)
{
    while (((*string)[0] == ' '))
    {
        del_symbol(string, len);
    }
}

//функция вносит вырезает из строки String первое слово до пробела и указывает элементу структуры teg на него. Это имя тега
int set_teg_name(char** string, int* len, HTML_teg* teg)
{
    //проверяем, есть ли пробелы перед именем тега
    del_gap(string, &len);
    //создаем динамическую строку
    int len_of_name = 0;
    int capacity = 1; // ёмкость контейнера динамической строки (1, так как точно будет '\0')
    char* s = (char*)malloc(sizeof(char));
    //ищем слово либо до ' ', либо до '>' - знака закрытия тега
    while (((*string)[0]!='>')&&((*string)[0]!=' '))
    {
        s[len_of_name++] = (*string)[0];
        if (len_of_name >= capacity) {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            s = (char*)realloc(s, capacity * sizeof(char)); // создаём новую строку с увеличенной ёмкостью  
        }
        del_symbol(string, &len);
    }
    s[len_of_name] = '\0'; //значение конца строки
    if (s=="\0")
        return ERROR_CALL;
    teg->name = s;
    return GOOD;
}
//функция присваивает структуре тега значения аттрибутов тега
int set_teg_attributes(char** string, int* len, HTML_teg* teg)
{
    //создаем динамический массив из структур аттрибутов тега
    teg_attribute* attributes = (teg_attribute*)malloc(sizeof(teg_attribute));
    //при отсутствии тегов создаем нулевые значения по умолчанию
    if ((*string)[0] == '>')
    {
        attributes[0].attribute_name = strdup ("\0");
        attributes[0].attribute_value = strdup ("\0");
    }
    // количество аттрибутов тега (количество элементов массива тегов)
    int nomber_of_attributes = 0;
    int capacity = 1; // ёмкость массива аттрибутов
    //удаление пробелов
    del_gap(string, &len);
    while (((*string)[0] != '>')&&((*string)[0] != '\0') )
    {    
        //присвоение имени аттрибута
        attributes[nomber_of_attributes].attribute_name = devide_string(string, len, '=');
        del_symbol(string, &len);//удаляем символ равно у атрибута тега
        del_gap(string, &len);//удаляем возможные пробелы
        del_symbol(string, &len);//удаляем первую кавычку у значения атрибута
        //присвоение значения аттрибута
        attributes[nomber_of_attributes].attribute_value = devide_string(string, len, '\'');
        if (nomber_of_attributes >= capacity)
        {
            capacity *= 2; // увеличиваем ёмкость строки в два раза
            attributes = (teg_attribute*)realloc(attributes, capacity * sizeof(teg_attribute)); // создаём новую строку с увеличенной ёмкостью  
        }
        del_symbol(string, &len);
        //удаление пробелов
        del_gap(string, &len);
        ++nomber_of_attributes;
        if ((attributes[nomber_of_attributes-1].attribute_name=="\0")||(attributes[nomber_of_attributes-1].attribute_value=="\0"));
        {
            return ERROR_CALL;
        }
    }
    teg->attributes= attributes;
    teg->number_of_attributes= nomber_of_attributes;
    return GOOD;
}

void free_atr_mem(teg_attribute* atribute)
{
    free(atribute->attribute_name);
    free(atribute->attribute_value);
    free(atribute);
}

void free_teg_mem(HTML_teg* teg)
{
    free(teg->name);
    free(teg->open_or_close_feature);
    int i=0;
    //чтобы выполнилось минимум 1 раз, 1 раз вне цикла
    free_atr_mem(&(teg->attributes[i]));
    ++i;
    printf("                       nomber     %d     ", teg->number_of_attributes);
    while (i<teg->number_of_attributes)
        {
        free_atr_mem(&teg->attributes[i]);
        //free(teg->attributes[i].attribute_name);
        //free(teg->attributes[i].attribute_value);
        ++i;
        }
    //free(teg->attributes);
    free(teg);
}

//функция сообщает об ошибке и делает тег нулевым
void call_eror(HTML_teg* teg)
{
    printf("ERROR TEG INPUT");
    teg_attribute* attributes = (teg_attribute*)calloc(1,sizeof(teg_attribute));
    teg->attributes = attributes;
    teg->number_of_attributes = 0;
    teg->name = strdup ("\0");
    teg->open_or_close_feature = strdup ("\0");
}

//функция последовательно вызывает чтение строки, присвоение параметров тега или вызывает срабатывание сообщения о неправильно введённых данных
HTML_teg *read_HTML_teg(FILE* file)
{   
    int len;
    char* ptr_string = get_string_from_file(&len, file);
    //char* ptr_string =get_string(&len);//динамическая строка, указывает на начало строки
    char* string = ptr_string; //текущее местоположение на строке
    HTML_teg* teg=(HTML_teg*)calloc(1,sizeof(HTML_teg));//создание тега
    if ((string[0] == '<') && (string[len - 1] == '>'))
    {
        //двигаем строку, чтобы пропустить символ '<'
        ++(*string);
        --len;
        set_open_or_close_teg(&string, &len, teg);
        if (set_teg_name(&string, &len, teg)==ERROR_CALL)
            call_eror(teg);
        if (set_teg_attributes(&string, &len, teg)==ERROR_CALL)
            call_eror(teg);
    }
    else
    {
        call_eror(teg);
    }

    free(ptr_string);
    return(teg);
}