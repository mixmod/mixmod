FROM ubuntu:14.04

ENV DEBIAN_FRONTEND noninteractive

RUN apt-get update
RUN apt-get install -y wget
RUN apt-get install -y libqt4-xmlpatterns libqt4-xml libqtgui4
RUN apt-get install -y libqwt6
RUN apt-get install -y sudo

RUN cd /opt
RUN wget http://www.mixmod.org/IMG/deb/mixmodGUI_1-2-1_x86_64-applications.deb
RUN dpkg -i ./mixmodGUI_1-2-1_x86_64-applications.deb
RUN apt-get install -y -f

CMD ["/usr/bin/mixmodGUI"]
 
