import math
from math import sqrt
from decimal import Decimal, getcontext
import operator

def manhattan(rating1, rating2):
    distance = 0
    difnan = False
    for key in rating1:
        if key in rating2:
            distance += abs(rating1[key] - rating2[key])
            difnan = True
    if (difnan == True):
        return float(distance) 
    else:
        return "Nan"

def euclidiana(rating1, rating2):
    distance = 0
    difnan = False
    for key in rating1:
        if key in rating2:
            distance += math.pow(rating1[key] - rating2[key],2)
            difnan = True
    if (difnan == True):
        return float(math.sqrt(distance))
    else:
        return "Nan"

def pearson(rating1, rating2):
    sum_xy = 0
    sum_x = 0
    sum_y = 0
    sum_x2 = 0
    sum_y2 = 0
    n = 0
    for key in rating1:
        if key in rating2:
            n += 1
            x = rating1[key]
            y = rating2[key]
            sum_xy += x * y
            sum_x += x
            sum_y += y
            sum_x2 += pow(x, 2)
            sum_y2 += pow(y, 2)
    
    if n== 0:
        return "Nan"

    denominator = sqrt(sum_x2 - pow(sum_x, 2) / n) * sqrt(sum_y2 - pow(sum_y, 2) / n)
    producto = sum_xy - (sum_x * sum_y) / n
    
    if denominator == 0:
        return "Nan"
    getcontext().prec = 5
    res = Decimal(producto) / Decimal(denominator)
    if res >= 1.0 or producto == denominator:
        return 1.0
    else:
        return res

def cosine(rating1, rating2):
    ppunto = 0
    logx = 0
    logy = 0
    for key in rating1:
        if key in rating2:
            ppunto += (rating1[key] * rating2[key])
            logx += pow(rating1[key], 2)
            logy += pow(rating2[key], 2)
    
    denominator = sqrt(logx) * sqrt(logy)
    

    if denominator == 0:
        return "Nan"
    getcontext().prec = 5
    res= Decimal(ppunto) / Decimal(denominator)    
    if res >= 1.0 or ppunto == denominator:
        return 1.0
    else:
        return res


def knn(user, k, metric, data):

    dict_new = {}

    if metric == 'euclidiana':
        for i in data.keys():
          if i != user:
            res = euclidiana(data[user],data[i])
            if res != "Nan":
              dict_new [i] = res
        
        sortedDict = sorted(dict_new.items(), key=lambda x: x[1])

        for x in list(sortedDict)[0:k]:
          print (x)

    if metric == 'manhattan':
        for i in data.keys():
          if i != user:
            res = manhattan(data[user],data[i])
            if res != "Nan":
              dict_new [i] = res

        sortedDict = sorted(dict_new.items(), key=lambda x: x[1])

        for x in list(sortedDict)[0:k]:
          print (x)

    if metric == 'cosine':
        for i in data.keys():
          if i != user:
            res = cosine(data[user],data[i])
            if res != "Nan":
              dict_new [i] = res

        sortedDict = sorted(dict_new.items(), key=lambda x: x[1], reverse=True)

        for x in list(sortedDict)[0:k]:
          print (x)

    if metric == 'pearson':
        for i in data.keys():
          if i != user:
            res = pearson(data[user],data[i])
            if res != "Nan":
              dict_new [i] = res

        sortedDict = sorted(dict_new.items(), key=lambda x: x[1], reverse=True)

        for x in list(sortedDict)[0:k]:
          print (x)