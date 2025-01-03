SocialMedia: main.o ReadPost.o User.o Manager.o Person.o
	g++ main.o ReadPost.o User.o Manager.o Person.o -o SocialMedia
main.o:main.cpp
	g++ -c main.cpp
ReadPost.o:ReadPost.cpp
	g++ -c ReadPost.cpp
User.o:User.cpp
	g++ -c User.cpp
Manager.o:Manager.cpp
	g++ -c Manager.cpp
Person.o:Person.cpp
	g++ -c Person.cpp

clean:
	rm *.o SocialMedia