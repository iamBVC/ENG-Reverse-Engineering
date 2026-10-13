/* Startup gamma ramp recovered from the original x87 and SetGammaRamp calls. */
uint sub_410480(float param_1,float param_2,float param_3)
{
  unsigned short ramp[3][256];
  int index;
  double value;
  float rounded;
  unsigned short entry;

  if (DAT_00582cec == 0) return 0;
  for (index = 0; index < 256; ++index) {
    value = pow((double)index * DAT_0056e15c, (double)param_3);
    value = value * param_2 + param_1;
    rounded = (float)value;
    if (!(value > 0.0)) entry = 0;
    else if (!(rounded < 1.0f)) entry = 0xffff;
    else entry = (unsigned short)((uint)((double)rounded * DAT_0056e1cc) & 0xffff);
    ramp[0][index] = entry;
    ramp[1][index] = entry;
    ramp[2][index] = entry;
  }
  return (**(groove_com3 **)(*DAT_00582cec + 0x10))(DAT_00582cec, 0, ramp) == 0;
}
