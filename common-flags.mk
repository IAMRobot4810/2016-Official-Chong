# Copyright IAMRobot 2015-2016 (c)

# Define some common flags to be included in Makefile.
# These flags may include syntax fixes, warning enhancements, and optimizations.
WORKLOAD := -fipa-sra \
            -fgcse-sm \
            -fgcse-las \
            -fgcse-after-reload \
            -fmodulo-sched \
            -fira-loop-pressure \
            -fira-hoist-pressure

MULTITHREAD := -fopenmp \
               -ftree-parallelize-loops=2 \
               -ftree-parallelize-all

LTO := -flto=2

GRAPHITE := -fgraphite \
            -fgraphite-identity 

MEMLEAK := -fsanitize=leak

HARDWARE := -march=armv7-a \
            -mcpu=cortex-a9 \
            -mtune=cortex-a9 \
            -marm

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
           $(WORKLOAD)\
           $(MULTITHREAD) \
           $(LTO) \
           $(GRAPHITE) \
           $(MEMLEAK) \
           $(HARDWARE)
           
