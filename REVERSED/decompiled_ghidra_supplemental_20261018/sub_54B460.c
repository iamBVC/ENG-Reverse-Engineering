/* Selected Ghidra export at 0054b460. */

void sub_54B460(void)

{
  if (DAT_005fcf08 != 0) {
    sub_41A160(0);
  }
  if (DAT_006d9c1c == 0) {
    sub_436840((&PTR_s_Inizia_Gioco_0057bbf0)[DAT_00584f04],0xa0,0,DAT_0058463c,0x112);
    sub_436840((&PTR_s_Opzioni_0057bc00)[DAT_00584f04],0xb4,1,DAT_0058463c,0x112);
    sub_436840((&PTR_DAT_0057bba0)[DAT_00584f04],200,2,DAT_0058463c,0x112);
  }
  else {
    sub_436840((&PTR_s_Sei_sicuro_che_vuoi_0057bbc4)[DAT_00584f04],0x96,0,DAT_0058463c,0x112);
    sub_436840((&PTR_s_uscire__0057bbcc)[DAT_00584f04],0xaa,1,DAT_0058463c,0x112);
    sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],200,1,DAT_006d9c20,1,0x15e);
    sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],200,0,DAT_006d9c20,0,0x19a);
  }
  sub_54B590();
  return;
}

