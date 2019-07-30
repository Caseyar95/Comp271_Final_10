# Find The Suspects

  My project was to figure out which cars a thief could possibly have used to steal bikes based on the date and times of the thefts and the date and times the cars were parked.  To start, I read the information of the parked cars into a vector and did the same to the theft information using structs.  Then I compared the dates and time frame of when all the cars were parked with the all the thefts and if they matched with at least one theft then I outputted that car’s information.
  I used vectors to hold the information of the thefts and the car parking, as opposed to arrays, because I wasn’t sure how big I was going to need them and the vector functions came in handy.  I also created a structure for each set of information since each car and theft had multiple parts to it but was really just one thing.  It made the reading in, sorting, and comparing easier as well.
  All you do to use the code is click run and it will ask for the file for the parking information and then the file for the theft information.  If the files aren’t found, it will let you know and ask again.  Then it will output cars that were possibly used in a theft.
Created in Visual Studio 2015 on Windows.

