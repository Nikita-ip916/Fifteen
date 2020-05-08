#include "stopwatch.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class StopWatchTest : public CxxTest::TestSuite {
    int i, t[3], exp[3];

public:
    void test_seconds_negValue()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[0] = -1;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_minutes_negValue()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[1] = -1;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_hours_negValue()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[2] = -1;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_seconds_outofRange()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[0] = 61;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_minutes_outofRange()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[1] = 60;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_hours_outofRange()
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        t[2] = 24;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_time_woutChangesL() // значения, проходя через ф-ю не меняются
                                  // левГрЭквив
    {
        for (i = 0; i < 3; i++) {
            t[i] = exp[i] = 0;
        }
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_time_woutChangesR() // значения, проходя через ф-ю не меняются
                                  // правГрЭквив
    {
        t[0] = exp[0] = 59;
        t[1] = exp[1] = 59;
        t[2] = exp[2] = 23;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_minutes_changeL() // изменение минут левГрЭквив
    {
        t[0] = 60;
        exp[0] = 0;
        t[1] = 0;
        exp[1] = t[1] + 1;
        t[2] = exp[2] = 0;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_minutes_changeR() // изменение минут правГрЭквив
    {
        t[0] = 60;
        exp[0] = 0;
        t[1] = 58;
        exp[1] = t[1] + 1;
        t[2] = exp[2] = 0;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_hours_changeL() // изменение часов левГрЭквив
    {
        t[0] = 60;
        exp[0] = 0;
        t[1] = 59;
        exp[1] = 0;
        t[2] = 0;
        exp[2] = 1;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_hours_changeR() // изменение часов правГрЭквив
    {
        t[0] = 60;
        exp[0] = 0;
        t[1] = 59;
        exp[1] = 0;
        t[2] = 22;
        exp[2] = 23;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
    void test_time_restart() // сброс времени после 23:59:59 правГрЭквив
    {
        t[0] = 60;
        exp[0] = 0;
        t[1] = 59;
        exp[1] = 0;
        t[2] = 23;
        exp[2] = 0;
        stopWatch(t);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(exp[i], t[i]);
        }
    }
};
