#!/bin/bash

# Compilers
OS_COMPILER="i686-elf-gcc"
OS_LINKER="i686-elf-ld"
OS_ASSEMBLER="nasm"

# Files with sources
NASMF="./asm/"
CPPF="./src/"
CF="./src/"
# Linker script
LDSCRIPT="link.ld"
LDSRC=""
# Flags for compiling and linking
NASMFLAGS="-felf -o "
CFLAGS="-nostdlib -nostdinc -fno-builtin -fno-stack-protector -c -o "
LDFLAGS=" -T $LDSCRIPT -o "
# Sources for compiling
NASMSRC="boot.s interrupt.s gdt.s"
CPPSRC=""
CSRC="main.c common.c monitor.c string.c descriptor_tables.c isr.c"
# Output folder for object files
OUTPUT="./object/"
# Output file for kernel
OUTKERNEL="./kernel/"
KERNEL="./kernel/kernel.bin"

function CheckPrerequisites(){
	command -v $OS_COMPILER >/dev/null 2>&1 || { echo >&2 "Compiler '$OS_COMPILER' required but it's not installed.  Aborting."; exit 1; }
	command -v $OS_LINKER >/dev/null 2>&1 || { echo >&2 "Linker '$OS_LINKER' required but it's not installed.  Aborting."; exit 1; }
	command -v $OS_ASSEMBLER >/dev/null 2>&1 || { echo >&2 "Assembler '$OS_ASSEMBLER' required but it's not installed.  Aborting."; exit 1; }
}
function Assemble(){
	while((${#1}!=0)); do
		printf "\n"
		input=$1
		output="${1%.asm}.o"
		echo "Assembling file \"$input\"!"
		nasm $NASMFLAGS $OUTPUT$output $NASMF$input || printf "Assembling failed! Check the file for errors!\n\n"
		if [ -a $OUTPUT$output ]; then
			printf "Assembling was a success! Output file = $output!\n\n"
			LDSRC="$LDSRC $OUTPUT$output"
		fi
		shift
	done
}
function CompileC(){
	while((${#1}!=0)); do
		printf "\n"
		input=$1
		output="${1%.c}.o"
		echo "Compiling file \"$input\"!"
		$OS_COMPILER $CFLAGS $OUTPUT$output $CF$input || printf "Compiling failed! Check the file for errors!\n\n"
		if [ -a $OUTPUT$output ]; then
			printf "Compiling was a success! Output file = $output!\n\n"
			LDSRC="$LDSRC $OUTPUT$output"
		fi
		shift
	done
}
function Link(){
	$OS_LINKER $LDFLAGS $KERNEL $LDSRC || printf "Linking failed!\n\n"
	if [ -a $KERNEL ]; then
		printf "Linkig was a success! Kernel file = $KERNEL!\n\n"
	fi
}
function Clean(){
	printf "\nCleaning the object files!\n"
	FLAG="$OUTPUT"*.o
	rm $FLAG || printf "No object files to clean!\n"
	printf "\nCleaning done!\n"
}
function CleanAll(){
	printf "\nCleaning the object files!\n"
	FLAG="$OUTPUT"*.o
	rm $FLAG || printf "No object files to clean!\n"	
	FLAG="$OUTKERNEL"*.bin
	printf "\nCleaning the kernel binaries!\n"
	rm $FLAG || printf "No kernel binaries to clean!\n"
	printf "\nCleaning done!\n"
}
function Run(){
	printf "\nTESTING KERNEL IN QEMU!\n"
	FLAG="-kernel $KERNEL -no-kvm"
	qemu-system-i386 $FLAG || printf "Testing failed! Check the kernel binary! \n"
}
function Help(){
	cat help.txt		
}
function Prepare(){
	if [ -d $OUTPUT ]; then
		CleanAll;	
	else
		mkdir $OUTPUT
	fi
}

CheckPrerequisites

case $1 in
	(help|h)
		Help;;
	(assemble)
		shift
		if ((${#1}!=0)); then
			NASMSRC=""	
		fi
		while((${#1}!=0)); do
			NASMSRC="$NASMSRC $1"
			shift
		done
		Assemble $NASMSRC ;;
	(compile)
		shift
		if ((${#1}!=0)); then
			CPPSRC=""
			CSRC=""
		fi
		while((${#1}!=0)); do
			end=${1:((${#1}-3)):3}
			if [ end == "cpp" ]; then
				CPPSRC="$CPPSRC $1"
			else
				CSRC="$CSRC $1"
			fi
			shift
		done
		CompileC $CSRC ;
		CompileCpp $CPPSRC ;;
	(link)
		shift
		while((${#1}!=0)); do
			LDSRC="$LDSRC $OUTPUT$1"
			shift
		done
		Link;;
	(clean)
		CleanAll;;
	(run)
		Run;;
	(all)
		Prepare;		
		Assemble $NASMSRC;
		CompileC $CSRC;
		Link;
		Clean;;
	(*)
		Help;;
esac
exit 0
