void stopWatch(int* t)
{
    if (t[0] > 59) {
        t[1]++;
    }
    if (t[1] > 59) {
        t[1] = 0;
        t[2]++;
    }
}
