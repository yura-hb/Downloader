## Usage
From the root directory call the program with the `-h` flag to show possible options.

    ./hayeuyur -h

To call the program from the Makefile use `ARGS` argument. For example:

    make run ARGS=-roODx\ \-d\ 1\ -l\ http://testing-ground.scraping.pro

## Description
This is the simplified version of the website mirror:

 - HTTP download
 - The recursive mirror of websites
 - The different ways of stepping through the website (Breadth-first stepping, Deapth-first stepping)
 - The possibility to limit downloading depth
 - Correct downloading of the `chuncked` format
 - Overwriting of the local references of the mirrored files and fix html files pathes.

## Some test sites

 - Mirror - http://testing-ground.scraping.pro
 - Chuncked image - https://www.zdravionline.cz/imgs/articles/858-1_vychod_slunce_main.jpg
