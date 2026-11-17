/* _AAL_Unlock@0 @ 21102b80   8 bytes */

void _AAL_Unlock_0(void)

{
                    /* 0x2b80  74  _AAL_Unlock@0 */
  LOCK();
  DAT_211155c8 = DAT_211155c8 + -1;
  UNLOCK();
  return;
}

