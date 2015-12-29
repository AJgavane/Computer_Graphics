CC = g++
CFLAGS = -Wall -std=c++11 -w
PROG = assignment3
PARSE_PROG = parse

SRCS = main.cpp surf_rot.cpp
PSRCS = parse_main.cpp parse_mesh.cpp 

ifeq ($(shell uname),Darwin)
	LIBS = -framework OpenGL -framework GLUT
else
	LIBS = -lglut -lGLU -lGL
endif

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
	
parse: $(PARSE_PROG)

$(PARSE_PROG):      $(PSRCS)
	$(CC) $(CFLAGS) -o $(PARSE_PROG) $(PSRCS) $(LIBS)
                
clean: 
	rm -f $(PARSE_PROG)                       	
