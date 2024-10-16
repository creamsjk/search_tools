# 定义变量
bin = ./bin
include = ./include
src = ./src

# 默认目标
all: $(bin)/SplitTool_test $(bin)/DirScanner_test $(bin)/dict_test  $(bin)/XmlRss_test $(bin)/PageLib_test $(bin)/WebPage_test \
	$(bin)/config_test $(bin)/PageLibPreprocessor_test $(bin)/key_test $(bin)/server $(bin)/WebQuery_test

# 生成可执行文件
$(bin)/SplitTool_test: $(bin)/SplitTool_test.o $(bin)/SplitTool.o
	g++ $(bin)/SplitTool_test.o $(bin)/SplitTool.o -o $(bin)/SplitTool_test

$(bin)/DirScanner_test: $(bin)/DirScanner_test.o $(bin)/DirScanner.o
	g++ $(bin)/DirScanner_test.o $(bin)/DirScanner.o -o $(bin)/DirScanner_test

$(bin)/dict_test: $(bin)/dict_test.o $(bin)/DirScanner.o $(bin)/DictProducer.o $(bin)/SplitTool.o
	g++ $(bin)/dict_test.o $(bin)/DirScanner.o $(bin)/DictProducer.o $(bin)/SplitTool.o -o $(bin)/dict_test

$(bin)/XmlRss_test: $(bin)/XmlRss.o $(bin)/XmlRss_test.o $(bin)/tinyxml2.o
	g++ $(bin)/XmlRss.o $(bin)/XmlRss_test.o  $(bin)/tinyxml2.o -o $(bin)/XmlRss_test

$(bin)/PageLib_test: $(bin)/PageLib.o $(bin)/PageLib_test.o $(bin)/XmlRss.o $(bin)/DirScanner.o $(bin)/tinyxml2.o
	g++ $(bin)/PageLib.o $(bin)/PageLib_test.o $(bin)/XmlRss.o $(bin)/DirScanner.o $(bin)/tinyxml2.o -o $(bin)/PageLib_test

$(bin)/WebPage_test: $(bin)/WebPage_test.o $(bin)/WebPage.o
	g++ $(bin)/WebPage_test.o $(bin)/WebPage.o -o $(bin)/WebPage_test

$(bin)/config_test: $(bin)/Configuration.o $(bin)/config_test.o
	g++ $(bin)/Configuration.o $(bin)/config_test.o -o  $(bin)/config_test

$(bin)/PageLibPreprocessor_test: $(bin)/PageLibPreprocessor_test.o $(bin)/PageLibPreprocessor.o $(bin)/SplitTool.o $(bin)/WebPage.o
	g++  $(bin)/PageLibPreprocessor_test.o $(bin)/PageLibPreprocessor.o $(bin)/SplitTool.o $(bin)/WebPage.o -o $(bin)/PageLibPreprocessor_test

$(bin)/key_test: $(bin)/key_test.o $(bin)/DictProducer.o $(bin)/SplitTool.o $(bin)/DirScanner.o $(bin)/KeyRecommander.o
	g++  $(bin)/key_test.o $(bin)/DictProducer.o $(bin)/SplitTool.o $(bin)/DirScanner.o $(bin)/KeyRecommander.o -o $(bin)/key_test

$(bin)/server: $(bin)/Acceptor.o $(bin)/EchoServer.o $(bin)/EventLoop.o $(bin)/InetAddress.o  $(bin)/Socket.o $(bin)/SocketIO.o $(bin)/TaskQueue.o $(bin)/TcpConnection.o $(bin)/TcpServer.o $(bin)/ThreadPool.o $(bin)/SplitTool.o $(bin)/KeyRecommander.o $(bin)/WebPage.o $(bin)/DictProducer.o $(bin)/DirScanner.o $(bin)/Configuration.o  $(bin)/PageLib.o $(bin)/PageLibPreprocessor.o  $(bin)/XmlRss.o $(bin)/tinyxml2.o $(bin)/TestEchoserver.o $(bin)/WebQuery.o
	g++  $(bin)/Acceptor.o $(bin)/EchoServer.o $(bin)/EventLoop.o $(bin)/InetAddress.o  $(bin)/Socket.o $(bin)/SocketIO.o $(bin)/TaskQueue.o $(bin)/TcpConnection.o $(bin)/TcpServer.o $(bin)/ThreadPool.o $(bin)/SplitTool.o $(bin)/KeyRecommander.o $(bin)/WebPage.o $(bin)/DictProducer.o $(bin)/DirScanner.o $(bin)/Configuration.o  $(bin)/PageLib.o $(bin)/PageLibPreprocessor.o  $(bin)/XmlRss.o $(bin)/tinyxml2.o $(bin)/TestEchoserver.o  $(bin)/WebQuery.o -o $(bin)/server -lpthread -g

$(bin)/WebQuery_test: $(bin)/WebQuery_test.o $(bin)/WebQuery.o  $(bin)/PageLibPreprocessor.o $(bin)/SplitTool.o $(bin)/WebPage.o
	g++ $(bin)/WebQuery_test.o $(bin)/WebQuery.o  $(bin)/PageLibPreprocessor.o $(bin)/SplitTool.o $(bin)/WebPage.o -o $(bin)/WebQuery_test


	

# 编译规则
$(bin)/SplitTool.o: $(include)/SplitTool.h $(src)/SplitTool.cpp
	g++  -g -I$(include) -c $(src)/SplitTool.cpp -o $(bin)/SplitTool.o

$(bin)/SplitTool_test.o: $(src)/SplitTool_test.cpp $(include)/SplitTool.h
	g++  -g -I$(include) -c $(src)/SplitTool_test.cpp -o $(bin)/SplitTool_test.o

$(bin)/DirScanner.o: $(include)/DirScanner.h $(src)/DirScanner.cpp
	g++  -g -I$(include) -c $(src)/DirScanner.cpp -o $(bin)/DirScanner.o

$(bin)/DirScanner_test.o: $(src)/DirScanner_test.cpp
	g++  -g -I$(include) -c $(src)/DirScanner_test.cpp -o $(bin)/DirScanner_test.o

$(bin)/DictProducer.o: $(include)/DictProducer.h $(src)/DictProducer.cpp
	g++  -g -I$(include) -c $(src)/DictProducer.cpp -o $(bin)/DictProducer.o

$(bin)/dict_test.o: $(src)/dict_test.cpp
	g++  -g -I$(include) -c $(src)/dict_test.cpp -o $(bin)/dict_test.o

$(bin)/XmlRss.o: $(src)/XmlRss.cpp
	g++  -g -I$(include) -c $(src)/XmlRss.cpp   -o $(bin)/XmlRss.o

$(bin)/XmlRss_test.o: $(src)/XmlRss_test.cpp
	g++  -g -I$(include) -c $(src)/XmlRss_test.cpp -o $(bin)/XmlRss_test.o

$(bin)/tinyxml2.o: ./tools/tinyxml2-master/tinyxml2.h ./tools/tinyxml2-master/tinyxml2.cpp
	g++  -g -c ./tools/tinyxml2-master/tinyxml2.cpp -o $(bin)/tinyxml2.o

$(bin)/PageLib.o: $(src)/PageLib.cpp
	g++  -g -I$(include) -c $(src)/PageLib.cpp -o $(bin)/PageLib.o
	
$(bin)/PageLib_test.o: $(src)/PageLib_test.cpp
	g++  -g -I$(include) -c $(src)/PageLib_test.cpp -o $(bin)/PageLib_test.o

$(bin)/WebPage.o: $(src)/WebPage.cpp
	g++  -g -I$(include) -c $(src)/WebPage.cpp -o $(bin)/WebPage.o

$(bin)/WebPage_test.o: $(src)/WebPage_test.cpp
	g++  -g -I$(include) -c $(src)/WebPage_test.cpp -o $(bin)/WebPage_test.o

$(bin)/Configuration.o: $(src)/Configuration.cpp
	g++  -g -I$(include) -c $(src)/Configuration.cpp -o $(bin)/Configuration.o

$(bin)/config_test.o: $(src)/config_test.cpp
	g++  -g -I$(include) -c $(src)/config_test.cpp -o $(bin)/config_test.o

$(bin)/PageLibPreprocessor.o: $(src)/PageLibPreprocessor.cpp
	g++  -g -I$(include) -c   $(src)/PageLibPreprocessor.cpp -o $(bin)/PageLibPreprocessor.o

$(bin)/PageLibPreprocessor_test.o: $(src)/PageLibPreprocessor_test.cpp
	g++  -g -I$(include) -c   $(src)/PageLibPreprocessor_test.cpp -o $(bin)/PageLibPreprocessor_test.o

$(bin)/KeyRecommander.o: $(src)/KeyRecommander.cpp
	g++  -g -I$(include) -c   $(src)/KeyRecommander.cpp  -o $(bin)/KeyRecommander.o

$(bin)/key_test.o: $(src)/key_test.cpp
	g++  -g -I$(include) -c   $(src)/key_test.cpp  -o $(bin)/key_test.o

$(bin)/Acceptor.o: $(src)/Acceptor.cpp
	g++  -g -I$(include) -c   $(src)/Acceptor.cpp  -o $(bin)/Acceptor.o

$(bin)/TcpServer.o: $(src)/TcpServer.cpp
	g++  -g -I$(include) -c   $(src)/TcpServer.cpp  -o $(bin)/TcpServer.o

$(bin)/EchoServer.o: $(src)/EchoServer.cpp
	g++  -g -I$(include) -c   $(src)/EchoServer.cpp  -o $(bin)/EchoServer.o

$(bin)/EventLoop.o: $(src)/EventLoop.cpp
	g++  -g -I$(include) -c   $(src)/EventLoop.cpp  -o $(bin)/EventLoop.o

$(bin)/InetAddress.o: $(src)/InetAddress.cpp
	g++  -g -I$(include) -c   $(src)/InetAddress.cpp  -o $(bin)/InetAddress.o

$(bin)/Socket.o: $(src)/Socket.cpp
	g++  -g -I$(include) -c   $(src)/Socket.cpp  -o $(bin)/Socket.o

$(bin)/SocketIO.o: $(src)/SocketIO.cpp
	g++  -g -I$(include) -c   $(src)/SocketIO.cpp  -o $(bin)/SocketIO.o

$(bin)/TaskQueue.o: $(src)/TaskQueue.cpp
	g++  -g -I$(include) -c   $(src)/TaskQueue.cpp  -o $(bin)/TaskQueue.o

$(bin)/TcpConnection.o: $(src)/TcpConnection.cpp
	g++  -g -I$(include) -c   $(src)/TcpConnection.cpp  -o $(bin)/TcpConnection.o

$(bin)/ThreadPool.o: $(src)/ThreadPool.cpp
	g++  -g -I$(include) -c   $(src)/ThreadPool.cpp  -o $(bin)/ThreadPool.o

$(bin)/TestEchoserver.o: $(src)/TestEchoserver.cpp
	g++  -g -I$(include) -c   $(src)/TestEchoserver.cpp  -o $(bin)/TestEchoserver.o

$(bin)/WebQuery.o: $(src)/WebQuery.cpp
	g++  -g -I$(include) -c   $(src)/WebQuery.cpp  -o $(bin)/WebQuery.o

$(bin)/WebQuery_test.o: $(src)/WebQuery_test.cpp
	g++  -g -I$(include) -c   $(src)/WebQuery_test.cpp  -o $(bin)/WebQuery_test.o




# 清理目标
clean:
	mv $(bin)/*  ./delete
#	rm -f $(bin)/* 































