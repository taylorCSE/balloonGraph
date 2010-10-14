# Directories
BUILD     = build
DIST      = dist
SRC	      = src

# Tools
WXLIBNAME = wxmsw28
CPP	      = g++.exe
LINK      = g++.exe
WINDRES   = windres.exe
RM        = rm -f
ZIP       = zip

# Output filenames
BIN       = App.exe

# Source files and objects
SRCS = $(wildcard $(SRC)/*.cpp)
OBJ = $(subst $(SRC),$(BUILD),$(patsubst %.cpp,%.o,$(SRCS)))

# Libraries to include
LIBS	  = -mwindows \
			-l$(WXLIBNAME) \
			-lwxpng \
			-lwxtiff \
			-lwxjpeg \
			-lwxzlib \
			-lkernel32 \
			-luser32 \
			-lgdi32 \
			-lcomdlg32 \
			-lwinmm \
			-lshell32 \
			-lcomctl32 \
			-lole32 \
			-loleaut32 \
			-luuid \
			-lrpcrt4 \
			-ladvapi32 \
			-lodbc32 \
			-llibmysql

# Compile Flags			
CXXFLAGS  = -fno-exceptions \
			-fno-pcc-struct-return \
			-fstrict-aliasing \
			-Wall \
			-D__WXMSW__ \
			-D__GNUWIN32__ \
			-D__WIN95__ \
			-Wno-deprecated \
			-ggdb \
			-O0

LDFLAGS   = -Wl

# Color codes

W=\x1b[0m
G=\x1b[32;01m
R=\x1b[31;01m
Y=\x1b[33;01m

.PHONY: all all-before all-after clean clean-custom dist dist-custom todo todo-custom
all: all-before src/version.h $(BIN) all-after

clean: clean-custom
	@echo -e "$(G)Removing temporary files$(W)..."
	-@$(RM) $(OBJ) "$(BIN)"
	@echo -e "$(G)Done$(W)."

# Update version file
	
all-before:
	@echo $$((`cat build_num.txt`+1)) > build_num.txt
	@echo "/* Automatically generated based on head commit */" > $(SRC)/version.h
	@echo "#define VERSION_COMMIT \"`git rev-parse HEAD`\"" >> $(SRC)/version.h
	@echo "#define VERSION_BUILD \"`cat build_num.txt`\"" >> $(SRC)/version.h
	@echo -e "$(G)Starting build `cat build_num.txt`$(W)"
	@echo -e "$(G)===================$(W)"
	@echo -e "Current commit is `git rev-parse HEAD`."

dist: dist-custom
	@echo -e "$(G)Building distribution $(DIST)/hawkgraph-`cat build_num.txt`.zip$(W)..."
	@$(RM) $(DIST)/hawkgraph.zip
	@$(ZIP) $(DIST)/hawkgraph-`cat build_num.txt`.zip $(BIN) libmysql.dll

todo: todo-custom
	-@for file in $(SRCS); do grep -H -e TODO -e FIXME $$file; done; true
	
# Build exes
	
$(BIN): $(OBJ)
	@echo -e "Linking $(G)$<...$(W)"
	@$(RM) temp.log temp2.log
	-@$(LINK) $(OBJ) -o "$(BIN)" $(LIBS) $(LDFLAGS) 2> temp.log
	@if test -s temp.log; then echo -e "$(R)`cat temp.log`$(W)"; fi;
	@$(RM) temp.log temp2.log

# Build Objects
	
$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	@echo -e "Compiling $(G)$<$(W) to $(Y)$@$(W)..."
	@$(RM) temp.log temp2.log
	-@$(CPP) -c $< -o $@ $(CXXFLAGS) 2> temp.log
	@if test -s temp.log; then echo -e "$(R)`cat temp.log`$(W)"; fi;
	@$(RM) temp.log temp2.log
	