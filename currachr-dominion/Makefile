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

# This command will generate all random test.out files
test.out: randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	# Unit test 1
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 1: isGameOver" > test.out
	./unittest1 >> test.out
	gcov dominion.c >> test.out
	# Unit test 2, not sure why -e shows up in output here
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 2: buyCard" >> test.out
	./unittest2 >> test.out
	gcov dominion.c >> test.out
	# Unit test 3
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 3: whoseTurn" >> test.out
	./unittest3 >> test.out
	gcov dominion.c >> test.out
	# Unit test 4
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
	echo "Unit Test 4: isGameOver" >> test.out
	./unittest4 >> test.out
	gcov dominion.c >> test.out
	# Card test 1
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 1: Smithy" >> test.out
	./cardtest1 >> test.out
	gcov dominion.c >> test.out
	# Card test 2
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 2: Village" >> test.out 
	./cardtest2 >> test.out
	gcov dominion.c >> test.out
	# Card test 3
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
	echo "Card Test 3: Great Hall" >> test.out 
	./cardtest3 >> test.out
	gcov dominion.c >> test.out
	# Didn't write an Adventurer test :c
	## Random test 1
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	echo "Random Test 1: Smithy" >> test.out
	./randomtestcard1 >> test.out
	gcov -f -b dominion.c >> test.out
	## Random test 2, not sure why -e shows up in output here
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	echo "Random Test 2: Village" >> test.out
	./randomtestcard2 >> test.out
	gcov -f -b dominion.c >> test.out
	# Random test 3, not sure why -e shows up in output here
	gcc -o randomtestadventurer -g randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	echo "Random Test 3: Adventurer" >> test.out
	./randomtestadventurer >> test.out
	gcov -f -b dominion.c >> test.out

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
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer
	rm -f cardtest1 cardtest2 cardtest3
	rm -f unittest1 unittest2 unittest3 unittest4
