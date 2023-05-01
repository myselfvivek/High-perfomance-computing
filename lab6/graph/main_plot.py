import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv("data_cluster.csv")
# df1 = pd.read_csv("data_PC.csv")
# df1 = pd.read_csv("Q2_cluster.csv")
# df1 = pd.read_csv("Q2_PC.csv")
# df1 = pd.read_csv("Q3_cluster.csv")
# df1 = pd.read_csv("Q3_PC.csv")


plt.figure(1)

plt.plot(df1.iloc[0:6, 2], df1.iloc[0:6, 4], ".-")
plt.plot(df1.iloc[6:12, 2], df1.iloc[6:12, 4], ".-")
plt.plot(df1.iloc[12:18, 2], df1.iloc[12:18, 4], ".-")
plt.plot(df1.iloc[18:24, 2], df1.iloc[18:24, 4], ".-")
plt.plot(df1.iloc[24:30, 2], df1.iloc[24:30, 4], ".-")

plt.xscale("log",base=2)
plt.grid(True)
plt.ylabel("Time")
plt.xlabel("N")

# plt.title("Alog Performance on pc")
plt.title("Alog Performance on cluster")

# plt.title("Alog Performance on pc(Q1)")
# plt.title("Alog Performance on cluster(Q1)")
# plt.title("Alog Performance on pc(Q2)")
# plt.title("Alog Performance on cluster(Q2)")
# plt.title("Alog Performance on pc(Q3)")
# plt.title("Alog Performance on cluster(Q3)")


# plt.legend(["proc = 0", "proc = 2", "proc = 4"], loc ="upper left")
plt.legend(["proc = 0", "proc = 2", "proc = 4" ,"proc = 8", "proc = 16"], loc ="upper left")


plt.savefig("Q_cluster.png", format="png", dpi=300)
# plt.savefig("Q_PC.png", format="png", dpi=300)
# plt.savefig("Q1_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q2_PC.png", format="png", dpi=300)
# plt.savefig("Q2_CLUSTER.png", format="png", dpi=300)
# plt.savefig("Q3_PC.png", format="png", dpi=300)
# plt.savefig("Q3_CLUSTER.png", format="png", dpi=300)