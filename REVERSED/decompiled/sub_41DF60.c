/* sub_41DF60 @ 0041df60   90 bytes */

void sub_41DF60(void)

{
  if (DAT_00585739 == '\0') {
    sub_40F220();
    sub_545270();
    sub_41EDE0();
    sub_41EF30();
    sub_41EE80();
    sub_4195C0();
    if (DAT_005846e8 != (int *)0x0) {
      (**(code **)(*DAT_005846e8 + 8))(DAT_005846e8);
      DAT_005846e8 = (int *)0x0;
    }
    sub_40FE10();
    sub_40FD00();
    DAT_00585739 = '\x01';
    PostQuitMessage(0);
  }
  return;
}

