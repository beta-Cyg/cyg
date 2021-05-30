import turtle
t=turtle.Turtle();t.pensize(2)
turtle.colormode(255)
t.speed(0);t.left(90);t.ht()
a=int(input('step:'))
b=int(input('size:'))
c=input('color:')
d=int(input('direction:'))
for i in range(1,b*10+1):
  if(c=='R'):
    t.color(int(202/b/10*i),2,2)
  elif(c=='B'):
    t.color(2,2,int(202/b/10*i))
  elif(c=='P'):
    t.color(int(202/b/10*i),2,int(202/b/10*i))
  elif(c=='Y'):
    t.color(int(202/b/10*i),int(202/b/10*i),2)
  elif(c=='W'):
    t.color(int(202/b/10*i),int(202/b/10*i),int(202/b/10*i))
  else:
    t.color(2,int(202/b/10*i),2)
  t.circle(b*10,steps=a);t.fd(1)
  if(d<0 and i%abs(d)==0):
    t.left(90)
    t.fd(1)
    t.right(90)
  elif(d>0 and i%d==0):
    t.right(90)
    t.fd(1)
    t.left(90)
  else:
    pass
t.begin_fill()
t.circle(b*10,steps=a)
t.end_fill()
print('return 0;')
if(c=='R'):
  t.color(100,2,2)
elif(c=='B'):
  t.color(2,2,100)
elif(c=='P'):
  t.color(100,2,100)
elif(c=='Y'):
  t.color(100,100,2)
elif(c=='W'):
  t.color(100,100,100)
else:
  t.color(2,100,2)
t.circle(b*10,steps=a)
turtle.done()