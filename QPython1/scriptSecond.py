import turtle #����turtle��
def temperImg():
    turtle.pensize(4)#���û�������Ϊ4����
    turtle.pencolor("red")#���û�����ɫΪ��ɫ
    turtle.fillcolor("pink")#���������ɫΪ�ۺ�ɫ
    turtle.begin_fill()#��ʼ���
    #��ʼ���ư���
    turtle.left(135)
    turtle.forward(100)
    turtle.circle(-50,180)#��һ����Բ
    turtle.left(90)
    turtle.circle(-50,180)#�ڶ�����Բ
    turtle.forward(100)
    turtle.end_fill()#�������
    turtle.done()

temperImg()