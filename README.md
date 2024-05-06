# So_Long

Summary:
This project is a small 2D game.
Its purpose is to make you work with textures, sprites,
and some other very basic gameplay elements.

Here the subject =>
[en.subject-13.pdf](https://github.com/pfalli/So_Long/files/14945660/en.subject-13.pdf)

Leaks:
Do mind that "mlx_png_file_to_image" currently leaks memory => use mlx_destroy_image to free the images;

As well "mlx_init" => use mlx_destroy_display after the loop game;

Tools:
https://reactive.so/post/42-a-comprehensive-guide-to-so_long

I really reccomend to follow this guide on Minilibx: 
https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html
