include config.mk

ALL_SRC := $(shell find $(SRC) -type f -name "*.c") \
		   $(shell find $(SRC) -type f -name "*.s")

ALL_OBJ := $(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(filter %.c,$(ALL_SRC))) \
		   $(patsubst $(SRC)/%.s,$(BUILD)/%.o,$(filter %.s,$(ALL_SRC)))

.PHONY: build clean test

build: $(BINARY)

clean:
	rm -rf $(BUILD) $(DIST) $(TEST)
	make -C vendor/kboot clean

test: $(BINARY) $(OVMF_VARS) $(LOADER)
	@mkdir -p $(TEST)/img/{KBOOT,EFI/BOOT}
	@cp $(BINARY) $(TEST)/img/KBOOT/$(NAME)
	@printf "CP        $(NAME) -> EFI:\\KBOOT\\$(NAME)\n"
	@cp $(LOADER_PATH) $(TEST)/img/EFI/BOOT/$(LOADER)
	@printf "CP        $(LOADER) -> EFI:\\EFI\\BOOT\\$(LOADER)\n"
	qemu-system-x86_64 \
		-enable-kvm \
		-cpu host \
		-m 4G \
		-drive if=pflash,format=raw,readonly=on,file=$(OVMF_PATH)/$(OVMF_CODE) \
		-drive if=pflash,format=raw,file=$(TEST)/$(OVMF_VARS) \
		-drive file=fat:rw:$(TEST)/img,format=raw,id=bootdrive,if=none \
		-device virtio-blk-pci,drive=bootdrive,bootindex=1

debug: $(BINARY) $(OVMF_VARS) $(LOADER)
	@mkdir -p $(TEST)/img/{KBOOT,EFI/BOOT}
	@cp $(BINARY) $(TEST)/img/KBOOT/$(NAME)
	@printf "CP        $(NAME) -> EFI:\\KBOOT\\$(NAME)\n"
	@cp $(LOADER_PATH) $(TEST)/img/EFI/BOOT/$(LOADER)
	@printf "CP        $(LOADER) -> EFI:\\EFI\\BOOT\\$(LOADER)\n"
	qemu-system-x86_64 \
		-enable-kvm \
		-cpu host \
		-m 4G \
		-s -S \
		-drive if=pflash,format=raw,readonly=on,file=$(OVMF_PATH)/$(OVMF_CODE) \
		-drive if=pflash,format=raw,file=$(TEST)/$(OVMF_VARS) \
		-drive file=fat:rw:$(TEST)/img,format=raw,id=bootdrive,if=none \
		-device virtio-blk-pci,drive=bootdrive,bootindex=1 &
	gdb $(INTERMEDIATE) --silent -ex "target remote localhost:1234"
# -----

$(BINARY): $(INTERMEDIATE)
	@mkdir -p $(dir $@)
	@$(CPY) -O binary $< $@
	@printf "OBJCOPY   $(notdir $<) -> $(notdir $@)\n"

$(INTERMEDIATE): $(ALL_OBJ) 
	@mkdir -p $(dir $@)
	@$(LD) $(LDFLAGS) -o $@ $(ALL_OBJ)
	@printf "LD        $(notdir $@)\n"

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CCFLAGS) $< -o $@
	@printf "CC        $(notdir $<)\n"

$(BUILD)/%.o: $(SRC)/%.s
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) $< -o $@
	@printf "AS        $(notdir $<)\n"

# -----

$(OVMF_VARS):
	@mkdir -p $(TEST)
	@cp $(OVMF_PATH)/$(OVMF_VARS) $(TEST)/$(OVMF_VARS)

$(LOADER):
	@make -C vendor/kboot all
	@mkdir -p $(TEST)/img/{KBOOT,EFI/BOOT}
	@cp $(LOADER_PATH) $(TEST)/img/EFI/BOOT/$(LOADER)
