import random


f = open('rand_10,000.csv', 'w')
for i in range(10000):
    x = random.randint(1, 10000)
    f.writelines(str(x))
    f.writelines("\n")
    
    
f.close()