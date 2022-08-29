SELECT songs.name FROM songs JOIN artists ON artists.id = songs.artist_id
WHERE songs.artist_id = artists.id AND artists.name = "Post Malone";