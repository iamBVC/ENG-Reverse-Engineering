/* sub_43C7B0 @ 0043c7b0   394 bytes */

void sub_43C7B0(short param_1,short param_2,int param_3,short param_4,short param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar2 = param_3;
  iVar1 = param_3;
  if (((short)param_3 == param_5) && (param_4 != -1)) {
    iVar1 = (int)param_5;
    iVar2 = (int)*(short *)(&DAT_00584a8c)[iVar1 * 0xb + (int)param_4] *
            *(int *)(&DAT_00572368 + (short)param_3 * 0x18);
    iVar3 = (int)((short *)(&DAT_00584a8c)[iVar1 * 0xb + (int)param_4])[1] *
            *(int *)(&DAT_00572368 + (short)param_3 * 0x18);
    iVar2 = (((int)(iVar2 + (iVar2 >> 0x1f & 0xffU)) >> 8) -
            (int)*(short *)((&DAT_00584a8c)[iVar1 * 0xb] + 0xc) / 2) +
            *(int *)(&DAT_00572360 + iVar1 * 0x18) + (int)param_1;
    iVar1 = (((int)(iVar3 + (iVar3 >> 0x1f & 0xffU)) >> 8) -
            (int)*(short *)((&DAT_00584a8c)[iVar1 * 0xb] + 0xe) / 2) +
            *(int *)(&DAT_00572364 + iVar1 * 0x18) + (int)param_2;
  }
  iVar4 = (short)param_3 * 0x18;
  iVar3 = (&DAT_00584a8c)[(short)param_3 * 0xb];
  sub_43B990(iVar3,(int)(short)((*(short *)(&DAT_00572360 + iVar4) - *(short *)(iVar3 + 0xc) / 2) +
                               param_1),
             (int)(short)((*(short *)(&DAT_00572364 + iVar4) - *(short *)(iVar3 + 0xe) / 2) +
                         param_2),*(undefined4 *)(&DAT_00572368 + iVar4),0,0x80,0x80,0x80);
  if (((short)param_3 == param_5) && (param_4 != -1)) {
    sub_43B990((&DAT_00584a8c)[param_5 * 0xb + (int)param_4],iVar2,iVar1,
               *(undefined4 *)(&DAT_00572368 + iVar4),0,0x80,0x80,0x80);
  }
  return;
}

