#Monte Carlo Simulation Class

Assembles the common features of the Monte Carlo simulation into a set of classes.
Currently there are two classes that form the top-level interface to user programs:
MonteCarloSimulation and StateMatrix. They are largely similar in structure and may
be combined in the future. But there are two major dissimilarities to work out:

    - The incorporation of more complicated state structure by the 
    MonteCarloSimulation class in a general way. This may be accomplished
    through the condition_met function but remains to be investigated.
    
    - The separation of the random number generator from the distributions
    in StateMatrix. They are combined in the Distribution class for the
    MonteCarloSimulation. Thus for StateMatrix, several distributions are
    using the same random number generator.

The development is iterative in nature as the subtleties of implementation are
worked out. A number of the existing exercises (See Git repositories
Digital_Dice, Duelling_Idiots, etc.) are used to help verify the developing
classes (see Digital_Dice files ending in _MCS for examples).

For the MonteCarloSimulation class, a template-based approach has been used
since it allows the clean separation of classes by template specialization.
On the other hand, it only makes sense to use integral types for the
x-axis in the StateMatrix.

Note also that the classes are header file based only (so far).
