cc = g++
cpp = -fPIC -Wall -g

inc += -I./
inc += -I/usr/include

libs += -L/usr/local/lib -lprotobuf -lpthread

.PHONY:all
all:write read

write:write.o lm.helloworld.pb.o
	$(cc) $(cpp) $(inc) lm.helloworld.pb.o write.o -o write $(libs)

lm.helloworld.pb.o:lm.helloworld.pb.cc
	$(cc) $(cpp) $(inc) -o $@ -c $<

write.o:write.cpp
	$(cc) $(cpp) $(inc) -o $@ -c $<

read:read.o lm.helloworld.pb.o
	$(cc) $(cpp) $(inc) lm.helloworld.pb.o read.o -o read $(libs)

read.o:read.cpp
	$(cc) $(cpp) $(inc) -o $@ -c $<

#objs=$(patsubst %.cc,%.o, $(wildcard *.cc))
#objs+=$(patsubst %.cpp,%.o, $(wildcard *.cpp))
#%.o:%.cc
#	$(cc) $(cpp) $(inc) -o $@ -c $<
#	@echo "$@"

#%.o:%.cpp
#	$(cc) $(cpp) $(inc) -o $@ -c $<
#	@echo "$@"

#module=./writer

#write:$(module)

#$(module):$(objs)
#	$(cc) $(cpp) $(inc) -o $(module) $^ $(libs)
#	@echo "$@"

clean:
#	@rm -f $(objs) $(module)
	@rm -f $(all) *.o
	@echo "clean done."
