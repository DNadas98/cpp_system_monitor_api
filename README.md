<p align="center">
  <a href="https://github.com/DNadas98/crow_api/releases/tag/v0.0.1">
    <img src="https://img.shields.io/github/v/release/DNadas98/crow_api.svg?style=for-the-badge" alt="Releases">
  </a>
  <a href="https://github.com/DNadas98/crow_api/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/DNadas98/crow_api.svg?style=for-the-badge" alt="Contributors">
  </a>
  <a href="https://github.com/DNadas98/crow_api/issues">
    <img src="https://img.shields.io/github/issues/DNadas98/crow_api.svg?style=for-the-badge" alt="Issues">
  </a>
  <a href="https://linkedin.com/in/daniel-nadas">
    <img src="https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555" alt="LinkedIn">
  </a>
</p>

<br xmlns="http://www.w3.org/1999/html"/>
<div align="center">
  <a href="https://github.com/DNadas98/crow_api">
    <img src="https://avatars.githubusercontent.com/u/125133206?v=4" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">C++ System Monitoring API</h3>
  <p align="center">
    Created by <a href="https://github.com/DNadas98">DNadas98 (Dániel Nádas)</a>
    <br />
    <a href="https://github.com/DNadas98/crow_api/issues">Report Bug</a>
    ·
    <a href="https://github.com/DNadas98/crow_api/issues">Request Feature</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#tech-stack">Tech Stack</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#deployment">Deployment</a></li>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#setup--run">Setup and run</a></li>
      </ul>
    </li>
    <li>
      <a href="#usage">Usage</a>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#images">Images</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>

## About The Project

This is a learning project, a simple API built to experiment with the C++ language libpqxx database connector.

## Tech Stack

[![C++](https://img.shields.io/badge/-C++-4183c4?style=for-the-badge)](https://isocpp.org/)
[![CrowCpp](https://img.shields.io/badge/-CrowCpp-CCCCCC?style=for-the-badge)](https://crowcpp.org/master/)
[![LibPQXX](https://img.shields.io/badge/-LibPQXX-CCCCCC?style=for-the-badge)](https://pqxx.org/libpqxx/)  
[![PostgreSQL](https://img.shields.io/badge/-PostgreSQL-4479A1?style=for-the-badge&logo=postgresql&logoColor=black)](https://www.postgresql.org/)  
[![Docker](https://img.shields.io/badge/-Docker-1d63ed?style=for-the-badge&logo=docker&logoColor=black)](https://www.docker.com/)

## Getting Started

### Prerequisites

#### Docker Compose

- [Docker](https://www.docker.com/)

#### Manual setup

- postgresql (e.g. [PostgreSQL](https://www.postgresql.org/)) (or run the docker-compose-dev.yml file)
- Executable from the latest release, or:
- C++ compiler (e.g. [GCC](https://gcc.gnu.org/))
- [CMake](https://cmake.org/)
- [libpq-dev](https://www.postgresql.org/docs/9.3/libpq.html)
- [pkg-config](https://www.freedesktop.org/wiki/Software/pkg-config/)

### Setup & Run

#### Docker Compose

- Copy `env.txt` template and rename to `.env` and `.env.dev`, modify values (see details in the
  template)
- Run `docker compose up -d` in the project root to start the project with Docker Compose
  - Access the application at [`http://localhost:8080`](http://localhost:8080) (by default)
    <br><br>
- Run `docker compose logs -f` in the project root to view the logs

#### Manual setup

- Copy `env.txt` template and rename to `.env` and `.env.dev`, modify values (see details in the
  template)
- Download PostgreSQL (if not using Docker Compose)
  ```bash
  sudo apt-get install -y postgresql
  ```
- Create the database
  ```bash
  sudo -u postgres psql
  CREATE DATABASE <DB_NAME>;
  CREATE USER <DB_USER> WITH PASSWORD '<DB_PASSWORD>';
  GRANT ALL PRIVILEGES ON DATABASE <DB_NAME> TO <DB_USER>;
  ```
- Run `db/init.sql` in the database
  ```bash
  psql -U <DB_USER> -d <DB_NAME> -a -f ./db/init.sql
  ```
- Download and run the executable of the latest release, or:

- Download `gcc`
  ```bash
  sudo apt-get update
  sudo apt-get install -y gcc
  ```
- Download `libpq-dev`
  ```bash
  sudo apt-get install -y libpq-dev
  ```
- Download `pkg-config`
  ```bash
  sudo apt-get install -y pkg-config
  ```
- Build the project with CMake
  ```bash
  mkdir build
  cd build
  cmake ..
  make
  ```
- Run the project
  ```bash
  ./crow_api
  ```

## Usage

## Roadmap

- See the [open issues](https://github.com/DNadas98/crow_api/issues) for a
  full list of proposed features (and known issues).

## Contact

Dániel Nádas

- My GitHub profile: [DNadas98](https://github.com/DNadas98)
- My webpage: [dnadas.net](https://dnadas.net)
- E-mail: [daniel.nadas@dnadas.net](mailto:daniel.nadas@dnadas.net)
- LinkedIn: [Dániel Nádas](https://www.linkedin.com/in/daniel-nadas)

Project
Link: [https://github.com/DNadas98/crow_api](https://github.com/DNadas98/crow_api)
