/* sub_545190 @ 00545190   215 bytes */

void sub_545190(void)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  
  if (DAT_006d9490 != 0) {
    sub_546CC0();
    sub_546A10(0);
    sub_546300();
    sub_5464D0();
    sub_545C00();
    sub_545C00();
    puVar2 = PTR_DAT_00571f54;
    if ((PTR_DAT_00571f54 != (undefined *)0xfffffff8) && (PTR_DAT_00571f54[0x1c] != '\0')) {
      iVar3 = 0;
      if (0 < *(int *)(PTR_DAT_00571f54 + 0x24)) {
        do {
          _AAL_UnloadFile_4(*(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x20) + iVar3 * 4) + 0x14));
          iVar1 = *(int *)(*(int *)(*(int *)(puVar2 + 0x20) + iVar3 * 4) + 0x10);
          if (iVar1 != 0) {
            sub_562941(iVar1);
            *(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x20) + iVar3 * 4) + 0x10) = 0;
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(puVar2 + 0x24));
      }
      iVar3 = 0;
      *(undefined4 *)(puVar2 + 0x20) = 0;
      *(undefined4 *)(puVar2 + 0x24) = 0;
      if (0 < *(int *)(puVar2 + 0x2c)) {
        do {
          iVar1 = *(int *)(*(int *)(*(int *)(puVar2 + 0x28) + iVar3 * 4) + 0x10);
          if (iVar1 != 0) {
            sub_562941(iVar1);
            *(undefined4 *)(*(int *)(*(int *)(puVar2 + 0x28) + iVar3 * 4) + 0x10) = 0;
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < *(int *)(puVar2 + 0x2c));
      }
      *(undefined4 *)(puVar2 + 0x28) = 0;
      *(undefined4 *)(puVar2 + 0x2c) = 0;
    }
    DAT_00586430 = 0;
  }
  return;
}

