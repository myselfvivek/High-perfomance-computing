import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv("data_PC.csv")
df = df1.to_numpy()


for i in range(0,24):
    if(i != 23 and i != 22):
        continue
    x = i + 24
    p = 2
    cluster_speedup_array = []
    cluster_processor = []
    while(x < 72):
        cluster_speedup_array.append(df[x][6])
        cluster_processor.append(p)
        x = x + 24
        p = p + 2
    print(cluster_processor)
    plt.plot(cluster_processor, cluster_speedup_array)
    

plt.figure(1)


# plt.xscale("log",base=2)
plt.grid(True)
plt.ylabel("Speedup")
plt.xlabel("Number of processor")


plt.title("Speedup on PC")
# plt.title("Speedup on cluster")


plt.legend(["Problem size = 2^26", "Problem size = 2^27"])



# plt.savefig("Q_cluster_speedup_processor.png", format="png", dpi=300)
plt.savefig("Q_PC_speedup_processor.png", format="png", dpi=300)
# plt.savefig("Q1_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q2_PC.png", format="png", dpi=300)
# plt.savefig("Q2_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q3_PC.png", format="png", dpi=300)
# plt.savefig("Q3_CLUSTER.png", format="png", dpi=300)