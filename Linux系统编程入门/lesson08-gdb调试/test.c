#include <stdio.h>
#include <stdlib.h>

int test(int a);

int main(int argc, char* argv[]) {
    int a, b;
    printf("argc = %d\n", argc);

    if(argc < 3) {
        a = 10;
        b = 30;
    } else {
        a = atoi(argv[1]);
        b = atoi(argv[2]);
    }
    printf("a = %d, b = %d\n", a, b);
    printf("a + b = %d\n", a + b);

    for(int i = 0; i < a; ++i) {
        printf("i = %d\n", i);
        // 函数调用
        int res = test(i);
        printf("res value: %d\n", res);
    }

    printf("THE END !!!\n");
    return 0;
}

int test(int a) {
    int num = 0;
    for(int i = 0; i < a; ++i) {
        num += i;
    }
    return num;
}

//生成gdb的可执行文件需要 gcc -g(打开调试) -Wall(打开警告) *.c -o *
//
/*启动和退出
		gdb 可执行程序
		quit
◼ 给程序设置参数/获取设置参数
		set args 10 20
		show args
◼ GDB 使用帮助
		help
 ◼ 查看当前文件代码 tmux直接看比较好
		list/l （从默认位置显示）
		list/l 行号 （从指定的行显示）
		list/l 函数名（从指定的函数显示）
◼ 查看非当前文件代码 tmux看比较好
		list/l 文件名:行号
		list/l 文件名:函数名
◼ 设置显示的行数
		show list/listsize
		set list/listsize 行数
*/
/*
设置断点
b/break 行号
b/break 函数名
b/break 文件名:行号
b/break 文件名:函数
◼ 查看断点
i/info b/break
◼ 删除断点
d/del/delete 断点编号
 ◼ 设置断点无效
dis/disable 断点编号
◼ 设置断点生效
ena/enable 断点编号
◼ 设置条件断点（一般用在循环的位置）
b/break 10 if i==5
*/

/*
运行GDB程序
		start（程序停在第一行）
		run（遇到断点才停）
◼ 继续运行，到下一个断点停
		c/continue
◼ 向下执行一行代码（不会进入函数体）
		n/next
◼ 变量操作
		p/print 变量名（打印变量值）
		ptype 变量名（打印变量类型）
◼ 向下单步调试（遇到函数进入函数体）
		s/step
		finish（跳出函数体）
◼ 自动变量操作
		display 变量名（自动打印指定变量的值）
		i/info display
		undisplay 编号
◼ 其它操作
		set var 变量名=变量值 （循环中用的较多）
		until （跳出循环）
*/
