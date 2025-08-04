#include <pattern/Deeper.h>
#include <pattern/HalfnHalf.h>
#include <pattern/Insist.h>
#include <pattern/RandomDepth.h>
#include <pattern/RoboStroke.h>
#include <pattern/StopNGo.h>
#include <pattern/TeasingPounding.h>

static TeasingPounding teasingPounding("PoundingTeasing");
static RoboStroke roboStroke("RoboStroke");
static HalfnHalf halfnHalf("Half'n'Half");
static Deeper deeper("Deeper");
static StopNGo stopNGo("Stop'n'Go");
static Insist insist("Insist");
static RandomDepth randomDepth("RandomDepth");
// <-- instantiate your new pattern class here!

static Pattern *patternTable[] = {
    &teasingPounding,
    &roboStroke,
    &halfnHalf,
    &deeper,
    &stopNGo,
    &insist,
    &randomDepth
    // <-- insert your new pattern class here!
};