TARGET2 = hash
TARGET1 = handle
PREF_SRC1 = ./handle_text/
PREF_SRC2 = ./basic_hash_table/
PREF_OBJ = ./obj/
SRC1 = $(wildcard $(PREF_SRC1)*.cpp)
OBJ1 = $(patsubst $(PREF_SRC1)%.cpp, $(PREF_OBJ)%.o, $(SRC1))
SRC2 = $(wildcard $(PREF_SRC2)*.cpp)
OBJ2 = $(patsubst $(PREF_SRC2)%.cpp, $(PREF_OBJ)%.o, $(SRC2))

STRCMP = -DMY_STRCMP
CRC32 = -DMY_CRC32
LEN = -DMY_STRLEN -masm=intel


$(TARGET2) : $(OBJ2)
	g++ $(OBJ2) -o $(TARGET2) -L./list -llist
$(PREF_OBJ)%.o : $(PREF_SRC2)%.cpp
	g++ -c $< -o $@

base:
	g++ -c hash_table/file.cpp -o obj/file.o
	g++ -c hash_table/hash-functions.cpp -o obj/hash-functions.o -O3
	g++ -c hash_table/main.cpp -o obj/main.o
	g++ -c hash_table/search.cpp -o obj/search.o
	g++  ./obj/file.o  ./obj/hash-functions.o  ./obj/main.o  ./obj/search.o -o hash -L./list -llist

upgrade:
	nasm -g -f elf64 hash_table/my_strcmp.asm -o obj/my_strcmp.o
	g++ -c hash_table/file.cpp -o obj/file.o
	g++ -c hash_table/hash-functions.cpp -o obj/hash-functions.o -march=znver3 -O3 $(CRC32) $(LEN)
	g++ -c hash_table/main.cpp -o obj/main.o
	g++ -c hash_table/search.cpp obj/my_strcmp.o -o obj/search.o $(STRCMP)
	g++  ./obj/file.o  ./obj/hash-functions.o  ./obj/main.o ./obj/search.o obj/my_strcmp.o -o hash2 -L./list -llist -no-pie

handle:
	g++ -c handle_text/text_handler.cpp -o obj/text_handler.o
	g++  ./obj/text_handler.o -o handle -L./list -llist


make_lib:
	g++ -c ./list/list.cpp -o ./list/list.o
	ar r ./list/liblist.a ./list/list.o
	rm ./list/list.o

draw:
	python3 ./drawing_graphs/drawing.py const.txt
	python3 ./drawing_graphs/drawing.py first_ascii.txt
	python3 ./drawing_graphs/drawing.py length.txt
	python3 ./drawing_graphs/drawing.py right.txt
	python3 ./drawing_graphs/drawing.py left.txt
	python3 ./drawing_graphs/drawing.py ascii_sum.txt
	python3 ./drawing_graphs/drawing.py crc32.txt

valgr:
	valgrind --tool=callgrind ./hash
	kcachegrind callgrind.out.6021

.PHONY : clean
clean :
	rm -f $(PREF_OBJ)*.o
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f hash2
