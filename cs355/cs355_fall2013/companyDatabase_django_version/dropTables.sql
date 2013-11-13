use zthompson;
BEGIN;
set @@foreign_key_checks = 0;

DROP TABLE IF EXISTS company_employee;
DROP TABLE IF EXISTS company_department;
DROP TABLE IF EXISTS company_deptlocation;
DROP TABLE IF EXISTS company_project;
DROP TABLE IF EXISTS company_workson;
DROP TABLE IF EXISTS company_dependent;

set @@foreign_key_checks = 1;

COMMIT;
