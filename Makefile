# Makefile -- makefile for project.
# Author: Luis Colorado <luiscoloradourcola@gmail.com>
# Date: Mon Nov 25 08:55:07 EET 2019
#

RM ?= rm -f
targets = bt rnd
toclean = $(targets)

all: $(targets)
clean:
	$(RM) $(toclean)

bt_objs = bt.o build.o prtree.o
toclean += $(bt_objs)
bt: $(bt_objs)
	$(CC) -o $@ $(bt_objs)

rnd_objs = rnd.o
toclean += $(rnd_objs)
rnd: $(rnd_objs)
	$(CC) -o $@ $(rnd_objs)

$(bt_objs): node.h
