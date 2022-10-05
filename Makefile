CXX		= c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -Wshadow -pedantic-errors

NAME	= main
CLASSES	= Color.cpp
TMPLATES= iterator.hpp pair.hpp debug_utility.hpp utility.hpp vector.hpp
HEADERS	= $(patsubst %.cpp,%.hpp,$(CLASSES)) $(TMPLATES)
TST_SRCS= test_iterator.cpp test_pair.cpp test_vector.cpp
SRCS	= main.cpp $(patsubst %.cpp,tests/%.cpp,$(TST_SRCS)) $(CLASSES)
OBJDIR	= obj
OBJS	= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

INTRA_MAIN = intra_main.cpp


all: $(NAME)

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) -f $(NAME).dSYM
	$(RM) -f $(INTRA_MAIN)
	$(RM) -f mine.txt
	$(RM) -f theirs.txt

fclean: clean
	$(RM) -f $(NAME)

re: fclean
	make all

show:
	@echo HEADERS=$(HEADERS)
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo INTRA_MAIN=$(INTRA_MAIN)

debug: fclean
debug: CXXFLAGS := $(CXXFLAGS) -g -DDEBUG=1
debug: all

leaks: all
	leaks --atExit -- ./$(NAME)

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

test: all
	./$(NAME)

$(NAME): $(OBJS) $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(OBJDIR)/%.o: %.cpp $(TMPLATES) | $(OBJDIR) $(OBJDIR)/tests
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/tests: $(OBJDIR)
	mkdir -p $@

$(INTRA_MAIN):
	curl -o $@ https://projects.intra.42.fr/uploads/document/document/10932/main.cpp

use_stl: fclean
use_stl: CXXFLAGS := $(CXXFLAGS) -DUSE_STL=1
use_stl: all

use_stl_debug: fclean
use_stl_debug: CXXFLAGS := $(CXXFLAGS) -g -DDEBUG=1 -DUSE_STL=1
use_stl_debug: all

compare:
	make debug
	./$(NAME) > mine.txt
	make use_stl_debug
	./$(NAME) > theirs.txt
	diff -y mine.txt theirs.txt


.PHONY: all clean fclean re show debug leaks test valgrind use_stl use_stl_debug
