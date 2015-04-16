#---------- env ----------
CXX=g++
CXXFLAGS=-D_GNU_SOURCE -D__STDC_LIMIT_MACROS -g -pipe -W -Wall -fPIC -fno-omit-frame-pointer
INCPATH=-I. -I/home/meihua/dy/src/common_lib/../glog/include -I/home/meihua/dy/src/common_lib/../redis_proxy/output/include -I/home/meihua/dy/src/common_lib/../protobuf/include -I/home/meihua/dy/src/common_lib/../hiredis/include -I/home/meihua/dy/src/common_lib/../gflags/include -I/home/meihua/dy/src/common_lib/../mysql_proxy/output/include -I/home/meihua/dy/src/common_lib/../mysql-connector/include -I/home/meihua/dy/src/common_lib/../thrift/include -I/home/meihua/dy/src/common_lib/../common_lib/output/include
LIBPATH=-Xlinker "-(" -ldl -lpthread -lm -lrt /home/meihua/dy/src/common_lib/../glog/lib/libglog.a /home/meihua/dy/src/common_lib/../redis_proxy/output/lib/libredis_proxy.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotoc.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotobuf.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotobuf-lite.a /home/meihua/dy/src/common_lib/../hiredis/lib/libhiredis.a /home/meihua/dy/src/common_lib/../gflags/lib/libgflags.a /home/meihua/dy/src/common_lib/../gflags/lib/libgflags_nothreads.a /home/meihua/dy/src/common_lib/../mysql_proxy/output/lib/libmysql_proxy.a /home/meihua/dy/src/common_lib/../mysql-connector/lib/libmysqlclient.a /home/meihua/dy/src/common_lib/../thrift/lib/libthriftnb.a /home/meihua/dy/src/common_lib/../thrift/lib/libthriftz.a /home/meihua/dy/src/common_lib/../thrift/lib/libthrift.a -Xlinker "-)"


#---------- phony ----------
.PHONY:all
all:prepare \
libcommon_lib.a \


.PHONY:prepare
prepare:
	mkdir -p ./output/lib ./output/include

.PHONY:clean
clean:
	rm -rf /home/meihua/dy/src/common_lib/pinyin.o /home/meihua/dy/src/common_lib/string_helper.o ./output


#---------- link ----------
libcommon_lib.a:/home/meihua/dy/src/common_lib/pinyin.o \
/home/meihua/dy/src/common_lib/string_helper.o \

	ar crs ./output/lib/libcommon_lib.a /home/meihua/dy/src/common_lib/pinyin.o /home/meihua/dy/src/common_lib/string_helper.o
	cp /home/meihua/dy/src/common_lib/pinyin.h /home/meihua/dy/src/common_lib/string_helper.h ./output/include/


#---------- obj ----------
/home/meihua/dy/src/common_lib/pinyin.o: /home/meihua/dy/src/common_lib/pinyin.cpp \
 /home/meihua/dy/src/common_lib/pinyin.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/pinyin.o /home/meihua/dy/src/common_lib/pinyin.cpp
/home/meihua/dy/src/common_lib/string_helper.o: /home/meihua/dy/src/common_lib/string_helper.cpp \
 /home/meihua/dy/src/common_lib/string_helper.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/string_helper.o /home/meihua/dy/src/common_lib/string_helper.cpp


