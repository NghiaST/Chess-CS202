NAME = Chess
CXX = g++
BINDIR = bin
DATDIR = dat
OBJDIR = obj
SRCDIR = src
SOURCEDIR = $(SRCDIR)/source
HEADERDIR = $(SRCDIR)/header
OTHERDIR = $(SRCDIR)/other
SFMLINCDIR = SFML-2.5.1/include
SFMLLIBDIR = SFML-2.5.1/lib
IMAGEDIR = ${DATDIR}/img
ICON = $(OBJDIR)/resource.res
LIST = main Chess Color Theme GameSettings Settings Board Piece
FLAGS = $(SFMLLIBDIR) -lsfml-graphics-d -lsfml-window-d -lsfml-system-d -lsfml-audio-d -lsfml-network-d

SOURCES = $(LIST:%=$(SOURCEDIR)/%.cpp)
OBJS = $(SOURCES:$(SOURCEDIR)/%.cpp=$(OBJDIR)/%.o)
OBJDEL = $(wildcard $(OBJDIR)/*.*)
DEPS = $(OBJS:(OBJDIR)/%.o=(OBJDIR)/%.d)

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

build: ${OBJS} ${ICON}
	${HIDE} echo linking .o file to -*_*- ${NAME}.exe
	${HIDE} ${CXX} $^ -o ${NAME}.exe -L ${FLAGS}

${OBJDIR}/%.res: ${OTHERDIR}/%.rc
	${HIDE} echo compile $*.res
	${HIDE} windres $< -I ${IMAGEDIR} -O coff -o $@

${OBJDIR}/%.o: ${SOURCEDIR}/%.cpp
	${HIDE} echo compile $*.o
	${HIDE} ${CXX} -I ${SFMLINCDIR} -I ${HEADERDIR} -c $< -o $@
# -include $(patsubst ${SOURCEDIR}/%.cpp,${HEADERDIR}/%.hpp,$(wildcard ${SOURCEDIR}/*.cpp))

clean:
ifeq (${OBJDEL},)
	${HIDE} echo delete nothing
else
	${HIDE} echo delete files
	${HIDE} del obj\*.o
	${HIDE} del obj\*.res
endif

run:
	${HIDE} echo ${NAME}.exe
	${HIDE} ${NAME}.exe

rebuild: clean all
debug:
	./$(BINDIR)/$(NAME)

test: $(OBJDIR)/PieceBoard.o