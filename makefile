# I am a comment, and I want to say that the variable CC will be # the compiler to use. 

CC=g++ 

# Hey!, I am comment number 2. I want to say that CFLAGS will be the # options I'll pass to the compiler. 

CFLAGS= -c -Wall -std=c++14
EXENAME= SP

default: main.o SemanticDictionary.o SemanticDescriptor.o
	$(CC) main.o SemanticDictionary.o SemanticDescriptor.o -o $(EXENAME)

main.o: main.cpp 
	$(CC) $(CFLAGS) main.cpp 

SemanticDictionary.o: SemanticDictionary.cpp 
	$(CC) $(CFLAGS) SemanticDictionary.cpp 

SemanticDescriptor.o: SemanticDescriptor.cpp 
	$(CC) $(CFLAGS) SemanticDescriptor.cpp 

clean: 
	rm *.o $(EXENAME)

run:
	./$(EXENAME)