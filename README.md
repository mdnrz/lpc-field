## Template for programming LPC1768 MCU
If you don't like Keil (obviously) and also want to go deeper than mbed's abstraction layers, try this to build your LPC1768 project.
- Sources used:
    - [libopencm3](https://github.com/libopencm3/libopencm3)
    - [CMSIS drivers for LPC1768](https://drive.google.com/open?id=1qdtXqvLqQoIKSMrtabgRIH5fCs94qsPv)

### Structure

```
src
├── app
├── globals
└── shared
```

The shared directory contains library and driver sources which can be shared between applications.
The app directory contains code for the main application.
The global directory can be used for soem definitions that are accessible for all parts of the project (e.g. `version.h`)
Each subdirectory has a make module that sets up srouces and include paths for that specific part of the project.
The main Makefile at the root brings in all definitions of the make modules and builds the application to the `build`
directory.

User can create additional subdirectories for different applications like bootloader and etc. The linker script,
Makefile should be modified to create the binaries and executable based on the project needs.

### Building
- Dependencies: 
    - `arm-none-eabi-gcc` compiler
    - make

```
git clone https://github.com/mdnrz/lpc-field.git
cd lpc-field
make
```
The object files and the final `.elf`, `.bin`, `.hex`, and `.map` files will be on the `build` directory. The name
of the final output files will be based on the latest tag and commit hash and updates automatically with new
commits.

Also a copy of the latest firmware will be created as `fw.elf` which will be used in `fw-debug` target.

### Flashing
- Dependencies:
    - openocd
    - jlink or ft232h debugger

By default the ft232h board is used as debug interface
(look
[here](https://github.com/m3y54m/cjmcu-ft232hq-programmer?utm_source=pocket_shared)
for more information)
User can change the debugger on the root Makefile by changing the `OPENOCD_INTERFACE` variable.

```
make flash-app
```

### Debugging
- Dependencies:
    - arm-none-eabi-gdb (Can be changed by `DB` variable in Makefile)
    - openocd
    - [cmsis-svd](https://github.com/cmsis-svd/cmsis-svd) python package (optional)
     
```
make fw-debug
```
This command flashes the latest firmware on the board, starts an openocd process in the background, runs
gdb and connects to the remote target and brings up gdb tui interface halted at the `main()`.

The `.gdbinit` file contains configs and commands executed at gdb startup. If you don't want to use svd 
when debugging, comment out these two lines:
```
source /home/mehdi/extra/gits/svd-tools/gdb-svd.py
svd LPC176x5x.svd
```
Quiting gdb will also automatically kill the openocd process.
