Steps to build the reporting modul
==================================

1. Modify required properties in ant-config.properties file
2. Chcck for startup.sh file under $TOMCAT_HOME/bin folder. If it's not there modify check-environment.xml
   file with any existing file.


Project target
==============

1. clean - clean compiled classes and deploy files including entire build folder
2. build - build entire module including reports
3. deploy - deploy exploded reports module to specified tomcat version including compiled reports
4  deploy-reports - compile and deploy ONLY reports
5. build-javadoc - generate javadoc APIs
and more...

eg: ANT clean build deploy
will clean, compile (java and jasper reports) and deploy