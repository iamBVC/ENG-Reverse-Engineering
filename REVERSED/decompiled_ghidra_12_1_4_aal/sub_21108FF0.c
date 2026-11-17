/* sub_21108FF0 @ 21108ff0   184 bytes */

void __thiscall sub_21108FF0(void *this,int param_1)

{
  HMODULE hLibModule;
  int iVar1;
  uint *puVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  
  if (param_1 == 0) {
    puVar2 = *(uint **)this;
    if (*puVar2 != 0) {
      iVar5 = 0;
      uVar4 = 0;
      do {
        if ((iVar5 != 0) && (*(int *)(puVar2[3] + 8 + iVar5) != -1)) {
          sub_21108FF0(this,uVar4);
        }
        puVar2 = *(uint **)this;
        uVar4 = uVar4 + 1;
        iVar5 = iVar5 + 0x30;
      } while (uVar4 < *puVar2);
      return;
    }
  }
  else {
    iVar5 = param_1 * 0x30;
    hLibModule = *(HMODULE *)(*(int *)(*(int *)this + 0xc) + 0xc + iVar5);
    if (hLibModule != (HMODULE)0x0) {
      FreeLibrary(hLibModule);
    }
    iVar1 = *(int *)this;
    if ((param_1 != -1) &&
       (piVar3 = (int *)(*(int *)(iVar1 + 0xc) + iVar5),
       *(int *)(*(int *)(iVar1 + 0xc) + 8 + iVar5) != -1)) {
      piVar3[2] = -1;
      if (*piVar3 != 0) {
        *(int *)(*piVar3 + 4) = piVar3[1];
      }
      if ((int *)piVar3[1] != (int *)0x0) {
        *(int *)piVar3[1] = *piVar3;
      }
      if (*(int **)(iVar1 + 4) == piVar3) {
        *(int *)(iVar1 + 4) = *piVar3;
      }
      *piVar3 = *(int *)(iVar1 + 8);
      piVar3[1] = 0;
      if (*(int *)(iVar1 + 8) != 0) {
        *(int **)(*(int *)(iVar1 + 8) + 4) = piVar3;
      }
      *(int **)(iVar1 + 8) = piVar3;
    }
  }
  return;
}

