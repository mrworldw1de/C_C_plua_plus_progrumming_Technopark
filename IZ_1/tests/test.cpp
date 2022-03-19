#include <gtest/gtest.h>

extern "C" {
    #include "IZ_1.h"
}

TEST(read_HTML_teg, zero tests) 
{
    HTML_teg* test_teg;
    teg_attribute* attributes = (teg_attribute*)calloc(1,sizeof(teg_attribute));
    test_teg->attributes = attributes;
    test_teg->number_of_attributes = 0;
    test_teg->name = strdup ("\0");
    test_teg->open_or_close_feature = strdup ("\0");

    char* string=strdup("Teg");
    Test_stream = fmemopen(string, strlen (string), "r");
    
    EXPECT_EQ(test_teg, main(Test_stream));

    char* string=strdup("\0");
    Test_stream = fmemopen(string, strlen (string), "r")

    EXPECT_EQ(test_teg, main(Test_stream));;
}

TEST(read_HTML_teg, other_tests) 
{
    HTML_teg* test_teg;
    test_teg->name = strdup ("teg");



        char* string=strdup("<teg>");
    Test_stream = fmemopen(string, strlen (string), "r");
    
    EXPECT_EQ(test_teg->name[0], main(Test_stream)->name[0]);

    char* string=strdup("<teg atr='val'>");
    Test_stream = fmemopen(string, strlen (string), "r")

    EXPECT_EQ(test_teg->name[0], main(Test_stream)->name[0]);
            char* string=strdup("<teg atr1='val1' atr2='val2'>");
    Test_stream = fmemopen(string, strlen (string), "r");
    
    EXPECT_EQ(test_teg->name[0], main(Test_stream)->name[0]);

    char* string=strdup("teg      atr     =   'val'       >");
    Test_stream = fmemopen(string, strlen (string), "r")

    EXPECT_EQ(test_teg->name[0], main(Test_stream)->name[0]);
}

int main(FILE* file) 
{
    
    HTML_teg* ptr = read_HTML_teg(file);
    free_teg_mem(ptr);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}