USE zthompson;

LOCK TABLES project WRITE;

SET foreign_key_checks = 0;

INSERT INTO project VALUES
('ProductX',1,'Bellair',5),
('ProductY',2,'Sugarland',5),
('ProductZ',3,'Houston',5),
('Computerization',10,'Stafford',4),
('Reorganization',20,'Houston',1),
('Newbenefits',30,'Stafford',4);

SET foreign_key_checks = 1;

UNLOCK TABLES;
