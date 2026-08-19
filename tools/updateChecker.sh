#!/bin/bash
REMOTE_VERSION_URL="https://raw.githubusercontent.com/Nuggets10/sonar/refs/heads/main/VERSION"
LOCAL_VERSION_FILE="../VERSION"

echo "Searching for local version file..."
if [ ! -f "$LOCAL_VERSION_FILE" ]; then
    echo "Error: Local version file not found."
    exit 1
else
    echo "Found local version file."
fi

LOCAL_VERSION=$(cat "$LOCAL_VERSION_FILE")
echo ""
echo "Checking for updates..."
echo ""

response_file=$(mktemp)
http_code=$(curl -w "%{http_code}" -o "$response_file" "$REMOTE_VERSION_URL")

if [ "$http_code" != "200" ]; then
    echo "Error: Failed to fetch remote version. HTTP status: $http_code"
    rm -f "$response_file"
    exit 1
fi

REMOTE_VERSION=$(cat "$response_file")
rm -f "$response_file"

if [ "$REMOTE_VERSION" != "" ] && [ "$REMOTE_VERSION" != "$LOCAL_VERSION" ]; then
    echo ""
    echo "A new version is available: $REMOTE_VERSION"
    echo "You are currently using $LOCAL_VERSION"
else
    echo ""
    echo "You are using the latest version: $LOCAL_VERSION"
fi
