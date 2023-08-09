# awesome-code-by-aly
Here you will find all labs, projects, and personal endeavors that I've created over the years.  Enjoy!

# Name-A-Gator
Created by Alyssa Perkins, Nikhil Anantha, and Jonah Diaz

What is Name-A-Gator (NAG)?  NAG is a GUI developed to help people learn how unique their names are.  It can be used to find the most common/unique name of a search, or compare the 'uniquity' of names you might have in mind for your future baby gators!

 [ Uniquity % = # of occurences for searched name / # of occurences of all names under your search parameters ]

NAG uses a U.S. Census data set that contains name statistics from 1910-2021.  It includes the number of people born with the same name each year for that state and gender.  Names can be ranked from Unique, Rare, Uncommon, Common, and Popular.  Along with each search you do, the user also gets to choose a sorting algorithm to order the returned data.  We included merge, quick, comb, and tim sorts.  The GUI will output the sorting time along with your uniquity rankings.

To learn more about NAG, check out this PDF: [Name-A-Gator Documentation.pdf](https://github.com/alyssaperkins/awesome-code-by-aly/files/12303741/Name-A-Gator.Documentation.pdf)

## To run Name-A-Gator:
1. Go to this link and download the folder: https://drive.google.com/file/d/1emOXle0OTjGWKm53OAlUsKa-7W-jtMhy/view?usp=sharing and run Name-A-Gator.exe
2. or download this folder in the repository: awesome-code-by-aly/NAGGui/x64/Release and run Name-A-Gator.exe

## Video Explanation of Name-A-Gator
https://youtu.be/6jpk0YYYDkI 

## To view the code of Name-A-Gator
### Follow this directory: NAGGui/NAGGui
- NameData.txt -> U.S. Census Data Set that we use to rank names
- Window.h / Window.cpp -> GUI Front End
- MapWrapper.h -> Wrapper Class for inner code (C++) to communicate with GUI code (C++/CLI)
- map.h/map.cpp -> Class to manage back end functionality, aka the core of Name-A-Gator

