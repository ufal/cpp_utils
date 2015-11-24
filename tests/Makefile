include Makefile.builtem

TARGETS = compile_test

C_FLAGS += $(call include_dir,../src)

.PHONY: all compile
all: compile

compile: $(call exe,$(TARGETS))

$(call exe,compile_test): $(call obj,compile_test ../src/compressor_load ../src/compressor_save ../src/options)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

.PHONY: clean
clean:
	$(call rm,.build $(call all_exe,$(TARGETS)))
