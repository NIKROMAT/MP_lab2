TARGET = lab2
CXX = g++
PY = python3
OBJ = main.o lab2.o

OTHER = ${TARGET} graphics.png results.csv target_key.txt datasets latex html


.PHONY : clean cleanall all graphs doc generate

all : ${TARGET} target_key.txt datasets 


${TARGET} : ${OBJ}
	${CXX} $^ -o $@

main.o : main.cpp
	${CXX} -c $^ -o $@

lab2.o : lab2.cpp
	${CXX} -c $^ -o $@


graphs : graphics.png collisions.png

graphics.png collisions.png &: graphics.py results.csv collisions.csv
	${PY} graphics.py

results.csv collisions.csv &: ${TARGET} | target_key.txt datasets
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
