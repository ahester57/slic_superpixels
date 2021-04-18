# Repo directories
INCDIR=include
SRCDIR=src
OBJDIR=obj
TARGETDIR=bin

# Uncomment following line to include opencv video support
# VIDEO := 1

# OpenCV directories
IOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include
LOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/x64/mingw/bin
LDLIBS= -llibopencv_core411 -llibopencv_highgui411 -llibopencv_imgcodecs411 -llibopencv_imgproc411
ifdef VIDEO
	LDLIBS += -llibopencv_video411
endif

# Compiler options
CC=g++
CFLAGS=-Wall -g -I $(INCDIR) -I $(IOPENCV) -L $(LOPENCV) $(LDLIBS)
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
