#---------- env ----------
CXX=g++
CXXFLAGS=-D_GNU_SOURCE -D__STDC_LIMIT_MACROS -g -pipe -W -Wall -fPIC -fno-omit-frame-pointer
INCPATH=-I. -I/home/meihua/dy/src/common_lib/../glog/include -I/home/meihua/dy/src/common_lib/../se/include -I/home/meihua/dy/src/common_lib/../redis_proxy/output/include -I/home/meihua/dy/src/common_lib/../protobuf/include -I/home/meihua/dy/src/common_lib/../hiredis/include -I/home/meihua/dy/src/common_lib/../gflags/include -I/home/meihua/dy/src/common_lib/../seg_origin/output/include -I/home/meihua/dy/src/common_lib/../seg_origin/dep/include -I/home/meihua/dy/src/common_lib/../mysql_proxy/output/include -I/home/meihua/dy/src/common_lib/../mysql-connector/include -I/home/meihua/dy/src/common_lib/../thrift/include -I/home/meihua/dy/src/common_lib/../common_lib/output/include
LIBPATH=-Xlinker "-(" -ldl -lpthread -lm -lrt /home/meihua/dy/src/common_lib/../seg/lib/libseg_ext.a /home/meihua/dy/src/common_lib/../seg/lib/libsegment.a /home/meihua/dy/src/common_lib/../glog/lib/libglog.a /home/meihua/dy/src/common_lib/../redis_proxy/output/lib/libredis_proxy.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotoc.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotobuf.a /home/meihua/dy/src/common_lib/../protobuf/lib/libprotobuf-lite.a /home/meihua/dy/src/common_lib/../hiredis/lib/libhiredis.a /home/meihua/dy/src/common_lib/../gflags/lib/libgflags.a /home/meihua/dy/src/common_lib/../gflags/lib/libgflags_nothreads.a /home/meihua/dy/src/common_lib/../mysql_proxy/output/lib/libmysql_proxy.a /home/meihua/dy/src/common_lib/../mysql-connector/lib/libmysqlclient.a /home/meihua/dy/src/common_lib/../thrift/lib/libthriftnb.a /home/meihua/dy/src/common_lib/../thrift/lib/libthriftz.a /home/meihua/dy/src/common_lib/../thrift/lib/libthrift.a -Xlinker "-)"


#---------- phony ----------
.PHONY:all
all:prepare \
test_file_group \
libcommon_lib.a \


.PHONY:prepare
prepare:
	mkdir -p ./output/bin
	mkdir -p ./output/lib ./output/include

.PHONY:clean
clean:
	rm -rf /home/meihua/dy/src/common_lib/file_group/file_group_writer.o /home/meihua/dy/src/common_lib/string_helper.o /home/meihua/dy/src/common_lib/file_group/file_group_reader.o /home/meihua/dy/src/common_lib/test/test_file_group.o /home/meihua/dy/src/common_lib/test.o /home/meihua/dy/src/common_lib/pinyin.o ./output


#---------- link ----------
test_file_group:/home/meihua/dy/src/common_lib/test/test_file_group.o \
/home/meihua/dy/src/common_lib/file_group/file_group_writer.o \
/home/meihua/dy/src/common_lib/file_group/file_group_reader.o \

	$(CXX) /home/meihua/dy/src/common_lib/test/test_file_group.o /home/meihua/dy/src/common_lib/file_group/file_group_writer.o /home/meihua/dy/src/common_lib/file_group/file_group_reader.o $(LIBPATH) -o ./output/bin/test_file_group

libcommon_lib.a:/home/meihua/dy/src/common_lib/pinyin.o \
/home/meihua/dy/src/common_lib/string_helper.o \
/home/meihua/dy/src/common_lib/file_group/file_group_writer.o \
/home/meihua/dy/src/common_lib/file_group/file_group_reader.o \
/home/meihua/dy/src/common_lib/test.o \

	ar crs ./output/lib/libcommon_lib.a /home/meihua/dy/src/common_lib/pinyin.o /home/meihua/dy/src/common_lib/string_helper.o /home/meihua/dy/src/common_lib/file_group/file_group_writer.o /home/meihua/dy/src/common_lib/file_group/file_group_reader.o /home/meihua/dy/src/common_lib/test.o
	cp /home/meihua/dy/src/common_lib/pinyin.h /home/meihua/dy/src/common_lib/sign.h /home/meihua/dy/src/common_lib/file_group/file_group_writer.h /home/meihua/dy/src/common_lib/file_group/file_group_reader.h /home/meihua/dy/src/common_lib/string_helper.h ./output/include/


#---------- obj ----------
/home/meihua/dy/src/common_lib/file_group/file_group_writer.o: \
 /home/meihua/dy/src/common_lib/file_group/file_group_writer.cpp \
 /home/meihua/dy/src/common_lib/file_group/file_group_writer.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/file_group/file_group_writer.o /home/meihua/dy/src/common_lib/file_group/file_group_writer.cpp
/home/meihua/dy/src/common_lib/string_helper.o: /home/meihua/dy/src/common_lib/string_helper.cpp \
 /home/meihua/dy/src/common_lib/string_helper.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/string_helper.o /home/meihua/dy/src/common_lib/string_helper.cpp
/home/meihua/dy/src/common_lib/file_group/file_group_reader.o: \
 /home/meihua/dy/src/common_lib/file_group/file_group_reader.cpp \
 /home/meihua/dy/src/common_lib/file_group/file_group_reader.h \
 string_helper.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/file_group/file_group_reader.o /home/meihua/dy/src/common_lib/file_group/file_group_reader.cpp
/home/meihua/dy/src/common_lib/test/test_file_group.o: \
 /home/meihua/dy/src/common_lib/test/test_file_group.cpp \
 file_group/file_group_writer.h file_group/file_group_reader.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/test/test_file_group.o /home/meihua/dy/src/common_lib/test/test_file_group.cpp
/home/meihua/dy/src/common_lib/test.o: /home/meihua/dy/src/common_lib/test.cpp \
 /home/meihua/dy/src/common_lib/sign.h \
 /home/meihua/dy/src/common_lib/hash/city_hash.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/test.o /home/meihua/dy/src/common_lib/test.cpp
/home/meihua/dy/src/common_lib/pinyin.o: /home/meihua/dy/src/common_lib/pinyin.cpp \
 /home/meihua/dy/src/common_lib/pinyin.h
	$(CXX) $(INCPATH) $(CXXFLAGS) -c -o /home/meihua/dy/src/common_lib/pinyin.o /home/meihua/dy/src/common_lib/pinyin.cpp


