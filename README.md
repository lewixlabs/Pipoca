# Pipoca
Pipoca is a simple (veeeery simple 😄) tool to generate string values.
It's written in pure C, I used this language to brush up my c skills (good times with pos with 8bit architecture...) because nowdays I mostly use C# and Javascript in my projects.

I was inspired by Crunch, but I needed a tool to generate some string values to get a smaller result (or file size).

## Common use
### A file with 10.000.000 records of 24 chars random string
'./pipoca 24 10000000 > chaos.txt
