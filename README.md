# climbing-companion-app
## General summary
An app for tracking workout progress.

## Explanation of features
The best exercises for working out are those that you can progressively overload, which could mean adding weight, more time, etc. It is valuable to track your progress and create benchmarks, as I have found in my experience and talking to other well-established climbers and trainers. Famed free soloist Alex Honnold talks about using a journal to track his strength gains in the movie "Free Solo." It is effective for many reasons, including informing you on the effectiveness of your training plan or rehabbing an injury.
This tool aims to make it more convenient and streamlined to keep track of progress. It will display your current weight/unit in front of your exercise (for example, weighted pull-ups: 80 lbs), but will also store all the times you have changed the value in the past and generate a graph of your progress (In this example, weight on the y-axis, date on the x-axis). You can also edit these values if one is incorrect or perhaps you are porting data from a journal.
Documents or spreadsheets can work for this purpose, but one cannot make graphs, and the other is not very readable, especially when you are at the gym (besides, who has a spreadsheet open at a rock gym?).

## Implementation
The C++ classes designed to store information were vital to the implementation. For example, data lines must be in a hashmap with a unique ID and the data (two strings and an int). Also, I needed to store another hashmap that correlates these values and a date. The nested data gets messy quickly with default data types and cannot be saved in a .dat file. So you can see the need for custom classes to organize this data, designed with encapsulation in mind. This design choice is to make it easy to retrieve and edit the data using getter and setter functions.

## Future expansions
I want to port this application to phones. It would be more convenient as most people (including me) use their phones to check and update their workouts.
Improving the overall look of the app would be a nice quality-of-life feature. Currently, it looks very blank, with just different shades of gray filling the window. I have drawn pixel art icons for the menus, but it needs an entire overhaul.
