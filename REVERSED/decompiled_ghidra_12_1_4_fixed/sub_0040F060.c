/* sub_40F060 @ 0040f060   270 bytes */

undefined4 sub_40F060(undefined4 param_1)

{
  int iVar1;
  int *piVar2;
  
  piVar2 = DAT_00582260;
  if (DAT_00582a80 != (int *)0x0) {
    iVar1 = (**(code **)(*DAT_00582a80 + 0x24))(DAT_00582a80,0x100,param_1);
    if (iVar1 == -0x7ff8ffe2) {
      PostMessageA(DAT_00582a70,0x400,1,0);
      return 0;
    }
    piVar2 = DAT_00582260;
    if (iVar1 != 0) {
      return 0;
    }
  }
LAB_0040f0b7:
  if ((*piVar2 == 0) && (piVar2[1] != 0)) {
    return 1;
  }
  if (piVar2[0x1d] != 0) {
    if ((piVar2[0x1d] & 0x80000000U) != 0) {
      PostMessageA(DAT_00582a70,0x400,1,0);
      piVar2 = (int *)*piVar2;
      goto LAB_0040f0b7;
    }
    iVar1 = (**(code **)(*(int *)piVar2[2] + 100))((int *)piVar2[2]);
    if (iVar1 == -0x7ff8fff4) {
LAB_0040f15d:
      piVar2[0x1d] = 0;
    }
    else {
      if (iVar1 == -0x7ff8ffe2) {
        piVar2[0x1d] = piVar2[0x1d] | 0x80000000;
        PostMessageA(DAT_00582a70,0x400,1,0);
        piVar2 = (int *)*piVar2;
        goto LAB_0040f0b7;
      }
      if ((iVar1 != 0) && (iVar1 != 1)) goto LAB_0040f160;
      iVar1 = (**(code **)(*(int *)piVar2[2] + 0x24))((int *)piVar2[2],0x50,piVar2 + 3);
      if (iVar1 == -0x7ff8ffe2) {
        PostMessageA(DAT_00582a70,0x400,1,0);
        piVar2[0x1d] = piVar2[0x1d] | 0x80000000;
        piVar2 = (int *)*piVar2;
        goto LAB_0040f0b7;
      }
      if (iVar1 != 0) goto LAB_0040f15d;
    }
  }
LAB_0040f160:
  piVar2 = (int *)*piVar2;
  goto LAB_0040f0b7;
}

