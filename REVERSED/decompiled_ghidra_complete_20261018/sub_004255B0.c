/* sub_4255B0 @ 004255b0   265 bytes */

void sub_4255B0(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  char *pcVar7;
  char *pcVar8;
  char local_10 [16];
  
  DAT_005fcf50 = 0;
  DAT_005fcf40 = 0;
  DAT_005fcf38 = 0;
  DAT_005fcf3c = param_1;
  DAT_005fcf0c = 0;
  if (param_1 == 0) {
    DAT_005fcf54 = 99;
    return;
  }
  uVar3 = 0xffffffff;
  pcVar6 = (char *)&DAT_006da340;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = local_10;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar3 = 0xffffffff;
  pcVar6 = (char *)&DAT_005733f8;
  do {
    pcVar8 = pcVar6;
    if (uVar3 == 0) break;
    uVar3 = uVar3 - 1;
    pcVar8 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar8;
  } while (cVar1 != '\0');
  uVar3 = ~uVar3;
  iVar5 = -1;
  pcVar6 = local_10;
  do {
    pcVar7 = pcVar6;
    if (iVar5 == 0) break;
    iVar5 = iVar5 + -1;
    pcVar7 = pcVar6 + 1;
    cVar1 = *pcVar6;
    pcVar6 = pcVar7;
  } while (cVar1 != '\0');
  pcVar6 = pcVar8 + -uVar3;
  pcVar8 = pcVar7 + -1;
  for (uVar4 = uVar3 >> 2; uVar4 != 0; uVar4 = uVar4 - 1) {
    *(undefined4 *)pcVar8 = *(undefined4 *)pcVar6;
    pcVar6 = pcVar6 + 4;
    pcVar8 = pcVar8 + 4;
  }
  for (uVar3 = uVar3 & 3; uVar3 != 0; uVar3 = uVar3 - 1) {
    *pcVar8 = *pcVar6;
    pcVar6 = pcVar6 + 1;
    pcVar8 = pcVar8 + 1;
  }
  uVar2 = sub_415690(&DAT_00570348,local_10);
  uVar2 = sub_562AEE(uVar2,&DAT_00570350);
  sub_5629E6(&DAT_005fcf04,4,1,uVar2);
  DAT_005fcf5c = sub_41EE40(DAT_005fcf04 * 8);
  sub_5629E6(DAT_005fcf5c,DAT_005fcf04 * 8,1,uVar2);
  sub_5628EB(uVar2);
  DAT_005fcf54 = DAT_005fcf04;
  return;
}

