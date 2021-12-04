#Monte Carlo Simulation Class

MonteCarloSimulation_beta represents the latest attempt at realizing a Monte Carlo
simulation engine.  The template parameters are: X_AXIS, Y_AXIS, PARAM, and STD_DIST.

    X_AXIS: Represents the actual values produced by the random engine for each Monte
    Carlo trial. Hence, the associated Distribution_beta class also contains a
    corresponding X_AXIS template parameter and the Distribution_beta constructor
    nr_events parameter. The nr_events determine the amount of X_AXIS values chosen
    for each trial.

    Y_AXIS: Represents the desired interpretation of X_AXIS values - these are the
    actual values that will be interpreted and output by the Monte Carlo engine. They
    can represent the X_AXIS values directly or can be based on a different type of
    value, e.g., Y_AXIS are of type int representing counts meeting a criterion that
    depends on X_AXIS of type double.

    PARAM: This is another template parameter passed on to Distribution_beta. It is used
    for certain distributions such as the Poisson where the type PARAM is applied to the
    mean. In this case, the type of X_AXIS is integral, the type of PARAM is floating
    point, hence the need for the PARAM type.

    STD_DIST: This is a template template parameter (it is a template parameter with
    another template embedded). The internal template is the same type as X_AXIS (as
    made clear in Distribution_beta). The actual type of distribution is defined by
    the user application (e.g., std::uniform_real_distribution,
    std::exponential_distribution, etc.).

Assembles the common features of the Monte Carlo simulation into a set of classes.
Currently, there are three classes that form the top-level interface to user programs:
MonteCarloSimulation, StateMatrix and List_Without_Repetition. They are largely similar
in structure and may be combined in the future. But there are two major dissimilarities
to work out:

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

In addition, there is the factor of complexity versus compression, i.e., the gains to
be had by having a single but complicated mechanism versus having several mechanisms
with some repetition of the common elements.

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

Note also, at this point, that the classes are header file based only.

Note that MonteCarloSimulation_alpha has been added as an attempt at rebuilding
the simulation library using what I have learned so far. Currently it has been
limited to one distribution and the second template parameter has been
applied to the y-axis (as opposed to the secondary_distribution).
