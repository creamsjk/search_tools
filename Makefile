# 定义变量
bin = ./bin
include = ./include
src = ./src

# 默认目标
all: $(bin)/SplitTool_test $(bin)/DirScanner_test $(bin)/dict_test  $(bin)/XmlRss_test $(bin)/PageLib_test $(bin)/WebPage_test \
	$(bin)/config_test $(bin)/PageLibPreprocessor_test

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
	g++ $(bin)/PageLibPreprocessor_test.o $(bin)/PageLibPreprocessor.o $(bin)/SplitTool.o $(bin)/WebPage.o -o $(bin)/PageLibPreprocessor_test


# 编译规则
$(bin)/SplitTool.o: $(include)/SplitTool.h $(src)/SplitTool.cpp
	g++ -Wall -g -I$(include) -c $(src)/SplitTool.cpp -o $(bin)/SplitTool.o

$(bin)/SplitTool_test.o: $(src)/SplitTool_test.cpp $(include)/SplitTool.h
	g++ -Wall -g -I$(include) -c $(src)/SplitTool_test.cpp -o $(bin)/SplitTool_test.o

$(bin)/DirScanner.o: $(include)/DirScanner.h $(src)/DirScanner.cpp
	g++ -Wall -g -I$(include) -c $(src)/DirScanner.cpp -o $(bin)/DirScanner.o

$(bin)/DirScanner_test.o: $(src)/DirScanner_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/DirScanner_test.cpp -o $(bin)/DirScanner_test.o

$(bin)/DictProducer.o: $(include)/DictProducer.h $(src)/DictProducer.cpp
	g++ -Wall -g -I$(include) -c $(src)/DictProducer.cpp -o $(bin)/DictProducer.o

$(bin)/dict_test.o: $(src)/dict_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/dict_test.cpp -o $(bin)/dict_test.o

$(bin)/XmlRss.o: $(src)/XmlRss.cpp
	g++ -Wall -g -I$(include) -c $(src)/XmlRss.cpp   -o $(bin)/XmlRss.o

$(bin)/XmlRss_test.o: $(src)/XmlRss_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/XmlRss_test.cpp -o $(bin)/XmlRss_test.o

$(bin)/tinyxml2.o: ./tools/tinyxml2-master/tinyxml2.h ./tools/tinyxml2-master/tinyxml2.cpp
	g++ -Wall -g -c ./tools/tinyxml2-master/tinyxml2.cpp -o $(bin)/tinyxml2.o

$(bin)/PageLib.o: $(src)/PageLib.cpp
	g++ -Wall -g -I$(include) -c $(src)/PageLib.cpp -o $(bin)/PageLib.o
	
$(bin)/PageLib_test.o: $(src)/PageLib_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/PageLib_test.cpp -o $(bin)/PageLib_test.o

$(bin)/WebPage.o: $(src)/WebPage.cpp
	g++ -Wall -g -I$(include) -c $(src)/WebPage.cpp -o $(bin)/WebPage.o

$(bin)/WebPage_test.o: $(src)/WebPage_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/WebPage_test.cpp -o $(bin)/WebPage_test.o

$(bin)/Configuration.o: $(src)/Configuration.cpp
	g++ -Wall -g -I$(include) -c $(src)/Configuration.cpp -o $(bin)/Configuration.o

$(bin)/config_test.o: $(src)/config_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/config_test.cpp -o $(bin)/config_test.o

$(bin)/PageLibPreprocessor.o: $(src)/PageLibPreprocessor.cpp
	g++ -Wall -g -I$(include) -c  -W $(src)/PageLibPreprocessor.cpp -o $(bin)/PageLibPreprocessor.o

$(bin)/PageLibPreprocessor_test.o: $(src)/PageLibPreprocessor_test.cpp
	g++ -Wall -g -I$(include) -c $(src)/PageLibPreprocessor_test.cpp -o $(bin)/PageLibPreprocessor_test.o







# 清理目标
clean:
	rm -f $(bin)/*.o 































