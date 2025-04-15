#################################################################
# Dockerfile for the project 2
# TODO: Refer to the pointer-example excercise for the Dockerfile
#################################################################
# Build stage
FROM gcc:12-bullseye as builder
WORKDIR /app

# Copy source files first
COPY src/ ./src/
COPY tests/ ./tests/
COPY Makefile .

RUN make all

# Main executable stage
FROM debian:bullseye-slim as main 
WORKDIR /app
COPY --from=builder /app/build/final_proj .
ENTRYPOINT ["./final_proj"]

# Test executable stage
FROM debian:bullseye-slim as test
WORKDIR /app
COPY --from=builder /app/build/test_final_proj .
ENTRYPOINT ["./test_final_proj"]
