ROOT_DIR	:= C:\WORKS\WS\Eclipse_Luna\C_SoundProg\main\D-3
C_SRCS_TRUNK	:= ex1_1
C_SRCS := $(C_SRCS_TRUNK).c
#C_SRCS := ex1_1.c
C_OBJ := $(C_SRCS_TRUNK).o
#C_OBJ := ex1_1.o

C_EXE := $(C_SRCS_TRUNK).exe
#C_EXE := ex1_1.exe

INC:=	-I.

RM	:= del

CC	:= gcc

#VAR	:= ffffff

#######################################
#######################################

all: $(C_EXE)

$(C_EXE): clean

	$(CC)  $(ROOT_DIR)\$(C_SRCS) -o $(ROOT_DIR)\$(C_EXE)
#	$(CC)  $(C_SRCS) -o $(C_EXE)

#	echo yes

clean:
	
	$(RM) $(ROOT_DIR)\$(C_EXE)
	
test:

	echo $(VAR)
