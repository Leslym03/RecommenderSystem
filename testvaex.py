import vaex
import pandas as pd
import numpy as np

n_rows = 1000000
n_cols = 1000
df = pd.DataFrame(np.random.randint(0, 100, size=(n_rows, n_cols)), columns=['col%d' % i for i in range(n_cols)])
df.head()

#df.info(memory_usage='deep')
