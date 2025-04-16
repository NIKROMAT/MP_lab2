TARGET = lab2
CXX = g++
PY = python3
OBJ = main.o lab2.o

OTHER = ${TARGET} graphics.png results.csv target_key.txt datasets latex html


.PHONY : clean cleanall all graph doc generate

all : ${TARGET} target_key.txt datasets 


${TARGET} : ${OBJ}
	${CXX} $^ -o $@

main.o : main.cpp
	${CXX} -c $^ -o $@

lab2.o : lab2.cpp
	${CXX} -c $^ -o $@


graph : graphics.png

graphics.png : graphics.py results.csv
	${PY} graphics.py

results.csv : ${TARGET} | target_key.txt datasets
	./${TARGET}

target_key.txt datasets &: | datamaker.py
	${PY} datamaker.py


generate: target_key.txt datasets


doc: Doxyfile
	doxygen Doxyfile

Doxyfile: 
	doxygen -g


clean :
	rm ${OBJ}

cleanall : clean
	rm -rI ${OTHER}
