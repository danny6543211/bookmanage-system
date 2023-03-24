cd client
g++ main.cpp client.cpp -lpthread -o client
cd ../server
g++ main.cpp server.cpp -lpthread -o server
cd ..