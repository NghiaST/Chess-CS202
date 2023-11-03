NAME = Chess
CXX = g++
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

FILE_ORIGIN = main Graphic Chess
FILE_INGAMESCREEN = Board BoardPrint ChessHistory Piece IngameScreen
FILE_DATACONTROL = Button Color GameSettings Include Settings StaticButton Theme
FILE = $(FILE_ORIGIN) $(FILE_INGAMESCREEN:%=IngameScreen/%) $(FILE_DATACONTROL:%=DataControl/%)
FILE_O = $(FILE_ORIGIN:%=%.o) $(FILE_INGAMESCREEN:%=IngameScreen/%.o) $(FILE_DATACONTROL:%=DataControl/%.o)
FILE_CPP = $(FILE_ORIGIN:%=/%.cpp) $(FILE_INGAMESCREEN:%=IngameScreen/%.cpp) $(FILE_DATACONTROL:%=DataControl/%.cpp)

SOURCES = $(FILE_CPP:%=$(SRCDIR)/%)
OBJS = $(FILE_O:%=$(OBJDIR)/%)
OBJDEL = $(wildcard $(OBJDIR)/*)
DEPS = $(OBJS:$(OBJDIR)/%.o=$(OBJDIR)/%.d)
FFF = $(ICON:$(OBJDIR)/%.res=$(SRCDIR)/%.rc)

FILENAME = $(notdir $(wildcard src/*))

VERBOSE = FALSE
ifeq (${VERBOSE}, TRUE)
	HIDE = 
else
	HIDE = @
endif

all: dir build run

dir:
ifeq ($(wildcard $(OBJDIR)),)
	${HIDE} echo create folder "${OBJDIR}"
	${HIDE} mkdir ${OBJDIR}
endif

ifeq ($(wildcard $(OBJDIR)\IngameScreen),)
	${HIDE} echo create folder "${OBJDIR}\IngameScreen"
	${HIDE} mkdir $(OBJDIR)\IngameScreen
endif

ifeq ($(wildcard $(OBJDIR)\DataControl),)
	${HIDE} echo create folder "${OBJDIR}\DataControl"
	${HIDE} mkdir $(OBJDIR)\DataControl
endif

ifeq ($(wildcard $(OBJDIR)\Other),)
	${HIDE} echo create folder "${OBJDIR}\Other"
	${HIDE} mkdir $(OBJDIR)\Other
endif

build: ${OBJS} ${ICON}
	${HIDE} echo linking .o file to -*_*- ${NAME}.exe
	${HIDE} ${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

${OBJDIR}/Other/%.res: ${SRCDIR}/Other/%.rc
	${HIDE} echo compile $*.res
	${HIDE} windres $< -I ${IMAGEDIR} -O coff -o $@

# *.o: *.cpp
# 	echo asdsfgh
# 	${HIDE} echo compile $*.o
# 	${HIDE} ${CXX} -I ${SFMLINCDIR} -c $< -o $@

${OBJDIR}/%.o: ${SRCDIR}/%.cpp
	${HIDE} echo compile $(notdir $*.o)
	${HIDE} ${CXX} -I ${SFMLINCDIR} -c $< -o $@

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
	${HIDE} ${NAME}.exe

rebuild: clean all

test: $(OBJDIR)/Board.o

neww:
	echo $(FFF)
	echo $(ICON)