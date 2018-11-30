# Attempt to load a config.make file.
# If none is found, project defaults in config.project.make will be used.
ifneq ($(wildcard config.make),)
	include config.make
endif

# make sure the the OF_ROOT location is defined
ifndef OF_ROOT
	OF_ROOT=$(realpath ../../of_v0.10.0_linux64gcc6_release)
endif

# call the project makefile!
include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

CC = g++
CFLAGS = -g -std=c++17 -DU_TEST
TEST = unittest

run_test: $(TEST)
	./$(TEST)

$(TEST): src/seam_carver.cpp test/test.cpp
	$(CC) $(CFLAGS) -o $(TEST) src/seam_carver.cpp test/test.cpp

clean_test:
	rm -f $(TEST)
