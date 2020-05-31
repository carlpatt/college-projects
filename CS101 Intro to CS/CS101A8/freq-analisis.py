'''
I found this two liner on stackoverflow and decided to use it instead of wasting
time coming up with a 50 line script myself to do the same thing

I also used a program from the book invent with python that uses patterns to 
suggest possible words from a dictionary file to help the process go a bit
faster. Link to page http://inventwithpython.com/hacking/chapter18.html.
This wasn't terribly helpful as many words had dozens of suggestions and it only
helped me to find out what two of the words were. 
'''

import collections
letters = collections.Counter('text goes here')

print(letters)