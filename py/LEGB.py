global x
x = 0


def foo():
    x = 2

    def bar():
        print x

    def goo():
        x = 3
        print x

    return bar, goo


def func():
    global x
    x = 1


func()
print x  # 1

bar, goo = foo()

bar()  # 2
goo()  # 3
