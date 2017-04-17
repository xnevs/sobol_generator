import sys

import numpy as np
import matplotlib.pyplot as plt

with open(sys.argv[1]) as f:
    a = np.loadtxt(f)
    n,d = a.shape
    plt.scatter(a[np.arange(n//2),0],a[np.arange(n//2),1])
    plt.scatter(a[np.arange(n//2,n),0],a[np.arange(n//2,n),1])
    plt.show()
