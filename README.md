#Monte Carlo Simulation Class

Assembles the common features of the Monte Carlo simulation into a set of classes.
Currently there are two classes that form the top-level interface to user programs:
MonteCarloSimulation and StateMatrix. They are largely similar in structure and may
be combined in the future. But there are two major dissimilarities to work out:

    - The incorporation of a more complicated state structure by the 
    MonteCarloSimulation class in a general way. An example of this
    "more complicated state structure" is what is contained in the
    StateMatrix class: a fixed set of state transitions that are
    nevertheless randomly chosen as function of state. The fixed part
    is the allowed state transitions as a function of the current state.
    
    - The separation of the random number generator from the distributions
    in StateMatrix. They are combined in the Distribution class for the
    MonteCarloSimulation. But for StateMatrix, several distributions are
    using the same random number generator. Note also that the single random
    number engine has to be passed into a State class method to be used
    by the mutiple distributions.

The development is iterative in nature as the subtleties of implementation are
worked out. A number of the existing exercises are used to help verify the 
developing classes. See cpp files ending in _MCS in the following repositories:

    - Digital_Dice
    - duelling_idiots
    - Alive_10_Years
    - MC_methods

For the MonteCarloSimulation class, a template-based approach has been used
since it allows the clean separation of classes by template specialization.
On the other hand, it only makes sense to use integral types for the
x-axis in the StateMatrix class.

Note also that the classes are header file based only (so far).

Note that MonteCarloSimulation_alpha has been added as an attempt at rebuilding
the simulation library using what I have learned so far. It has so far been
limited to one distribution and the second template parameter has been
applied to the y-axis so far (as opposed to the secondary_distribution).
