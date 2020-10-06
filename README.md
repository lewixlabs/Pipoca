# Pipoca 🍿
Pipoca is a (veeeery simple 😄 ) tool to generate string values, to use in my hashcat/aircrack tests.

It's written in pure C, I used this language to brush up my c skills (good times with pos with 8bit architecture...) because nowdays I mostly use C# and Javascript in my projects.

I was inspired by Crunch, but I needed a tool to generate few string values to get a smaller result (or file size).

![C/C++ CI](https://github.com/lewixlabs/Pipoca/workflows/C/C++%20CI/badge.svg)
![CodeQL](https://github.com/lewixlabs/Pipoca/workflows/CodeQL/badge.svg)

## Common use
### A file with 100.000.000 records of 24 chars random string => time: ~55s on old macOS High Sierra and 8GB
>./pipoca -r 100000000 -c 24 -o chaos.txt

## With Docker 🐳
>docker run -v /tmp:/tmp --rm lewixlabs/pipoca -r100000000 -c24 -o /tmp/chaos.txt 

## Features
>pipoca [options] -r <number_of_rows> -c <number_of_chars>
>
>Optional params:
>
>-o <file_to_write>: save rows to a file (overwrite mode)
>
>-a <file_to_write>: save rows to a file (append mode)
>
>-n : numbers only (default is alphanumeric)
>
>-l : lowercase chars only

## TODO
- [x] add alphanumeric chars
- [x] generate strings with threads (it's slower, to investigate 🧐)

## Credits
Pipoca is name given by my wife to popcorns; popcorns remember me this kind of chaos (generating random words).

I think it's a portuguese word, strange, mine is an Italian family 😄.
