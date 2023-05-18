import os
import pandas as pd
import matplotlib as plt

PATH_RATINGS = "data/ml-10m/ml-10M100K/ratings.dat"
PATH_MOVIE = "data/ml-10m/ml-10M100K/movies.dat"

r_cols = ['user_id', 'movie_id', 'rating', 'unix_timestamp']
ratings = pd.read_csv(PATH_RATINGS,names=r_cols, header=None, sep='::', encoding='latin-1', engine='python')

m_cols = ['movie_id', 'title', 'release_date', 'video_release_date', 'imdb_url', "unknown", "action", "adventure", "animation",
                             "childrens", "comedy", "crime", "documentary", "drama", "fantasy", 
                             "film_noir", "horror", "musical", "mystery", "romance", 
                             "sci-fi", "thriller", "war", "western"]
movies = pd.read_csv(PATH_MOVIE,names=m_cols, header=None, sep='::', encoding='latin-1', engine='python')

# create one merged DataFrame
movie_ratings = pd.merge(movies, ratings)

print(ratings[:5])

print(f"Total de usuarios: {ratings['user_id'].nunique()}")
print(f"Total de peliculas: {ratings['movie_id'].nunique()}")

movies_rated = ratings.groupby('user_id').size().sort_values(ascending=False) 
print(f"Películas máximas calificadas por un usuario: {max(movies_rated)}\nPelículas mínimas calificadas por un usuario: {min(movies_rated) }")


genres= ["unknown", "action", "adventure", "animation", "childrens", "comedy", "crime", "documentary", "drama", "fantasy", "film_noir", "horror", "musical", "mystery", "romance", "sci-fi", "thriller", "war", "western"]
label= movies.loc[:, "unknown":].sum().index
label_counts= movies.loc[:, "unknown":].sum().values
# plot a bar chart
plt.figure(figsize=(12, 5))
plt.barh(y= label, width= label_counts)
plt.title("Genre Popularity", fontsize=16)
plt.ylabel("Genres", fontsize=14)
plt.xlabel("Counts", fontsize=14)
plt.show()