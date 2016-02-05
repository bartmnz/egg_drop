CFLAGS= -std=c11 -Wall -Werror -Wextra -Wpedantic -Wwrite-strings -Wno-deprecated -Wstack-usage=1024 -Wfloat-equal  -Waggregate-return -Winline

CC = gcc

TARGET=egg_drop

OBJS1=egg.o 

.PHONY: clean debug profile 

$(TARGET): $(OBJS1)

debug: CFLAGS+=-g
debug: $(TARGET)


clean:
	-$(RM) $(TARGET1) $(OBJS1) 

profile: CFLAGS+=-pg
profile: LDFLAGS+=-pg
profile: $(TARGET)