/* sub_21105D10 @ 21105d10   949 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall sub_21105D10(void *this,void *param_1)

{
  undefined4 *puVar1;
  uint uVar2;
  uint uVar3;
  void *this_00;
  uint uVar4;
  int iVar5;
  int iVar6;
  int local_34;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  int local_20;
  undefined4 local_1c;
  int local_18;
  uint local_14;
  int local_10;
  int local_c;
  int local_8;
  
  this_00 = param_1;
  if ((*(byte *)((int)param_1 + 0xc) & 2) != 0) {
    *(undefined4 *)((int)param_1 + 0x114) = 0;
    *(undefined4 *)((int)param_1 + 0x110) = 0;
    *(undefined4 *)((int)param_1 + 0x10c) = 0;
    local_2c = 0;
    if (0 < *(int *)((int)this + 0x5c)) {
      do {
        uVar4 = *(uint *)((int)this_00 + 0x58);
        uVar2 = *(uint *)((int)this_00 + uVar4 * 4 + 0x48);
        iVar5 = *(int *)((int)this_00 + uVar4 * 4 + 0x40);
        local_34 = uVar2 - iVar5;
        if (((*(int *)((int)this_00 + 0x70) != 1) &&
            (uVar3 = *(uint *)((int)this_00 + 0x6c), uVar3 != 0)) && (uVar3 < uVar2)) {
          local_34 = uVar3 - iVar5;
        }
        if (local_34 < 1) {
          if (*(int *)((int)this_00 + 0x104) != 0) {
            *(int *)((int)this_00 + 0x110) = *(int *)((int)this_00 + 0x110) + 1;
          }
          if (*(int *)((int)this_00 + 0x70) == 1) {
            if (((*(byte *)((int)this_00 + 0xc) & 8) == 0) ||
               (uVar4 = uVar4 ^ 1, *(int *)((int)this_00 + uVar4 * 4 + 0x50) != 0)) {
              *(undefined4 *)((int)this_00 + 0xc) = 5;
              if (*(int *)((int)this_00 + 0x108) != 0) {
                *(int *)((int)this_00 + 0x114) = *(int *)((int)this_00 + 0x114) + 1;
              }
              break;
            }
            if ((*(int *)((int)this_00 + uVar4 * 4 + 0x48) == 0) ||
               (*(int *)((int)this_00 + uVar4 * 4 + 0x40) != 0)) {
              *(uint *)((int)this_00 + 0xc) = *(uint *)((int)this_00 + 0xc) | 4;
              break;
            }
            *(uint *)((int)this_00 + 0x58) = uVar4;
          }
          else {
            *(undefined4 *)((int)this_00 + uVar4 * 4 + 0x40) = *(undefined4 *)((int)this_00 + 0x68);
            if (*(int *)((int)this_00 + 0x70) != 0) {
              *(int *)((int)this_00 + 0x70) = *(int *)((int)this_00 + 0x70) + -1;
            }
          }
        }
        else {
          if (*(int *)((int)this_00 + 0x100) != 0) {
            *(int *)((int)this_00 + 0x10c) = *(int *)((int)this_00 + 0x10c) + 1;
          }
          param_1 = (void *)0x10;
          if (*(short *)((int)this + 0x22) == 2) {
            param_1 = (void *)0x11;
          }
          if (*(short *)(*(int *)((int)this_00 + 0x18) + 2) == 2) {
            param_1 = (void *)((uint)param_1 | 8);
          }
          if (*(short *)(*(int *)((int)this_00 + 0x18) + 0xe) == 0x10) {
            param_1 = (void *)((uint)param_1 | 2);
          }
          local_10 = (int)ROUND(ROUND(((float)*(uint *)((int)this_00 + 100) * _DAT_2111233c) /
                                      (float)*(int *)((int)this + 0x24)));
          if ((0x1028f < local_10) || (local_10 < 0xfd71)) {
            param_1 = (void *)((uint)param_1 | 0x20);
          }
          if (*(int *)((int)this_00 + 0x90) == 0) {
            local_8 = *(int *)((int)this_00 + *(int *)((int)this_00 + 0x58) * 4 + 0x40) +
                      *(int *)((int)this_00 + *(int *)((int)this_00 + 0x58) * 4 + 0x38);
            local_34 = local_8 + local_34;
          }
          else {
            if (((uint)param_1 & 8) == 0) {
              local_34 = *(int *)((int)this_00 + 100) << 1;
            }
            else {
              local_34 = *(int *)((int)this_00 + 100) << 2;
            }
            local_14 = (int)ROUND(ROUND(((float)(*(uint *)((int)this + 0x4c) -
                                                local_2c /
                                                (int)(*(uint *)((int)this + 0x5c) /
                                                     *(uint *)((int)this + 0x4c))) * (float)local_34
                                        ) / (float)(int)((uint)*(ushort *)((int)this + 0x2c) *
                                                        *(int *)((int)this + 0x24)))) + 3U &
                       0xfffffffc;
            if (local_14 == 0) {
              local_14 = 4;
            }
            if ((int)*(uint *)((int)this + 100) < (int)local_14) {
              local_14 = *(uint *)((int)this + 100);
            }
            local_8 = *(int *)((int)this + 0x68) + 0x10;
            local_34 = (**(code **)((int)this_00 + 0xa0))
                                 (*(undefined4 *)((int)this_00 + 0xac),local_8,local_14);
            local_34 = local_34 + local_8;
          }
          local_c = local_2c + *(int *)((int)this + 0x60);
          iVar5 = *(int *)((int)this + 0x60) + *(int *)((int)this + 0x5c);
          if ((iVar5 == local_c || iVar5 - local_c < 0) ||
             (local_34 == local_8 || local_34 - local_8 < 0)) {
            local_2c = *(int *)((int)this + 0x5c);
          }
          else {
            if (*(uint *)((int)this_00 + 100) < *(uint *)((int)this + 0x24)) {
              param_1 = (void *)((uint)param_1 | 4);
            }
            local_24 = *(undefined4 *)((int)this_00 + 0x80);
            local_28 = *(undefined4 *)((int)this_00 + 0x84);
            puVar1 = (undefined4 *)((int)this_00 + 0x74);
            local_1c = *puVar1;
            local_20 = local_c;
            local_18 = local_8;
            if ((*(int *)((int)this_00 + 0xb4) == 0) ||
               (iVar6 = (**(code **)(*(int *)((int)this_00 + 0xbc) + 0x24))
                                  (*(undefined4 *)((int)this_00 + 0xc0),&local_18,&local_1c,local_34
                                   ,&local_20,iVar5,&local_24,&local_28,local_10,
                                   *(undefined4 *)((int)this_00 + 0x88),
                                   *(undefined4 *)((int)this_00 + 0x8c),(int)this_00 + 0xe0,param_1)
               , iVar6 != 0)) {
              (**(code **)((int)this_00 + 0xe4))
                        (&local_8,puVar1,local_34,&local_c,iVar5,(int)this_00 + 0x80,
                         (int)this_00 + 0x84,local_10,*(undefined4 *)((int)this_00 + 0x88),
                         *(undefined4 *)((int)this_00 + 0x8c),param_1);
            }
            else {
              local_8 = local_18;
              *puVar1 = local_1c;
              local_c = local_20;
              *(undefined4 *)((int)this_00 + 0x80) = local_24;
              *(undefined4 *)((int)this_00 + 0x84) = local_28;
            }
            sub_211060D0(this_00,local_8,local_34);
            local_2c = local_c - *(int *)((int)this + 0x60);
          }
          if (local_2c == 0) break;
        }
      } while (local_2c < *(int *)((int)this + 0x5c));
    }
    if (*(int *)((int)this_00 + 0x114) != 0) {
      *(int *)((int)this_00 + 0x114) = *(int *)((int)this_00 + 0x114) + -1;
      do {
        (**(code **)((int)this_00 + 0x108))(*(undefined4 *)((int)this_00 + 0xfc));
        iVar5 = *(int *)((int)this_00 + 0x114);
        *(int *)((int)this_00 + 0x114) = iVar5 + -1;
      } while (iVar5 != 0);
    }
  }
  return;
}

