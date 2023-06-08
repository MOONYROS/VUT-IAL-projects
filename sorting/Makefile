CC := gcc
CFLAGS := -std=c99 -Wall -Wextra -Wpedantic

all : selectSort bubbleSort heapSort bubbleInsertSort binaryInsertSort quickSort quickSort2 shellSort mergeSort

selectSort: selectSort.o
	$(CC) -o selectSort selectSort.o

bubbleSort: bubbleSort.o
	$(CC) -o bubbleSort bubbleSort.o

heapSort: heapSort.o
	$(CC) -o heapSort heapSort.o

bubbleInsertSort: bubbleInsertSort.o
	$(CC) -o bubbleInsertSort bubbleInsertSort.o

binaryInsertSort: binaryInsertSort.o
	$(CC) -o binaryInsertSort binaryInsertSort.o

quickSort: quickSort.o
	$(CC) -o quickSort quickSort.o

quickSort2: quickSort2.o
	$(CC) -o quickSort2 quickSort2.o

shellSort: shellSort.o
	$(CC) -o shellSort shellSort.o

mergeSort: mergeSort.o
	$(CC) -o mergeSort mergeSort.o

clean:
	rm -f *.o
	rm -f selectSort
	rm -f bubbleSort
	rm -f heapSort
	rm -f bubbleInsertSort
	rm -f binaryInsertSort
	rm -f quickSort
	rm -f quickSort2
	rm -f shellSort
	rm -f mergeSort