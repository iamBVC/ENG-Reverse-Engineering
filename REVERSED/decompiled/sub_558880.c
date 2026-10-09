/* sub_558880 @ 00558880   920 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_558880(undefined4 *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  char *pcVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 local_18;
  int local_14;
  undefined1 local_10 [16];
  
  sub_545190(0x36000);
  sub_41EEE0();
  puVar1 = param_1;
  local_14 = 0;
  local_18 = 0;
  switch(param_1[3]) {
  case 0:
    uVar8 = param_1[2];
    uVar7 = param_1[1];
    uVar6 = *param_1;
    pcVar5 = s_T_01dL_01dM_03d_0057c488;
    break;
  case 1:
    uVar8 = param_1[2];
    uVar7 = param_1[1];
    uVar6 = *param_1;
    pcVar5 = s_T_01dB_01dM_03d_0057c468;
    break;
  case 2:
    uVar8 = param_1[2];
    uVar7 = param_1[1];
    uVar6 = *param_1;
    pcVar5 = s_T_01dS_01dM_03d_0057c478;
    break;
  case 3:
    uVar8 = param_1[2];
    uVar7 = param_1[1];
    uVar6 = *param_1;
    pcVar5 = s_T_01dI_01dM_03d_0057c458;
    break;
  default:
    goto switchD_005588af_default;
  }
  sub_562717(&DAT_006da340,pcVar5,uVar6,uVar7,uVar8);
switchD_005588af_default:
  sub_562717(local_10,s__s_wad_0057c450,&DAT_006da340);
  iVar2 = sub_415690(&DAT_00570348,local_10);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = sub_562AEE(iVar2,&DAT_00570350);
  if (iVar2 == 0) {
    return 0;
  }
  sub_415AB0(iVar2,&local_14);
LAB_00558969:
  iVar4 = 0;
  if ((*(byte *)(iVar2 + 0xc) & 0x10) != 0) {
LAB_00558bce:
    sub_5628EB(iVar2);
    sub_4071D0();
    sub_41E1C0(0);
    DAT_00581164 = 0;
    DAT_00584f04 = DAT_005f6ec0;
    sub_426500();
    DAT_005fd08c = 0;
    DAT_005fd090 = 0;
    _DAT_0058113c = 0;
    *(undefined1 *)(puVar1 + 5) = 1;
    return 1;
  }
  sub_415AB0(iVar2,&local_14);
  if ((*(byte *)(iVar2 + 0xc) & 0x10) != 0) {
    sub_5628EB(iVar2);
    return 0;
  }
  sub_415AB0(iVar2,&local_18);
  if (local_14 < 0x52494d48) {
    if (local_14 == 0x52494d47) {
      sub_437B40(iVar2);
      sub_437D00();
      goto LAB_00558969;
    }
    if (local_14 < 0x4c474855) {
      if (local_14 == 0x4c474854) {
        if (DAT_00584648 == 0) {
          DAT_00584648 = sub_42AA60();
        }
        sub_42C180(DAT_00584648,iVar2);
        goto LAB_00558969;
      }
      if (local_14 != 0x414d5043) {
        if (local_14 == 0x454e4420) goto LAB_00558bce;
        if (local_14 != 0x464f4e54) goto LAB_00558b7b;
        sub_558C90(puVar1,iVar2);
        goto LAB_00558969;
      }
      if (DAT_005834dc != 0) {
        sub_558D70(puVar1,iVar2);
        goto LAB_00558969;
      }
    }
    else {
      if (local_14 == 0x4c475043) {
        sub_558DB0(puVar1,iVar2);
        goto LAB_00558969;
      }
      if (local_14 == 0x4c4e464f) {
        sub_42AB10(iVar2);
        goto LAB_00558969;
      }
      if (local_14 == 0x4d415020) {
        if (DAT_00584648 == 0) {
          DAT_00584648 = sub_42AA60();
        }
        sub_42AC50(DAT_00584648,iVar2);
        goto LAB_00558969;
      }
    }
  }
  else if (local_14 < 0x53545044) {
    if (local_14 == 0x53545043) {
      if (DAT_00584648 == 0) {
        DAT_00584648 = sub_42AA60();
      }
      sub_42AB50(DAT_00584648,iVar2,local_18);
      goto LAB_00558969;
    }
    if (local_14 == 0x534d5043) {
      if (DAT_005834dc != 0) {
        sub_558D30(puVar1,iVar2);
        goto LAB_00558969;
      }
    }
    else {
      if (local_14 == 0x53505254) {
        sub_415AB0(iVar2,&DAT_005ff728);
        if (((DAT_006da330 & 0x100000) != 0) && (sub_415AB0(iVar2,&param_1), 0 < (int)param_1)) {
          puVar3 = &DAT_005fcfa0;
          do {
            sub_415AB0(iVar2,puVar3);
            iVar4 = iVar4 + 1;
            puVar3 = puVar3 + 4;
          } while (iVar4 < (int)param_1);
        }
        goto LAB_00558969;
      }
      if (local_14 == 0x53525043) {
        if (DAT_005834dc == 0) {
          sub_415B10(iVar2,local_18);
        }
        else {
          sub_545350(puVar1,iVar2,2);
        }
        goto LAB_00558969;
      }
    }
  }
  else {
    if (local_14 == 0x54455854) {
      sub_4067B0(iVar2,local_18);
      goto LAB_00558969;
    }
    if (local_14 == 0x5452414b) {
      sub_42AAC0(iVar2,local_18);
      goto LAB_00558969;
    }
    if (local_14 == 0x57465043) {
      sub_415AB0(iVar2,&DAT_006da330);
      goto LAB_00558969;
    }
  }
LAB_00558b7b:
  sub_415B10(iVar2,local_18);
  goto LAB_00558969;
}

