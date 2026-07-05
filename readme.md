> [!WARNING]
> This software is work in progress. Alpha level expectations.

![WHP16 Screenshot](Screenshot.png)

# WHP_x16

Windows GUI lab for editing, building, and executing 16-bit x86 modules on WHP (Windows Hypervisor Platform).

## What It Does

- Edit `.asm` source in-app
- Build via external `fasm2.cmd`
- Run module binaries in WHP
- Show MMIO console output and LFB video output
- Capture runtime exits/capabilities for debugging and discovery

## Quick Start

1. See [Alex Ionescu](https://www.alex-ionescu.com)'s How to [install WHP](https://github.com/ionescu007/Simpleator#testing).
2. `git clone --recursive https://github.com/bitRAKE/whp_x16.git`
3. Launch `whp16.exe`.
4. Use `File -> New Module`.
5. Save with `File -> Save Assembly As...`.
6. Build with `Session -> Build`.
7. Run with `Session -> Run`.
8. Stop long-running guests with `Session -> Stop`.

## Useful Settings

- `View -> Settings...`
  - `fasm2 command line template` (default: `%SCRIPT% -e 5 %SOURCE% %OUTPUT%`)
  - log/highlight colors
  - LFB clear color
  - `Present min ms` throttle (`0` = off, `16` = ~60 Hz pacing)
