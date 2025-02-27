# Model Inputs

The model has 4 sources of model input: the model properties file, the underived R parameters file, the derived R
parameters file and the command line. The order in which the parameter sources are read and parsed is:

1. model properties file
2. underived R parameter file
3. command line
4. derived parameter file

Parameter sources can override the parameters loaded from previous sources. So, parameters set in the command line can
override those in the model properties file, such as *stop.at* or *output.directory*, and those in those in the underived 
R parameter file. The expectation is that the model exploration mechanism will pass parameters on the command line overriding
those in model.properties and more importantly in the underived R parameter file in order to explore the effects of those
parameters.

## Model Properties File

The model properties file is passed as the first argument to the model executable. The file itself defines properties 
for such things as when to stop the model, the paths to additional file input (e.g. the underived and derived
R parameters files) and where the model output will be written too.

## R parameter files
The underived and derived R parameter files contain parameters, as R varibles, used by both the C++ and R parts of 
the model. The files are in R format and can be sourced into the R environment. The underived file defines parameters
that do not depend on (are not derived from) other R parameters. The derived file contains the parameters that use the
underived parameters in their definitions. For example,

**underived**
```
n <- 5000
mean_deg <- (0*0.566)+(1*0.412)+(2*0.018)+(3*0.003)
```

Most of the parameters are straight forward or relatively self-explanatory. However, these require some
explanation.

The lag between diagnosis and ART initialization: *art.init.lag.X*

The value of the *art.init.lag.X* parameters has the following format: "probabilty,range_in_days". The probability
is the probability for a person to be assigned that lag. The range_in_days is a range in days where the lag
is drawn from a geometric distribution intialized with 1 / mean of the range. Some examples:

```
art.init.lag.1 <- ".167142,0-7"  
art.init.lag.2 <- ".298142,7-30"
```

The final value in the parameters name (i.e. "1" in *asm.init.lag.1*) is used to distinguish the different
*asm.init.lag* parameters from one another.

Age specific mortality values: *asm.X*

The value of *asm.X* specifies the probabilty of a person within the age range X of dying on any particular
day. The age range is encoded in the parameter name. For example,

```
asm.15_20 <- 0.002333 / (365 * 5)
asm.20_25 <- 0.002711  / (365 * 5)
```
are the probabilities for persons aged 15 up to but not including 20 and 20 up to but not including 25.

**derived**
```
nedges <- n*mean_deg/2 
```

## Command line
Parameters can be passed on the command line as the second argument to the model executable. The format is a comma
delimited string of parameter name value pairs: `name=value,name=value,...`. For example, `stop.at=10,prep.use.rate=.10`.
