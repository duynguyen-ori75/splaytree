SRC = splaytree/splaytree.c

PROGRAMS = test example benchmark

3RD_INCLUDES 	= -I./3rd/avltree/avltree -I./3rd/avltree/rbtree
3RD_SOURCES 	= ./3rd/avltree/avltree/avltree.c

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

benchmark: clean
	$(CXX) $(CXXFLAGS) app/bench.cc $(SRC) $(3RD_SOURCES) $(3RD_INCLUDES) -o $@ $(LDFLAGS) -lgtest -lbenchmark -lpthread

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so