from django import forms

class AddEmployeeToProject(forms.Form):
    employee_name = forms.CharField()
    project = forms.CharField()
    hours = forms.IntegerField()
    age = forms.IntegerField(required=False)
