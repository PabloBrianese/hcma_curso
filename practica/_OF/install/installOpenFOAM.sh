#!/usr/bin/bash

curl -s https://dl.openfoam.com/add-debian-repo.sh | bash

apt install openfoam-default
