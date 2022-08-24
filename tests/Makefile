include Makefile.builtem

TESTS = $(call exe,compile_test compile_test_bundle named_values_test)
TESTS+= $(call exe,parse_value_test run_process_test)
TESTS+= $(call exe,threadsafe_resource_loader_burn_test)
TESTS+= $(call exe,threadsafe_resource_loader_test url_detector_test)

C_FLAGS += $(call include_dir,../src)
C_FLAGS += $(treat_warnings_as_errors)

.PHONY: all compile
all: compile

compile: $(TESTS)

$(call exe,compile_test): $(call obj,../src/compressor_load ../src/compressor_save ../src/options ../src/url_detector)
$(call exe,threadsafe_resource_loader_burn_test threadsafe_resource_loader_test): LD_FLAGS+=$(call use_threads)
$(call exe,url_detector_test): $(call obj,../src/url_detector)

$(TESTS): $(call exe,%): $$(call obj,%)
	$(call link_exe,$@,$^,$(call win_subsystem,console))

.PHONY: clean
clean:
	$(call rm,.build $(call all_exe,$(TESTS)))
