/* sub_410480 @ 00410480   208 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint sub_410480(float param_1,float param_2)

{
  int *piVar1;
  undefined2 uVar2;
  uint in_EAX;
  undefined2 *puVar3;
  int iVar4;
  float10 fVar5;
  undefined2 local_600 [256];
  undefined2 local_400 [256];
  undefined2 local_200 [256];
  
  piVar1 = DAT_00582cec;
  if (DAT_00582cec == (int *)0x0) {
    return in_EAX & 0xffffff00;
  }
  iVar4 = 0;
  puVar3 = local_400;
  do {
    fVar5 = (float10)sub_563360();
    fVar5 = fVar5 * (float10)param_2 + (float10)param_1;
    if ((float10)_DAT_0056e00c < fVar5) {
      if ((float)fVar5 < _DAT_0056e008) {
        uVar2 = __ftol();
      }
      else {
        uVar2 = 0xffff;
      }
    }
    else {
      uVar2 = 0;
    }
    puVar3[0x100] = uVar2;
    *puVar3 = uVar2;
    puVar3[-0x100] = uVar2;
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 1;
  } while (iVar4 < 0x100);
  iVar4 = (**(code **)(*piVar1 + 0x10))(piVar1,0,local_600);
  return (uint)(iVar4 == 0);
}

