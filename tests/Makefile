include Makefile.builtem

TARGETS = compile_test compile_test_bundle named_values_test parse_value_test
TARGETS+= threadsafe_resource_loader_burn_test threadsafe_resource_loader_test url_detector_test

C_FLAGS += $(call include_dir,../src)

.PHONY: all compile
all: compile

compile: $(call exe,$(TARGETS))

$(call exe,compile_test): $(call obj,../src/compressor_load ../src/compressor_save ../src/options ../src/url_detector)
$(call exe,threadsafe_resource_loader_burn_test threadsafe_resource_loader_test): LD_FLAGS+=$(call use_threads)
$(call exe,url_detector_test): $(call obj,../src/url_detector)

$(call exe,%): $$(call obj,%)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

.PHONY: clean
clean:
	$(call rm,.build $(call all_exe,$(TARGETS)))
