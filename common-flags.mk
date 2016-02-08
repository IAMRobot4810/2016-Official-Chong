# Copyright IAMRobot 2015-2016 (c)

# Define some common flags to be included in Makefile.
# These flags may include syntax fixes, warning enhancements, and optimizations.
GRAPHITE := -fgraphite \
            -fgraphite-identity 
HARDWARE := -march=armv7-a \
            -mcpu=cortex-a9 \
            -mtune=cortex-a9 \
            -marm
LOOP     := -fipa-sra \
            -fgcse-sm \
            -fgcse-las \
            -fgcse-after-reload \
            -fmodulo-sched \
            -fira-loop-pressure \
            -fira-hoist-pressure
LSAN     := -fsanitize=leak
LTO      := -flto=2
OPENMP   := -fopenmp \
            -ftree-parallelize-loops=2 \
            -ftree-parallelize-all

# Create two sets of flags, debug and release, for easy incorporation into build.
DEBUG := -Og \
         -g3 \
         -Wall \
         -Werror \
         -DDEBUG \
         -std=gnu11 \
         $(HARDWARE)
         
RELEASE := -O3 \
           -g0 \
           -DNDEBUG \
           -std=gnu11 \
           $(GRAPHITE) \
           $(HARDWARE) \
           $(LOOP)\
           $(LSAN) \
           $(LTO) \
           $(OPENMP)
