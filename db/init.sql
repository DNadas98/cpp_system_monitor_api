CREATE TABLE IF NOT EXISTS system_record
(
  id               SERIAL PRIMARY KEY,
  cpu_usage        DOUBLE PRECISION,
  memory_usage     DOUBLE PRECISION,
  total_memory     INTEGER,
  used_memory      INTEGER,
  disk_usage       DOUBLE PRECISION,
  total_disk_space INTEGER,
  used_disk_space  INTEGER,
  network_in       INTEGER,
  network_out      INTEGER,
  timestamp        TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);