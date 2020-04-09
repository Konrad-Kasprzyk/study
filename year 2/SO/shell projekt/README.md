Dodałem w pliku command.c do procedur do_bg i do_kill wywołanie watchjobs(FINISHED);
Uzasadniam to tym, że tak samo działa shell od prowadzącego.

Przeniosłem implementację funkcji is_pipeline w pliku shell.c nad funkcję do_pipeline.
Zrobiłem tak dlatego, bo korzystam z funkcji is_pipeline wewnątrz do_pipeline.

