#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "../src/until.h"


void strIsInt_test (void ** state)
{
    bool result1 = strIsInt("6");
    assert_true (result1);

    bool result2 = strIsInt("-1");
    assert_true(result2);

    bool result3 = strIsInt("hello");
    assert_false(result3);

    bool result4 = strIsInt("189");
    assert_true(result4);

    bool result5 = strIsInt("10000");
    assert_true(result5);
}
//bool strIsInt(const char *str);


