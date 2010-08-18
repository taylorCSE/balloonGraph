BUILD	 = build
SRC	   = src

WXLIBNAME = wxmsw28
CPP	   = g++.exe
LINK	  = g++.exe
WINDRES   = windres.exe
BIN	   = App.exe

OBJ	   = $(BUILD)/App.o \
			$(BUILD)/MainFrame.o \
			$(BUILD)/MathPlot.o \
			$(BUILD)/database.o \
			
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
			
CXXFLAGS  = -ffunction-sections \
			-fdata-sections \
			-fno-exceptions \
			-fno-pcc-struct-return \
			-fstrict-aliasing \
			-Wall \
			-D__WXMSW__ \
			-D__GNUWIN32__ \
			-D__WIN95__ \
			-s

LDFLAGS   = -s -Wl,--gc-sections
RM		= rm -f

.PHONY: all all-before all-after clean clean-custom
all: all-before $(BIN) all-after

clean: clean-custom
	$(RM) $(OBJ) "$(BIN)"

all-before:

$(BIN): $(OBJ)
	$(LINK) $(OBJ) -o "$(BIN)" $(LIBS) $(LDFLAGS)

$(BUILD)/App.o: $(SRC)/App.cpp $(SRC)/App.h $(SRC)/MainFrame.h  
	$(CPP) -c $(SRC)/App.cpp -o $(BUILD)/App.o $(CXXFLAGS)

$(BUILD)/Resource.o: $(SRC)/Resource.rc icons/main.ico
	$(WINDRES) $(SRC)/Resource.rc $(BUILD)/Resource.o

$(BUILD)/MainFrame.o: $(SRC)/MainFrame.cpp $(SRC)/MainFrame.h  
	$(CPP) -c $(SRC)/MainFrame.cpp -o $(BUILD)/MainFrame.o $(CXXFLAGS)
	
$(BUILD)/MathPlot.o: $(SRC)/MathPlot.cpp $(SRC)/MathPlot.h  
	$(CPP) -c $(SRC)/MathPlot.cpp -o $(BUILD)/MathPlot.o $(CXXFLAGS)

$(BUILD)/database.o: $(SRC)/database.cpp
	$(CPP) -c $(SRC)/database.cpp -o $(BUILD)/database.o $(CXXFLAGS)