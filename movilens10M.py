from collections import defaultdict
from metrics import *
import os

PATH_DATA = "data/ml-10m/ml-10M100K/ratings.dat"

new_data_dict = {}
with open(PATH_DATA, 'r') as f:
    lines = f.readlines()
    for line in lines:
        fields = line.split('::')
        item = new_data_dict.get(fields[0], dict())
        item[fields[1]] = Decimal(fields[2])
        new_data_dict[fields[0]] = item


#print(pearson(new_data_dict['1'],new_data_dict['55'] ))
knn('1', 10, 'cosine', new_data_dict)