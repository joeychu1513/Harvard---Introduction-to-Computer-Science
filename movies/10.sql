SELECT DISTINCT(people.name)
FROM movies, ratings, directors, people
WHERE movies.id = ratings.movie_id
AND directors.movie_id = movies.id
AND directors.person_id = people.id
AND ratings.rating >= 9;