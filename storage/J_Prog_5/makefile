ROOT_DIR	:= C:\WORKS\WS\Eclipse_Luna\C_SoundProg\main\J_Prog_5
#ROOT_DIR	:= C:\WORKS\WS\Eclipse_Luna\C_SoundProg\main\D-3
C_SRCS_TRUNK	:= D-5_s-1-1
C_SRCS := $(C_SRCS_TRUNK).c
C_OBJ := $(C_SRCS_TRUNK).o

C_SRCS_OTHERS	:= utils.c

C_EXE := $(C_SRCS_TRUNK).exe

INC:=	-I.

RM	:= rm
#RM	:= del

CC	:= gcc

#VAR	:= ffffff

#######################################
#######################################

all: $(C_EXE)

$(C_EXE):  
	
	echo "yes"
	$(CC)  $(C_SRCS) $(C_SRCS_OTHERS) $(INC) -o $(C_EXE)
#	$(CC)  $(C_SRCS) -o $(C_EXE)
	

#all: $(C_EXE)
#
#$(C_EXE): clean
#
#	$(CC)  $(ROOT_DIR)\$(C_SRCS) -o $(ROOT_DIR)\$(C_EXE)
##	$(CC)  $(C_SRCS) -o $(C_EXE)
#
##	echo yes
#
clean:
	
	$(RM) $(ROOT_DIR)\$(C_EXE)
#	
#test:
#
#	echo $(VAR)
