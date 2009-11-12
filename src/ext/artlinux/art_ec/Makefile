CXXFLAGS = `rtm-config --cflags`
LDFLAGS  = `rtm-config --libs`
SHFLAGS  = -shared
ARTLIB   = /usr/lib/art_syscalls.o

all: ArtExecutionContext.so

ArtExecutionContext.o: ArtExecutionContext.cpp
	$(CXX) -c $(CXXFLAGS) -o ArtExecutionContext.o ArtExecutionContext.cpp

ArtExecutionContext.so: ArtExecutionContext.o
	$(CXX) $(SHFLAGS) $(LDFLAGS) -o ArtExecutionContext.so ArtExecutionContext.o $(ARTLIB)

clean:
	rm -rf *~ *.o *.so