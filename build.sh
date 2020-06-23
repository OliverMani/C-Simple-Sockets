#!/bin/bash
echo "Building client..."
g++ test/client_test.cpp sokkar/*.cpp sokkar/stream/*.cpp -o client.out
echo "Building server..."
g++ test/server_test.cpp sokkar/*.cpp sokkar/stream/*.cpp -o server.out
echo "Done."