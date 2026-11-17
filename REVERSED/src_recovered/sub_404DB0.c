/* Hand reconstruction of 0x00404DB0: convert a direction vector held in 12.12
   fixed point into the two turn angles the original stores back in 12.12 form.
   The dy square the original computes is overwritten by the dz square, so only
   dx^2 + dz^2 reaches the sqrt; DAT_0056e078 is 4096*2/pi, so a full turn is
   4096 and the result is masked to its low 12 bits before being shifted up. */

void sub_404DB0(int *param_1,int *param_2,int *param_3,int *param_4)

{
  int dx, dy, dz;
  int square_x, square_z, length;

  dx = param_1[0] - param_2[0];
  dy = param_1[1] - param_2[1];
  dz = param_1[2] - param_2[2];
  square_x = (int)(((longlong)dx * dx) >> 12);
  square_z = (int)(((longlong)dz * dz) >> 12);
  *param_3 = ((int)(fpatan((double)dx,(double)dz) * DAT_0056e078) & 0xfff) << 12;
  length = (int)(sqrt((double)(square_x + square_z) * DAT_0056e020) * DAT_0056e070);
  *param_4 = ((int)(fpatan((double)dy,(double)length) * DAT_0056e078) & 0xfff) << 12;
  return;
}
