#/bin/sh

git update-index --assume-unchanged Project/Objects/*
git update-index --assume-unchanged Project/Listings/*
git update-index --assume-unchanged Project/*
git update-index --assume-unchanged Project/Objects/Template.axf
git update-index --assume-unchanged Project/Objects/timer.o
git update-index --assume-unchanged Project/Template.uvoptx
git update-index --assume-unchanged Project/Template.uvprojx


# git rm -r --cached Project/
# git add Project/
# git restore --staged Project/
