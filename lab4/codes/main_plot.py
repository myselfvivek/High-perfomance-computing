import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df1 = pd.read_csv("B2_PC_data.csv")
# df1 = pd.read_csv("data2.csv")
# print(df1.iloc[23:46, 2])

plt.figure(1)

plt.plot(df1.iloc[0:24, 2], df1.iloc[0:24, 4], ".-")
plt.plot(df1.iloc[24:48, 2], df1.iloc[24:48, 4], ".-")
plt.plot(df1.iloc[48:72, 2], df1.iloc[48:72, 4], ".-")
# plt.plot(df1.iloc[72:96, 2], df1.iloc[72:96, 4], ".-")
# plt.plot(df1.iloc[96:120, 2], df1.iloc[96:120, 4], ".-")

plt.xscale("log",base=2)
plt.grid(True)
plt.ylabel("Time")
plt.xlabel("N")
plt.title("Alog Performance on pc(Q2)")
# plt.title("Alog Performance on cluster(Q2)")
plt.legend(["proc = 0", "proc = 2", "proc = 4"], loc ="upper left")
# plt.legend(["proc = 0", "proc = 2", "proc = 4" ,"proc = 8", "proc = 16"], loc ="upper left")
plt.savefig("Q2_pc.png", format="png", dpi=300)