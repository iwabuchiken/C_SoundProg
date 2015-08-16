ROOT_DIR	:= C:\WORKS\WS\Eclipse_Luna\C_SoundProg\main\D-3
C_SRCS := ex1_1.c
C_OBJ := ex1_1.o

C_EXE := ex1_1.exe

INC:=	-I.

RM	:= del

CC	:= gcc

#######################################
#######################################

all: $(C_EXE)

$(C_EXE): clean

	$(CC)  $(ROOT_DIR)\$(C_SRCS) -o $(ROOT_DIR)\$(C_EXE)
#	$(CC)  $(C_SRCS) -o $(C_EXE)

#	echo yes

clean:
	
	$(RM) $(ROOT_DIR)\$(C_EXE)