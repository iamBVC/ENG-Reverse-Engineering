# Cyan-screen investigation

The reconstructed executable is not yet visually functional: the user reports
only cyan after the logo. Successful draw return codes are not visual proof.

## REA evidence

Original input: `Game/groove.exe`, SHA-256
`151102050d79c0cc703d121e7755f7bb75f436d5822d31e72a43c31cc1adb9bc`.
Analysis used REA 6.4.0 with Ghidra 12.1.4 through the installed public launcher.
The owned analysis session was closed. Complete output is retained in
`build/rea_cyan_evidence.json`.

- `0x439490`: Evidence
  `ev_cdd570f69547ca80a9241668d79c4fc1b58da031298dcdca2fca66c2a5cd58e4`.
  Static pseudocode confirms the front/back-surface flip and optional intermediate
  blit paths. The reconstruction uses the same calls with restored COM signatures.
  This does not prove which pixels reach the screen at runtime.
- `0x438CD0`: Evidence
  `ev_017e3376d9b8a152d951cdeebe66872221a01075c1682ab5bfa9942b9b3117b9`.
  Static analysis identifies the 32-byte conversion callback records and the
  original `0x409640` upload callback. The recovered callback has a focused
  conversion test. Actual texture contents remain a runtime question.

## Other observations

The prior user-visible bounded run logged accepted Direct3D calls with distinct
UI rectangle positions and packed colors. The captured render surface was uniformly
cyan, and all 15 texture surfaces read back as zero despite nonzero source hashes
for several textures. These are harness runtime observations, not REA runtime
evidence.

The native-boundary viewport and indexed texture-upload tests pass with the
current build. They verify descriptor contents, callback arguments, pitch and
stack balance using mocks; they do not test the physical DirectDraw device.

## Prepared next probe

The subsequent trace localized the texture-side defect to `sub_436CC0`: its
decompiled pointer-versus-original-address loop never initialized the RGB square
table after relocation. That function now uses a bounded 256-entry loop, and a
focused test confirms histogram accumulation, palette construction, and texel
remapping for representative RGB555 samples. The full executable was rebuilt.

A bounded launch from the isolated Codex account reached adapter enumeration but
did not enter the hardware-rendered frame path, so it supplied no visual validation
of the repaired build. The user still needs to run `run_rebuild_visible_8s.cmd` on
the desktop. Main-menu visibility, intro playback, input and gameplay remain
unverified.
