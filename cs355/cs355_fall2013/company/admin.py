from company.models import Employee, Department
from django.contrib import admin

class EmployeeAdmin(admin.ModelAdmin):
    list_display = [ 'employee_name', 'ssn', 'bDate', 'sex', 'dNo', 'supervisor' ]
    list_filter = ['sex', 'dNo']
    fieldsets = [
        (None, {'fields': ['fName', 'mInit', 'lName', 'ssn', 'sex', 'salary', 'bDate']}),
        ('Department', {'fields': ['dNo']}),
        ('Supervisor', {'fields': ['superSSN']}),
    ]
    search_fields = ['fName', 'lName']
    ordering = ['lName']

class DepartmentAdmin(admin.ModelAdmin):
    list_display = ['dName', 'mgrSSN', 'dNumber', 'mgrStartDate', 'num_employees']

admin.site.register( Employee, EmployeeAdmin )
admin.site.register( Department, DepartmentAdmin )
