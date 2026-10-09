/* sub_413A60 @ 00413a60   172 bytes */

void __thiscall sub_413A60(undefined4 *param_1,code *param_2)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  
  piVar1 = (int *)*param_1;
  do {
    do {
      piVar3 = piVar1;
      piVar1 = (int *)*piVar3;
      if ((piVar1 == (int *)0x0) && (piVar3[1] != 0)) {
        return;
      }
      piVar4 = (int *)*param_1;
    } while (piVar4 == piVar3);
    do {
      iVar2 = (*param_2)(piVar4,piVar3);
      if (0 < iVar2) {
        if (piVar4 != piVar3) {
          if ((*piVar3 != 0) && (piVar3[1] != 0)) {
            *(int *)(*piVar3 + 4) = piVar3[1];
            *(int *)piVar3[1] = *piVar3;
            *piVar3 = 0;
            piVar3[1] = 0;
          }
          if (((int *)*piVar3 != piVar4) && (piVar4[1] != 0)) {
            if (((int *)*piVar3 != (int *)0x0) && (piVar3[1] != 0)) {
              *(int *)(*piVar3 + 4) = piVar3[1];
              *(int *)piVar3[1] = *piVar3;
              *piVar3 = 0;
              piVar3[1] = 0;
            }
            *piVar3 = (int)piVar4;
            piVar3[1] = piVar4[1];
            piVar4[1] = (int)piVar3;
            *(int **)piVar3[1] = piVar3;
          }
        }
        break;
      }
      piVar4 = (int *)*piVar4;
    } while (piVar4 != piVar3);
  } while( true );
}

