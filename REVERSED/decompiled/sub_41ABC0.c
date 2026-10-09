/* sub_41ABC0 @ 0041abc0   211 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41ABC0(void)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  undefined4 *puVar6;
  char *pcVar7;
  undefined4 *puVar8;
  
  uVar2 = 0xffffffff;
  pcVar5 = s_Groove_005722dc;
  do {
    pcVar7 = pcVar5;
    if (uVar2 == 0) break;
    uVar2 = uVar2 - 1;
    pcVar7 = pcVar5 + 1;
    cVar1 = *pcVar5;
    pcVar5 = pcVar7;
  } while (cVar1 != '\0');
  uVar2 = ~uVar2;
  pcVar5 = pcVar7 + -uVar2;
  pcVar7 = (char *)&DAT_005848ec;
  for (uVar3 = uVar2 >> 2; uVar3 != 0; uVar3 = uVar3 - 1) {
    *(undefined4 *)pcVar7 = *(undefined4 *)pcVar5;
    pcVar5 = pcVar5 + 4;
    pcVar7 = pcVar7 + 4;
  }
  for (uVar2 = uVar2 & 3; uVar2 != 0; uVar2 = uVar2 - 1) {
    *pcVar7 = *pcVar5;
    pcVar5 = pcVar5 + 1;
    pcVar7 = pcVar7 + 1;
  }
  DAT_005848e8 = 0;
  _DAT_005848f8 = DAT_00580d00;
  sub_4057C0(s_MusicVolume_00571f48,0x41200000,0);
  _DAT_005848fc = __ftol();
  sub_4057C0(s_SoundEffectsVolume_005722c8,0x41200000,0);
  _DAT_00584900 = __ftol();
  _DAT_00584904 = 0x5622;
  _DAT_0058490c = 8;
  _DAT_00584908 = 1;
  DAT_00584910 = 1;
  DAT_00584911 = 1;
  DAT_00584913 = 1;
  DAT_00584912 = 1;
  puVar6 = &DAT_005848e8;
  puVar8 = &DAT_00584920;
  for (iVar4 = 0xb; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar8 = *puVar6;
    puVar6 = puVar6 + 1;
    puVar8 = puVar8 + 1;
  }
  sub_419810();
  _DAT_0058494c = (float)DAT_00583378 * _DAT_0056e2ac;
  return;
}

