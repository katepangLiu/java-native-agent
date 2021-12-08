FROM centos:centos7
RUN yum update -y
RUN yum group install "Development Tools" -y
RUN yum install wget cmake maven lrzsz -y
RUN yum install java-1.7.0-openjdk java-1.7.0-openjdk-devel -y
RUN yum clean all
