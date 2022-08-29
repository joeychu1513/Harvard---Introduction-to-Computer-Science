SELECT DISTINCT(people.name)
FROM people, movies, stars
WHERE movies.id = stars.movie_id
AND stars.person_id = people.id
AND movies.year = 2004
ORDER BY people.birth;