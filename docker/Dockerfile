# Use an official Ubuntu base image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /app

# Copy the ircserv file from the host machine's ../ircserv directory to the container
#  Don't forget to move the binary
COPY ./ircserv /app/ircserv

# Make sure the copied file is executable
RUN chmod +x /app/ircserv

# Install valgrind
RUN apt-get update && \
    apt-get install -y valgrind && \
    apt-get clean
EXPOSE 6667
# Run the ircserv program with valgrind and the specified arguments
CMD ["valgrind", "/app/ircserv", "6667", "42password"]
