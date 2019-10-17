ifneq ($V,1)
	Q ?= @
endif

DEBUG   = -O3
CC      = g++
INCLUDE = -I/usr/local/include -I/usr/include
CFLAGS  = $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

SRCS    = $(wildcard *.cpp)
OBJS    = ${SRCS:.cpp=.o}

LDFLAGS = -L/usr/local/lib
LDLIBS  = 

NAME    = picapinterface

SRC     = $(NAME).cpp
BIN     = $(NAME:.cpp=)

.PHONY: run clean

$(NAME):	$(OBJS)
	$Q echo [link]
	$Q $(CC) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

.cpp.o:
	$Q echo [CC] $<
	$Q $(CC) -c $(CFLAGS) $< -o $@

clean:
	$Q echo "[Clean]"
	$Q rm -f $(OBJS) *~ core tags $(BIN)

tags:	$(SRC)
	$Q echo [ctags]
	$Q ctags $(SRC)

depend:
	makedepend -Y $(SRC)

run:
	sudo ./$(NAME)

# DO NOT DELETE
