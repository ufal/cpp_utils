include Makefile.builtem

TARGETS = compile_test compile_test_bundle url_detector_test

C_FLAGS += $(call include_dir,../src)

.PHONY: all compile
all: compile

compile: $(call exe,$(TARGETS))

$(call exe,compile_test): $(call obj,compile_test ../src/compressor_load ../src/compressor_save ../src/options ../src/url_detector)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

$(call exe,compile_test_bundle): $(call obj,compile_test_bundle)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

$(call exe,url_detector_test): $(call obj,url_detector_test ../src/url_detector)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

.PHONY: clean
clean:
	$(call rm,.build $(call all_exe,$(TARGETS)))
