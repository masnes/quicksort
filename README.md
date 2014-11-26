### Quicksort

I programmed quicksort as an exercise.

Later, as a bonus, I've added a multithreaded implementation. This wasn't too
hard, as quicksort is easily paralizable.

Notably, neither implementation is currently randomized quicksort. I'll see
about putting that part in when I feel like it. Should be easy for the
singlethreaded version, but rand is not threadsafe, so the multithreaded version
may be more complicated.
