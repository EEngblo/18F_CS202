import random
n = 1000
f = open('mytest.txt','w')
a = list(range(1,n+1))

random.shuffle(a)
f.write(str(n) + '\n')
for i in a:
    f.write(str(i)+'\n')