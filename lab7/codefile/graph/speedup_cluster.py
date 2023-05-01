import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv("data_cluster.csv")
df = df1.to_numpy()


for i in range(0,24):
    if(i != 23 and i != 22):
        continue
    x = i + 24
    p = 4
    cluster_speedup_array = []
    cluster_processor = []
    while(x < 120):
        cluster_speedup_array.append(df[x][6])
        cluster_processor.append(p)
        x = x + 24
        p = p + 4
    print(cluster_processor)
    plt.plot(cluster_processor, cluster_speedup_array)
        

# # for problem size 128(2^7)
# cluster_speedup_array1 = np.array([0.169, 0.00306, 0.00746, 0.00254])
# cluster_processor1 = np.array([4,8,12,16])

# # for problem size 131072(2^17)
# cluster_speedup_array2 = np.array([3.54, 0.541, 1.22, 0.395])
# cluster_processor2 = np.array([4,8,12,16])

# # for problem size 134217728(2^27)
# cluster_speedup_array3 = np.array([3.58, 6.64, 8.42, 9.31])
# cluster_processor3 = np.array([4,8,12,16])


# plt.plot(cluster_processor1, cluster_speedup_array1)

# plt.plot(cluster_processor2, cluster_speedup_array2)

# plt.plot(cluster_processor3, cluster_speedup_array3)

plt.figure(1)


# plt.xscale("log",base=2)
plt.grid(True)
plt.ylabel("Speedup")
plt.xlabel("Number of processor")


# plt.title("Speedup on PC")
plt.title("Speedup on cluster")


plt.legend(["Problem size = 2^26", "Problem size = 2^27"])



plt.savefig("Q_cluster_speedup_processor.png", format="png", dpi=300)
# plt.savefig("Q_PC_speedup_processor.png", format="png", dpi=300)
# plt.savefig("Q1_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q2_PC.png", format="png", dpi=300)
# plt.savefig("Q2_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q3_PC.png", format="png", dpi=300)
# plt.savefig("Q3_CLUSTER.png", format="png", dpi=300)