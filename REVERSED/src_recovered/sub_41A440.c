/* The original stores twice atan(focal constant / width) at camera byte +0x20. */
void sub_41A440(ushort param_1)
{
  double angle = atan2(DAT_0056e280 / (double)param_1, 1.0);
  *(float *)((unsigned char *)DAT_00581168 + 0x20) = (float)(angle + angle);
  sub_402910((int)DAT_00581168, 1.0f, 1.0f);
}
