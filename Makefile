CXX		= c++
CXXFLAGS= -Wall -Wextra -Werror -std=c++98 -Wshadow -pedantic-errors

NAME			= mine
NAME_STL		= stl
NAME_DEBUG		:= $(NAME)_debug
NAME_STL_DEBUG	:= $(NAME_STL)_debug

DEBUG_DIR = debug
DEBUG_TMPLATES = \
		debug_tree_utility.hpp \
		debug_utility.hpp

CLASSES	= $(DEBUG_DIR)/Color.cpp

TMPLATES= \
			algorithm.hpp \
			iterator.hpp \
			map.hpp \
			pair.hpp \
			set.hpp \
			stack.hpp \
			tree.hpp \
			type_traits.hpp \
			utility.hpp \
			vector.hpp

HEADERS	= $(patsubst %.cpp,%.hpp,$(CLASSES)) $(TMPLATES) $(addprefix $(DEBUG_DIR)/,$(DEBUG_TMPLATES))
TST_SRCS= \
			main.cpp \
			test_iterator.cpp \
			test_map.cpp \
			test_pair.cpp \
			test_set.cpp \
			test_stack.cpp \
			test_utility.cpp \
			test_vector.cpp
			# test_rb_tree.cpp \ # causes namespace conflict because there is no counter part in STL
TESTS_SRC_DIR = tests

UNAME = $(shell uname -s)
DIFF_OPTIONS = --width=200
ifeq ($(UNAME), Linux)
	DIFF_OPTIONS := $(DIFF_OPTIONS) --color=always
endif

SRCS	= $(patsubst %.cpp,$(TESTS_SRC_DIR)/%.cpp,$(TST_SRCS)) $(CLASSES)
OBJDIR	= obj
OBJS	= $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCS))

INTRA_MAIN = intra_main.cpp
SEED = 4242

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
	$(RM) -f test_intra
	$(RM) -f $(INTRA_MAIN)

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

test_rb_tree: tests/test_rb_tree.cpp debug/Color.cpp tree.hpp pair.hpp utility.hpp $(addprefix $(DEBUG_DIR)/,$(DEBUG_TMPLATES))
	$(CXX) $(CXXFLAGS) -g -DDEBUG=1 -I. -I$(DEBUG_DIR) tests/test_rb_tree.cpp debug/Color.cpp -o $@
	./$@

test_intra: $(INTRA_MAIN) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INTRA_MAIN) -I. -o $@
	./$@ $(SEED)

$(NAME): $(OBJS) $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(OBJS) -I. -o $@

$(NAME_STL): $(SRCS) $(HEADERS)
	$(CXX) $(filter-out -std=c++98,$(CXXFLAGS)) -DUSE_STL=1 $(SRCS) -I. -I$(DEBUG_DIR) -o $@

$(NAME_DEBUG): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -g -DDEBUG=1 -I. -I$(DEBUG_DIR) $(SRCS) -o $@

$(NAME_STL_DEBUG): $(SRCS) $(HEADERS)
	$(CXX) $(filter-out -std=c++98,$(CXXFLAGS)) -g -DDEBUG=1 -DUSE_STL=1 -I. -I$(DEBUG_DIR) $(SRCS) -o $@

$(OBJDIR)/%.o: %.cpp $(TMPLATES) | $(OBJDIR) $(OBJDIR)/tests $(OBJDIR)/$(DEBUG_DIR)
	$(CXX) $(CXXFLAGS) -c $< -I. -I$(DEBUG_DIR) -o $@

$(OBJDIR):
	mkdir $@

$(OBJDIR)/tests: | $(OBJDIR)
	mkdir -p $@

$(OBJDIR)/$(DEBUG_DIR): | $(OBJDIR)
	mkdir -p $@

$(INTRA_MAIN):
	curl -o $@ https://projects.intra.42.fr/uploads/document/document/10932/main.cpp


compare: $(NAME_DEBUG) $(NAME_STL_DEBUG)
	./$< > mine.txt 2>&1
	./$(NAME_STL_DEBUG) > theirs.txt 2>&1
	diff -y $(DIFF_OPTIONS) mine.txt theirs.txt

.PHONY: all clean fclean re show debug leaks test valgrind test_rb_tree test_intra compare
