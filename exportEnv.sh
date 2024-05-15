#!/bin/bash
# exportEnv.sh

# Check if .env file exists
if [ ! -f ./.env ]; then
  echo "Error: .env file not found in the current directory."
  exit 1
fi

# Export all variables from the .env file
export $(grep -v '^#' ./.env | xargs)

# Optional: Print a message indicating the variables have been exported
echo "Environment variables exported from .env file."
