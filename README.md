# hr
> :straight_ruler: for your terminal

## Versions

| Filename |  Standard    |  Wide characters |      Windows     |        Unix      |
|:---------|:------------:|:----------------:|:----------------:|:----------------:|
| hr89w.c  | ANSI C (C89) |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr99w.c  | C99          |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr98w.cpp| C++98        |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr17w.cpp| C++17        |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr3.py   | Python 3.x   |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr.p6**  | Perl 6       |:heavy_check_mark:|:heavy_check_mark:|:heavy_check_mark:|
| hr.rb    | Ruby 2.x     |:heavy_check_mark:|     Untested     |:heavy_check_mark:|
| hr89.c   | ANSI C (C89) |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr99.c   | C99          |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr98.cpp | C++98        |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr17.cpp | C++17        |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr2.py   | Python 2.7   |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr.php*  | PHP 7        |        :x:       |:heavy_check_mark:|:heavy_check_mark:|
| hr.lua** | Lua 5.3      |        :x:       |:heavy_check_mark:|:heavy_check_mark:| 

\* Can only fetch width from ncurses module \
\** Can only fetch width from COLUMNS environment variable

## Usage

```sh
$ hr
########################################...
```

```sh
$ COLUMS=5 hr
#####
```

```fish
$ env COLUMS=5 hr
#####
```

```sh
$ hr 123 qwerty
1231231231231231231231231231231231231231...
qwertyqwertyqwertyqwertyqwertyqwertyqwer...
```

```sh
$ COLUMNS=7 hr 123 qwerty
1231231
qwertyq
```
```fish
$ env COLUMNS=7 hr 123 qwerty
1231231
qwertyq
```
