# libpqxx-bazel

Example showing how to build the libpqxx C++ binding for PostgreSQL with Bazel using rules_foreign_cc.

See libpqxx: https://github.com/jtv/libpqxx

First, ensure you have the dependencies needed for `libpqxx`: Postgres installed and specifically `libpq`.

I satisfied these dependencies by installing Postgres and `libpq` specifically via `sudo apt-get install -y libpq-dev`.

A sample program is provided to demo the connection; it simply executes a `SELECT` query.

# Build:

`bazel build //:main`

# Run:

The sample program uses environment variables to pass in the Postgres DB configuration used for connection. Ensure you
pass the following environment variables before calling `bazel run`.

Example:

```bash
export DB_HOST=<host>
export DB_NAME=<name of the db>
export DB_PORT=<port of db>
export DB_USERNAME=<username of db>
export DB_PASSWORD=<password of db>
```

`bazel run //:main`