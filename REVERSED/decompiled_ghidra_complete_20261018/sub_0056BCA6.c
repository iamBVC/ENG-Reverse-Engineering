/* sub_56BCA6 @ 0056bca6   409 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_56BCA6(undefined4 param_1)

{
  BYTE *pBVar1;
  byte *pbVar2;
  byte bVar3;
  byte bVar4;
  UINT CodePage;
  UINT *pUVar5;
  BOOL BVar6;
  uint uVar7;
  BYTE *pBVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  byte *pbVar12;
  undefined4 *puVar13;
  _cpinfo local_1c;
  uint local_8;
  
  CodePage = sub_56BE3F(param_1);
  if (CodePage == DAT_006da5ac) {
    return 0;
  }
  if (CodePage != 0) {
    iVar11 = 0;
    pUVar5 = &DAT_0057d1c0;
    do {
      if (*pUVar5 == CodePage) {
        puVar13 = &DAT_006da6c0;
        for (iVar9 = 0x40; iVar9 != 0; iVar9 = iVar9 + -1) {
          *puVar13 = 0;
          puVar13 = puVar13 + 1;
        }
        local_8 = 0;
        iVar11 = iVar11 * 0x30;
        *(undefined1 *)puVar13 = 0;
        pbVar12 = (byte *)(iVar11 + 0x57d1d0);
        do {
          bVar3 = *pbVar12;
          pbVar10 = pbVar12;
          while ((bVar3 != 0 && (bVar3 = pbVar10[1], bVar3 != 0))) {
            uVar7 = (uint)*pbVar10;
            if (uVar7 <= bVar3) {
              bVar4 = (&DAT_0057d1b8)[local_8];
              do {
                pbVar2 = (byte *)((int)&DAT_006da6c0 + uVar7 + 1);
                *pbVar2 = *pbVar2 | bVar4;
                uVar7 = uVar7 + 1;
              } while (uVar7 <= bVar3);
            }
            pbVar10 = pbVar10 + 2;
            bVar3 = *pbVar10;
          }
          local_8 = local_8 + 1;
          pbVar12 = pbVar12 + 8;
        } while (local_8 < 4);
        _DAT_006da5bc = 1;
        DAT_006da5ac = CodePage;
        DAT_006da7c4 = sub_56BE89(CodePage);
        DAT_006da5b0 = *(undefined4 *)(iVar11 + 0x57d1c4);
        DAT_006da5b4 = *(undefined4 *)(iVar11 + 0x57d1c8);
        DAT_006da5b8 = *(undefined4 *)(iVar11 + 0x57d1cc);
        goto LAB_0056be2e;
      }
      pUVar5 = pUVar5 + 0xc;
      iVar11 = iVar11 + 1;
    } while ((int)pUVar5 < 0x57d2b0);
    BVar6 = GetCPInfo(CodePage,&local_1c);
    if (BVar6 == 1) {
      puVar13 = &DAT_006da6c0;
      DAT_006da5ac = CodePage;
      for (iVar11 = 0x40; iVar11 != 0; iVar11 = iVar11 + -1) {
        *puVar13 = 0;
        puVar13 = puVar13 + 1;
      }
      *(undefined1 *)puVar13 = 0;
      DAT_006da7c4 = 0;
      if (local_1c.MaxCharSize < 2) {
        _DAT_006da5bc = 0;
      }
      else {
        if (local_1c.LeadByte[0] != '\0') {
          pBVar8 = local_1c.LeadByte + 1;
          do {
            bVar3 = *pBVar8;
            if (bVar3 == 0) break;
            for (uVar7 = (uint)pBVar8[-1]; uVar7 <= bVar3; uVar7 = uVar7 + 1) {
              pbVar12 = (byte *)((int)&DAT_006da6c0 + uVar7 + 1);
              *pbVar12 = *pbVar12 | 4;
            }
            pBVar1 = pBVar8 + 1;
            pBVar8 = pBVar8 + 2;
          } while (*pBVar1 != 0);
        }
        uVar7 = 1;
        do {
          pbVar12 = (byte *)((int)&DAT_006da6c0 + uVar7 + 1);
          *pbVar12 = *pbVar12 | 8;
          uVar7 = uVar7 + 1;
        } while (uVar7 < 0xff);
        DAT_006da7c4 = sub_56BE89(CodePage);
        _DAT_006da5bc = 1;
      }
      DAT_006da5b0 = 0;
      DAT_006da5b4 = 0;
      DAT_006da5b8 = 0;
      goto LAB_0056be2e;
    }
    if (DAT_006da580 == 0) {
      return 0xffffffff;
    }
  }
  sub_56BEBC();
LAB_0056be2e:
  sub_56BEE5();
  return 0;
}

