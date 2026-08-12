#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// Build region. Set by the makefile: -DREGION=0 (JP) or -DREGION=1 (US).
#define REGION_JP 0
#define REGION_US 1

#ifndef REGION
#define REGION REGION_JP
#endif

#define IS_US (REGION == REGION_US)
#define IS_JP (REGION == REGION_JP)

#endif // GUARD_CONFIG_H
