/* sub_550E60 @ 00550e60   6118 bytes */

void sub_550E60(int param_1,int param_2,undefined4 param_3)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 local_10 [2];
  undefined4 local_8;
  
  switch(param_3) {
  case 0:
  case 0x13:
  case 0x76:
    goto switchD_00550e72_caseD_0;
  case 1:
    sub_54BBD0(param_1,DAT_006d94d0 << 0xc);
    return;
  default:
    goto switchD_00550e72_caseD_2;
  case 3:
    uVar2 = 0;
    if ((*(int **)(param_2 + 0x120))[1] == 0) {
      uVar2 = 2;
    }
    if (**(int **)(param_2 + 0x120) == 0) {
      uVar2 = uVar2 | 1;
    }
    sub_54BBD0(param_1,uVar2);
    return;
  case 4:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0x120) + 0x28));
    return;
  case 5:
    uVar1 = sub_404BB0(param_2 + 0x30,*(int *)(param_2 + 0x120) + 0x18);
    sub_54BBD0(param_1,uVar1);
    return;
  case 6:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0x120) + 0x18));
    return;
  case 7:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0x120) + 0x1c));
    return;
  case 8:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0x120) + 0x20));
    return;
  case 9:
    sub_54BBD0(param_1,*(int *)(*(int *)(param_2 + 0x120) + 8) << 0xc);
    return;
  case 10:
    sub_54BBD0(param_1,*(int *)(*(int *)(param_2 + 0x120) + 0xc) << 0xc);
    return;
  case 0xb:
    iVar3 = *(int *)(*(int *)(param_2 + 0x120) + 0x10);
    break;
  case 0xc:
    if (DAT_006d9e1c == 0) {
      sub_54BBD0(param_1,0x64000);
      return;
    }
    uVar1 = sub_404BB0(DAT_006d9e1c + 0x30,*(int *)(param_2 + 0x120) + 0x18);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0xd:
    uVar1 = sub_404D60(*(int *)(param_2 + 0x120) + 0x18,param_2 + 0x30);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0xe:
    sub_54BBD0(param_1,*(int *)(param_2 + 0x110) << 0xc);
    return;
  case 0xf:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xe8) >> 3 & 1);
    return;
  case 0x10:
    if (*(undefined4 **)(param_2 + 0xc0) != (undefined4 *)0x0) {
      sub_54BBD0(param_1,**(undefined4 **)(param_2 + 0xc0));
      return;
    }
    sub_54BBD0(param_1,0);
    return;
  case 0x11:
    if (*(int *)(param_2 + 0xc0) != 0) {
      sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 4) << 0xc);
      return;
    }
  case 0x47:
  case 0x77:
  case 0x98:
  case 0xd8:
  case 0xed:
switchD_00550e72_caseD_47:
    sub_54BBD0(param_1,0);
    return;
  case 0x12:
    if (*(int *)(param_2 + 0xc0) == 0) {
      sub_54BBD0(param_1,0);
      return;
    }
    iVar3 = (int)*(short *)(*(int *)(param_2 + 0xc0) + 0x30);
    break;
  case 0x14:
    if (*(int *)(param_2 + 0xc0) != 0) {
      sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 0x2c) << 0xc);
      return;
    }
    sub_54BBD0(param_1,0);
    return;
  case 0x15:
    iVar3 = 0;
    if (*(int *)(param_2 + 0xc0) != 0) {
      sub_54BBD0(param_1,0);
      return;
    }
    goto LAB_00552673;
  case 0x16:
    sub_54BBD0(param_1,(int)*(short *)(param_2 + 0xd2));
    return;
  case 0x1d:
    sub_54BBD0(param_1,*(byte *)(*(int *)(param_2 + 0xf0) + 0x44) & 8);
    return;
  case 0x1e:
    sub_54BBD0(param_1,*(byte *)(*(int *)(param_2 + 0xf0) + 0x44) & 4);
    return;
  case 0x1f:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) & 2);
    return;
  case 0x20:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xe8) >> 0x16 & 1);
    return;
  case 0x21:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xe8) >> 0x17 & 1);
    return;
  case 0x22:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x30));
    return;
  case 0x23:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x34));
    return;
  case 0x24:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x38));
    return;
  case 0x25:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x20) & 0xffffff);
    return;
  case 0x26:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x24) & 0xffffff);
    return;
  case 0x27:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x28) & 0xffffff);
    return;
  case 0x29:
    if (DAT_006d9e1c != 0) {
      uVar1 = sub_404D60(DAT_006d9e1c + 0x30,param_2 + 0x30);
      sub_54BBD0(param_1,uVar1);
      return;
    }
    goto switchD_00550e72_caseD_0;
  case 0x2a:
    sub_54BBD0(param_1,DAT_005fcf20);
    return;
  case 0x2b:
    sub_54BBD0(param_1,DAT_005fcf34);
    return;
  case 0x2c:
    sub_54BBD0(param_1,DAT_005fcf30);
    return;
  case 0x2d:
    if (*(int *)(param_2 + 0x1c) == 0) {
      uVar1 = __ftol();
      *(undefined4 *)(param_2 + 0x1c) = uVar1;
    }
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x1c));
    return;
  case 0x2f:
  case 0x31:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 100));
    return;
  case 0x30:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x60));
    return;
  case 0x32:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x68));
    return;
  case 0x33:
    iVar3 = DAT_006d9dc8;
    break;
  case 0x34:
    iVar3 = *(int *)(DAT_00584648 + 8);
    break;
  case 0x35:
    uVar1 = sub_404C50(param_2 + 0x30,*(int *)(param_2 + 0x120) + 0x18);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x36:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0xd8));
    return;
  case 0x37:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0xdc));
    return;
  case 0x38:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0xe0));
    return;
  case 0x39:
    sub_54BBD0(param_1,DAT_006d9e1c);
    return;
  case 0x3a:
    sub_54BBD0(param_1,DAT_006d9d80);
    return;
  case 0x3b:
    sub_54BBD0(param_1,DAT_006d9d84);
    return;
  case 0x3c:
    sub_54BBD0(param_1,DAT_006d9d88);
    return;
  case 0x3d:
    sub_54BBD0(param_1,DAT_00584eb4 << 0xc);
    return;
  case 0x3e:
    iVar3 = DAT_00584eb8;
    break;
  case 0x3f:
    sub_54BBD0(param_1,DAT_00584ebc << 0xc);
    return;
  case 0x40:
    sub_54BBD0(param_1,DAT_00584ec0 << 0xc);
    return;
  case 0x41:
    if (DAT_006d9e30 != 0) {
      sub_54BBD0(param_1,0xffffffff);
      return;
    }
    goto switchD_00550e72_caseD_75;
  case 0x42:
    if (DAT_006d9e34 != 0) {
      sub_54BBD0(param_1,0xffffffff);
      return;
    }
    goto switchD_00550e72_caseD_47;
  case 0x43:
    sub_54BBD0(param_1,DAT_005fcf18 << 0xc);
    return;
  case 0x44:
    iVar3 = DAT_006d9e30;
    if (DAT_006d9e28 == 0) {
      sub_54BBD0(param_1,0);
      return;
    }
    goto LAB_00551c86;
  case 0x45:
    iVar3 = DAT_006d9e34;
    if (DAT_006d9e28 == 0) {
      sub_54BBD0(param_1,0);
      return;
    }
LAB_00551c86:
    uVar1 = sub_404BB0(DAT_006d9e28 + 0x30,iVar3 + 0x30);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x46:
    uVar1 = sub_54DAE0(*(undefined4 *)(DAT_006d9e30 + 0x24),*(undefined4 *)(DAT_006d9e28 + 0x24));
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x48:
    uVar1 = sub_404CC0(DAT_006d9e28 + 0x30,DAT_006d9e30 + 0x30);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x49:
    uVar1 = sub_404CC0(DAT_006d9e28 + 0x30,DAT_006d9e34 + 0x30);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x4b:
    sub_54BBD0(param_1,DAT_005fcf1c);
    return;
  case 0x4c:
    sub_54BBD0(param_1,DAT_005fcf2c);
    return;
  case 0x4d:
    sub_54BBD0(param_1,DAT_005fcefc);
    return;
  case 0x4e:
    sub_54BBD0(param_1,(int)DAT_005fcf4e << 0xc);
    return;
  case 0x4f:
    sub_54BBD0(param_1,((int)DAT_005fcf00 + (int)DAT_005fcf4e & 0xfffU) << 0xc);
    return;
  case 0x50:
    sub_54BBD0(param_1,DAT_005fcf28);
    return;
  case 0x51:
    sub_54BBD0(param_1,DAT_005fcf24);
    return;
  case 0x52:
    sub_54BBD0(param_1,DAT_005fcef8);
    return;
  case 0x53:
    iVar3 = (int)DAT_005fcf4c;
    break;
  case 0x54:
    sub_54BBD0(param_1,((int)DAT_005fcf00 + (int)DAT_005fcf4c & 0xfffU) << 0xc);
    return;
  case 0x55:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dda8);
    return;
  case 0x56:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dd90);
    return;
  case 0x57:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dd94 << 0xc);
    return;
  case 0x58:
    sub_54BBD0(param_1,DAT_005fcf58);
    return;
  case 0x5a:
    sub_54BBD0(param_1,DAT_005fcf60);
    return;
  case 0x5b:
    sub_54BBD0(param_1,DAT_00584f10 << 0xc);
    return;
  case 0x5c:
    sub_54BBD0(param_1,DAT_00584e70);
    return;
  case 0x5d:
    sub_54BBD0(param_1,DAT_0058464c);
    return;
  case 0x5e:
  case 0x60:
    sub_54BBD0(param_1,0x54);
    return;
  case 0x5f:
  case 0x61:
    sub_54BBD0(param_1,0x7b);
    return;
  case 0x62:
    sub_54BBD0(param_1,-(uint)(*(int *)(param_1 + 0x118) != 0) & 0x1000);
    return;
  case 99:
    if (DAT_006d9e24 != 0) {
      uVar1 = sub_404BB0(DAT_006d9e24 + 0x30,param_2 + 0x30);
      sub_54BBD0(param_1,uVar1);
      return;
    }
    goto LAB_005522c8;
  case 100:
    if (DAT_006d9e24 != 0) {
      uVar1 = sub_404C50(DAT_006d9e24 + 0x30,param_2 + 0x30);
      sub_54BBD0(param_1,uVar1);
      return;
    }
    goto LAB_005522c8;
  case 0x65:
    iVar3 = sub_54D560(param_2);
    if (iVar3 != 0) {
      sub_54BBD0(param_1,*(uint *)(iVar3 + 0xc) & 0xfffff000);
      return;
    }
    goto LAB_0055136c;
  case 0x66:
    iVar3 = sub_54D560(param_2);
    if (iVar3 == 0) {
      sub_54BBD0(param_1,0xfffff000);
      return;
    }
    sub_54BBD0(param_1,*(uint *)(iVar3 + 0x10) & 0xfffff000);
    return;
  case 0x67:
    iVar3 = sub_54D560(param_2);
    if (iVar3 == 0) {
      sub_54BBD0(param_1,0xfffff000);
      return;
    }
    sub_54BBD0(param_1,*(uint *)(iVar3 + 0x14) & 0xfffff000);
    return;
  case 0x68:
  case 0xc2:
    uVar1 = sub_404C10(param_2 + 0x30,*(int *)(param_2 + 0x120) + 0x18);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x69:
    iVar3 = *(int *)(param_2 + 0x120) + 0x18;
LAB_005522ac:
    uVar1 = sub_404C90(param_2 + 0x30,iVar3);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0x6a:
    iVar3 = sub_414FB0();
    sub_54BBD0(param_1,(uint)(iVar3 == 0) * 0x1000);
    return;
  case 0x6b:
    if (DAT_006d9e1c != 0) {
      uVar1 = sub_404C50(DAT_006d9e1c + 0x30,param_2 + 0x30);
      sub_54BBD0(param_1,uVar1);
      return;
    }
    goto LAB_005522c8;
  case 0x6c:
    sub_54BBD0(param_1,(uint)DAT_00585219 << 0xc);
    return;
  case 0x6e:
    sub_54BBD0(param_1,(uint)(DAT_006d9858 < '\x01') << 0xc);
    return;
  case 0x6f:
    sub_54BBD0(param_1,(uint)(DAT_006d94e8 < '\x01') << 0xc);
    return;
  case 0x75:
  case 0x9e:
  case 0xc1:
  case 0xee:
  case 0x102:
    goto switchD_00550e72_caseD_75;
  case 0x78:
    sub_54BBD0(param_1,DAT_00586424);
    return;
  case 0x79:
    sub_54BBD0(param_1,DAT_006d9d20);
    return;
  case 0x7a:
    sub_54BBD0(param_1,DAT_006d9d24);
    return;
  case 0x7b:
    sub_54BBD0(param_1,DAT_006d9d28);
    return;
  case 0x7c:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) >> 0x18 & 1);
    return;
  case 0x7d:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) >> 0x19 & 1);
    return;
  case 0x7e:
    sub_54BBD0(param_1,(int)*(short *)(param_2 + 0xd4));
    return;
  case 0x7f:
    sub_54BBD0(param_1,(int)*(short *)(param_2 + 0xd6) << 0xc);
    return;
  case 0x80:
    sub_54BBD0(param_1,DAT_00585004 << 0xc);
    return;
  case 0x81:
    iVar3 = sub_54D560(param_2);
    if (iVar3 != 0) {
      sub_54BBD0(param_1,(*(uint *)(iVar3 + 0x20) & 0xc00) << 0xc);
      return;
    }
LAB_0055136c:
    sub_54BBD0(param_1,0xfffff000);
    return;
  case 0x82:
  case 0x83:
    sub_54BBD0(param_1,0x2a);
    return;
  case 0x84:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x50));
    return;
  case 0x85:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x54));
    return;
  case 0x86:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x58));
    return;
  case 0x87:
    sub_54BBD0(param_1,DAT_006da2c0);
    return;
  case 0x88:
    sub_54BBD0(param_1,DAT_006da2c4);
    return;
  case 0x89:
    if ((DAT_006d9858 < '\x01') && (DAT_006d94e8 < '\x01')) {
      sub_54BBD0(param_1,0x1000);
      return;
    }
    sub_54BBD0(param_1,0);
    return;
  case 0x8a:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x10c));
    return;
  case 0x8b:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x40) & 0xffffff);
    return;
  case 0x8c:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x44) & 0xffffff);
    return;
  case 0x8d:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0x48) & 0xffffff);
    return;
  case 0x8e:
    sub_54BBD0(param_1,DAT_006da330 & 0x80000);
    return;
  case 0x8f:
    sub_54BBD0(param_1,DAT_006d9d30);
    return;
  case 0x90:
    sub_54BBD0(param_1,(uint)*(ushort *)(DAT_00584648 + 0xc) << 0xc);
    return;
  case 0x91:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dda4 << 0xc);
    return;
  case 0x93:
    iVar3 = sub_41AF40(DAT_00584eb4,DAT_00584eb8,DAT_00584ec0);
    sub_54BBD0(param_1,(uint)(byte)(&DAT_00585024)[iVar3] << 0xc);
    return;
  case 0x94:
    if ((DAT_006d9e28 != 0) && ((*(uint *)(DAT_006d9e28 + 0xec) & 0x800000) != 0)) {
      local_10[0] = DAT_005790b0;
      local_8 = DAT_005790b8;
      uVar1 = sub_404C50(DAT_006d9e1c + 0x30,local_10);
      sub_54BBD0(param_1,uVar1);
      return;
    }
    goto switchD_00550e72_caseD_75;
  case 0x95:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) & 1);
    return;
  case 0x96:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) & 0x8000000);
    return;
  case 0x97:
    sub_54BBD0(param_1,DAT_00584710 & 0x20);
    return;
  case 0x99:
    sub_54BBD0(param_1,DAT_006d9e10);
    return;
  case 0x9a:
    sub_54BBD0(param_1,(uint)*(byte *)(param_2 + 0x130) << 0xc);
    return;
  case 0x9b:
    sub_54BBD0(param_1,DAT_006d9d38);
    return;
  case 0x9c:
    sub_54BBD0(param_1,DAT_006d9cf0);
    return;
  case 0x9d:
    if ((*(uint *)(param_2 + 0xec) & 0x18000) == 0x18000) {
      sub_54BBD0(param_1,1);
      return;
    }
    goto switchD_00550e72_caseD_75;
  case 0x9f:
    sub_54BBD0(param_1,DAT_006d9e68);
    return;
  case 0xa0:
    sub_54BBD0(param_1,DAT_006d9e74);
    return;
  case 0xa1:
    sub_54BBD0(param_1,DAT_006da300);
    return;
  case 0xa2:
    sub_54BBD0(param_1,DAT_006da2f8);
    return;
  case 0xa3:
    sub_54BBD0(param_1,DAT_006da2fc);
    return;
  case 0xa4:
    if (*(int *)(param_2 + 0xf0) == 0) {
      return;
    }
    sub_54BBD0(param_1,**(undefined4 **)(*(int *)(param_2 + 0xf0) + 0x28));
    return;
  case 0xa5:
    if (*(int *)(param_2 + 0xf0) == 0) {
      return;
    }
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(*(int *)(param_2 + 0xf0) + 0x28) + 4));
    return;
  case 0xa6:
    sub_54BBD0(param_1,*(uint *)(param_2 + 0xec) & 0x8000);
    return;
  case 0xa9:
    sub_54BBD0(param_1,DAT_00584e6c);
    return;
  case 0xab:
    iVar3 = DAT_00585008;
    break;
  case 0xac:
    sub_54BBD0(param_1,DAT_0058500c << 0xc);
    return;
  case 0xad:
    sub_54BBD0(param_1,DAT_00585010 << 0xc);
    return;
  case 0xae:
    iVar3 = DAT_00585014;
    break;
  case 0xaf:
    sub_54BBD0(param_1,DAT_006da308);
    return;
  case 0xb2:
    sub_54BBD0(param_1,DAT_00584710 & 0x10);
    return;
  case 0xb3:
    sub_54BBD0(param_1,DAT_006da2e0);
    return;
  case 0xb5:
    sub_54BBD0(param_1,DAT_00581d74);
    return;
  case 0xb6:
    if (DAT_006d9e28 != 0) {
      sub_54BBD0(param_1,*(uint *)(DAT_006d9e28 + 0xec) & 0x800000);
      return;
    }
    sub_54BBD0(param_1,0);
    return;
  case 0xb7:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dd9c);
    return;
  case 0xb8:
    if (DAT_0057ddc0 != param_2) {
      sub_4054C0(param_2);
    }
    sub_54BBD0(param_1,DAT_0057dda0);
    return;
  case 0xb9:
    if (*(int *)(param_2 + 0x120) != 0) {
      sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0x120) + 0x2c));
      return;
    }
switchD_00550e72_caseD_0:
    sub_54BBD0(param_1,0);
    return;
  case 0xba:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x13c));
    return;
  case 0xbb:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x140));
    return;
  case 0xbc:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x144));
    return;
  case 0xbd:
    sub_54BBD0(param_1,DAT_00584e70);
    return;
  case 0xbe:
    sub_54BBD0(param_1,(&DAT_00584f1c)[DAT_00584ebc + DAT_00584eb8 * 6]);
    return;
  case 0xbf:
    sub_54BBD0(param_1,DAT_00584ffc);
    return;
  case 0xc0:
    sub_54BBD0(param_1,DAT_00584ff4);
    return;
  case 0xc9:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x148));
    return;
  case 0xca:
    if (DAT_006d9e1c != 0) {
      iVar3 = param_2 + 0x30;
      param_2 = DAT_006d9e1c;
      goto LAB_005522ac;
    }
LAB_005522c8:
    sub_54BBD0(param_1,0x64000);
    return;
  case 0xcb:
    sub_54BBD0(param_1,DAT_006da2cc);
    return;
  case 0xcc:
    sub_54BBD0(param_1,DAT_006da2d0);
    return;
  case 0xd2:
    if (*(int *)(param_2 + 0xc0) != 0) {
      sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0xc0) + 0x18));
      return;
    }
switchD_00550e72_caseD_75:
    sub_54BBD0(param_1,0);
    return;
  case 0xd3:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0xc0) + 0x1c));
    return;
  case 0xd4:
    sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 0x24) << 0xc);
    return;
  case 0xd5:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0xc0) + 0x20));
    return;
  case 0xd6:
    sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 0x26) << 0xc);
    return;
  case 0xd7:
    sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 0x3a) << 0xc);
    return;
  case 0xd9:
    sub_54BBD0(param_1,(int)*(short *)(*(int *)(param_2 + 0xc0) + 0x38));
    return;
  case 0xda:
    sub_54BBD0(param_1,DAT_006da290);
    return;
  case 0xe2:
    sub_54BBD0(param_1,*(int *)(*(int *)(param_2 + 0x14) + 8) << 0xc);
    return;
  case 0xe3:
    uVar1 = sub_404D60(&DAT_006d9d80,param_2 + 0x30);
    sub_54BBD0(param_1,uVar1);
    return;
  case 0xe4:
    sub_54BBD0(param_1,DAT_0057d830);
    return;
  case 0xe5:
    sub_54BBD0(param_1,DAT_0057d83c);
    return;
  case 0xe6:
    sub_54BBD0(param_1,DAT_0057d840);
    return;
  case 0xe7:
    sub_54BBD0(param_1,DAT_0057d834);
    return;
  case 0xe8:
    sub_54BBD0(param_1,DAT_006da304);
    return;
  case 0xe9:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x14));
    return;
  case 0xea:
    sub_54BBD0(param_1,DAT_00584710 & 2);
    return;
  case 0xec:
    sub_54BBD0(param_1,DAT_006da2dc);
    return;
  case 0xef:
    sub_54BBD0(param_1,DAT_0057ddb0);
    return;
  case 0xf0:
    sub_54BBD0(param_1,DAT_0057ddb4);
    return;
  case 0xf1:
    sub_54BBD0(param_1,DAT_0057ddb8);
    return;
  case 0xf2:
    if ((*(uint *)(param_2 + 0xec) & 0x10000) == 0) {
      sub_54BBD0(param_1,0x3e8000);
      return;
    }
    if ((*(uint *)(param_2 + 0xec) & 0x400000) == 0) {
      sub_54BBD0(param_1,DAT_00586590 + 0x800);
      return;
    }
    sub_54BBD0(param_1,DAT_0058658c + 0x800);
    return;
  case 0xf3:
    sub_54BBD0(param_1,*(undefined4 *)(*(int *)(param_2 + 0xc0) + 0x28));
    return;
  case 0xf4:
    sub_54BBD0(param_1,DAT_006da298);
    return;
  case 0xf9:
    sub_54BBD0(param_1,*(undefined4 *)(param_2 + 0x120));
    return;
  case 0xfa:
    sub_54BBD0(param_1,DAT_00584e60);
    return;
  case 0xfd:
    iVar3 = sub_546600(DAT_006d94b4,0);
    sub_54BBD0(param_1,iVar3 == 2);
    return;
  case 0x109:
    iVar3 = DAT_00586430;
  }
  iVar3 = iVar3 << 0xc;
LAB_00552673:
  sub_54BBD0(param_1,iVar3);
switchD_00550e72_caseD_2:
  return;
}

