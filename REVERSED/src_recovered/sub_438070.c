/* sub_438070 @ 00438070   257 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_438070(void)

{
  static unsigned int traced;
  int trace = traced++ < 3;
  char cVar1;
  int iVar2;
  if (trace) fprintf(stderr, "[render] setup begin dirty=%d/%d/%d\n", DAT_006d8731, DAT_006d8732, DAT_006d8733);
  
  if (DAT_006d8731 != '\0') {
    cVar1 = sub_438180();
    if (cVar1 != '\0') {
      sub_408300();
      sub_4071D0();
    }
    sub_439600();
    DAT_006d8731 = '\0';
  }
  if (DAT_006d8732 != '\0') {
    sub_410480(DAT_00573d38,DAT_00573d3c,DAT_00573d40);
    DAT_006d8732 = '\0';
  }
  if (DAT_006d8733 != '\0') {
    sub_42C790();
    if (DAT_0058115c != 0) {
      sub_41BF30((int)DAT_0058115c);
    }
    if (DAT_00581160 != 0) {
      sub_41BF30((int)DAT_00581160);
    }
    DAT_006d8733 = '\0';
  }
  if (DAT_005833e1 == '\0') {
    iVar2 = (**(code **)(*DAT_00582cd4 + 0x24))(DAT_00582cd4);
    if (iVar2 != 0) {
      return 0;
    }
  }
  else {
    _DAT_005832f8 = 0x7c;
    iVar2 = (**(code **)(*DAT_00582ce4 + 100))(DAT_00582ce4,0,&DAT_005832f8,1,0);
    if (iVar2 != 0) {
      return 0;
    }
  }
  if (trace) fprintf(stderr, "[render] scene generation begin\n");
  sub_41A5E0();
  if (trace) fprintf(stderr, "[render] scene generation complete; submission begin\n");
  sub_424BE0();
  if (trace) fprintf(stderr, "[render] submission complete\n");
  if (DAT_005833e1 == '\0') {
    iVar2 = (**(code **)(*DAT_00582cd4 + 0x28))(DAT_00582cd4);
    if (iVar2 != 0) {
      return 0;
    }
  }
  else {
    (**(code **)(*DAT_00582ce4 + 0x80))(DAT_00582ce4,0);
  }
  return 1;
}
