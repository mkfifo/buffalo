if [ ! -e bin ] ; then
  mkdir bin
fi

#gcc editor.c codes.c -o bin/buffalo
gcc buffalo.c codes.c -o bin/buffalo -std=c99 -pedantic -Wall
#gcc cbtree.c cbtree_test.c -o bin/cbtree_test
gcc forking.c -o bin/forking
gcc test.c codes.c -o bin/test
