/* sub_41DD20 @ 0041dd20   94 bytes */

undefined1 sub_41DD20(void)

{
  static unsigned int traced;
  int trace = traced++ < 3;
  char cVar1;
  if (trace) fprintf(stderr, "[frame] draw begin state=%d active=%d\n", DAT_005846e4, DAT_00582cc8);
  
  if ((DAT_005846e4 != 0x11) && (DAT_00582cc8 != '\0')) {
    cVar1 = sub_41DD80();
    if (cVar1 != '\0') {
      if (((DAT_006d9e28 == 0) &&
          (((DAT_005846e4 == 3 || (DAT_005846e4 == 4)) || (DAT_005846e4 == 2)))) &&
         (DAT_0057f8bc == 0)) {
        sub_439280();
      }
      else {
        if (trace) fprintf(stderr, "[frame] clear begin\n");
        sub_439160();
        if (trace) fprintf(stderr, "[frame] scene begin\n");
        cVar1 = sub_438070();
        if (cVar1 == '\0') {
          return 0;
        }
      }
      if (trace) fprintf(stderr, "[frame] present begin\n");
      sub_439490();
      if (trace) fprintf(stderr, "[frame] present complete\n");
    }
  }
  return 1;
}
