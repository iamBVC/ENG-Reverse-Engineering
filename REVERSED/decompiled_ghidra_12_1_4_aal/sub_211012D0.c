/* sub_211012D0 @ 211012d0   58 bytes */

void sub_211012D0(void)

{
  if ((DAT_2111558c != 0) && (DAT_2111558c = DAT_2111558c + -1, DAT_2111558c == 0)) {
    DAT_211155a0 = 0;
    FreeLibrary(DAT_21115590);
    DAT_21115590 = (HMODULE)0x0;
  }
  Sleep(1);
  return;
}

