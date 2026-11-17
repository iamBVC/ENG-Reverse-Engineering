/* sub_41DD20 @ 0041dd20   94 bytes */

undefined1 sub_41DD20(void)

{
  char cVar1;
  
  if ((DAT_005846e4 != 0x11) && (DAT_00582cc8 != '\0')) {
    cVar1 = sub_41DD80();
    if (cVar1 != '\0') {
      if (((DAT_006d9e28 == 0) &&
          (((DAT_005846e4 == 3 || (DAT_005846e4 == 4)) || (DAT_005846e4 == 2)))) &&
         (DAT_0057f8bc == 0)) {
        sub_439280();
      }
      else {
        sub_439160();
        cVar1 = sub_438070();
        if (cVar1 == '\0') {
          return 0;
        }
      }
      sub_439490();
    }
  }
  return 1;
}

