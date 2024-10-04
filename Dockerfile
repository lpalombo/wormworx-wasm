FROM emscripten/emsdk:latest

WORKDIR /app

# Copy all source files and the Makefile
COPY . /app/

# Install make
RUN apt-get update && apt-get install -y make

# Set the default command to run make
CMD ["make"]