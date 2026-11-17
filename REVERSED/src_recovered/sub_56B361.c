/* sub_56B361 @ 0056b361, recovered from the original Ghidra instruction listing.
 * Preserve incoming EAX across the x87 argument spill and the call to sub_56AB70. */
undefined4 __declspec(naked) sub_56B361(void)
{
  __asm {
    push eax
    sub esp, 2Ch
    fstp tbyte ptr [esp+0Ch]
    fstp tbyte ptr [esp]
    call sub_56AB70
    add esp, 2Ch
    pop eax
    ret
  }
}
