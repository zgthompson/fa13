USE zthompson; 

LOCK TABLES company_deptlocation WRITE;

SET foreign_key_checks = 0;

INSERT INTO company_deptlocation VALUES
(NULL,1,'Houston'),
(NULL,4,'Stafford'),
(NULL,5,'Bellair'),
(NULL,5,'Sugarland'),
(NULL,5,'Houston');

SET foreign_key_checks = 1;

UNLOCK TABLES;



