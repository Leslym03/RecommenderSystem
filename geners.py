from collections import defaultdict
from metrics import *
import os

PATH_DATA = "data/ml-20m/movies.csv"

generos = {1: 'Adventure',
 2: 'Animation',
 3: 'Children',
 4: 'Comedy',
 5: 'Fantasy',
 6: 'Romance',
 7: 'Drama',
 8: 'Action',
 9: 'Crime',
 10: 'Thriller',
 11: 'Horror',
 12: 'Mystery',
 13: 'Sci-Fi',
 14: 'IMAX',
 15: 'Documentary',
 16: 'War',
 17: 'Musical',
 18: 'Western',
 19: 'Film-Noir'}

gen = {'Adventure': 1,
 'Animation': 2,
 'Children': 3,
 'Comedy': 4,
 'Fantasy': 5,
 'Romance': 6,
 'Drama': 7,
 'Action': 8,
 'Crime': 9,
 'Thriller': 10,
 'Horror': 11,
 'Mystery': 12,
 'Sci-Fi': 13,
 'IMAX': 14,
 'Documentary': 15,
 'War': 16,
 'Musical': 17,
 'Western': 18,
 'Film-Noir': 19}

new_data_dict = {}
with open(PATH_DATA, 'r') as f:
    lines = f.readlines()
    for line in lines:
        fields = line.split(',')
        #item = new_data_dict.get(fields[0], dict())
        #item[fields[1]] = Decimal(fields[2])
        #new_data_dict[fields[0]] = fields[0]
        #cad = []
        cad = fields[2].split("|")
        #cad = cad
        #print(cad)
        for c in cad:
            c = c.strip('\n')
            #print(c)
            val = gen.get(c)
            #print(val)
            new_data_dict[fields[0]] = val

print(new_data_dict['1'])

#print(pearson(new_data_dict['1'],new_data_dict['55'] ))
#knn('1', 10, 'cosine', new_data_dict)