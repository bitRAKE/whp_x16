# WHP16 User Guide (Beginner Friendly)

This guide is for 16-bit assembly programmers who want to use `whp16.exe` as a small lab.

## What WHP16 Is

`whp16.exe` is a Windows GUI app where you can:

- Edit 16-bit assembly (`.asm`)
- Build a module (`.bin`) through `fasm2.cmd`
- Run that module inside WHP (Windows Hypervisor Platform)
- See output in:
  - Console MMIO text output
  - LFB video output (320x200 BGRA by default)
  - App log/runtime log panes

## Quick Start (First Run)

1. Launch `whp16.exe` from the repo root.
2. In the app, use `File -> New Module` (loads `x16\template.asm`).
3. Use `File -> Save Assembly As...` and save to `x16\my_first.asm`.
4. Use `Session -> Build`.
5. Use `Session -> Run`.
6. Check:
   - Log window (build/runtime status)
   - Console window (MMIO text output)
7. If your guest loops forever, use `Session -> Stop`.

## The Core Workflow

For normal daily use:

1. Edit source in the left code pane.
2. Save (`File -> Save Assembly`).
3. Build (`Session -> Build`).
4. Run (`Session -> Run`).
5. Stop when needed (`Session -> Stop`).

Notes:

- If the `.bin` is missing and source is known, `Run` tries to build first.
- The current source/module paths are shown in startup log messages.

## Your First Module Structure

Most examples include:

- `include 'module_impl.inc'`
- `use16`
- `org 0x7C00`

Start from `x16\template.asm` and modify it.

## Important MMIO Basics

WHP16 currently exposes a simple MMIO contract (see `x16\mmio.inc`).

Common registers:

- TX output: write bytes to `REG_TX_FIFO`
- Framebuffer present: write any byte to `REG_FB_PRESENT`
- Geometry read/write: `REG_FB_GEOM`
- Ticks: `REG_TICKS_LO` / `REG_TICKS_HI`

## Working with LFB (Video)

Current default mode is flat LFB at `0xA0000`, 320x200, 32-bit BGRA.

UI controls:

- `View -> Video Window Open`
- `View -> Video Window Docked`
- `View -> Clear LFB`

New convenience features:

- Right-click the LFB area (docked panel or undocked video window) for video options:
  - Open/close video window
  - Dock/undock video window
  - Clear LFB
  - Open Settings
- LFB clear color is configurable in `Settings` (`LFB clear` field, `#RRGGBB`).
- Clear color is persisted in `whp16.ini` (`[Video] ClearColor`).

## Settings You Should Know

Open `View -> Settings...`

Useful fields:

- `fasm2 command line template`:
  - Default: `%SCRIPT% -e 5 %SOURCE% %OUTPUT%`
  - Keep tokens unless you know your toolchain changes.
- Log colors and code highlight colors.
- `LFB clear` color.
- `Present min ms`:
  - Minimum interval between guest-triggered presents.
  - `0` disables throttle.
  - `16` is a good default for smooth viewing (~60 Hz).

Persisted automatically:

- Main window position
- Video window open/docked/state
- Console window position
- Color settings and fasm2 template
- Present throttle (`[Video] PresentIntervalMs`)

## Minimum Deployment for 16-bit Developers

If you want a small, practical package for module authors, deploy this:

1. `whp16.exe`
2. `whp16.ini`
3. `fasm2.cmd`
4. `x16\` includes used by modules:
   - `template.asm`
   - `module_impl.inc`
   - `module_unreal_impl.inc`
   - `module_flags.inc`
   - `module.inc`
   - `mmio.inc`
   - `whp.inc`
5. Example guests/tests in `x16\` (recommended for onboarding)

And keep the assembler bridge target available:

- Default `fasm2.cmd` expects `fasm2\fasmg` and `fasm2\include`.

If you cannot deploy that sibling folder, update `Fasm2CommandTemplate` in `whp16.ini` to point to your local assembler command.

## Capabilities and Why a Guest May Refuse to Run

Open `View -> Capabilities...` to see host and runtime capability info.

Some modules declare required capability flags. If missing, load/run can fail with clear diagnostics.

Examples:

- `x16\test_ioport_probe.asm` requests preferred I/O port support and exercises the `IN 60h` exit path.
- `x16\test_caps_exact_profile.asm` uses exact-profile policy negotiation for capability-failure testing.

## Recommended Learning Modules

Start with:

- `x16\guest_console.asm` - text MMIO
- `x16\guest_ticks.asm` - time/ticks
- `x16\test_fb_gradient.asm` - framebuffer basics
- `x16\guest_unreal.asm` - unreal-mode experiment
- `x16\guest_donut_unreal.asm` - animated unreal-mode framebuffer sample

Focused tests:

- `x16\test_console_tx.asm`
- `x16\test_ticks_64.asm`
- `x16\test_fb_gradient.asm`
- `x16\test_speed_alu.asm` (rough speed benchmark)

## Troubleshooting

### Build fails: `fasm2.cmd` not found

- Check `View -> Settings...` command template.
- Default should be `%SCRIPT% -e 5 %SOURCE% %OUTPUT%`.
- Ensure `fasm2.cmd` exists in repo root.

### Build succeeds but run fails early

- Read runtime log lines carefully; WHP exits are reported with detail.
- Open `Capabilities...` and compare with module requirements.

### Runtime looks stuck

- Guest may be in an intentional loop waiting for events.
- Use `Session -> Stop`.
- `HLT` may return as `X64Halt` in runtime logs, which is expected.

### No video update

- Make sure guest writes LFB and triggers present (`REG_FB_PRESENT`).
- Verify video window is open (`View -> Video Window Open`).
- Use `View -> Clear LFB` to confirm the display path is active.

## External Build from Terminal (Optional)

From `x16\`:

```powershell
..\fasm2.cmd YourFile.asm YourFile.bin
```

Then run:

```powershell
..\whp16.exe YourFile.bin
```

## Current Limits (Expected)

- This is an evolving lab, not a full DOS emulator yet.
- `INT` and broader `IN`/`OUT` ecosystem are still expanding.
- COM import/execute flow is planned, not fully complete.
