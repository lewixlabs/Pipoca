# Pipoca 🍿
Pipoca is a simple (veeeery simple 😄 ) tool to generate string values, to use in my hashcat/aircrack tests.

It's written in pure C, I used this language to brush up my c skills (good times with pos with 8bit architecture...) because nowdays I mostly use C# and Javascript in my projects.

I was inspired by Crunch, but I needed a tool to generate few string values to get a smaller result (or file size).

## Common use
### A file with 10.000.000 records of 24 chars random string => time: ~5s on old macOS High Sierra and 8GB
> ./pipoca -r 10000000 -c 24 -o chaos.txt

## TODO
- [x] add alphanumeric chars
- [ ] generate strings with threads

## Credits
Pipoca is name given by my wife to popcorns; popcorns remember me this kind of chaos (generating random words)
(I think it's a portuguese word, strange, mine is an Italian family 😄 )
