SRCDIR="src"
SRC="example/main.cc"
LDIR=`pwd`"/"${SRCDIR}

CXX=g++
FLAGS=-std=c++11 -g -Wall -Wextra

all:
	${CXX} ${FLAGS} -I${LDIR} ${SRC}

