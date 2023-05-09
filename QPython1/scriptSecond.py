import turtle #导入turtle库
def temperImg():
    turtle.pensize(4)#设置画笔像素为4像素
    turtle.pencolor("red")#设置画笔颜色为红色
    turtle.fillcolor("pink")#设置填充颜色为粉红色
    turtle.begin_fill()#开始填充
    #开始绘制爱心
    turtle.left(135)
    turtle.forward(100)
    turtle.circle(-50,180)#第一个半圆
    turtle.left(90)
    turtle.circle(-50,180)#第二个半圆
    turtle.forward(100)
    turtle.end_fill()#结束填充
    turtle.done()

temperImg()