BUILD_DIR := build
MOD_TOML ?= ./mod.toml
LIB_NAME ?= lua_host
# Allow the user to specify the compiler and linker on macOS
# as Apple Clang does not support MIPS architecture
ifeq ($(OS),Windows_NT)
    CC      := clang
    LD      := ld.lld
else ifneq ($(shell uname),Darwin)
    CC      := clang
    LD      := ld.lld
else
    CC      ?= clang
    LD      ?= ld.lld
endif

# Python Info:
ifeq ($(OS),Windows_NT)
PYTHON_EXEC ?= python
else
PYTHON_EXEC ?= python3
endif

PYTHON_FUNC_MODULE := make_python_functions
define call_python_func
	$(PYTHON_EXEC) -c "import $(PYTHON_FUNC_MODULE); $(PYTHON_FUNC_MODULE).ModInfo(\"$(MOD_TOML)\", \"$(BUILD_DIR)\", \"$(LIB_NAME)\").$(1)($(2))"
endef
define get_python_func
$(shell $(PYTHON_EXEC) -c "import $(PYTHON_FUNC_MODULE); $(PYTHON_FUNC_MODULE).ModInfo(\"$(MOD_TOML)\", \"$(BUILD_DIR)\", \"$(LIB_NAME)\").$(1)($(2))")
endef

define get_python_val
$(shell $(PYTHON_EXEC) -c "import $(PYTHON_FUNC_MODULE); print($(PYTHON_FUNC_MODULE).ModInfo(\"$(MOD_TOML)\", \"$(BUILD_DIR)\", \"$(LIB_NAME)\").$(1))")
endef

# Mod building info:
MOD_ELF := $(BUILD_DIR)/mod.elf
MOD_SYMS := $(BUILD_DIR)/mod_syms.bin
MOD_BINARY := $(BUILD_DIR)/mod_binary.bin
ZELDA_SYMS := Zelda64RecompSyms/mm.us.rev1.syms.toml
OFFLINE_C_OUTPUT := $(BUILD_DIR)/mod_offline.c
LDSCRIPT := mod.ld
CFLAGS   := -target mips -mips2 -mabi=32 -O2 -G0 -mno-abicalls -mno-odd-spreg -mno-check-zero-division \
			-fomit-frame-pointer -ffast-math -fno-unsafe-math-optimizations -fno-builtin-memset \
			-Wall -Wextra -Wno-incompatible-library-redeclaration -Wno-unused-parameter -Wno-unknown-pragmas -Wno-unused-variable \
			-Wno-missing-braces -Wno-unsupported-floating-point-opt -Werror=section
CPPFLAGS := -nostdinc -D_LANGUAGE_C -DMIPS -DF3DEX_GBI_2 -DF3DEX_GBI_PL -DGBI_DOWHILE -I include -I include/mod -I include/dummy_headers \
			-I mm-decomp/include -I mm-decomp/src -I mm-decomp/extracted/n64-us -I mm-decomp/include/libc \
			-I assets_extracted -I assets_extracted/assets -I assets_extracted/assets/assets
LDFLAGS  := -nostdlib -T $(LDSCRIPT) -Map $(BUILD_DIR)/mod.map --unresolved-symbols=ignore-all --emit-relocs -e 0 --no-nmagic

C_SRCS := $(wildcard src/mod/*.c)
C_OBJS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.o))
C_DEPS := $(addprefix $(BUILD_DIR)/, $(C_SRCS:.c=.d))

# Recomp tools building info:
N64RECOMP_DIR := N64Recomp
N64RECOMP_BUILD_DIR := $(N64RECOMP_DIR)/build
RECOMP_MOD_TOOL := $(N64RECOMP_BUILD_DIR)/RecompModTool
OFFLINE_MOD_TOOL := $(N64RECOMP_BUILD_DIR)/OfflineModRecomp

# Extlib building info:
nrm_runtime: nrm
	$(call call_python_func,copy_to_runtime_dir,)

# Recipes:
nrm: $(MOD_ELF) $(RECOMP_MOD_TOOL)
	$(RECOMP_MOD_TOOL) mod.toml $(BUILD_DIR)

offline: nrm
	$(OFFLINE_MOD_TOOL) $(MOD_SYMS) $(MOD_BINARY) $(ZELDA_SYMS) $(OFFLINE_C_OUTPUT)

elf: $(MOD_ELF)

$(MOD_ELF): $(C_OBJS) $(LDSCRIPT) | $(BUILD_DIR)
	$(LD) $(C_OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR) $(BUILD_DIR)/src $(BUILD_DIR)/src/mod $(N64RECOMP_BUILD_DIR):
ifeq ($(OS),Windows_NT)
	mkdir $(subst /,\,$@)
else
	mkdir -p $@
endif

$(RECOMP_MOD_TOOL): $(N64RECOMP_BUILD_DIR) 
	cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S $(N64RECOMP_DIR) -B $(N64RECOMP_BUILD_DIR)
	cmake --build $(N64RECOMP_BUILD_DIR)

$(C_OBJS): $(BUILD_DIR)/%.o : %.c | $(BUILD_DIR) $(BUILD_DIR)/src/mod
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -MMD -MF $(@:.o=.d) -c -o $@

clean:
ifeq ($(OS),Windows_NT)
	rmdir "$(BUILD_DIR)" /s /q
	rmdir "$(N64RECOMP_BUILD_DIR)" /s /q
else
	rm -rf $(BUILD_DIR)
	rm -rf $(N64RECOMP_BUILD_DIR)
endif

-include $(C_DEPS)

.PHONY: clean nrm offline
