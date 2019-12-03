# Rapid ROM tester

Rapid ROM tester is a project made for use in the Game History Teaching Collection at Champlain College. To sort through our large collection efficiently, and upload formatted data to the GHTC Pineapple Wiki documentation, this project was concieved.

This project is OPEN SOURCE under GPL v3. However, neither I nor my employers nor associates are responsible for damage this program may cause.

(for the purposes of clarity, all commands will be prefixed by "> " and arguments will be in {curly brackets})

## Requisites

Must have RetroArch installed, as well as any ROMs and cores
Must point Rapid ROM tester to the RetroArch installation directory (const.h : RETROARCH_BASE_DIR)

## How to use

Load a ROM using > rom {filepath}. Works with raw game dumps or ZIPs.
Load a core (DLL) using > core {filepath}. Alternatively a folder may be used to iterate through each usable core--see > batch for details.
To launch a single test environment, simply type > go. To launch multiple, use > batch. Be aware that > batch will, for each: > go then > wiki add
To input a test-result entry, use > wiki add
To save all test-result entries, use > wiki out {outfile}