SRC = splaytree/splaytree.c

PROGRAMS = test example benchmark

3RD_INCLUDES 	= -I./3rd/avltree -I./3rd/rbtree
3RD_SOURCES 	= ./3rd/avltree/avltree.c ./3rd/rbtree/rbtree.c ./3rd/rbtree/rbwrap.c

LDFLAGS = -lgtest -lbenchmark -lpthread

CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./splaytree \
	-O2 -Wall -Wno-unused-variable \
	-D_SPLAY_SIBLING_POINTER -D_SPLAY_INSERT_RANDOM \
	-D_AVL_NEXT_POINTER \
	-D_RB_NEXT_POINTER

CXXFLAGS = $(CFLAGS) --std=c++11

all: $(PROGRAMS)

example:
	$(CC)  $(CFLAGS) 		app/example.c $(SRC) -o $@ $(LDFLAGS)

test: clean
	$(CXX) $(CXXFLAGS) 	app/test.cc $(SRC) $(3RD_SOURCES) $(3RD_INCLUDES) -o $@ $(LDFLAGS)

benchmark: clean
	$(CXX) $(CXXFLAGS) 	app/bench.cc $(SRC) $(3RD_SOURCES) $(3RD_INCLUDES) -o $@ $(LDFLAGS)

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so