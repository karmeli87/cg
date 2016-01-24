

SRCDIR        = src
INCDIR        = include

# Main program
PROGRAM       = GLSample


HFILES        = $(INCDIR)/Common.h \
                $(INCDIR)/RenderIf.h \
                $(INCDIR)/RenderTriangle.h \
                $(INCDIR)/ShaderProgram.h \
                $(INCDIR)/lodepng.h


SOURCES       = $(SRCDIR)/Common.cpp \
                $(SRCDIR)/RenderTriangle.cpp \
                $(SRCDIR)/ShaderProgram.cpp \
                $(SRCDIR)/lodepng.cpp

OBJECTS       = $(SOURCES:.cpp=.o)

# definitions
INCLUDE       = -I$(INCDIR) -I/usr/include
C++FLAGS      = -g -Wall -pthread $(INCLUDE)
ARFLAGS       = -rcuv
DEPENDFLAGS   = -Y 
LDFLAGS       = -Wl,--no-as-needed -pthread
LIBS          = -lGLEW -lGL -lglut -lm -lrt 



.SUFFIXES: .SUFFIXES .cpp .o

all: $(PROGRAM)


.cpp.o: $(SOURCES) $(HFILES)
	g++ -c $(C++FLAGS) $< -o $(<:.cpp=.o)


$(PROGRAM): $(SRCDIR)/$(PROGRAM).o $(OBJECTS)
	g++ $(SRCDIR)/$(PROGRAM).o $(OBJECTS) -o $(PROGRAM) $(LIBS) $(LDFLAGS)


clean:
	rm -f $(PROGRAM) $(SRCDIR)/$(PROGRAM).o $(OBJECTS) 


