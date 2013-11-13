from django.db import models

class Employee( models.Model ):
    #class Meta:
    #    db_table = 'employee'

    fName = models.CharField(max_length=20)
    mInit = models.CharField(max_length=1)
    lName = models.CharField(max_length=40)
    ssn = models.CharField(max_length=9, primary_key=True)
    bDate = models.DateTimeField('birth date')
    address = models.CharField(max_length=50)
    sex = models.CharField(max_length=1)
    salary = models.FloatField()
    superSSN = models.ForeignKey('Employee', blank=True, null=True)
    dNo = models.ForeignKey('Department', blank=True, null=True)

    def supervisor(self):
        return self.superSSN

    def __unicode__(self):
        return self.lName + ", " + self.fName

    def employee_name(self):
        return self.lName + ", " + self.fName

    def total_hours(self):
        total = 0
        for w in Workson.employee_set.filter(essn_id=self.ssn):
            total += w.hours
        return total

class Department( models.Model ):
    # class Meta:
    #    db_table = 'department'

    dName = models.CharField(max_length=50, unique=True)
    dNumber = models.IntegerField(primary_key=True)
    mgrSSN = models.OneToOneField('Employee')
    mgrStartDate = models.DateTimeField()

    def __unicode__(self):
        return self.dName

    def num_employees(self):
        return Employee.objects.filter(dNo=self.dNumber).count()

class Workson( models.Model ):
    #class Meta:
    #    db_table = 'workson'

    employee = models.ForeignKey("Employee")
    project = models.ForeignKey("Project")
    hours = models.FloatField()

    def __unicode__(self):
        return "Employee: " + str(self.employee) + ", Project: " +  \
                str(self.project) + ", hours: " + str(self.hours)

class Project( models.Model ):
    """ Employee projects """
    #class Meta:
    #    db_table = 'project'

    pName = models.CharField(max_length=25)
    pNumber = models.IntegerField(primary_key=True)
    pLocation = models.CharField(max_length=25)
    department = models.ForeignKey('Department')
    employees = models.ManyToManyField(Employee, through='Workson')

    def __unicode__(self):
        return self.pName

class Dependent( models.Model ):
    """ children of employee """
    #class Meta:
    #    db_table = 'dependent'

    employee = models.ForeignKey( 'Employee', blank=True, null=True )
    dependentName = models.CharField(max_length=20)
    sex = models.CharField(max_length=1)
    bDate = models.DateTimeField('Birth Date')
    relationship = models.CharField(max_length=25)

    def __unicode__(self):
        return self.dependentName + ", " + self.relationship.lower() + " of " + str( self.employee )

class DeptLocation( models.Model ):
    """ Location of departments """
    #class Meta:
    #    db_table = 'deptlocation'

    dNumber = models.ForeignKey('Department')
    dLocation = models.CharField(max_length=50)

    def __unicode__(self):
        return str(self.dNumber)
