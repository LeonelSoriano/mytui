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


void collide_rect_point_test() {
    assert_false(collide_rect_point(1, 1, 10, 10, 30, 30));
    assert_true(collide_rect_point(1,1, 10, 10, 5, 5));
    assert_true(collide_rect_point(1, 1, 10 ,10, 10, 10));
    assert_true(collide_rect_point(20, 25, 10, 10, 20, 25));
    assert_true(collide_rect_point(5, 5, 5, 5, 7, 6));
    assert_false(collide_rect_point(9, 1, 10, 10, 100, 120));
    assert_true(collide_rect_point(80, 20, 5, 5, 84, 22));
    assert_false(collide_rect_point(1, 1, 15, 15, 120, 123));
}

//bool strIsInt(const char *str);
