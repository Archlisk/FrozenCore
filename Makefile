PROJECTS = \
	  Engine \
	  TestModule

PROJECTS_CLEAN = $(addsuffix .clean,$(PROJECTS))

all: $(PROJECTS)

run: all
	Bin/Engine

clean: $(PROJECTS_CLEAN)

$(PROJECTS):
	@make -C $@

$(PROJECTS_CLEAN): %.clean:
	@make -C $* clean

.PHONY: $(PROJECTS) $(PROJECTS_CLEAN) all clean
