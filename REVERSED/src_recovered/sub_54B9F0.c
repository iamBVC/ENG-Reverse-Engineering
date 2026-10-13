/* Thiscall timer setter takes an object plus one eight-byte double argument. */
void sub_54B9F0(unsigned int *timer, double value)
{
  LARGE_INTEGER sample;
  int running = timer[6] == 1;
  if (running) {
    QueryPerformanceCounter(&sample);
    timer[6] = 0;
  }
  *(long long *)timer = (long long)value;
  if (running) {
    QueryPerformanceCounter(&sample);
    timer[2] = sample.LowPart;
    timer[3] = sample.HighPart;
    timer[6] = 1;
  }
}
