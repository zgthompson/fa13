from django.conf.urls import patterns, include, url

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
from company import views
admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'cs355_fall2013.views.home', name='home'),
    # url(r'^cs355_fall2013/', include('cs355_fall2013.foo.urls')),

    url(r'^admin/doc/', include('django.contrib.admindocs.urls')),
    url(r'^employees/', views.list_employees),
    url(r'^add_EtoP2/$', views.add_employee_to_project2, name='add_to_project'),

    url(r'^admin/', include(admin.site.urls)),
)
