/* sub_42C180 @ 0042c180   732 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_42C180(float param_1,undefined4 param_2)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 local_30;
  int local_2c;
  uint local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  float local_14;
  uint local_10;
  uint local_c;
  uint local_8;
  uint local_4;
  
  uVar2 = param_2;
  fVar1 = param_1;
  local_2c = 0;
  *(undefined4 *)((int)param_1 + 0x5c) = 0;
  *(undefined4 *)((int)param_1 + 0x60) = 0;
  sub_415AB0(param_2,&local_2c);
  if (local_2c != 0) {
    uVar3 = sub_41EF00(local_2c * 4);
    *(undefined4 *)((int)fVar1 + 0x60) = uVar3;
    iVar5 = 0;
    if (0 < local_2c) {
      do {
        sub_415AD0(uVar2,&local_4);
        sub_415AD0(uVar2,&local_10);
        sub_415AD0(uVar2,&local_c);
        sub_415AD0(uVar2,&local_8);
        local_14 = (float)((local_10 & 0xff) << 1) * _DAT_0056e0c8;
        uVar4 = local_4 & 0xff;
        local_18 = (float)((local_c & 0xff) << 1) * _DAT_0056e0c8;
        local_1c = (float)((local_8 & 0xff) << 1) * _DAT_0056e0c8;
        if (uVar4 == 1) {
          sub_415AB0(uVar2,&local_30);
          sub_415AB0(uVar2,&param_2);
          sub_415AB0(uVar2,&param_1);
          param_1 = -param_1;
          uVar3 = sub_41B8A0(1,local_14,local_18,local_1c,local_30,param_2,param_1,0,0,0);
LAB_0042c427:
          *(undefined4 *)(*(int *)((int)fVar1 + 0x60) + *(int *)((int)fVar1 + 0x5c) * 4) = uVar3;
          sub_41BD70(*(undefined4 *)(*(int *)((int)fVar1 + 0x60) + *(int *)((int)fVar1 + 0x5c) * 4))
          ;
          *(int *)((int)fVar1 + 0x5c) = *(int *)((int)fVar1 + 0x5c) + 1;
        }
        else {
          if (uVar4 == 2) {
            sub_415AB0(uVar2,&local_30);
            sub_415AB0(uVar2,&param_2);
            sub_415AB0(uVar2,&param_1);
            param_1 = -param_1;
            sub_415AB0(uVar2,&local_20);
            sub_415AB0(uVar2,&local_24);
            sub_415AD0(uVar2,&local_28);
            uVar3 = sub_41B8A0(2,local_14,local_18,local_1c,local_30,param_2,param_1,local_20,
                               local_24,local_28 & 0xff);
            goto LAB_0042c427;
          }
          if (uVar4 == 4) {
            sub_415AB0(uVar2,&local_30);
            sub_415AB0(uVar2,&param_2);
            sub_415AB0(uVar2,&param_1);
            param_1 = -param_1;
            sub_415AB0(uVar2,&local_20);
            sub_415AB0(uVar2,&local_24);
            sub_415AD0(uVar2,&local_28);
            uVar3 = sub_41B8A0(2,(local_14 + _DAT_0056e008) * _DAT_0056e1d4,
                               (local_18 + _DAT_0056e008) * _DAT_0056e1d4,
                               (local_1c + _DAT_0056e008) * _DAT_0056e1d4,local_30,param_2,param_1,
                               local_20,local_24,local_28 & 0xff);
            goto LAB_0042c427;
          }
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 < local_2c);
    }
  }
  return;
}

