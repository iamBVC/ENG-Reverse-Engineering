/* sub_21108F30 @ 21108f30   188 bytes */

int __thiscall sub_21108F30(void *this,LPCSTR param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  UINT UVar4;
  HMODULE pHVar5;
  
  piVar3 = sub_21109A40(*(int **)this);
  iVar1 = piVar3[2];
  piVar3[3] = 0;
  *(int *)((int)this + 8) = iVar1;
  UVar4 = SetErrorMode(0x8000);
  pHVar5 = LoadLibraryA(param_1);
  SetErrorMode(UVar4 & 0xffff);
  if (pHVar5 == (HMODULE)0x0) {
    iVar2 = *(int *)this;
    if ((iVar1 != -1) && (piVar3 = (int *)(*(int *)(iVar2 + 0xc) + iVar1 * 0x30), piVar3[2] != -1))
    {
      piVar3[2] = -1;
      if (*piVar3 != 0) {
        *(int *)(*piVar3 + 4) = piVar3[1];
      }
      if ((int *)piVar3[1] != (int *)0x0) {
        *(int *)piVar3[1] = *piVar3;
      }
      if (*(int **)(iVar2 + 4) == piVar3) {
        *(int *)(iVar2 + 4) = *piVar3;
      }
      *piVar3 = *(int *)(iVar2 + 8);
      piVar3[1] = 0;
      if (*(int *)(iVar2 + 8) != 0) {
        *(int **)(*(int *)(iVar2 + 8) + 4) = piVar3;
      }
      *(int **)(iVar2 + 8) = piVar3;
    }
    return 0;
  }
  *(HMODULE *)(*(int *)(*(int *)this + 0xc) + 0xc + iVar1 * 0x30) = pHVar5;
  return iVar1;
}

