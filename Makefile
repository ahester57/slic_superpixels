IDIR=include
CDIR=src
ODIR=obj
IOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/include
LOPENCV=C:/dev/OpenCV-MinGW-Build-OpenCV-4.1.1-x64/x64/mingw/bin
LDLIBS= -llibopencv_core411 -llibopencv_highgui411 -llibopencv_imgcodecs411 -llibopencv_imgproc411# -llibopencv_video411

CC=g++
CFLAGS=-Wall -g -I $(IDIR) -I $(IOPENCV) -L $(LOPENCV) $(LDLIBS)
DEPS = $(wildcard $(IDIR)/*.hpp)
SOURCES= $(wildcard $(CDIR)/*.cpp)
OBJECTS = $(patsubst $(CDIR)/%.cpp, %.o, $(SOURCES))

$(info OBJECTS: $(OBJECTS))
$(info SOURCES: $(SOURCES))
$(info DEPS: $(DEPS))

.PHONY: all clean

default: all

all: slic

$(OBJECTS): $(SOURCES)
	${CC} -c $^ -I ${IDIR} -I ${IOPENCV}

slic: $(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	$(RM) $(OBJECTS) $(wildcard $(IDIR)/*.gch)

destroy:
	$(RM) $(OBJECTS) slic slic.exe $(wildcard $(IDIR)/*.gch)

# https://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
