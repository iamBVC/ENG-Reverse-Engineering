/* sub_40E9A0 @ 0040e9a0   159 bytes */

undefined4 sub_40E9A0(void)

{
  int *piVar1;
  char cVar2;
  int iVar3;
  int *piVar4;
  undefined4 *puVar5;
  
  puVar5 = &DAT_00582a88;
  for (iVar3 = 0x32; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = 0;
    puVar5 = puVar5 + 1;
  }
  iVar3 = (**(code **)(*DAT_00582a74 + 0x10))(DAT_00582a74,4,&LAB_0040ea40,0,1);
  if ((iVar3 != 0) || (piVar4 = DAT_00582260, DAT_00582260 == (int *)&DAT_00582264)) {
    return 0;
  }
LAB_0040e9d9:
  do {
    if ((*piVar4 == 0) && (piVar4[1] != 0)) {
      return 1;
    }
    iVar3 = (**(code **)(*(int *)piVar4[2] + 0x2c))((int *)piVar4[2],&DAT_0056e744);
    if (iVar3 == 0) {
      cVar2 = sub_40E830(piVar4[2],1,0);
      if (cVar2 == '\0') {
        piVar1 = (int *)piVar4[2];
        if (piVar1 != (int *)0x0) {
          (**(code **)(*piVar1 + 8))(piVar1);
          piVar4[2] = 0;
        }
        goto LAB_0040ea2e;
      }
    }
    else {
      piVar1 = (int *)piVar4[2];
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1);
        piVar4[2] = 0;
        piVar4[0x1d] = 0;
        piVar4 = (int *)*piVar4;
        goto LAB_0040e9d9;
      }
LAB_0040ea2e:
      piVar4[0x1d] = 0;
    }
    piVar4 = (int *)*piVar4;
  } while( true );
}

