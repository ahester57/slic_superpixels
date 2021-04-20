# Repo directories
INCDIR=include
SRCDIR=src
OBJDIR=obj
TARGETDIR=bin

# OpenCV directories
IOPENCV=T:/dev/opencv/include
LOPENCV=T:/dev/opencv/x64/mingw/bin
OPENCV_LIBS= -llibopencv_world452# -llibopencv_highgui452 -llibopencv_imgcodecs452 -llibopencv_imgproc452
OPENCV_CFLAGS = -I $(IOPENCV) -L $(LOPENCV) $(OPENCV_LIBS)

# Compiler options
# g++.exe (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0
#CC=g++
CC=C:/mingw64/bin/g++
CFLAGS=-Wall -g
CFLAGS+= -I $(INCDIR)
CFLAGS+= $(OPENCV_CFLAGS)
#DEPS = $(wildcard $(INCDIR)/*.hpp)
SOURCES= $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, %.o, $(SOURCES))

$(info OBJECTS: $(OBJECTS))
$(info SOURCES: $(SOURCES))
$(info DEPS: $(DEPS))

.PHONY: all clean

default: all

all: slic

#TODO put objects in OBJDIR
$(OBJECTS): $(SOURCES)
	${CC} -c $^ -I ${INCDIR} -I ${IOPENCV}

#TODO put executable in $(TARGETDIR)
slic: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJECTS) $(wildcard $(INCDIR)/*.gch)

destroy:
	$(RM) $(OBJECTS) slic slic.exe $(wildcard $(INCDIR)/*.gch)

# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
