#!/usr/bin/bash

cd /opt

url="https://www.paraview.org/paraview-downloads/download.php?submit=Download&version=v5.9&type=binary&os=Linux&downloadFile=ParaView-5.9.1-MPI-Linux-Python3.8-64bit.tar.gz"
filename="ParaView-5.9.1-MPI-Linux-Python3.8-64bit"

curl $url --output ${filename}.tar.gz

tar --extract --file ${filename}.tar.gz

rm "ParaView-5.9.1-MPI-Linux-Python3.8-64bit.tar.gz"

ln --symbolic /opt/$filename ParaView

cd ~/bin

ln --symbolic /opt/ParaView ParaView


