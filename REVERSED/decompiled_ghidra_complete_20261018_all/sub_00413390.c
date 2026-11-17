/* sub_413390 @ 00413390   238 bytes */

void __fastcall sub_413390(int *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0056d823;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  sub_5628BC(param_1[2]);
  if (param_1[3] != 0) {
    sub_562941(param_1[3]);
  }
  if ((int *)param_1[0xb] != param_1 + 0xc) {
    do {
      piVar1 = (int *)param_1[0xb];
      if (piVar1 != param_1 + 0xc) {
        if ((*piVar1 != 0) && (piVar1[1] != 0)) {
          *(int *)(*piVar1 + 4) = piVar1[1];
          *(int *)piVar1[1] = *piVar1;
          *piVar1 = 0;
          piVar1[1] = 0;
        }
        if (piVar1 != (int *)0x0) {
          sub_4135C0();
          sub_562941(piVar1);
        }
      }
    } while ((int *)param_1[0xb] != param_1 + 0xc);
  }
  piVar1 = (int *)param_1[0xb];
  while (piVar1 != param_1 + 0xc) {
    if ((*piVar1 != 0) && (piVar1[1] != 0)) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      *piVar1 = 0;
      piVar1[1] = 0;
    }
    piVar1 = (int *)param_1[0xb];
  }
  if ((*param_1 != 0) && (param_1[1] != 0)) {
    *(int *)(*param_1 + 4) = param_1[1];
    *(int *)param_1[1] = *param_1;
    *param_1 = 0;
    param_1[1] = 0;
  }
  ExceptionList = local_c;
  return;
}

