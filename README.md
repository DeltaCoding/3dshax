Codebase for 3ds arm9 stuff + arm11 kernel/userland patches etc. This also includes ctrserver, which is a network server which runs on the 3ds.

# Building
To build just the non-ctrserver codebase: make -f Makefile.arm9 OUTPATH={path to sdcard root} {other optional makefile parameters}  
To build just ctrserver: make -f Makefile_ctrserver.arm11 OUTPATH={path to sdcard root} {other optional makefile parameters}  
To build arm9code+ctrserver:make -f Makefile_ctrserver OUTPATH={path to sdcard root} {other optional makefile parameters}  

Building ctrserver requires "3dshaxarm11_ctrserver_data/auth.bin", this is the "auth.txt" which would be used on the client-side.

The end result of building both of these is "3dshax_arm9.bin" and "3dshax_arm11_ctrserver.bin". After building, each .bin is copied to OUTPATH, for the latter .bin it's copied to OUTPATH/3dshax_arm11.bin.

The arm9 codebase will handle launching the sdcard "/3dshax_arm11.bin", when enabled(which is the default). By default this arm11code is loaded into the "dlp" process, this can be overridden with "spider" by holding down the "Up" D-Pad button when main() is executed.

Running the arm9 binary requires 3ds arm9haxx which can handle loading it. The first u32 is the load-address for the following data, for offset+4 see 3dshax9_start.s for the rest of the structure. With the default PRAM settings near the start of the .bin, the arm9code uses FW1F(system-version v4.1-v4.5) settings. The arm9 code loader must setup the PRAM parameter fields to the correct values, when not running on FW1F. The code-loader can ignore the PRAM structure when running on FW1F.

By default NAND-redir is enabled, see below for disabling it. When NAND-redir is enabled, the base sector-num must be specified via Makefile parameter NANDREDIR_SECTORNUM.

The FIRM-launch code loads the plaintext FIRM from SD "/firm.bin". The FWVER values used by the arm9code is automatically determined by checking the first u32 in the FIRM RSA signature.

# Makefile parameters  
"DISABLEAES=1" Disables all arm9 AES code.  
"DISABLENANDREDIR=1" Disables NAND->SD redirection.  
"NANDREDIR_SECTORNUM={sectornum}" Sector-num base for the SD nandimage, for NAND-redir when enabled.  
"DISABLE_ARM11KERNEL_DEBUG=1" Disables ARM11-kernel patches.  
"DISABLE_ARM11KERNEL_PROCSTARTHOOK=1" Disables the ARM11-kernel process-start hook, used for loading arm11code(ctrserver) etc. This isn't needed when "DISABLE_ARM11KERNEL_DEBUG=1" is used.  
"DISABLE_GETEXHDRHOOK=1" Disables the arm9 get-exheader hook. This option must be used when DISABLE_ARM11KERNEL_DEBUG/DISABLE_ARM11KERNEL_PROCSTARTHOOK is set, otherwise when doing a firm-launch the system will eventually trigger a fatal-error when dlp-module fails to get service-handles.  
"ENABLE_LOADA9_x01FFB800=1" This enables arm9 code which loads the SD file @ "/x01ffb800.bin" to arm9-mem 0x01ffb800. This should only be used when NAND-redir is enabled, and when the SD nandimage is originally from another 3ds, converted for usage on another 3ds.  
"ENABLE_GAMECARD=1" Enables 3ds gamecard reading code.  
"ENABLE_CMDLOGGING=1" Enables ARM11-kernel patches+code for logging commands. Which process-names to log for the commands is currently determined via hard-coded process-names.  
"ENABLE_DUMP_NANDIMAGE=1" Enables nandimage dumping to SD "/3dshax_dump.bin", when button Y is pressed once from the arm9 thread. To dump the physical NAND, "DISABLENANDREDIR=1" should be used.  

# FIRM Compatibility
Supported NATIVE_FIRM system-versions(versions where NATIVE_FIRM wasn't updated don't apply here):
* v4.1
* v6.x (mostly)
* v7.x
* v8.0

Some of the codebase automatically determines what addresses to patch on-the-fly(NAND-redir, etc). However some of the codebase still uses hard-coded addresses for each FIRM version(which includes the FS code).
