SRC = splaytree/splaytree.c

PROGRAMS = test example

LDFLAGS =

CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./splaytree \
	-O2 -Wall \
	-D_SPLAY_SIBLING_POINTER

CXXFLAGS = $(CFLAGS) --std=c++11

all: $(PROGRAMS)

example:
	$(CC)  $(CFLAGS) app/example.c $(SRC) -o $@ $(LDFLAGS)

test: clean
	$(CXX) $(CXXFLAGS) app/test.cc $(SRC) -o $@ $(LDFLAGS) -lgtest -lpthread

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so