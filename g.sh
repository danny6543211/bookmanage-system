g++ client/main.cpp client/client.cpp -lpthread -o client/client
g++ server/main.cpp server/server.cpp -lpthread -o server/server
g++ sqlite/main.cpp sqlite/sqlite.cpp -lsqlite3 -o sqlite/sqlite