USE zthompson;

LOCK TABLES company_department WRITE;

SET foreign_key_checks = 0;

INSERT INTO company_department VALUES
('Research',5,'333445555','1988-05-22'),
('Administration',4,'987654321','1995-01-01'),
('Headquarters',1,'888665555','1981-06-19');

SET foreign_key_checks = 1;


UNLOCK TABLES;
