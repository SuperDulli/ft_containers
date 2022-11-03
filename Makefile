CXX		= c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -Wshadow -pedantic-errors

NAME			= mine
NAME_STL		= stl
NAME_DEBUG		:= $(NAME)_debug
NAME_STL_DEBUG	:= $(NAME_STL)_debug

CLASSES	= Color.cpp
TMPLATES= \
			iterator.hpp \
			pair.hpp \
			debug_utility.hpp \
			utility.hpp \
			vector.hpp \
			tree.hpp \
			map.hpp

HEADERS	= $(patsubst %.cpp,%.hpp,$(CLASSES)) $(TMPLATES)
TST_SRCS= \
			test_iterator.cpp \
			test_pair.cpp \
			test_vector.cpp \
			test_utility.cpp \
			test_map.cpp
			# test_rb_tree.cpp \ # causes namespace conflict because there is no counter part in STL

SRCS	= main.cpp $(patsubst %.cpp,tests/%.cpp,$(TST_SRCS)) $(CLASSES)
OBJDIR	= obj
OBJS	= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

INTRA_MAIN = intra_main.cpp


all: $(NAME) $(NAME_STL) $(NAME_DEBUG) $(NAME_STL_DEBUG)

clean:
	$(RM) -rf $(OBJDIR)
	$(RM) -f $(NAME).dSYM
	$(RM) -f $(INTRA_MAIN)

fclean: clean
	$(RM) -f $(NAME)
	$(RM) -f $(NAME_STL)
	$(RM) -f $(NAME_DEBUG)
	$(RM) -f $(NAME_STL_DEBUG)
	$(RM) -f test_rb_tree
	$(RM) -f mine.txt
	$(RM) -f theirs.txt

re: fclean
	make all

show:
	@echo NAME=$(NAME)
	@echo NAME_STL=$(NAME_STL)
	@echo NAME_DEBUG=$(NAME_DEBUG)
	@echo NAME_STL_DEBUG=$(NAME_STL_DEBUG)
	@echo HEADERS=$(HEADERS)
	@echo SRCS=$(SRCS)
	@echo OBJS=$(OBJS)
	@echo INTRA_MAIN=$(INTRA_MAIN)

debug: clean
debug: CXXFLAGS := $(CXXFLAGS) -g -DDEBUG=1
debug: $(NAME_DEBUG)

leaks: $(NAME)
	leaks --atExit -- ./$@

valgrind: debug
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME_DEBUG)

test: $(NAME)
	./$^

test_debug: $(NAME_DEBUG)
	./$^

test_rb_tree: tests/test_rb_tree.cpp Color.cpp tree.hpp pair.hpp utility.hpp debug_utility.hpp debug_tree_utility.hpp
	$(CXX) $(CXXFLAGS) -g -DDEBUG=1 tests/test_rb_tree.cpp Color.cpp -o $@

$(NAME): $(OBJS) $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

$(NAME_STL): $(SRCS) $(HEADERS)
	$(CXX) $(filter-out -std=c++98,$(CXXFLAGS)) -DUSE_STL=1 $(SRCS) -o $@

$(NAME_DEBUG): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -g -DDEBUG=1 $(SRCS) -o $@

$(NAME_STL_DEBUG): $(SRCS) $(HEADERS)
	$(CXX) $(filter-out -std=c++98,$(CXXFLAGS)) -g -DDEBUG=1 -DUSE_STL=1 $(SRCS) -o $@

$(OBJDIR)/%.o: %.cpp $(TMPLATES) | $(OBJDIR) $(OBJDIR)/tests
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/tests: | $(OBJDIR)
	mkdir -p $@

$(INTRA_MAIN):
	curl -o $@ https://projects.intra.42.fr/uploads/document/document/10932/main.cpp


compare: $(NAME_DEBUG) $(NAME_STL_DEBUG)
	./$< > mine.txt 2>&1
	./$(NAME_STL_DEBUG) > theirs.txt 2>&1
	diff -y --width=200 --color=always mine.txt theirs.txt

.PHONY: all clean fclean re show debug leaks test valgrind test_rb_tree
