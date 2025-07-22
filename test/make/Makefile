
# 定义变量
# 目标名：前置依赖文件
# 	命令1
# 	命令2
# 目标名和生成的目标文件要同名 --是以目标名为参照判断目标文件是否存在-不存在就生成
# 依赖文件必须写            --如果依赖文件发生变化，则重新执行命令会成功， 否则提示当前存在的已经是最新了

#objects := main.o hello.o
#objects := main.o \
		hello.o
objects := main.o
objects += hello.o


# 定义伪目标
.PHONY: clean

main: $(objects)
	gcc  $(objects) -o main

hello.o: hello.c
	gcc -c hello.c -o hello.o

main.o: main.c hello.h
	gcc -c main.c -o main.o

clean: 
	rm $(objects) main

clean2:
	-rm main.o
	-rm hello.o
	-rm main
