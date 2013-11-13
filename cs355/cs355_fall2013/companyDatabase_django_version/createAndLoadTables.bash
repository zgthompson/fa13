#! /bin/bash

sed -i 's/cs355user/zthompson/' *.sql

for dataFile in   employee.sql project.sql dependent.sql worksOn.sql deptLocation.sql department.sql; do
    echo "Poplulating table $(echo $dataFile | sed 's/\.sql//')."
    mysql --password="$PASS" --user=zthompson < $dataFile
    echo "Poplulating table $(echo $dataFile | sed 's/\.sql//') completed."
done

## The above loop can be replace by these statements.
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < employee.sql
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < project.sql
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < dependent.sql
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < worksOn.sql
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < deptLocation.sql
## mysql --password='yourMySQLpassword' --user=yourMySQLloginName  < department.sql

