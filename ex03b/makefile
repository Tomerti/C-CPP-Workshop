CCFLAGS = -Wall -Wextra -Wvla
CC = gcc

snakes: linked_list.o markov_chain.o snakes_and_ladders.c
	$(CC) $(CCFLAGS) linked_list.o markov_chain.o snakes_and_ladders.c -o snakes_and_ladders

tweets: linked_list.o markov_chain.o tweets_generator.c
	$(CC) $(CCFLAGS) linked_list.o markov_chain.o tweets_generator.c -o tweets_generator

linked_list.o: linked_list.c linked_list.h
	$(CC) $(CCFLAGS) linked_list.c -c

markov_chain.o: markov_chain.c markov_chain.h linked_list.h
	$(CC) $(CCFLAGS) markov_chain.c -c
