OutDir = Build/
Libraries =\
Encrypt\
Graph\
Math\
Misc\
Template

all: $(Libraries)

$(Libraries):
	@mkdir -p $(OutDir)
	@echo Building $@Lib...
	@make -C Library/$@ --no-print-directory
