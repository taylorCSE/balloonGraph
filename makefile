# Directories
BUILD     = build
SRC	      = src

# Tools
WXLIBNAME = wxmsw28
CPP	      = g++.exe
LINK      = g++.exe
WINDRES   = windres.exe
RM        = rm -f

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
			-O2 

LDFLAGS   = -Wl

.PHONY: all all-before all-after clean clean-custom
all: all-before src/version.h $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) "$(BIN)"

# Update version file
	
all-before:
	@echo $$((`cat build_num.txt`+1)) > build_num.txt
	@echo "/* Automatically generated based on head commit */" > $(SRC)/version.h
	@echo "#define VERSION_COMMIT \"`git rev-parse HEAD`\"" >> $(SRC)/version.h
	@echo "#define VERSION_BUILD \"`cat build_num.txt`\"" >> $(SRC)/version.h
	@echo "Current commit is `git rev-parse HEAD`"
	@echo "Current build is `cat build_num.txt`"
	
# Build exes
	
$(BIN): $(OBJ)
	$(LINK) $(OBJ) -o "$(BIN)" $(LIBS) $(LDFLAGS)

# Build Objects
	
$(BUILD)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CPP) -c $< -o $@ $(CXXFLAGS)
	
$(BUILD)/Resource.o: $(SRC)/Resource.rc icons/main.ico
	$(WINDRES) $(SRC)/Resource.rc $(BUILD)/Resource.o
	
	