use zthompson;
BEGIN;
set @@foreign_key_checks = 0;

DROP TABLE IF EXISTS employee;

CREATE TABLE employee (
    fName         varchar(20) 	   NOT NULL,
    mInit 	  varchar(1),
    lName 	  varchar(40) 	   NOT NULL,
    ssn   	  varchar(9)  	   NOT NULL PRIMARY KEY,
    bDate         datetime    	   NOT NULL,
    address       varchar(50) 	   NOT NULL,
    sex           varchar(1)  	   NOT NULL,
    salary        double precision NOT NULL,
    superSSN      varchar(9),
    dNo           integer          NOT NULL
);

ALTER TABLE employee ADD CONSTRAINT employee_superSSN_refs_employee_ssn FOREIGN KEY (superSSN) REFERENCES employee (ssn);

DROP TABLE IF EXISTS department;

CREATE TABLE department (
    dName         varchar(50)      NOT NULL UNIQUE,
    dNumber       integer          NOT NULL PRIMARY KEY,
    mgrSSN        varchar(9)       NOT NULL UNIQUE,
    mgrStartDate  datetime         NOT NULL
);

ALTER TABLE department ADD CONSTRAINT department_mgrSSN_refs_employee_ssn FOREIGN KEY (mgrSSN) REFERENCES employee (ssn);
ALTER TABLE employee ADD CONSTRAINT employee_dNo_refs_department_dNumber FOREIGN KEY (dNo) REFERENCES department (dNumber);

DROP TABLE IF EXISTS deptLocation;

CREATE TABLE deptLocation (
    dNumber      integer,
    dLocation    varchar(50),
    PRIMARY KEY(dNumber, dLocation)
);

DROP TABLE IF EXISTS project;

CREATE TABLE project (
    pName        varchar(25) NOT NULL,
    pNumber      integer     NOT NULL PRIMARY KEY,
    pLocation    varchar(25) NOT NULL,
    dNum         integer     NOT NULL
);

ALTER TABLE project ADD CONSTRAINT project_dNum_refs_department_dNumber FOREIGN KEY (dNum) REFERENCES department (dNumber);

DROP TABLE IF EXISTS workson;

CREATE TABLE workson (
    essn         varchar(9) NOT NULL,
    pNo          integer    NOT NULL,
    hours        double precision NOT NULL,

    PRIMARY KEY(essn, pNo)
);

ALTER TABLE workson ADD CONSTRAINT workson_pNo_refs_project_pNumber FOREIGN KEY (pNo) REFERENCES project (pNumber);
ALTER TABLE workson ADD CONSTRAINT workson_essn_refs_employee_ssn FOREIGN KEY (essn) REFERENCES employee (ssn);

DROP TABLE IF EXISTS dependent;

CREATE TABLE dependent (
    essn          varchar(9)    NOT NULL,
    dependentName varchar(20)   NOT NULL,
    sex           varchar(1)    NOT NULL,
    bDate         datetime      NOT NULL,
    relationship  varchar(20)   NOT NULL,

    PRIMARY KEY(essn, dependentName)
);

ALTER TABLE dependent ADD CONSTRAINT dependent_essn_refs_employee_ssn FOREIGN KEY (essn) REFERENCES employee (ssn);
set @@foreign_key_checks = 1;

COMMIT;
