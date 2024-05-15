#!/bin/bash
# start_crow_api.sh

# Check if required environment variables are set
required_vars=("DB_HOST" "DB_PORT" "DB_USER" "DB_PASSWORD" "DB_NAME" "APP_PORT")

missing_vars=()

for var in "${required_vars[@]}"; do
  if [ -z "${!var}" ]; then
    missing_vars+=("$var")
  fi
done

if [ "${#missing_vars[@]}" != "0" ]; then
  echo "Error: The following required environment variables are missing:"
  for var in "${missing_vars[@]}"; do
    echo "  - $var"
  done
  echo "Please set these variables in your environment."
  exit 1
fi

# Start the application
SCRIPT_DIR=$(dirname "$0")
"$SCRIPT_DIR/crow_api"
