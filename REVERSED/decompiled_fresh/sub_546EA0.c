/* sub_546EA0 @ 00546ea0   604 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_546EA0(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  undefined4 *puVar5;
  char *pcVar6;
  bool bVar7;
  undefined1 local_24 [4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined2 local_10;
  undefined2 local_e;
  undefined4 local_c;
  undefined4 local_8;
  undefined2 local_4;
  undefined2 local_2;
  
  if (DAT_006d9490 == 0) {
    iVar2 = _AAL_Init_0();
    if (iVar2 != 0) {
      DAT_005834dc = 0;
      return;
    }
    sub_4057C0(s_SoundDevice_00578ebc,0,0);
    DAT_005834d8 = __ftol();
    sub_4057C0(s_SoundVolume_00571f30,0x42fe0000,0);
    _DAT_005834e0 = __ftol();
    sub_4057C0(s_MusicVolume_00571f48,0x42c00000,0);
    _DAT_005834ec = __ftol();
    sub_4057C0(s_SpeakerMode_00571f3c,0x40800000,0);
    DAT_005834f0 = __ftol();
    DAT_005834dc = 1;
    DAT_005834f4 = 0;
    _DAT_005834fc = 0;
    _DAT_005834f8 = 4;
    local_20 = DAT_005834d8;
    local_14 = *(undefined4 *)(param_2 + 4);
    local_18 = 0;
    local_1c = 0;
    local_2 = 0x10;
    local_10 = 1;
    local_e = 2;
    local_c = 0xac44;
    local_4 = 4;
    local_8 = 0x2b110;
    _AAL_InitDriver_4(local_24);
    DAT_005834d8 = _AAL_GetDeviceId_4(1);
    if (DAT_005834d8 == -1) {
      DAT_005834dc = 0;
      _AAL_Quit_0();
      return;
    }
    DAT_005834f4 = sub_546E50();
    DAT_005834f0 = _AAL_SetSpeakerMode_4(DAT_005834f0);
    if (DAT_005834f4 != 0) {
      iVar2 = 0;
      if (0 < DAT_005834f4) {
        puVar5 = &DAT_006d91e0;
        do {
          pbVar3 = (byte *)*puVar5;
          pcVar6 = s_Creative_Labs_EAX_2__TM__00578ea0;
          do {
            bVar1 = *pbVar3;
            bVar7 = bVar1 < (byte)*pcVar6;
            if (bVar1 != *pcVar6) {
LAB_00547026:
              iVar4 = (1 - (uint)bVar7) - (uint)(bVar7 != 0);
              goto LAB_0054702b;
            }
            if (bVar1 == 0) break;
            bVar1 = pbVar3[1];
            bVar7 = bVar1 < (byte)pcVar6[1];
            if (bVar1 != pcVar6[1]) goto LAB_00547026;
            pbVar3 = pbVar3 + 2;
            pcVar6 = pcVar6 + 2;
          } while (bVar1 != 0);
          iVar4 = 0;
LAB_0054702b:
          if (iVar4 == 0) break;
          iVar2 = iVar2 + 1;
          puVar5 = puVar5 + 2;
        } while (iVar2 < DAT_005834f4);
      }
      if (iVar2 == DAT_005834f4) {
        DAT_005834f4 = 0;
      }
      else {
        iVar4 = _AAL_Open3DProvider_4((&DAT_006d91e4)[iVar2 * 2]);
        if (iVar4 == 0) {
          DAT_005834f4 = (&DAT_006d91e4)[iVar2 * 2];
        }
        else {
          DAT_005834f4 = 0;
        }
      }
    }
    DAT_006d9490 = param_1;
    *(undefined4 *)(param_1 + 0x100) = 0x1000;
    *(undefined4 *)(DAT_006d9490 + 0xf4) = 0x1000;
    *(undefined4 *)(DAT_006d9490 + 0xfc) = 0;
    *(undefined4 *)(DAT_006d9490 + 0xf8) = 0;
    if (DAT_005834f4 != 0) {
      *(undefined4 *)(DAT_006d9490 + 0x68) = 0xfffff;
      _AAL_Get3DAttributes_8(DAT_005834f4,DAT_006d9490 + 0x68);
      *(undefined4 *)(DAT_006d9490 + 0x68) = 0;
    }
    sub_547470(DAT_006d9490,param_2);
  }
  return;
}

