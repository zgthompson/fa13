USE zthompson; 

LOCK TABLES deptLocation WRITE;

SET foreign_key_checks = 0;

INSERT INTO deptLocation VALUES
(1,'Houston'),
(4,'Stafford'),
(5,'Bellair'),
(5,'Sugarland'),
(5,'Houston');

SET foreign_key_checks = 1;

UNLOCK TABLES;



