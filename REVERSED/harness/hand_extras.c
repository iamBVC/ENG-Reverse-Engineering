/* hand_extras.c - globals the harness needs on the hand-ported side.
 *
 * These are NOT ports: they exist so that both DLLs expose the same set of
 * globals to tools/verify.py.  `dword_5846EC` is the TRAK header-array base
 * (written by sub_5563F0 / read by sub_42AC50), which belongs to the loader
 * work rather than to the small batch ported by hand so far.
 */
unsigned int *dword_5846EC = 0;
