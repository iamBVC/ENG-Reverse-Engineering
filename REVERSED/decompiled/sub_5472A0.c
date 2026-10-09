/* sub_5472A0 @ 005472a0   428 bytes */

void sub_5472A0(uint param_1,int param_2,uint param_3,ushort *param_4)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  byte *pbVar4;
  ushort *puVar5;
  byte bVar6;
  uint uVar7;
  uint uVar8;
  undefined1 *puVar9;
  
  iVar2 = param_1;
  iVar3 = DAT_006d9490;
  *(ushort **)(*(int *)(DAT_006d9490 + 0x4c) + param_1 * 4) = param_4;
  bVar6 = 0;
  *(uint *)(*(int *)(iVar3 + 0x50) + param_1 * 4) = param_3;
  param_1 = 0;
  *(int *)(*(int *)(iVar3 + 0x48) + iVar2 * 4) = param_2;
  pbVar4 = (byte *)(param_2 + 0x20);
  puVar5 = (ushort *)(param_2 + 0x820);
  iVar3 = (iVar2 + -3) * 0x10;
  *(int *)((iVar2 + 5) * 0x10 + DAT_006d949c) = param_2;
  *(byte **)(DAT_006d949c + 0x84 + iVar3) = pbVar4;
  *(ushort **)(DAT_006d949c + 0x88 + iVar3) = puVar5;
  *(undefined4 *)(DAT_006d949c + 0x8c + iVar3) = 0;
  param_3 = 0;
  do {
    pbVar4[5] = bVar6;
    *(ushort **)(pbVar4 + 8) = puVar5;
    pbVar4[0xc] = 0;
    pbVar4[0xd] = 0;
    pbVar4[0xe] = 0;
    pbVar4[0xf] = 0;
    if (*pbVar4 != 0) {
      if (param_1 == 0) {
        param_1 = param_3;
      }
      bVar6 = bVar6 + 1;
      uVar7 = (uint)*pbVar4;
      uVar8 = 0;
      if (uVar7 != 0) {
        puVar5 = puVar5 + uVar7 * 0x10;
        uVar8 = uVar7;
      }
      puVar5 = puVar5 + (0x10 - uVar8) * 0x10;
    }
    param_3 = param_3 + 1;
    pbVar4 = pbVar4 + 0x10;
  } while (param_3 < 0x80);
  if (param_1 != 0) {
    uVar8 = 0;
    if (*(short *)(param_2 + 0x16) != 0) {
      puVar9 = (undefined1 *)(*(int *)(DAT_006d949c + 0x84 + iVar3) + 0x7f5);
      do {
        puVar5 = puVar5 + 1;
        uVar7 = (uint)*puVar5;
        iVar3 = _AAL_LoadResourceType_16(param_4,uVar7 * 8,0x15,0);
        *(int *)(puVar9 + 7) = iVar3;
        if (iVar3 == 0) {
          sub_426500(s_Failed_to_load_ambient_sound_id___00578ec8,uVar8);
        }
        _AAL_SetResource_8(*(undefined4 *)(puVar9 + 7),&stack0xffffffdc);
        uVar1 = *param_4;
        param_4 = param_4 + uVar7 * 4;
        *puVar9 = (char)((uVar7 & (byte)-((uVar1 & 0x200) != 0) >> 3) << 3);
        uVar8 = uVar8 + 1;
        puVar9 = puVar9 + -0x10;
      } while (uVar8 < *(ushort *)(param_2 + 0x16));
    }
  }
  return;
}

