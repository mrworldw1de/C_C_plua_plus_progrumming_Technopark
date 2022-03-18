#ifndef IZ_1_H
#define IZ_1_H
#pragma once
#include <stdio.h>

//Структура аттрибута тега 
typedef struct teg_attribute
{
    char* attribute_name;   //название тега
    char* attribute_value;  //значение

}teg_attribute;


//Структура тега. Тег имеет синтаксическую структуру "</name atribut1='something' atribut2='something'>" - аттрибутов может быть несколько, поэтому массив
typedef struct HTML_teg
{
    char* name; // название тега
    int number_of_attributes; //количество аттрибутов
    char* open_or_close_feature; //открывающийся или закрывающийся тег, за это отвеает наличие '/' после '<'
    teg_attribute* attributes; //указатель на массив аттрибутов

}HTML_teg;

//функция получения строки из файла
void del_symbol(char** string, int* len);

//получить строку из файла
char* get_string(int* len);

//функция устанавливает по введенной строке, открывающийся или закрывающийся html тег
void set_open_or_close_teg(char** string, int* len, HTML_teg* teg);

//функция принимает строку right_string и отрезает от нее все символы с начала строки до символа mark, либо до конца строки и возвращает указатель на отрезанную строку
char* devide_string(char** right_string, int* len, char mark);

//функция удаляет пробелы в строке
void del_gap(char** string, int* len);

//функция вносит вырезает из строки String первое слово до пробела и указывает элементу структуры teg на него. Это имя тега
void set_teg_name(char** string, int* len, HTML_teg* teg);

//функция присваивает структуре тега значения аттрибутов тега
void set_teg_attributes(char** string, int* len, HTML_teg* teg);

//функция сообщает об ошибке и делает тег нулевым
void call_eror(HTML_teg* teg);

//функция последовательно вызывает чтение строки, присвоение параметров тега или вызывает срабатывание сообщения о неправильно введённых данных
HTML_teg* read_HTML_teg();



#endif