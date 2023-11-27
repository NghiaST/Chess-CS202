ASSETDIR = asset
BINDIR = bin
DATDIR = dat
LIBDIR = libs
OBJDIR = obj
SRCDIR = src
IMAGEDIR = $(ASSETDIR)/image
SOUNDDIR = $(ASSETDIR)/sound
FONTDIR = $(ASSETDIR)/font
OTHERDIR = $(SRCDIR)/Other
SFMLINCDIR = $(LIBDIR)/SFML-2.5.1/include
SFMLLIBDIR = $(LIBDIR)/SFML-2.5.1/lib
ICON = $(OBJDIR)/Other/resource.res

NAME = Chess
CXX = g++
CXXFLAGS = -Wall -std=c++17 -MMD -MP
# -Wextra -Werror
INCLUDES = -I $(SFMLINCDIR) -I ".\include"
LIBS = -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-network-d
LIBS_RELEASE = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network
LFLAGS = -L $(SFMLLIBDIR) $(LIBS)
LFLAGS_RELEASE = -L $(SFMLLIBDIR) $(LIBS_RELEASE)

SUBFOLDER = ChessBoard IngameScreen DataControl HomeScreen SettingScreen StatisticsScreen OptionScreen Other Helpers

FILE_ORIGIN = main Graphic Chess Screen
FILE_CHESSBOARD = Bitboard BitboardProcess Board Bot GameState Move MoveSearching LogicBoard LogicBoardStandard LogicBoardKingHill LogicBoardAtomic
FILE_HELPERS = BoardHelpers Book Fen MoveUtility
FILE_HOMESCREEN = HomeScreen
FILE_INGAMESCREEN = BoardManager BoardPrint IngameScreen PiecePrint TimeButton PromotionManager NotificationEndGame
FILE_DATACONTROL = Arrow Button ButtonOption Circle Color FileManager GameAttributes GameSettings Image Include Point RenderRect TextBox Theme
FILE_OPTIONSCREEN = OptionScreen
FILE_SETTINGSCREEN = SettingScreen
FILE_STATISTICSSCREEN = StatisticsScreen Table ProcessStatistics

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

build: dir ${NAME}.exe

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
	${CXX} ${CXXFLAGS} ${INCLUDES} -c src/test.cpp -o test.exe -L ${LFLAGS}
	test.exe

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
	${HIDE} ${CXX} ${CXXFLAGS} ${INCLUDES} $^ -o $@ ${LFLAGS}

${OBJDIR}/Other/%.res: ${SRCDIR}/Other/%.rc
	${HIDE} echo compile $*.res
	${HIDE} windres $< -I ${IMAGEDIR} -O coff -o $@

-include $(DEPS)
${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	${HIDE} echo compile $(notdir $*.o)
	${HIDE} ${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@ ${LFLAGS}
-include $(DEPS)