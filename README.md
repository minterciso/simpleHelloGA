#Intro
This is a very simple Genetic Algorithm. I use this mainly for testing pourposes, and for teaching thee bases of a GA.

What it does, is evolve a random population to find a destination string, if passed. If no string is passed it'll use the default one. It's also possible to plot a graph in a PNG format if you have gnuplot installed.

# Parameters
As of right now, we are using some hardcoded parameters:

* Population size = 500
* Population keep = 20%
* Probability of mutation = 2%
* Amount of generations = 1000

# Pre-requisites:


* Autotools
* Gnu GCC
* gnuplot if you want to automatically plot the fitness evolution

# GA characteristics
I tried to keep it as simple as possible, so we basically use the C Standard lib rand() function to create randomnes and we select the best individuals by sorting from best fitness (closed to 0) to worst, and keeping
the 20% top. And we also **always** do a crossover. We could use some more advanced randomnes and selection, but for this specific project, this is sufficient.

# Extra
On a GA, usually you rank each individual based on how well it performs from the **population**, not like we did. What we did was simply how different the individual is from the target string. This is not a *cheat* per se, since we are not interested in finding a strategy to reach the destination string, but we are actually optimizing the search of the destination string on a gigantic sea of valid strings.

Usually, the GA is used to:

1. Find a strategy to execute on a problema
2. Find a straight solution

It's perfectly acceptable to what we did if we are dealing with the 2nd item, however when we are dealing with the 1st item the way we did here is at the best, not very used. If we make like this on the 1st item we will reach a local optimal strategy that, yes, it'll solve what we want, but only for the examples we want.

# Usage

    Usage: src/simpleHelloGA options
        -h	--help			Display this help message.
        -d	--destination "string"	String to try to evolve into.
        -o	--output filename	Output of fitness trough time.
        -s	--stop			Stop when finding the string.
        -p	--plot filename		Plot a file using gnuplot pipes, and save on filename (only .png).
