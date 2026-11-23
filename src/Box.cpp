bool boxdetect()
{
    if (Distance4.objectDistance() < YMAX - 5)
    {
        return true
    }
}

void nobox()
{
    wait(30, seconds);
}
