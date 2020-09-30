# Get the base Ubuntu image from Docker Hub
FROM alpine:latest

RUN apk --no-cache add gcc libc-dev

WORKDIR /myapp

# These commands copy your files into the specified directory in the image
# and set that as the working location
COPY src src

# Make Pipoca!🍿
RUN gcc -std=c11 -Wall -pthread src/*.c -o pipoca

# This command runs your application, comment out this line to compile only
ENTRYPOINT ["./pipoca"]

LABEL Name=pipoca Version=1.0.0
