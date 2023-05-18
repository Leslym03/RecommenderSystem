import os
import pandas as pd
import matplotlib as plt

PATH_RATINGS = "data/ml-20m/ratings.csv"
PATH_MOVIE = "data/ml-20m/movies.csv"


ratings = pd.read_csv(PATH_RATINGS, sep=',', encoding='latin-1', engine='python')
movies = pd.read_csv(PATH_MOVIE, sep=',', encoding='latin-1', engine='python')


# List of genres as a Python list 
genres = ['Action','Adventure','Animation','Children','Comedy','Crime','Documentary','Drama','Fantasy','Film-Noir','Horror','Musical','Mystery','Romance','Sci-Fi','Thriller','War','Western']

print(f"Total de usuarios: {ratings['user_id'].nunique()}")
print(f"Total de peliculas: {ratings['movie_id'].nunique()}")