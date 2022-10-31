#定义变量
# add.c mult.c div.c sub.c main.c
src=$(wildcard ./*.c )  #功能：获取指定目录下指定类型的文件列表
objs=$(patsubst %.c,%.o,$(src))#功能：查找 <pattern> 中的单词(单词以“空格”、“ Tab ”或“回车”“换行”分隔)是否符合
#模式 <pattern>，如果匹配的话，则以 <test> 替换。

target = app

$(target):$(objs)
	$(CC) $^ -o $(target)

%.o:%.c
	$(CC) -c $<  -o $@
.PHONY:clean
#./PHONY 来显示的指名一个目标是伪目标，有两个作用一个是改善性能，另外一个是来避免冲突。  
#如果没有./PHONY且有一个叫clean的文件 make clean将一直是最新 无法删除目标 

clean:
	rm $(objs)
