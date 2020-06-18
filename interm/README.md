To compile:
```
make -C lib

flex -l minor.l  

byacc -dv minor.y

gcc -g -DYYDEBUG -o minor -Ilib lex.yy.c y.tab.c lib/*.o    
```

or 

``
make
``

To run:

``
./minor
``

