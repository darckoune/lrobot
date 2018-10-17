srcdir=src
bindir=bin
docdir=doc
savedir=save
CC = gcc
CP = cp
EXE = prog
SRCS = $(shell find src -name *.c)
HEAD = $(shell find src -name *.h)
OBJS = $(subst $(srcdir),$(bindir),$(SRCS:.c=.o))
CFLAGS = -g -Wall
LDFLAGS = -lm

.PHONY : save

all : $(EXE)
	echo "Compilation des familles terminee !"

$(EXE) : $(OBJS)
	$(CC) $^ $(LDFLAGS) -o $@

./$(bindir)/%.o : ./$(srcdir)/%.c
	
	$(CC) $^ $(CFLAGS) -c -o $@


clean : 
	rm -f $(OBJS)
	rm -f src/*.bak
	rm -f src/*.old
	rm -f src/#*#


mrproper : clean
	rm -f $(EXE)

save :
	$(CP) $(SRCS) $(savedir)
	$(CP) $(HEAD) $(savedir)

bidon :
	echo $(SRCS)
	echo $(OBJS)

