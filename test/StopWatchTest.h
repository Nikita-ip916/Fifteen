#include "stopwatch.hpp"
#include <cxxtest/TestSuite.h>
#include <iostream>
using namespace std;

class StopWatchTest : public CxxTest::TestSuite {
    int i, time[3],
            expTime[3]; // Массивы Реального и ожидаемого изменения времени
                        // time[0] - секунды time[1] - минуты time[2] - часы
public:
    void testSecondsNegValue()
    {
        for (i = 0; i < 3; i++) { // Исходное обнуление времени
            time[i] = expTime[i] = 0;
        }
        time[0] = -1;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[0] = 0; // Возврат в исходное обнуление
    }
    void testMinutesNegValue()
    {
        time[1] = -1;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[1] = 0;
    }
    void testHoursNegValue()
    {
        time[2] = -1;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[2] = 0;
    }
    void testSecondsOutofRange()
    {
        time[0] = 61;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[0] = 0;
    }
    void testMinutesOutofRange()
    {
        time[1] = 60;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[1] = 0;
    }
    void testHoursOutofRange()
    {
        time[2] = 24;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
        time[2] = 0;
    }
    void testTimeWoutChangesL() // значения, проходя через ф-ю не меняются
                                  // левГрЭквив
    {
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
    void testTimeWoutChangesR() // значения, проходя через ф-ю не меняются
                                  // правГрЭквив
    {
        time[0] = expTime[0] = 59;
        time[1] = expTime[1] = 59;
        time[2] = expTime[2] = 23;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        } // Сейчас и далее обнуление не обязательно, т.к. изменяются все
    }     // разряды времени
    void testMinutesChangeL() // изменение минут левГрЭквив
    {
        time[0] = 60;
        expTime[0] = 0;
        time[1] = 0;
        expTime[1] = time[1] + 1;
        time[2] = expTime[2] = 0;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
    void testMinutesChangeR() // изменение минут правГрЭквив
    {
        time[0] = 60;
        expTime[0] = 0;
        time[1] = 58;
        expTime[1] = time[1] + 1;
        time[2] = expTime[2] = 0;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
    void testHoursChangeL() // изменение часов левГрЭквив
    {
        time[0] = 60;
        expTime[0] = 0;
        time[1] = 59;
        expTime[1] = 0;
        time[2] = 0;
        expTime[2] = 1;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
    void testHoursChangeR() // изменение часов правГрЭквив
    {
        time[0] = 60;
        expTime[0] = 0;
        time[1] = 59;
        expTime[1] = 0;
        time[2] = 22;
        expTime[2] = 23;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
    void testTimeRestart() // сброс времени после 23:59:59
    {
        time[0] = 60;
        expTime[0] = 0;
        time[1] = 59;
        expTime[1] = 0;
        time[2] = 23;
        expTime[2] = 0;
        stopWatch(time);
        for (i = 0; i < 3; i++) {
            TS_ASSERT_EQUALS(expTime[i], time[i]);
        }
    }
};
