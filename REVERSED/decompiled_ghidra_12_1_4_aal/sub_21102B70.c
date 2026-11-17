/* _AAL_Lock@0 @ 21102b70   8 bytes */

void _AAL_Lock_0(void)

{
                    /* 0x2b70  47  _AAL_Lock@0 */
  LOCK();
  DAT_211155c8 = DAT_211155c8 + 1;
  UNLOCK();
  return;
}

