import numpy as np
import matplotlib.pyplot as plt
import pandas

df2 = pandas.read_csv("A2data_cluster.csv",sep='\t',header=None, names=["name","tmp","size", "runs", "throughput"])

#plt.plot(df["size"].values, df["throughput"].values, "r", label="O1")
plt.plot(df2["size"].values, df2["throughput"].values, "k.-", label="O2")
plt.xscale("log",base=2)
plt.grid(True)
plt.ylabel("Time taken")
plt.xlabel(r"$N$")
#plt.plot()
plt.show()
#plt.savefig("vtriad.png", format="png", dpi=300)
print("success")