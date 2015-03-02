TARGET=libnico.so
SRCS=nc_tcp_server.cc nc_tcp_client.cc nc_tcp_connection.cc
OBJS=$(SRCS:.cc=.o)

CC=gcc

all:	$(TARGET) test


$(TARGET):	$(OBJS)
	$(CXX) -shared $(OBJS) -o $(TARGET)

.cc.o:
	$(CXX) -fPIC -c $< -o $@

.PHONY: test clean

test:
	$(CXX) -L./ -lnico testserver.cc -o testserver
	$(CXX) -L./ -lnico testclient.cc -o testclient

clean:
	rm $(OBJS) $(TARGET) testserver testclient
