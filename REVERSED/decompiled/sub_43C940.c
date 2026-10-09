/* sub_43C940 @ 0043c940   26 bytes */

void sub_43C940(void)

{
  if (DAT_006d91b8 != (int *)0x0) {
    (**(code **)(*DAT_006d91b8 + 8))(DAT_006d91b8);
  }
  DAT_006d91b8 = (int *)0x0;
  return;
}

