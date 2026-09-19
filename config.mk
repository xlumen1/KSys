# Global Project Info

TARGET := x86_64-unknown-none-elf

BUILD_TYPE ?= debug

# Directories

SRC := src
INCLUDE := include
BUILD := build
DIST := dist
TEST := test
RESOURCES := resources

# Important Files

NAME := KERNEL.BIN
BINARY := $(DIST)/$(NAME)
INTERMEDIATE := $(BUILD)/krnl.elf

LOADER := BOOTX64.EFI
LOADER_PATH := vendor/kboot/build/out/EFI/BOOT/$(LOADER)

OVMF_VARS := OVMF_VARS.4m.fd
OVMF_CODE := OVMF_CODE.4m.fd
OVMF_PATH := /usr/share/ovmf/x64

# Command Aliases

CC := clang
AS := clang
LD := ld.lld
CPY := llvm-objcopy

CCFLAGS := -target $(TARGET) -ffreestanding -fno-stack-protector \
		   -fno-pic -fno-pie -mno-red-zone -mcmodel=kernel -Wall -Wextra -Wpedantic \
		   -std=gnu23 -c -I$(INCLUDE) -g
LDFLAGS := -T $(RESOURCES)/linker.ld -nostdlib --no-dynamic-linker -g
ASFLAGS := -target $(TARGET) -c

