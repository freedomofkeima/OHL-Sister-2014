# the module names, without .cpp extension
MODULES = main frame midiplayer

LIB = -lwinmm
INCLUDE = 
FLAGS =

MODE = release
# release or debug

ifeq ($(MODE), release)
FLAGS += -O2
else
FLAGS += -O0 -g
endif

# Everything after this is generic

.PHONY: all run compile install clean
   
define module_template =
bin/$(1).o : src/$(1).cpp 
	g++ -c src/$(1).cpp -o bin/$(1).o $(INCLUDE) $(FLAGS)
endef

OBJFILE = $(foreach file,$(MODULES),bin/$(file).o)

all: $(OBJFILE)
	g++ -o bin/main $(OBJFILE) $(LIB)

run:
	./bin/main scene1.txt twist1.txt twist2.txt scene2.txt

compile:
	python dummy/dummy_compile.py
	
install:
	python dummy/dummy_installer.py

clean:
	rm -f bin/main bin/*.o

$(foreach file,$(MODULES),$(eval $(call module_template,$(file))))