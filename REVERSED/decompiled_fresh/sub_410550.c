/* sub_410550 @ 00410550   234 bytes */

undefined4 sub_410550(int param_1)

{
  undefined *local_40;
  char *local_3c;
  int local_38;
  undefined *local_34;
  char *local_30;
  int local_2c;
  undefined *local_28;
  char *local_24;
  int local_20;
  int *local_18;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0056d6e8;
  local_10 = ExceptionList;
  local_14 = &stack0xffffffa4;
  local_18 = (int *)0x0;
  local_8 = 0;
  ExceptionList = &local_10;
  local_20 = DirectDrawCreate(*(undefined4 *)(param_1 + 0xc),&local_18,0);
  if (local_20 != 0) {
    local_24 = s_Couldn_t_create_DirectDraw_devic_005717dc;
    local_28 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_28,&DAT_0056eff0);
  }
  local_2c = (**(code **)*local_18)(local_18,&DAT_0056e71c,&DAT_00582ccc);
  if (local_2c != 0) {
    local_30 = s_Couldn_t_get_DirectDraw4_interfa_005717b8;
    local_34 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_34,&DAT_0056eff0);
  }
  local_38 = (**(code **)*local_18)(local_18,&DAT_0056e6ec,&DAT_00582cd0);
  if (local_38 != 0) {
    local_3c = s_Couldn_t_get_Direct3D3_interface_00571794;
    local_40 = &DAT_0056e1c0;
                    /* WARNING: Subroutine does not return */
    __CxxThrowException_8(&local_40,&DAT_0056eff0);
  }
  (**(code **)(*local_18 + 8))(local_18);
  ExceptionList = local_10;
  return 1;
}

