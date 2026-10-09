/* sub_43CB40 @ 0043cb40   490 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_43CB40(int param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  DWORD DVar6;
  DWORD DVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  char *pcVar11;
  char *pcVar12;
  char local_180 [128];
  undefined1 local_100 [128];
  undefined1 local_80 [128];
  
  sub_4057C0(s_FrameAdvanceDelay_00578348,0x3f800000,0);
  iVar2 = __ftol();
  pcVar11 = &DAT_00578344;
  if (param_1 == 0) {
    pcVar11 = &DAT_00578340;
  }
  uVar8 = 0xffffffff;
  do {
    pcVar12 = pcVar11;
    if (uVar8 == 0) break;
    uVar8 = uVar8 - 1;
    pcVar12 = pcVar11 + 1;
    cVar1 = *pcVar11;
    pcVar11 = pcVar12;
  } while (cVar1 != '\0');
  uVar8 = ~uVar8;
  _DAT_006d946c = 0;
  pcVar11 = pcVar12 + -uVar8;
  pcVar12 = local_180;
  for (uVar9 = uVar8 >> 2; uVar9 != 0; uVar9 = uVar9 - 1) {
    *(undefined4 *)pcVar12 = *(undefined4 *)pcVar11;
    pcVar11 = pcVar11 + 4;
    pcVar12 = pcVar12 + 4;
  }
  _DAT_006d9470 = 0;
  for (uVar8 = uVar8 & 3; uVar8 != 0; uVar8 = uVar8 - 1) {
    *pcVar12 = *pcVar11;
    pcVar11 = pcVar11 + 1;
    pcVar12 = pcVar12 + 1;
  }
  sub_562717(local_100,s__s__s_wav_00578334,local_180,local_180);
  sub_546A30(local_100,0,1);
  iVar10 = 1;
  sub_562717(local_80,s__s_03d_bmp_00578328,local_180,1);
  uVar3 = sub_415690(local_180,local_80,DAT_00583374,DAT_00583378);
  piVar4 = (int *)sub_40CF10(DAT_00582ccc,uVar3);
  while (piVar4 != (int *)0x0) {
    sub_439330(piVar4);
    sub_562717(local_100,s__s__s_03d_wav_00578318,local_180,local_180,iVar10);
    iVar5 = sub_546A30(local_100,1,0);
    sub_439490();
    (**(code **)(*piVar4 + 8))(piVar4);
    if (iVar5 == 0) {
      DVar6 = timeGetTime();
      DVar7 = timeGetTime();
      uVar8 = DVar7 - DVar6;
      while (uVar8 <= (uint)(iVar2 * 1000)) {
        sub_545C00();
        DVar7 = timeGetTime();
        uVar8 = DVar7 - DVar6;
      }
    }
    else {
      iVar5 = sub_546B50(1);
      while (iVar5 != 0) {
        sub_545C00();
        iVar5 = sub_546B50(1);
      }
    }
    iVar10 = iVar10 + 1;
    sub_562717(local_80,s__s_03d_bmp_00578328,local_180,iVar10);
    uVar3 = sub_415690(local_180,local_80,DAT_00583374,DAT_00583378);
    piVar4 = (int *)sub_40CF10(DAT_00582ccc,uVar3);
  }
  return;
}

