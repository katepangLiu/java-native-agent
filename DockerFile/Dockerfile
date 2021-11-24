FROM centos:centos7
RUN yum update -y
RUN yum group install "Development Tools" -y
RUN yum install which libXtst-devel libXt-devel libXrender-devel cups-devel freetype-devel alsa-lib-devel wget cmake -y
RUN yum install java-1.7.0-openjdk java-1.7.0-openjdk-devel -y
RUN yum clean all