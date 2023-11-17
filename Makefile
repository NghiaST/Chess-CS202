NAME = Chess
CXX = g++
CXXFLAGS = -Wall -std=c++17 -MMD -MP
# -Wextra -Werror
ASSETDIR = asset
BINDIR = bin
DATDIR = dat
OBJDIR = obj
SRCDIR = src
IMAGEDIR = $(ASSETDIR)/image
SOUNDDIR = $(ASSETDIR)/sound
FONTDIR = $(ASSETDIR)/font
OTHERDIR = $(SRCDIR)/Other
SFMLINCDIR = SFML-2.5.1/include
SFMLLIBDIR = SFML-2.5.1/lib
ICON = $(OBJDIR)/Other/resource.res
FLAGS = $(SFMLLIBDIR) -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-network-d

SUBFOLDER = ChessBoard IngameScreen DataControl HomeScreen SettingScreen StatisticsScreen OptionScreen Other Helpers

FILE_ORIGIN = main Graphic Chess Screen
FILE_CHESSBOARD = Bitboard BitboardProcess Board Bot GameState Move MoveSearching
FILE_HELPERS = BoardHelpers Book Fen MoveUtility
FILE_HOMESCREEN = HomeScreen
FILE_INGAMESCREEN = BoardManager BoardPrint IngameScreen PiecePrint TimeButton PromotionManager
FILE_DATACONTROL = Arrow Button ButtonOption Circle Color FileInit GameAttributes GameSettings Image Include Point RenderPS TextBox Theme
FILE_OPTIONSCREEN = OptionScreen
FILE_SETTINGSCREEN = SettingScreen
FILE_STATISTICSSCREEN = StatisticsScreen

ifeq ($(OS),Windows_NT)
	DIRECTORIES = $(OBJDIR) $(SUBFOLDER:%=$(OBJDIR)\\%)
else
	DIRECTORIES = $(OBJDIR) $(SUBFOLDER:%=$(OBJDIR)/%)
endif


FILE = $(FILE_ORIGIN) $(FILE_CHESSBOARD:%=ChessBoard/%)  $(FILE_INGAMESCREEN:%=IngameScreen/%) $(FILE_DATACONTROL:%=DataControl/%) $(FILE_HOMESCREEN:%=HomeScreen/%) $(FILE_SETTINGSCREEN:%=SettingScreen/%) $(FILE_STATISTICSSCREEN:%=StatisticsScreen/%) $(FILE_OPTIONSCREEN:%=OptionScreen/%) $(FILE_HELPERS:%=Helpers/%)

FILE_O = $(FILE:%=%.o)
FILE_CPP = $(FILE:%=%.cpp)

SOURCES = $(FILE_CPP:%=$(SRCDIR)/%)
OBJS = $(FILE_O:%=$(OBJDIR)/%)
OBJDEL = $(wildcard $(OBJDIR)/*)
DEPS = $(OBJS:$(OBJDIR)/%.o=$(OBJDIR)/%.d)
RCICON = $(ICON:$(OBJDIR)/%.res=$(SRCDIR)/%.rc)

FILENAME = $(notdir $(wildcard src/*))

VERBOSE = FALSE
ifeq (${VERBOSE}, TRUE)
	HIDE = 
else
	HIDE = @
endif

all: dir build run

.PHONY: clean all

dir: $(DIRECTORIES)

build: ${NAME}.exe

clean:
ifeq (${OBJDEL},)
	${HIDE} echo delete nothing
else
	${HIDE} echo delete obj folder
	${HIDE} del /Q obj\*
	${HIDE} for /D %%i in (obj\*) do (rmdir /S /Q "%%i")
	${HIDE} rmdir obj
endif

run:
	${HIDE} echo ${NAME}.exe
	${HIDE} echo ------------------
	${HIDE} ${NAME}.exe

rebuild: clean all

test:
	${HIDE} echo test.cpp
	${CXX} ${CXXFLAGS} -I ${SFMLINCDIR} -c src/test.cpp -o test.exe -L ${FLAGS}
	test.exe

neww:
	echo $(RCICON)
	echo $(ICON)

ifeq ($(OS),Windows_NT)
$(DIRECTORIES):
	$(HIDE) echo create folder "$@"
	$(HIDE) mkdir $@
else
$(DIRECTORIES):
	mkdir -p $@
endif

%.exe: ${OBJS} ${ICON}
	${HIDE} echo linking .o file to -*_*- $@
	${HIDE} ${CXX} ${CXXFLAGS} $^ -o $@ -L ${FLAGS}

${OBJDIR}/Other/%.res: ${SRCDIR}/Other/%.rc
	${HIDE} echo compile $*.res
	${HIDE} windres $< -I ${IMAGEDIR} -O coff -o $@

-include $(DEPS)
${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	${HIDE} echo compile $(notdir $*.o)
	${HIDE} ${CXX} ${CXXFLAGS} -I ${SFMLINCDIR} -c $< -o $@
-include $(DEPS)