/* sub_5509F0 @ 005509f0   647 bytes */

undefined4 * sub_5509F0(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  switch(param_3) {
  case 4:
    return (undefined4 *)(*(int *)(param_2 + 0x120) + 0x28);
  case 6:
    return (undefined4 *)(*(int *)(param_2 + 0x120) + 0x18);
  case 7:
    return (undefined4 *)(*(int *)(param_2 + 0x120) + 0x1c);
  case 8:
    return (undefined4 *)(*(int *)(param_2 + 0x120) + 0x20);
  case 0x10:
    return *(undefined4 **)(param_2 + 0xc0);
  case 0x16:
    return (undefined4 *)(param_2 + 0xd2);
  case 0x22:
    return (undefined4 *)(param_2 + 0x30);
  case 0x23:
    return (undefined4 *)(param_2 + 0x34);
  case 0x24:
    return (undefined4 *)(param_2 + 0x38);
  case 0x25:
    return (undefined4 *)(param_2 + 0x20);
  case 0x26:
    return (undefined4 *)(param_2 + 0x24);
  case 0x27:
    return (undefined4 *)(param_2 + 0x28);
  case 0x3a:
    return &DAT_006d9d80;
  case 0x3b:
    return &DAT_006d9d84;
  case 0x3c:
    return &DAT_006d9d88;
  case 0x78:
    return &DAT_0058641c;
  case 0x79:
    return &DAT_006d9d20;
  case 0x7a:
    return &DAT_006d9d24;
  case 0x7b:
    return &DAT_006d9d28;
  case 0x84:
    return (undefined4 *)(param_2 + 0x50);
  case 0x85:
    return (undefined4 *)(param_2 + 0x54);
  case 0x86:
    return (undefined4 *)(param_2 + 0x58);
  case 0x8a:
    return (undefined4 *)(param_2 + 0x10c);
  case 0x8b:
    return (undefined4 *)(param_2 + 0x40);
  case 0x8c:
    return (undefined4 *)(param_2 + 0x44);
  case 0x8d:
    return (undefined4 *)(param_2 + 0x48);
  case 0x8f:
    return &DAT_006d9d30;
  case 0x9f:
    return &DAT_006d9e68;
  case 0xa0:
    return &DAT_006d9e74;
  case 0xa1:
    return &DAT_006da300;
  case 0xa2:
    return &DAT_006da2f8;
  case 0xa3:
    return &DAT_006da2fc;
  case 0xa4:
    iVar1 = *(int *)(param_2 + 0xf0);
    if (iVar1 == 0) {
      sub_414600(&DAT_00579a38,*(undefined4 *)(param_2 + 0x18));
    }
    else if (*(int *)(iVar1 + 0x24) != 0) {
      return *(undefined4 **)(iVar1 + 0x28);
    }
    break;
  case 0xa5:
    iVar1 = *(int *)(param_2 + 0xf0);
    if (iVar1 == 0) {
      sub_414600(&DAT_00579a08,*(undefined4 *)(param_2 + 0x18));
      return (undefined4 *)0x0;
    }
    if (*(int *)(iVar1 + 0x24) != 0) {
      return (undefined4 *)(*(int *)(iVar1 + 0x28) + 4);
    }
    break;
  case 0xa9:
    return &DAT_00584e6c;
  case 0xb3:
    return &DAT_006da2e0;
  case 0xb5:
    return &DAT_00581d74;
  case 0xb9:
    if (*(int *)(param_2 + 0x120) != 0) {
      return (undefined4 *)(*(int *)(param_2 + 0x120) + 0x2c);
    }
    break;
  case 0xba:
    return (undefined4 *)(param_2 + 0x13c);
  case 0xbb:
    return (undefined4 *)(param_2 + 0x140);
  case 0xbd:
    return &DAT_00584e70;
  case 0xbe:
    return &DAT_00584f1c + DAT_00584ebc + DAT_00584eb8 * 6;
  case 0xbf:
    return &DAT_00584ffc;
  case 0xc0:
    return &DAT_00584ff4;
  case 0xcb:
    if (DAT_006da29c != DAT_006da2cc) {
      sub_5509A0();
      DAT_006da29c = DAT_006da2cc;
    }
    return &DAT_006da2cc;
  case 0xcc:
    if (DAT_006d9e70 != DAT_006da2d0) {
      sub_5509A0();
      DAT_006d9e70 = DAT_006da2d0;
    }
    return &DAT_006da2d0;
  case 0xd2:
    return (undefined4 *)(*(int *)(param_2 + 0xc0) + 0x18);
  case 0xd9:
    return (undefined4 *)(*(int *)(param_2 + 0xc0) + 0x38);
  case 0xda:
    return &DAT_006da290;
  case 0xe4:
    return &DAT_0057d830;
  case 0xe5:
    return &DAT_0057d83c;
  case 0xe6:
    return &DAT_0057d840;
  case 0xe7:
    return &DAT_0057d834;
  case 0xe8:
    return &DAT_006da304;
  case 0xec:
    return &DAT_006da2dc;
  case 0xf9:
    return (undefined4 *)(param_2 + 0x120);
  case 0xfa:
    return &DAT_00584e60;
  }
  return (undefined4 *)0x0;
}

