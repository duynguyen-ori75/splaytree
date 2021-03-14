SRC = splaytree/splaytree.c

TEST_SRC = app/test.cc

PROGRAMS = test

LDFLAGS =

CFLAGS = \
	-g -D_GNU_SOURCE \
	-I. -I./splaytree \
	-O2 -Wall \

CXXFLAGS = $(CFLAGS) --std=c++11

all: $(PROGRAMS)

test:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) $(SRC) -o $@ $(LDFLAGS) -lgtest -lpthread

clean:
	rm -rf $(PROGRAMS) ./*.o ./*.so