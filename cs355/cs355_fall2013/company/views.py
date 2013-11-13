from django.shortcuts import render_to_response
from django.template import RequestContext
from django.core.context_processors import csrf
from django.http import HttpResponse


import datetime
from company.models import Employee, Project, Workson
from company.forms import AddEmployeeToProject

def list_employees(request):
    employees = Employee.objects.all().order_by('lName')
    num_emps = len( employees )
    context = {'num_employees': num_emps,
               'employees': employees}
    return render_to_response('employee.html', context )

def add_employee_to_project(request):
    employees = Employee.objects.all()
    projects = Project.objects.all()
    workson = Workson.objects.all()
    
    context = {'num_emps': len(employees),
               'employees': employees,
               'projects': projects,
               'workson': workson,
               'num_projs': len(projects),
               'num_workson': len(workson),
               }
    return render_to_response('add_EtoP2.html', context )

def process_add_employee_to_project(request):
    emp_error = False
    if 'employee_name' in request.GET and request.GET['employee_name']:
        message = 'Employee name is ' + request.GET['employee_name']
        return render_to_response('add_EtoP_ack.html', {'newRecord': request.GET})
    else:
        message = "Didn't enter employee name"
        emp_error = True

    employees = Employee.objects.all()
    projects = Project.objects.all()
    workson = Workson.objects.all()
    
    context = {'num_emps': len(employees),
               'employees': employees,
               'projects': projects,
               'workson': workson,
               'num_projs': len(projects),
               'num_workson': len(workson),
               'emp_error': True, 
               'fd': request.GET
               }

    return render_to_response('add_EtoP.html',  context)

def add_employee_to_project2(request):

    if request.method == 'POST':
        form = AddEmployeeToProject( request.POST )
        if form.is_valid():
            cd = form.cleaned_data
            emp = Employee.objects.filter(lName = cd['employee_name'])[0]
            proj = Project.objects.filter(pName = cd['project'])[0]
            workson = Workson(employee=emp, project=proj, hours=cd['hours'])
            workson.save()
            return HttpResponse( "<html><body> {} works on {} for {} hours.</body></html>".format(cd['employee_name'], cd['project'], cd['hours']) )
    else:
        form = AddEmployeeToProject()

    employees = Employee.objects.all()
    projects = Project.objects.all()
    workson = Workson.objects.all()

    context = {'num_emps': len(employees),
               'employees': employees,
               'projects': projects,
               'workson': workson,
               'num_projs': len(projects),
               'num_workson': len(workson),
               'form': form
               }
    return render_to_response('add_EtoP2.html', context, context_instance=RequestContext(request) )
