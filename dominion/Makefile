CFLAGS= -Wall -fpic -fprofile-arcs -ftest-coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

test.out: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	# Unit test 1
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 1: isGameOver" > unittestresults.out
	./unittest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Unit test 2, not sure why -e shows up in output here
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 2: buyCard" >> unittestresults.out
	./unittest2 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Unit test 3
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 3: whoseTurn" >> unittestresults.out
	./unittest3 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Unit test 4
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 4: isGameOver" >> unittestresults.out
	./unittest4 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Card test 1
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 1: Smithy" >> unittestresults.out
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Card test 2
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 1: Village" >> unittestresults.out 
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Card test 3
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 1: Great Hall" >> unittestresults.out 
	./cardtest1 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	# Didn't write an Adventurer test :c

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
