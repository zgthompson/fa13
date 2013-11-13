USE zthompson;

LOCK TABLES company_dependent WRITE;

SET foreign_key_checks = 0;

INSERT INTO company_dependent VALUES
(NULL,'333445555','Alice','F','1986-04-05','Daughter'),
(NULL,'333445555','Theodore','M','1983-10-25','Son'),
(NULL,'333445555','Joy','F','1958-05-03','Spouse'),
(NULL,'987654321','Abner','M','1942-01-28','Spouse'),
(NULL,'123456789','Michael','M','1988-01-04','Son'),
(NULL,'123456789','Alice','F','1988-12-30','Son'),
(NULL,'123456789','Elizabeth','F','1967-05-05','Spouse');

SET foreign_key_checks = 1;

UNLOCK TABLES;
