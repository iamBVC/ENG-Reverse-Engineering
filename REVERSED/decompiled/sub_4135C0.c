/* sub_4135C0 @ 004135c0   222 bytes */

void __fastcall sub_4135C0(int *param_1)

{
  int *piVar1;
  void *local_c;
  undefined1 *puStack_8;
  undefined4 local_4;
  
  puStack_8 = &LAB_0056d843;
  local_c = ExceptionList;
  local_4 = 1;
  ExceptionList = &local_c;
  sub_5628BC(param_1[2]);
  if ((int *)param_1[0xc] != param_1 + 0xd) {
    do {
      piVar1 = (int *)param_1[0xc];
      if (piVar1 != param_1 + 0xd) {
        if ((*piVar1 != 0) && (piVar1[1] != 0)) {
          *(int *)(*piVar1 + 4) = piVar1[1];
          *(int *)piVar1[1] = *piVar1;
          *piVar1 = 0;
          piVar1[1] = 0;
        }
        if (piVar1 != (int *)0x0) {
          sub_413750();
          sub_562941(piVar1);
        }
      }
    } while ((int *)param_1[0xc] != param_1 + 0xd);
  }
  piVar1 = (int *)param_1[0xc];
  while (piVar1 != param_1 + 0xd) {
    if ((*piVar1 != 0) && (piVar1[1] != 0)) {
      *(int *)(*piVar1 + 4) = piVar1[1];
      *(int *)piVar1[1] = *piVar1;
      *piVar1 = 0;
      piVar1[1] = 0;
    }
    piVar1 = (int *)param_1[0xc];
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

