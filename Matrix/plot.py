import csv  # 导入csv模块

import numpy as np
import matplotlib.pyplot as plt
import statistics
import numpy as np
import matplotlib.pyplot as plt


filename = 'data.csv'
with open(filename) as f:
    reader = csv.reader(f)
    header_row = next(reader)

    # 从文件中获取数据
    size, mmult, mmultO3, mmult_simd, mmult_simdO3 = [], [], [], [], []
    for column in reader:
        size.append(int(column[0]))
        mmult.append(float(column[1]))
        mmultO3.append(float(column[2]))
        mmult_simd.append(float(column[3]))
        mmult_simdO3.append(float(column[4]))

# 绘制图形
# plt.style.use('seaborn')
fig, ax = plt.subplots()
ax.plot(size, mmult, c='red', label='mmult')
ax.plot(size, mmultO3, c='blue', label='mmultO3')
ax.plot(size, mmult_simd, c='green', label='mmult_simd')
ax.plot(size, mmult_simdO3, c='yellow', label='mmult_simdO3')

# 设置图形的格式
ax.set_title("各算法对比", fontproperties="SimHei", fontsize=24)
ax.set_xlabel('Size', fontproperties="SimHei", fontsize=16)
ax.set_ylabel("Time (ms)", fontproperties="SimHei", fontsize=16)
ax.tick_params(axis='both', which='major', labelsize=16)
ax.legend()
print(statistics.mean(mmult))
print(statistics.mean(mmultO3))
print(statistics.mean(mmult_simd))
print(statistics.mean(mmult_simdO3))
plt.savefig("comparison_graph.png")

plt.show()





