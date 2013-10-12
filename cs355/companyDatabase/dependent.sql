USE zthompson;

LOCK TABLES dependent WRITE;

SET foreign_key_checks = 0;

INSERT INTO dependent VALUES
('333445555','Alice','F','1986-04-05','Daughter'),
('333445555','Theodore','M','1983-10-25','Son'),
('333445555','Joy','F','1958-05-03','Spouse'),
('987654321','Abner','M','1942-01-28','Spouse'),
('123456789','Michael','M','1988-01-04','Son'),
('123456789','Alice','F','1988-12-30','Son'),
('123456789','Elizabeth','F','1967-05-05','Spouse');

SET foreign_key_checks = 1;

UNLOCK TABLES;
