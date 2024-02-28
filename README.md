# xv6-rpi3b

## Introduction

`xv6-rpi3b` is a project aiming to port `xv6`, a simple Unix-like teaching operating system, to the Raspberry Pi 3B. Additionally, the project can be run on real hardware or in a simulated environment using QEMU, making development and testing more accessible.

## Getting Started

### Prerequisites

Before you begin, ensure you have a Raspberry Pi 3B and an SD card formatted and ready for use, if you plan to run on hardware. For simulation, ensure you have QEMU installed on your development machine. This project requires an AArch64 bare-metal target toolchain for cross-compilation.

### Installation

1. **Download the Toolchain:**

   Start by downloading the AArch64 bare-metal target toolchain. You can obtain the toolchain from [this](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads) link.

2. **Update Your PATH:**

   After downloading and extracting the toolchain, you need to add its `bin` directory to your system's PATH. This enables you to invoke the compiler and other tools from the command line. Replace `<user>` and `<version>` with your actual username and the toolchain version you downloaded, and add this line to your `.bashrc` or `.bash_profile`.

   ```bash
   export PATH=$PATH:/home/<user>/arm-gnu-toolchain-<version>-x86_64-aarch64-none-linux-gnu/bin
   ```

## Usage

### Running on Hardware

To build and run `xv6-rpi3b` on your Raspberry Pi 3B, follow these steps:

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/jakeknow17/xv6-rpi3
   ```

2. **Build the Project:**

   ```bash
   cd xv6-rpi3b
   make all
   ```

3. **Deploy on Raspberry Pi 3B:**

   After a successful build, the `make` command generates a `kernel8.img` file. This file, along with a set of specific files provided by the Raspberry Pi Foundation, needs to be copied to the root of your SD card:

   1. **Copy `kernel8.img`:** Place the `kernel8.img` file at the root of your formatted SD card.

   2. **Add Raspberry Pi Boot Files:** In addition to `kernel8.img`, your SD card must include the following essential files from the Raspberry Pi Foundation to boot:

      - `bootcode.bin`
      - `start.elf`
      - `fixup.dat`
      - `config.txt` (There is a working example in this repository.)

      These files can be obtained [here](https://github.com/raspberrypi/firmware) from the official Raspberry Pi firmware repository or from an existing Raspberry Pi OS image.

   3. **Insert SD Card and Boot:** Once all files are in place, insert the SD card into your Raspberry Pi 3B and power it up. Your Raspberry Pi should boot into the `xv6-rpi3b` operating system.

### Running with QEMU

First, make sure you have QEMU installed on your system. Then follow these steps after building the project:

1. **Create a Disk Image for QEMU:**

   Run `make test.dd` to create a disk image that QEMU will use as a virtual SD card.

2. **Start QEMU:**

   Run the project in QEMU with the following command:

   ```bash
   make qemu
   ```

   To run QEMU and wait for a gdb connection (for debugging), use:

   ```bash
   make qemu-gdb
   ```

## Original xv6 README

xv6 is a re-implementation of Dennis Ritchie's and Ken Thompson's Unix
Version 6 (v6).  xv6 loosely follows the structure and style of v6,
but is implemented for a modern RISC-V multiprocessor using ANSI C.

ACKNOWLEDGMENTS

xv6 is inspired by John Lions's Commentary on UNIX 6th Edition (Peer
to Peer Communications; ISBN: 1-57398-013-7; 1st edition (June 14,
2000)).  See also https://pdos.csail.mit.edu/6.1810/, which provides
pointers to on-line resources for v6.

The following people have made contributions: Russ Cox (context switching,
locking), Cliff Frey (MP), Xiao Yu (MP), Nickolai Zeldovich, and Austin
Clements.

We are also grateful for the bug reports and patches contributed by
Takahiro Aoyagi, Silas Boyd-Wickizer, Anton Burtsev, carlclone, Ian
Chen, Dan Cross, Cody Cutler, Mike CAT, Tej Chajed, Asami Doi,
eyalz800, Nelson Elhage, Saar Ettinger, Alice Ferrazzi, Nathaniel
Filardo, flespark, Peter Froehlich, Yakir Goaron, Shivam Handa, Matt
Harvey, Bryan Henry, jaichenhengjie, Jim Huang, Matúš Jókay, John
Jolly, Alexander Kapshuk, Anders Kaseorg, kehao95, Wolfgang Keller,
Jungwoo Kim, Jonathan Kimmitt, Eddie Kohler, Vadim Kolontsov, Austin
Liew, l0stman, Pavan Maddamsetti, Imbar Marinescu, Yandong Mao, Matan
Shabtay, Hitoshi Mitake, Carmi Merimovich, Mark Morrissey, mtasm, Joel
Nider, Hayato Ohhashi, OptimisticSide, Harry Porter, Greg Price, Jude
Rich, segfault, Ayan Shafqat, Eldar Sehayek, Yongming Shen, Fumiya
Shigemitsu, Cam Tenny, tyfkda, Warren Toomey, Stephen Tu, Rafael Ubal,
Amane Uehara, Pablo Ventura, Xi Wang, WaheedHafez, Keiichi Watanabe,
Nicolas Wolovick, wxdao, Grant Wu, Jindong Zhang, Icenowy Zheng,
ZhUyU1997, and Zou Chang Wei.


The code in the files that constitute xv6 is
Copyright 2006-2022 Frans Kaashoek, Robert Morris, and Russ Cox.

ERROR REPORTS

Please send errors and suggestions to Frans Kaashoek and Robert Morris
(kaashoek,rtm@mit.edu).  The main purpose of xv6 is as a teaching
operating system for MIT's 6.1810, so we are more interested in
simplifications and clarifications than new features.

BUILDING AND RUNNING XV6

You will need a RISC-V "newlib" tool chain from
https://github.com/riscv/riscv-gnu-toolchain, and qemu compiled for
riscv64-softmmu.  Once they are installed, and in your shell
search path, you can run "make qemu".