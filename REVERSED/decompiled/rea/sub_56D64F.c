/* SUB_56D64F @ 0056D64F
   produced by REA 6.4.0 (Ghidra 12.1.4 provider, read-only) on 2026-10-12 -
   tools/ghidra_decompile.bat produced no file for this function. */

/* Library Function - Single Match
    public: virtual __thiscall exception::~exception(void)
   
   Libraries: Visual Studio 2003 Release, Visual Studio 2005 Release */

void __thiscall exception::~exception(exception *this)

{
  *(undefined ***)this = &PTR_FUN_0056eda0;
  if (*(int *)(this + 8) != 0) {
    FUN_00562941(*(undefined4 *)(this + 4));
  }
  return;
}

