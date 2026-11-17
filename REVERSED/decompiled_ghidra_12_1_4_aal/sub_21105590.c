/* sub_21105590 @ 21105590   262 bytes */

/* WARNING: Removing unreachable block (ram,0x2110564a) */
/* WARNING: Removing unreachable block (ram,0x21105669) */
/* WARNING: Removing unreachable block (ram,0x2110566b) */
/* WARNING: Removing unreachable block (ram,0x21105670) */
/* WARNING: Removing unreachable block (ram,0x21105672) */

void sub_21105590(int *param_1)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 unaff_ESI;
  uint *puVar5;
  uint auStack_20 [3];
  uint local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_10 = 0;
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  local_14 = 0x14;
  (**(code **)(*param_1 + 0xc))(param_1);
  while( true ) {
    uVar2 = local_14;
    iVar3 = (**(code **)(*param_1 + 0x2c))(param_1);
    if (iVar3 != -0x7787ff6a) break;
    (**(code **)(*param_1 + 0x50))(param_1);
  }
  if (iVar3 == 0) {
    if ((auStack_20 != (uint *)0x0) && (uVar2 != 0)) {
      bVar1 = -(auStack_20[0] != 0x10);
      puVar5 = auStack_20;
      for (uVar4 = uVar2 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
        *puVar5 = CONCAT22(CONCAT11(bVar1,bVar1),CONCAT11(bVar1,bVar1)) & 0x80808080;
        puVar5 = puVar5 + 1;
      }
      for (uVar4 = uVar2 & 3; uVar4 != 0; uVar4 = uVar4 - 1) {
        *(byte *)puVar5 = bVar1 & 0x80;
        puVar5 = (uint *)((int)puVar5 + 1);
      }
    }
    (**(code **)(*param_1 + 0x4c))(param_1,auStack_20,uVar2,unaff_ESI,0);
  }
  return;
}

