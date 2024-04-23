import sys
from matplotlib import pyplot as plt

file_name = './files/' + sys.argv[1]

fp = open(file_name, 'r')
qty_list = list(map(int, fp.read().split('\n')[:-1]))

x_list = list(range(len(qty_list)))
plt.bar(x_list, qty_list, 2, color='r')
med_value = sorted(qty_list)[len(qty_list) // 2]

plt.axis([x_list[0]-1,x_list[-1]+1, 0, max(qty_list) + 3])
plt.title(f'medium value = {med_value}', fontsize=20)
plt.xlabel('index', color='gray', fontsize=20)
plt.ylabel('quantity',color='gray', fontsize=20)
plt.grid(True)
plt.plot(x_list, [med_value] * len(qty_list))
plt.legend({'Values', 'Medium value'}, loc=2)
# plt.show()

plt.savefig(f'./graphs/{sys.argv[1][:-4]}.png')
