/* sub_40EA40 @ 0040EA40, recovered from the Ghidra disassembly.
 * The original callback returns with RET 8, so it is stdcall with two stack
 * arguments. The vtable object comes back through the local output slot, and
 * the exception chain saved in piStack_c is restored on every exit. */
undefined4 __stdcall sub_40EA40(int *param_1, undefined4 param_2)
{
  uint *puVar1;
  int *piVar2;
  char cVar3;
  int iVar4;
  int *piVar5;
  void *pvVar6;
  uint uVar7;
  int *piVar8;
  int *enumerator;
  undefined4 auStack_14[2];
  int *piStack_c;
  undefined1 *puStack_8;
  undefined4 uStack_4;

  (void)param_2;
  uStack_4 = 0xffffffff;
  puStack_8 = &LAB_0056d6b3;
  piStack_c = ExceptionList;
  puVar1 = (uint *)(param_1 + 1);
  ExceptionList = &piStack_c;
  iVar4 = (**(code **)(*DAT_00582a74 + 0xc))(DAT_00582a74, puVar1, auStack_14, 0);
  enumerator = (int *)auStack_14[0];
  piVar8 = param_1;
  piVar5 = piStack_c;
  if (iVar4 == 0) {
    piVar5 = operator_new(0x160);
    if (piVar5 == (int *)0x0) {
      piVar5 = (int *)0x0;
    }
    else {
      *piVar5 = 0;
      piVar5[1] = 0;
      piVar8 = piVar5;
      for (iVar4 = 0x58; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar8 = 0;
        piVar8 = piVar8 + 1;
      }
      uStack_4 = 1;
      pvVar6 = operator_new(0x80);
      piVar5[0x1b] = (int)pvVar6;
      pvVar6 = operator_new(0x38);
      piVar5[0x1c] = (int)pvVar6;
      piVar5[0x1a] = -1;
      piVar5[0x19] = -1;
      piVar5[0x18] = -1;
      piVar5[0x17] = -1;
    }
    uStack_4 = 0xffffffff;
    iVar4 = (**(code **)*enumerator)(enumerator, &DAT_0056e6cc, piVar5 + 2);
    piVar8 = DAT_00582268;
    if (iVar4 != 0) {
      if (piVar5 != (int *)0x0) {
        if (piVar5[0x1b] != 0) {
          sub_562941(piVar5[0x1b]);
        }
        if (piVar5[0x1c] != 0) {
          sub_562941(piVar5[0x1c]);
        }
        if ((*piVar5 != 0) && (piVar5[1] != 0)) {
          *(int *)(*piVar5 + 4) = piVar5[1];
          *(int *)piVar5[1] = *piVar5;
          *piVar5 = 0;
          piVar5[1] = 0;
        }
        sub_562941(piVar5);
      }
      if (enumerator == (int *)0x0) {
        ExceptionList = piStack_c;
        return 1;
      }
      (**(code **)(*enumerator + 8))(enumerator);
      ExceptionList = piStack_c;
      return 1;
    }
    if (((piVar5 != DAT_00582268) && (piVar2 = (int *)piVar5[1], piVar2 != DAT_00582268)) &&
        (*DAT_00582268 != 0)) {
      if ((*piVar5 != 0) && (piVar2 != (int *)0x0)) {
        *(int **)(*piVar5 + 4) = piVar2;
        *(int *)piVar5[1] = *piVar5;
        *piVar5 = 0;
        piVar5[1] = 0;
      }
      iVar4 = *piVar8;
      piVar5[1] = (int)piVar8;
      *piVar5 = iVar4;
      *(int **)(iVar4 + 4) = piVar5;
      *(int **)piVar5[1] = piVar5;
    }
    piVar8 = piStack_c;
    if (enumerator != (int *)0x0) {
      (**(code **)(*enumerator + 8))(enumerator);
      piVar8 = piStack_c;
    }
  }
  sub_562717(piVar5 + 0x20, &DAT_00570300, (*puVar1 & 0xf) + 1);
  _strncpy((char *)(piVar5 + 0x34), (char *)(piVar8 + 0x4b), 0x4f);
  piVar5[0x48] = *puVar1;
  piVar5[0x49] = param_1[2];
  piVar5[0x4a] = param_1[3];
  piVar5[0x4b] = param_1[4];
  piVar5[0x4c] = piVar8[5];
  piVar5[0x4d] = piVar8[6];
  piVar5[0x4e] = piVar8[7];
  piVar5[0x4f] = piVar8[8];
  *(bool *)(piVar5 + 0x57) = (*puVar1 & 0xf) != 0;
  cVar3 = (char)((ushort)(short)piVar8[9] >> 8);
  if (cVar3 == '\x05') {
    uVar7 = 0x20;
  }
  else if (cVar3 == '\x04') {
    uVar7 = 2;
  }
  else if (cVar3 == '\x03') {
    uVar7 = 8;
  }
  else {
    uVar7 = 1;
    if (cVar3 != '\x02') {
      uVar7 = 0x10;
    }
  }
  DAT_00582b48 = DAT_00582b48 | uVar7;
  piVar5[0x1d] = piVar5[0x1d] | uVar7;
  ExceptionList = piStack_c;
  return 1;
}
